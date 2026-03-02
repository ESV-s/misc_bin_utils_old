#include "api_monitor.h"

#include <algorithm>
#include <utility>

#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QDateTime>
#include <QtCore/QTextStream>
#include <QtCore/QDataStream>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QByteArray>
#include <QtCore/QCryptographicHash>
#include <QtCore/QBuffer>

namespace apimon
{
    static QT::QString ToLowerTrim(const QT::QString& s)
    {
        return s.trimmed().toLower();
    }

    QT::QString NormalizeModuleNameLower(const QT::QString& moduleName)
    {
        QT::QString m = moduleName.trimmed();
        if (m.isEmpty())
            return QT::QString();

        m = m.toLower();

        // Если расширения нет, допишем .dll (для единообразия ключей).
        if (!m.endsWith(QLatin1String(".dll")) && !m.endsWith(QLatin1String(".exe")))
        {
            // Мягко: только если явно нет точки в конце имени.
            if (!m.contains(QLatin1Char('.')))
                m += QLatin1String(".dll");
        }

        return m;
    }

    bool CollectXmlFilesRecursive(const QT::QString& rootDir, QT::QVector<QT::QString>& outFiles)
    {
        outFiles.clear();

        QDir d(rootDir);
        if (!d.exists())
            return false;

        QDirIterator it(rootDir, QStringList() << QLatin1String("*.xml"),
                        QDir::Files, QDirIterator::Subdirectories);

        while (it.hasNext())
            outFiles.push_back(it.next());

        return true;
    }

    // --------------------------------------------------------------------
    // Pass A-1
    // --------------------------------------------------------------------

    bool BuildPassA(const Settings& s, PassAResult& out)
    {
        out = PassAResult();

        QT::QVector<QT::QString> files;
        if (!CollectXmlFilesRecursive(s.apiMonitorRootDir, files))
            return false;

        out.filesProcessed = (uint32_t)files.size();

        for (int i = 0; i < files.size(); ++i)
        {
            QFile f(files[i]);
            if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                out.filesWithErrors++;
                continue;
            }

            out.totalBytes += f.size();
        }

        return true;
    }

    bool WritePassALog(const Settings& s, const PassAResult& r)
    {
        QDir outDir(s.outputDir);
        if (!outDir.exists())
        {
            if (!outDir.mkpath(QLatin1String(".")))
                return false;
        }

        const QT::QString logPath = outDir.filePath(QLatin1String("apimon_passA_log.txt"));

        QFile lf(logPath);
        if (!lf.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

        QTextStream ts(&lf);
        ts.setCodec("UTF-8");

        ts << "ApiMonitorDoc Pass A-1 log\n";
        ts << "Generated: " << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n\n";

        ts << "RootDir: " << s.apiMonitorRootDir << "\n";
        ts << "FilesProcessed: " << r.filesProcessed << "\n";
        ts << "FilesWithErrors: " << r.filesWithErrors << "\n";
        ts << "TotalBytes: " << r.totalBytes << "\n";

        return true;
    }

    // --------------------------------------------------------------------
    // Pass B-1
    // --------------------------------------------------------------------

    static TypeKind ClassifyTypeKindByAttr(const QT::QString& typeAttr, bool sawEnum, bool sawFlag)
    {
        const QT::QString t = typeAttr.trimmed().toLower();

        if (t == QLatin1String("alias") || t == QLatin1String("typedef"))
            return TypeKind::Alias;

        if (t == QLatin1String("pointer") || t == QLatin1String("ptr"))
            return TypeKind::Pointer;

        if (t == QLatin1String("array"))
            return TypeKind::Array;

        if (t == QLatin1String("struct"))
            return TypeKind::Struct;

        if (t == QLatin1String("union"))
            return TypeKind::Union_;

        if (t == QLatin1String("interface"))
            return TypeKind::Interface_;

        if (t == QLatin1String("functionpointer") || t == QLatin1String("funcptr") || t == QLatin1String("function_pointer"))
            return TypeKind::FunctionPointer;

        // Иногда XML помечает enum/flag не через TypeAttr, а через вложенные теги.
        if (sawEnum)
            return TypeKind::Enum;

        if (sawFlag)
            return TypeKind::Flags;

        if (t == QLatin1String("enum"))
            return TypeKind::Enum;

        if (t == QLatin1String("flags") || t == QLatin1String("flag"))
            return TypeKind::Flags;

        return TypeKind::Unknown;
    }

static bool ParseOneXml_PassB1(const QT::QString& filePath, PassB1Result& out)
    {
        QFile f(filePath);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        QXmlStreamReader xr(&f);

        bool insideModule = false;
        QT::QString currentModuleLower;

        bool insideVariable = false;
        TypeRecord cur;              ///< Текущая собираемая запись Variable.
        bool sawEnum = false;        ///< Внутри Variable встретился <Enum>.
        bool sawFlag = false;        ///< Внутри Variable встретился <Flag>.
        bool collectFields = false;  ///< Variable@Type == Struct/Union (значит собираем <Field .../>).
        int enumDepth = 0;           ///< Глубина вложенности внутри <Enum>.
        int flagDepth = 0;           ///< Глубина вложенности внутри <Flag>.

        while (!xr.atEnd())
        {
            xr.readNext();

            if (xr.isStartElement())
            {
                const QT::QStringRef name = xr.name();

                if (name == QLatin1String("Module"))
                {
                    const QT::QString moduleName = xr.attributes().value(QLatin1String("Name")).toString();
                    currentModuleLower = NormalizeModuleNameLower(moduleName);

                    if (!currentModuleLower.isEmpty())
                        insideModule = true;
                    else
                    {
                        insideModule = false;
                        currentModuleLower.clear();
                    }
                }
                else if (name == QLatin1String("Variable"))
                {
                    if (insideModule && !currentModuleLower.isEmpty())
                    {
                        insideVariable = true;
                        cur = TypeRecord();
                        cur.moduleLower = currentModuleLower;

                        cur.name = xr.attributes().value(QLatin1String("Name")).toString().trimmed();
                        cur.typeAttr = xr.attributes().value(QLatin1String("Type")).toString().trimmed();
                        cur.base = xr.attributes().value(QLatin1String("Base")).toString().trimmed();
                        cur.count = xr.attributes().value(QLatin1String("Count")).toString().trimmed();

                        sawEnum = false;
                        sawFlag = false;
                        enumDepth = 0;
                        flagDepth = 0;

                        // Собираем поля только для Struct/Union.
                        collectFields = (cur.typeAttr.compare(QLatin1String("Struct"), Qt::CaseInsensitive) == 0)
                                     || (cur.typeAttr.compare(QLatin1String("Union"), Qt::CaseInsensitive) == 0);

                        cur.fields.clear();
                        cur.enumValues.clear();
                    }
                }
                else if (insideVariable && name == QLatin1String("Field"))
                {
                    if (collectFields)
                    {
                        FieldRecord fr;
                        fr.type = xr.attributes().value(QLatin1String("Type")).toString().trimmed();
                        fr.name = xr.attributes().value(QLatin1String("Name")).toString().trimmed();
                        fr.display = xr.attributes().value(QLatin1String("Display")).toString().trimmed();
                        fr.count = xr.attributes().value(QLatin1String("Count")).toString().trimmed();
                        cur.fields.push_back(fr);
                    }
                }
                else if (insideVariable && name == QLatin1String("Enum"))
                {
                    sawEnum = true;
                    enumDepth = 1;
                }
                else if (insideVariable && name == QLatin1String("Flag"))
                {
                    sawFlag = true;
                    flagDepth = 1;
                }
                else if (insideVariable && enumDepth > 0)
                {
                    // Пробуем вытащить элементы enum (структура XML может отличаться, поэтому делаем мягко).
                    // Типичные варианты: <Value Name="X" Value="1" .../> или <Member .../> и т.п.
                    if (name != QLatin1String("Enum"))
                    {
                        const QXmlStreamAttributes a = xr.attributes();
                        const QT::QString nm = a.value(QLatin1String("Name")).toString().trimmed();
                        const QT::QString val = a.value(QLatin1String("Value")).toString().trimmed();
                        const QT::QString disp = a.value(QLatin1String("Display")).toString().trimmed();

                        if (!nm.isEmpty() || !val.isEmpty())
                        {
                            EnumValueRecord ev;
                            ev.name = nm;
                            ev.value = val;
                            ev.display = disp;
                            cur.enumValues.push_back(ev);
                        }

                        enumDepth++;
                    }
                }
                else if (insideVariable && flagDepth > 0)
                {
                    if (name != QLatin1String("Flag"))
                    {
                        const QXmlStreamAttributes a = xr.attributes();
                        const QT::QString nm = a.value(QLatin1String("Name")).toString().trimmed();
                        const QT::QString val = a.value(QLatin1String("Value")).toString().trimmed();
                        const QT::QString disp = a.value(QLatin1String("Display")).toString().trimmed();

                        if (!nm.isEmpty() || !val.isEmpty())
                        {
                            EnumValueRecord ev;
                            ev.name = nm;
                            ev.value = val;
                            ev.display = disp;
                            cur.enumValues.push_back(ev);
                        }

                        flagDepth++;
                    }
                }
            }
            else if (xr.isEndElement())
            {
                const QT::QStringRef name = xr.name();

                if (name == QLatin1String("Variable"))
                {
                    if (insideVariable)
                    {
                        cur.kind = ClassifyTypeKindByAttr(cur.typeAttr, sawEnum, sawFlag);

                        out.kindCounts[(uint32_t)cur.kind]++;

                        if (cur.kind == TypeKind::Unknown)
                        {
                            const QT::QString key = cur.typeAttr.trimmed().toLower();
                            out.unknownTypeAttrCounts[key] = out.unknownTypeAttrCounts.value(key, 0) + 1;
                            if (!out.unknownTypeAttrOriginal.contains(key))
                                out.unknownTypeAttrOriginal.insert(key, cur.typeAttr);
                        }

                        out.types.push_back(cur);

                        insideVariable = false;
                        cur = TypeRecord();
                        sawEnum = false;
                        sawFlag = false;
                        collectFields = false;
                        enumDepth = 0;
                        flagDepth = 0;
                    }
                }
                else if (name == QLatin1String("Module"))
                {
                    insideModule = false;
                    currentModuleLower.clear();
                }
                else if (name == QLatin1String("Enum"))
                {
                    enumDepth = 0;
                }
                else if (name == QLatin1String("Flag"))
                {
                    flagDepth = 0;
                }
            }
        }

        if (xr.hasError())
        {
            out.filesWithErrors++;
            return false;
        }

        return true;
    }

    bool BuildPassB1(const Settings& s, PassB1Result& out)
    {
        out = PassB1Result();

        const QDir root(s.apiMonitorRootDir);
        if (!root.exists())
            return false;

        QT::QVector<QT::QString> files;
        CollectXmlFilesRecursive(s.apiMonitorRootDir, files);

        for (int i = 0; i < files.size(); ++i)
        {
            (void)ParseOneXml_PassB1(files[i], out);
            out.filesProcessed++;
        }

        return true;
    }

    static QT::QString TypeKindToString(TypeKind k)
    {
        switch (k)
        {
            case TypeKind::Unknown: return QLatin1String("Unknown");
            case TypeKind::Alias: return QLatin1String("Alias");
            case TypeKind::Pointer: return QLatin1String("Pointer");
            case TypeKind::Array: return QLatin1String("Array");
            case TypeKind::Struct: return QLatin1String("Struct");
            case TypeKind::Union_: return QLatin1String("Union");
            case TypeKind::Enum: return QLatin1String("Enum");
            case TypeKind::Flags: return QLatin1String("Flags");
            case TypeKind::Interface_: return QLatin1String("Interface");
            case TypeKind::FunctionPointer: return QLatin1String("FunctionPointer");
        }
        return QLatin1String("Unknown");
    }

    bool WritePassB1Log(const Settings& s, const PassB1Result& r)
    {
        QDir outDir(s.outputDir);
        if (!outDir.exists())
        {
            if (!outDir.mkpath(QLatin1String(".")))
                return false;
        }

        const QT::QString logPath = outDir.filePath(QLatin1String("apimon_passB1_log.txt"));

        QFile lf(logPath);
        if (!lf.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

        QTextStream ts(&lf);
        ts.setCodec("UTF-8");

        ts << "ApiMonitorDoc Pass B-1 log\n";
        ts << "Generated: " << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n\n";

        ts << "RootDir: " << s.apiMonitorRootDir << "\n";
        ts << "FilesProcessed: " << r.filesProcessed << "\n";
        ts << "FilesWithErrors: " << r.filesWithErrors << "\n";
        ts << "TypesStored: " << r.types.size() << "\n\n";

        ts << "Kind counts:\n";
        {
            QVector<QPair<uint32_t, uint32_t>> arr;
            arr.reserve(r.kindCounts.size());
            for (auto it = r.kindCounts.constBegin(); it != r.kindCounts.constEnd(); ++it)
                arr.push_back(QPair<uint32_t, uint32_t>(it.key(), it.value()));

            std::sort(arr.begin(), arr.end(), [](const QPair<uint32_t, uint32_t>& a,
                                                const QPair<uint32_t, uint32_t>& b)
            {
                return a.second > b.second;
            });

            for (int i = 0; i < arr.size(); ++i)
                ts << "  " << TypeKindToString((TypeKind)arr[i].first) << " : " << arr[i].second << "\n";
        }

        ts << "\nUnknown TypeAttr counts:\n";
        {
            QVector<QPair<QT::QString, uint32_t>> arr;
            arr.reserve(r.unknownTypeAttrCounts.size());
            for (auto it = r.unknownTypeAttrCounts.constBegin(); it != r.unknownTypeAttrCounts.constEnd(); ++it)
                arr.push_back(QPair<QT::QString, uint32_t>(it.key(), it.value()));

            std::sort(arr.begin(), arr.end(), [](const QPair<QT::QString, uint32_t>& a,
                                                const QPair<QT::QString, uint32_t>& b)
            {
                return a.second > b.second;
            });

            const int limit = std::min<int>(arr.size(), 60);
            for (int i = 0; i < limit; ++i)
            {
                const QT::QString key = arr[i].first;
                const QT::QString orig = r.unknownTypeAttrOriginal.value(key, key);
                ts << "  " << orig << " : " << arr[i].second << "\n";
            }
        }

        ts << "\nSamples (first 25):\n";
        const int sampleN = std::min<int>(r.types.size(), 25);
        for (int i = 0; i < sampleN; ++i)
        {
            const TypeRecord& t = r.types[i];
            ts << "\n[" << i << "] " << t.moduleLower << " :: " << t.name << "\n";
            ts << "  kind: " << TypeKindToString(t.kind) << "\n";
            ts << "  typeAttr: " << t.typeAttr << "\n";
            ts << "  base: " << t.base << "\n";
            ts << "  count: " << t.count << "\n";
            ts << "  fields: " << t.fields.size() << "\n";
            ts << "  enumValues: " << t.enumValues.size() << "\n";
        }

        return true;
    }

    // --------------------------------------------------------------------
    // Pass B-2 (минимальная статистика)
    // --------------------------------------------------------------------

    static bool ParseOneXml_PassB2(const QT::QString& filePath, PassB2Result& out)
    {
        QFile f(filePath);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        QXmlStreamReader xr(&f);

        bool insideVariable = false;
        QT::QString curTypeAttr;

        while (!xr.atEnd())
        {
            xr.readNext();

            if (xr.isStartElement())
            {
                const QT::QStringRef name = xr.name();

                if (name == QLatin1String("Variable"))
                {
                    insideVariable = true;
                    curTypeAttr = xr.attributes().value(QLatin1String("Type")).toString().trimmed();
                }
                else if (insideVariable && name == QLatin1String("Field"))
                {
                    // Считаем только для Struct/Union.
                    if (curTypeAttr.compare(QLatin1String("Struct"), Qt::CaseInsensitive) == 0 ||
                        curTypeAttr.compare(QLatin1String("Union"), Qt::CaseInsensitive) == 0)
                    {
                        out.structFieldsTotal++;
                    }
                }
            }
            else if (xr.isEndElement())
            {
                const QT::QStringRef name = xr.name();
                if (name == QLatin1String("Variable"))
                {
                    insideVariable = false;
                    curTypeAttr.clear();
                }
            }
        }

        if (xr.hasError())
        {
            out.filesWithErrors++;
            return false;
        }

        return true;
    }

    bool BuildPassB2(const Settings& s, PassB2Result& out)
    {
        out = PassB2Result();

        const QDir root(s.apiMonitorRootDir);
        if (!root.exists())
            return false;

        QT::QVector<QT::QString> files;
        CollectXmlFilesRecursive(s.apiMonitorRootDir, files);

        for (int i = 0; i < files.size(); ++i)
        {
            (void)ParseOneXml_PassB2(files[i], out);
            out.filesProcessed++;
        }

        return true;
    }

    bool WritePassB2Log(const Settings& s, const PassB2Result& r)
    {
        QDir outDir(s.outputDir);
        if (!outDir.exists())
        {
            if (!outDir.mkpath(QLatin1String(".")))
                return false;
        }

        const QT::QString logPath = outDir.filePath(QLatin1String("apimon_passB2_log.txt"));

        QFile lf(logPath);
        if (!lf.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

        QTextStream ts(&lf);
        ts.setCodec("UTF-8");

        ts << "ApiMonitorDoc Pass B-2 log\n";
        ts << "Generated: " << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n\n";

        ts << "RootDir: " << s.apiMonitorRootDir << "\n";
        ts << "FilesProcessed: " << r.filesProcessed << "\n";
        ts << "FilesWithErrors: " << r.filesWithErrors << "\n";
        ts << "StructFieldsTotal: " << r.structFieldsTotal << "\n";

        return true;
    }

    // --------------------------------------------------------------------
    // Pass F-1: функции <Api ...> (имена, параметры, return)
    // --------------------------------------------------------------------

    /// \brief
    /// Заглушка для построения поля links.
    /// Сейчас возвращает пустую строку, позже реализуем полноценную логику.
    static QT::QString BuildLinksStub(const ApiFunctionRecord& /*a*/)
    {
        return QT::QString();
    }

    static QT::QString AttrFirstNonEmpty(const QXmlStreamAttributes& a,
                                        const char* n1,
                                        const char* n2 = nullptr,
                                        const char* n3 = nullptr)
    {
        if (n1)
        {
            const QT::QString v = a.value(QLatin1String(n1)).toString().trimmed();
            if (!v.isEmpty())
                return v;
        }
        if (n2)
        {
            const QT::QString v = a.value(QLatin1String(n2)).toString().trimmed();
            if (!v.isEmpty())
                return v;
        }
        if (n3)
        {
            const QT::QString v = a.value(QLatin1String(n3)).toString().trimmed();
            if (!v.isEmpty())
                return v;
        }
        return QT::QString();
    }

    static bool ParseOneXml_PassF1(const QT::QString& filePath, PassF1Result& out)
    {
        QFile f(filePath);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        QXmlStreamReader xr(&f);

        bool insideModule = false;
        QT::QString currentModuleLower;

        bool insideApi = false;
        ApiFunctionRecord curApi;

        while (!xr.atEnd())
        {
            xr.readNext();

            if (xr.isStartElement())
            {
                const QT::QStringRef name = xr.name();

                if (name == QLatin1String("Module"))
                {
                    const QT::QString moduleName = xr.attributes().value(QLatin1String("Name")).toString();
                    currentModuleLower = NormalizeModuleNameLower(moduleName);

                    insideModule = !currentModuleLower.isEmpty();
                }
                else if (name == QLatin1String("Api"))
                {
                    if (insideModule && !currentModuleLower.isEmpty())
                    {
                        insideApi = true;
                        curApi = ApiFunctionRecord();
                        curApi.moduleLower = currentModuleLower;

                        const QXmlStreamAttributes a = xr.attributes();

                        curApi.name = a.value(QLatin1String("Name")).toString().trimmed();
                        curApi.dll = AttrFirstNonEmpty(a, "Dll", "Module", "Library");
                        curApi.convention = AttrFirstNonEmpty(a, "Convention", "CallConv", "CallingConvention");

                        // Возврат может быть задан разными способами (атрибутом или отдельным элементом <Return .../>).
                        curApi.retType = AttrFirstNonEmpty(a, "Return", "Ret", "Type");

                        out.apisTotal++;
                    }
                }
                else if (insideApi && (name == QLatin1String("Param") || name == QLatin1String("Parameter")))
                {
                    ApiParamRecord p;
                    const QXmlStreamAttributes a = xr.attributes();

                    p.name = a.value(QLatin1String("Name")).toString().trimmed();
                    p.type = a.value(QLatin1String("Type")).toString().trimmed();
                    p.display = a.value(QLatin1String("Display")).toString().trimmed();
                    p.count = a.value(QLatin1String("Count")).toString().trimmed();
                    p.dir = AttrFirstNonEmpty(a, "Dir", "Direction", "InOut");

                    curApi.params.push_back(p);
                    out.paramsTotal++;
                }
                else if (insideApi && name == QLatin1String("Return"))
                {
                    if (curApi.retType.isEmpty())
                    {
                        const QXmlStreamAttributes a = xr.attributes();
                        curApi.retType = AttrFirstNonEmpty(a, "Type", "Value", "Name");
                    }
                }
            }
            else if (xr.isEndElement())
            {
                const QT::QStringRef name = xr.name();

                if (name == QLatin1String("Api"))
                {
                    if (insideApi)
                    {
                        // Сохраняем даже если нет ретурна/параметров, но имя обязательно.
                        if (!curApi.name.isEmpty())
                        {
                            curApi.links = BuildLinksStub(curApi);

                            out.apis.push_back(curApi);

                            const QT::QString key = curApi.name.trimmed().toLower();
                            out.apiNameCounts[key] = out.apiNameCounts.value(key, 0) + 1;
                        }

                        insideApi = false;
                        curApi = ApiFunctionRecord();
                    }
                }
                else if (name == QLatin1String("Module"))
                {
                    insideModule = false;
                    currentModuleLower.clear();
                }
            }
        }

        if (xr.hasError())
        {
            out.filesWithErrors++;
            return false;
        }

        return true;
    }

    bool BuildPassF1(const Settings& s, PassF1Result& out)
    {
        out = PassF1Result();

        const QDir root(s.apiMonitorRootDir);
        if (!root.exists())
            return false;

        QT::QVector<QT::QString> files;
        CollectXmlFilesRecursive(s.apiMonitorRootDir, files);

        for (int i = 0; i < files.size(); ++i)
        {
            (void)ParseOneXml_PassF1(files[i], out);
            out.filesProcessed++;
        }

        return true;
    }

    bool WritePassF1Log(const Settings& s, const PassF1Result& r)
    {
        QDir outDir(s.outputDir);
        if (!outDir.exists())
        {
            if (!outDir.mkpath(QLatin1String(".")))
                return false;
        }

        const QT::QString logPath = outDir.filePath(QLatin1String("apimon_passF1_log.txt"));

        QFile lf(logPath);
        if (!lf.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

        QTextStream ts(&lf);
        ts.setCodec("UTF-8");

        ts << "ApiMonitorDoc Pass F-1 (Api functions) log\n";
        ts << "Generated: " << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n\n";

        ts << "RootDir: " << s.apiMonitorRootDir << "\n";
        ts << "FilesProcessed: " << r.filesProcessed << "\n";
        ts << "FilesWithErrors: " << r.filesWithErrors << "\n";
        ts << "ApisTotal: " << r.apisTotal << "\n";
        ts << "ParamsTotal: " << r.paramsTotal << "\n";
        ts << "ApisStored: " << r.apis.size() << "\n\n";

        ts << "Top API names (duplicates across modules, if any):\n";
        {
            QVector<QPair<QT::QString, uint32_t>> arr;
            arr.reserve(r.apiNameCounts.size());
            for (auto it = r.apiNameCounts.constBegin(); it != r.apiNameCounts.constEnd(); ++it)
                arr.push_back(QPair<QT::QString, uint32_t>(it.key(), it.value()));

            std::sort(arr.begin(), arr.end(), [](const QPair<QT::QString, uint32_t>& a,
                                                const QPair<QT::QString, uint32_t>& b)
            {
                return a.second > b.second;
            });

            const int limit = std::min<int>(arr.size(), 50);
            for (int i = 0; i < limit; ++i)
                ts << "  " << arr[i].first << " : " << arr[i].second << "\n";
        }

        ts << "\nSamples (first 40):\n";
        const int sampleN = std::min<int>(r.apis.size(), 40);
        for (int i = 0; i < sampleN; ++i)
        {
            const ApiFunctionRecord& a = r.apis[i];
            ts << "\n[" << i << "] " << a.moduleLower << " :: " << a.name << "\n";
            ts << "  ret: " << (a.retType.isEmpty() ? QT::QString("<empty>") : a.retType) << "\n";
            ts << "  params: " << a.params.size() << "\n";
            for (int k = 0; k < a.params.size(); ++k)
            {
                const ApiParamRecord& p = a.params[k];
                ts << "    - " << p.type << " " << p.name;
                if (!p.dir.isEmpty())
                    ts << " [" << p.dir << "]";
                if (!p.count.isEmpty())
                    ts << " {count=" << p.count << "}";
                if (!p.display.isEmpty())
                    ts << " {display=" << p.display << "}";
                ts << "\n";
            }
        }

        return true;
    }


    // --------------------------------------------------------------------
    // Pass SIG-1: сигнатура XML
    // --------------------------------------------------------------------

    static bool HashOneFileSha1(const QT::QString& absPath, uint8_t outSha1[20])
    {
        QFile f(absPath);
        if (!f.open(QIODevice::ReadOnly))
            return false;

        QCryptographicHash h(QCryptographicHash::Sha1);

        // Читаем блоками.
        const int kChunk = 64 * 1024;
        QByteArray buf;
        buf.resize(kChunk);

        while (!f.atEnd())
        {
            const qint64 rd = f.read(buf.data(), kChunk);
            if (rd <= 0)
                break;

            h.addData(buf.constData(), (int)rd);
        }

        const QByteArray digest = h.result();
        if (digest.size() != 20)
            return false;

        memcpy(outSha1, digest.constData(), 20);
        return true;
    }

    static void Sha1ToHex40(const uint8_t sha1[20], char outHex[41])
    {
        static const char* hex = "0123456789abcdef";
        for (int i = 0; i < 20; ++i)
        {
            const uint8_t b = sha1[i];
            outHex[i * 2 + 0] = hex[(b >> 4) & 0xF];
            outHex[i * 2 + 1] = hex[(b >> 0) & 0xF];
        }
        outHex[40] = '\0';
    }

    bool BuildInputSignature(const Settings& s, InputSignatureResult& out)
    {
        out = InputSignatureResult();

        QT::QVector<QT::QString> files;
        if (!CollectXmlFilesRecursive(s.apiMonitorRootDir, files))
            return false;

        out.filesProcessed = (uint32_t)files.size();

        // Считаем комбинированный хэш на основе: relPath|size|mtime|sha1
        QCryptographicHash combined(QCryptographicHash::Sha1);

        const QDir root(s.apiMonitorRootDir);

        for (int i = 0; i < files.size(); ++i)
        {
            const QT::QString absPath = files[i];
            QFileInfo fi(absPath);

            InputFileSignature fs;
            fs.relPath = root.relativeFilePath(absPath);
            fs.size = fi.size();
            fs.mtime = fi.lastModified().toMSecsSinceEpoch() / 1000;

            out.totalBytes += fs.size;

            if (!HashOneFileSha1(absPath, fs.sha1))
            {
                out.filesWithErrors++;
                continue;
            }

            // Добавляем в combined:
            combined.addData(fs.relPath.toUtf8());
            combined.addData("|", 1);

            QByteArray sb = QByteArray::number(fs.size);
            combined.addData(sb);
            combined.addData("|", 1);

            QByteArray mb = QByteArray::number(fs.mtime);
            combined.addData(mb);
            combined.addData("|", 1);

            combined.addData((const char*)fs.sha1, 20);
            combined.addData("\n", 1);

            out.files.push_back(fs);
        }

        const QByteArray digest = combined.result();
        if (digest.size() != 20)
            return false;

        uint8_t sha1[20];
        memcpy(sha1, digest.constData(), 20);

        char hex40[41];
        Sha1ToHex40(sha1, hex40);
        out.combinedSha1Hex = QT::QString::fromLatin1(hex40);

        return true;
    }

    bool WriteInputSignatureLog(const Settings& s, const InputSignatureResult& r)
    {
        QDir outDir(s.outputDir);
        if (!outDir.exists())
        {
            if (!outDir.mkpath(QLatin1String(".")))
                return false;
        }

        const QT::QString logPath = outDir.filePath(QLatin1String("apimon_input_signature_log.txt"));

        QFile lf(logPath);
        if (!lf.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

        QTextStream ts(&lf);
        ts.setCodec("UTF-8");

        ts << "ApiMonitorDoc Input Signature log\n";
        ts << "Generated: " << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n\n";

        ts << "RootDir: " << s.apiMonitorRootDir << "\n";
        ts << "FilesProcessed: " << r.filesProcessed << "\n";
        ts << "FilesWithErrors: " << r.filesWithErrors << "\n";
        ts << "TotalBytes: " << r.totalBytes << "\n";
        ts << "CombinedSHA1: " << r.combinedSha1Hex << "\n\n";

        ts << "Files (first 50):\n";
        const int limit = std::min<int>(r.files.size(), 50);
        for (int i = 0; i < limit; ++i)
        {
            const InputFileSignature& f = r.files[i];
            char hex40[41];
            Sha1ToHex40(f.sha1, hex40);

            ts << "  - " << f.relPath << " | size=" << f.size << " | mtime=" << f.mtime << " | sha1=" << hex40 << "\n";
        }

        return true;
    }

    // --------------------------------------------------------------------
    // Cache BIN-0
    // --------------------------------------------------------------------

    QT::QString GetCacheBinPath(const Settings& s)
    {
        QDir d(s.idaPluginsDir);
        return d.filePath(QLatin1String("apimon_cache.bin"));
    }

    static void HexToSha1_20(const QT::QString& hex40, uint8_t outSha1[20])
    {
        memset(outSha1, 0, 20);

        const QByteArray h = hex40.trimmed().toLatin1();
        if (h.size() < 40)
            return;

        for (int i = 0; i < 20; ++i)
        {
            const char c1 = h[i * 2 + 0];
            const char c2 = h[i * 2 + 1];

            auto nib = [](char c) -> uint8_t
            {
                if (c >= '0' && c <= '9') return (uint8_t)(c - '0');
                if (c >= 'a' && c <= 'f') return (uint8_t)(c - 'a' + 10);
                if (c >= 'A' && c <= 'F') return (uint8_t)(c - 'A' + 10);
                return 0;
            };

            outSha1[i] = (uint8_t)((nib(c1) << 4) | nib(c2));
        }
    }

    bool BuildCacheHeaderFromSignature(const InputSignatureResult& sig, CacheHeader& out)
    {
        out = CacheHeader();

        out.magic = 0x434D5041; // 'APMC'
        out.version = 1;
        out.headerSize = (uint32_t)sizeof(CacheHeader);
        out.filesProcessed = sig.filesProcessed;
        out.totalBytes = sig.totalBytes;
        out.createdUtcMs = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();

        HexToSha1_20(sig.combinedSha1Hex, out.combinedSha1);

        return true;
    }

    bool IsCacheHeaderValidForSignature(const CacheHeader& ch, const InputSignatureResult& sig)
    {
        uint8_t sha1[20];
        HexToSha1_20(sig.combinedSha1Hex, sha1);

        if (memcmp(ch.combinedSha1, sha1, 20) != 0)
            return false;

        return true;
    }

    bool WriteCacheHeaderBin(const Settings& s, const CacheHeader& ch)
    {
        const QT::QString path = GetCacheBinPath(s);

        QFile f(path);
        if (!f.open(QIODevice::WriteOnly))
            return false;

        const qint64 wr = f.write((const char*)&ch, sizeof(CacheHeader));
        f.close();

        return (wr == (qint64)sizeof(CacheHeader));
    }

    bool ReadCacheHeaderBin(const Settings& s, CacheHeader& out)
    {
        const QT::QString path = GetCacheBinPath(s);

        QFile f(path);
        if (!f.open(QIODevice::ReadOnly))
            return false;

        if (f.size() < (qint64)sizeof(CacheHeader))
            return false;

        const qint64 rd = f.read((char*)&out, sizeof(CacheHeader));
        f.close();

        return (rd == (qint64)sizeof(CacheHeader));
    }


    // --------------------------------------------------------------------
    // Data BIN-1: основной бинарник базы (типы + функции).
    // --------------------------------------------------------------------

    QT::QString DataBinPath(const Settings& s)
    {
        QDir d(s.idaPluginsDir);
        return d.filePath(QLatin1String("apimon_data.bin"));
    }

    /// \brief
    /// Внутренний пул строк: складываем все строки в общий blob UTF-8 + '\0'.
    class StringPool
    {
    public:
        StringPool()
        {
            // offset=0 зарезервирован под пустую строку.
            m_blob.append('\0');
        }

        /// \brief
        /// Добавить строку в пул и вернуть offset в blob.
        uint32_t Intern(const QT::QString& s)
        {
            const QT::QString t = s.trimmed();
            if (t.isEmpty())
                return 0;

            const auto it = m_map.constFind(t);
            if (it != m_map.constEnd())
                return it.value();

            const uint32_t off = (uint32_t)m_blob.size();
            const QByteArray u8 = t.toUtf8();

            m_blob.append(u8);
            m_blob.append('\0');

            m_map.insert(t, off);
            return off;
        }

        const QByteArray& Blob() const { return m_blob; }

    private:
        QByteArray m_blob;                   ///< Все строки подряд (UTF-8 + '\0').
        QHash<QT::QString, uint32_t> m_map;   ///< QString -> offset.
    };

    static QT::QString GetStringByOffset(const QByteArray& blob, uint32_t off)
    {
        if (off == 0)
            return QT::QString();

        if (off >= (uint32_t)blob.size())
            return QT::QString();

        const char* p = blob.constData() + off;
        const int maxLen = blob.size() - (int)off;

        // Ищем '\0' (границы строки в blob).
        int len = 0;
        for (; len < maxLen; ++len)
        {
            if (p[len] == '\0')
                break;
        }

        if (len <= 0)
            return QT::QString();

        return QT::QString::fromUtf8(p, len);
    }

    // Фиксированный размер заголовка (чтобы удобно добавлять поля без боли).
    static const uint32_t kDataBinHeaderSize = 128;
    static const uint32_t kDataBinMagic = 0x444D5041;   // 'APMD'
    static const uint32_t kDataBinVersion = 1;

    struct DataBinHeader_v1
    {
        uint32_t magic = kDataBinMagic;
        uint32_t version = kDataBinVersion;
        uint32_t headerSize = kDataBinHeaderSize;
        uint32_t reserved = 0;

        char combinedSha1Hex[41] = { 0 }; ///< 40 hex + '\0'

        uint32_t stringBlobOffset = 0;
        uint32_t stringBlobSize = 0;

        uint32_t typesOffset = 0;
        uint32_t typeCount = 0;

        uint32_t fieldsOffset = 0;
        uint32_t fieldCount = 0;

        uint32_t enumValsOffset = 0;
        uint32_t enumValCount = 0;

        uint32_t funcsOffset = 0;
        uint32_t funcCount = 0;

        uint32_t paramsOffset = 0;
        uint32_t paramCount = 0;
    };

    struct FieldRecBin_v1
    {
        uint32_t nameOff = 0;
        uint32_t typeOff = 0;
        uint32_t displayOff = 0;
        uint32_t countOff = 0;
    };

    struct EnumValRecBin_v1
    {
        uint32_t nameOff = 0;
        uint32_t valueOff = 0;
        uint32_t displayOff = 0;
    };

    struct TypeRecBin_v1
    {
        uint32_t moduleOff = 0;
        uint32_t nameOff = 0;
        uint32_t typeAttrOff = 0;
        uint32_t baseOff = 0;
        uint32_t countOff = 0;

        uint8_t kind = 0;
        uint8_t pad1 = 0;
        uint16_t pad2 = 0;

        uint32_t fieldIndex = 0;
        uint32_t fieldCount = 0;

        uint32_t enumIndex = 0;
        uint32_t enumCount = 0;
    };

    struct ParamRecBin_v1
    {
        uint32_t nameOff = 0;
        uint32_t typeOff = 0;
        uint32_t displayOff = 0;
        uint32_t countOff = 0;
        uint32_t dirOff = 0;
    };

    struct FuncRecBin_v1
    {
        uint32_t moduleOff = 0;
        uint32_t nameOff = 0;
        uint32_t dllOff = 0;
        uint32_t convOff = 0;
        uint32_t retOff = 0;
        uint32_t linksOff = 0;

        uint32_t paramIndex = 0;
        uint32_t paramCount = 0;
    };

    static void WriteFixedSha1(char out41[41], const QT::QString& sha1Hex)
    {
        memset(out41, 0, 41);

        QByteArray u8 = sha1Hex.trimmed().toUtf8();
        if (u8.size() > 40)
            u8 = u8.left(40);

        if (!u8.isEmpty())
            memcpy(out41, u8.constData(), std::min<int>(u8.size(), 40));
    }

    static void WriteHeader(QDataStream& ds, const DataBinHeader_v1& h)
    {
        ds << (quint32)h.magic;
        ds << (quint32)h.version;
        ds << (quint32)h.headerSize;
        ds << (quint32)h.reserved;

        ds.writeRawData(h.combinedSha1Hex, 41);

        ds << (quint32)h.stringBlobOffset;
        ds << (quint32)h.stringBlobSize;

        ds << (quint32)h.typesOffset;
        ds << (quint32)h.typeCount;

        ds << (quint32)h.fieldsOffset;
        ds << (quint32)h.fieldCount;

        ds << (quint32)h.enumValsOffset;
        ds << (quint32)h.enumValCount;

        ds << (quint32)h.funcsOffset;
        ds << (quint32)h.funcCount;

        ds << (quint32)h.paramsOffset;
        ds << (quint32)h.paramCount;

        // Паддинг до фиксированного размера заголовка.
        const int written = (int)ds.device()->pos();
        if (written < (int)kDataBinHeaderSize)
        {
            QByteArray pad;
            pad.resize((int)kDataBinHeaderSize - written);
            pad.fill('\0');
            ds.writeRawData(pad.constData(), pad.size());
        }
    }

    static bool ReadHeader(QDataStream& ds, DataBinHeader_v1& out)
    {
        out = DataBinHeader_v1();

        quint32 v = 0;

        ds >> v; out.magic = (uint32_t)v;
        ds >> v; out.version = (uint32_t)v;
        ds >> v; out.headerSize = (uint32_t)v;
        ds >> v; out.reserved = (uint32_t)v;

        if (ds.readRawData(out.combinedSha1Hex, 41) != 41)
            return false;

        ds >> v; out.stringBlobOffset = (uint32_t)v;
        ds >> v; out.stringBlobSize = (uint32_t)v;

        ds >> v; out.typesOffset = (uint32_t)v;
        ds >> v; out.typeCount = (uint32_t)v;

        ds >> v; out.fieldsOffset = (uint32_t)v;
        ds >> v; out.fieldCount = (uint32_t)v;

        ds >> v; out.enumValsOffset = (uint32_t)v;
        ds >> v; out.enumValCount = (uint32_t)v;

        ds >> v; out.funcsOffset = (uint32_t)v;
        ds >> v; out.funcCount = (uint32_t)v;

        ds >> v; out.paramsOffset = (uint32_t)v;
        ds >> v; out.paramCount = (uint32_t)v;

        // Пропускаем паддинг (если headerSize больше текущей позиции).
        if (out.headerSize > (uint32_t)ds.device()->pos())
        {
            ds.device()->seek(out.headerSize);
        }

        return !ds.status();
    }

    bool WriteDataBin(const Settings& s, const InputSignatureResult& sig, const PassB1Result& b1, const PassF1Result& f1)
    {
        // Собираем строковый пул и бинарные записи.
        StringPool sp;

        QVector<TypeRecBin_v1> typeBins;
        QVector<FieldRecBin_v1> fieldBins;
        QVector<EnumValRecBin_v1> enumBins;
        QVector<FuncRecBin_v1> funcBins;
        QVector<ParamRecBin_v1> paramBins;

        typeBins.reserve(b1.types.size());
        funcBins.reserve(f1.apis.size());

        // --- types ---
        for (int i = 0; i < b1.types.size(); ++i)
        {
            const TypeRecord& t = b1.types[i];

            TypeRecBin_v1 tb;
            tb.moduleOff = sp.Intern(t.moduleLower);
            tb.nameOff = sp.Intern(t.name);
            tb.typeAttrOff = sp.Intern(t.typeAttr);
            tb.baseOff = sp.Intern(t.base);
            tb.countOff = sp.Intern(t.count);
            tb.kind = (uint8_t)t.kind;

            tb.fieldIndex = (uint32_t)fieldBins.size();
            tb.fieldCount = (uint32_t)t.fields.size();
            for (int k = 0; k < t.fields.size(); ++k)
            {
                const FieldRecord& fr = t.fields[k];
                FieldRecBin_v1 fb;
                fb.nameOff = sp.Intern(fr.name);
                fb.typeOff = sp.Intern(fr.type);
                fb.displayOff = sp.Intern(fr.display);
                fb.countOff = sp.Intern(fr.count);
                fieldBins.push_back(fb);
            }

            tb.enumIndex = (uint32_t)enumBins.size();
            tb.enumCount = (uint32_t)t.enumValues.size();
            for (int k = 0; k < t.enumValues.size(); ++k)
            {
                const EnumValueRecord& ev = t.enumValues[k];
                EnumValRecBin_v1 eb;
                eb.nameOff = sp.Intern(ev.name);
                eb.valueOff = sp.Intern(ev.value);
                eb.displayOff = sp.Intern(ev.display);
                enumBins.push_back(eb);
            }

            typeBins.push_back(tb);
        }

        // --- functions ---
        for (int i = 0; i < f1.apis.size(); ++i)
        {
            const ApiFunctionRecord& a = f1.apis[i];

            FuncRecBin_v1 fb;
            fb.moduleOff = sp.Intern(a.moduleLower);
            fb.nameOff = sp.Intern(a.name);
            fb.dllOff = sp.Intern(a.dll);
            fb.convOff = sp.Intern(a.convention);
            fb.retOff = sp.Intern(a.retType);
            fb.linksOff = sp.Intern(a.links);

            fb.paramIndex = (uint32_t)paramBins.size();
            fb.paramCount = (uint32_t)a.params.size();

            for (int k = 0; k < a.params.size(); ++k)
            {
                const ApiParamRecord& p = a.params[k];

                ParamRecBin_v1 pb;
                pb.nameOff = sp.Intern(p.name);
                pb.typeOff = sp.Intern(p.type);
                pb.displayOff = sp.Intern(p.display);
                pb.countOff = sp.Intern(p.count);
                pb.dirOff = sp.Intern(p.dir);

                paramBins.push_back(pb);
            }

            funcBins.push_back(fb);
        }

        // Готовим header + пишем всё в память (QByteArray), затем на диск.
        DataBinHeader_v1 hdr;
        WriteFixedSha1(hdr.combinedSha1Hex, sig.combinedSha1Hex);

        hdr.stringBlobSize = (uint32_t)sp.Blob().size();

        hdr.typeCount = (uint32_t)typeBins.size();
        hdr.fieldCount = (uint32_t)fieldBins.size();
        hdr.enumValCount = (uint32_t)enumBins.size();
        hdr.funcCount = (uint32_t)funcBins.size();
        hdr.paramCount = (uint32_t)paramBins.size();

        QByteArray outBytes;
        QBuffer buf(&outBytes);
        if (!buf.open(QIODevice::WriteOnly))
            return false;

        QDataStream ds(&buf);
        ds.setByteOrder(QDataStream::LittleEndian);

        // Placeholder header (offsets заполним после вычисления).
        WriteHeader(ds, hdr);

        // --- string blob ---
        hdr.stringBlobOffset = (uint32_t)buf.pos();
        ds.writeRawData(sp.Blob().constData(), sp.Blob().size());

        // --- types ---
        hdr.typesOffset = (uint32_t)buf.pos();
        for (int i = 0; i < typeBins.size(); ++i)
        {
            const TypeRecBin_v1& t = typeBins[i];
            ds << (quint32)t.moduleOff;
            ds << (quint32)t.nameOff;
            ds << (quint32)t.typeAttrOff;
            ds << (quint32)t.baseOff;
            ds << (quint32)t.countOff;
            ds << (quint8)t.kind;
            ds << (quint8)t.pad1;
            ds << (quint16)t.pad2;
            ds << (quint32)t.fieldIndex;
            ds << (quint32)t.fieldCount;
            ds << (quint32)t.enumIndex;
            ds << (quint32)t.enumCount;
        }

        // --- fields ---
        hdr.fieldsOffset = (uint32_t)buf.pos();
        for (int i = 0; i < fieldBins.size(); ++i)
        {
            const FieldRecBin_v1& fbr = fieldBins[i];
            ds << (quint32)fbr.nameOff;
            ds << (quint32)fbr.typeOff;
            ds << (quint32)fbr.displayOff;
            ds << (quint32)fbr.countOff;
        }

        // --- enum values ---
        hdr.enumValsOffset = (uint32_t)buf.pos();
        for (int i = 0; i < enumBins.size(); ++i)
        {
            const EnumValRecBin_v1& ebr = enumBins[i];
            ds << (quint32)ebr.nameOff;
            ds << (quint32)ebr.valueOff;
            ds << (quint32)ebr.displayOff;
        }

        // --- functions ---
        hdr.funcsOffset = (uint32_t)buf.pos();
        for (int i = 0; i < funcBins.size(); ++i)
        {
            const FuncRecBin_v1& fr = funcBins[i];
            ds << (quint32)fr.moduleOff;
            ds << (quint32)fr.nameOff;
            ds << (quint32)fr.dllOff;
            ds << (quint32)fr.convOff;
            ds << (quint32)fr.retOff;
            ds << (quint32)fr.linksOff;
            ds << (quint32)fr.paramIndex;
            ds << (quint32)fr.paramCount;
        }

        // --- params ---
        hdr.paramsOffset = (uint32_t)buf.pos();
        for (int i = 0; i < paramBins.size(); ++i)
        {
            const ParamRecBin_v1& pr = paramBins[i];
            ds << (quint32)pr.nameOff;
            ds << (quint32)pr.typeOff;
            ds << (quint32)pr.displayOff;
            ds << (quint32)pr.countOff;
            ds << (quint32)pr.dirOff;
        }

        // Перезаписываем header с реальными оффсетами.
        buf.seek(0);
        QDataStream ds2(&buf);
        ds2.setByteOrder(QDataStream::LittleEndian);
        WriteHeader(ds2, hdr);

        buf.close();

        const QT::QString path = DataBinPath(s);
        QFile outFile(path);
        if (!outFile.open(QIODevice::WriteOnly))
            return false;

        const qint64 wr = outFile.write(outBytes);
        outFile.close();

        return (wr == outBytes.size());
    }

    bool ReadDataBin(const Settings& s, DataBinDb& out)
    {
        out = DataBinDb();

        const QT::QString path = DataBinPath(s);
        QFile f(path);
        if (!f.open(QIODevice::ReadOnly))
            return false;

        QDataStream ds(&f);
        ds.setByteOrder(QDataStream::LittleEndian);

        DataBinHeader_v1 hdr;
        if (!ReadHeader(ds, hdr))
            return false;

        if (hdr.magic != kDataBinMagic)
            return false;
        if (hdr.version != kDataBinVersion)
            return false;
        if (hdr.headerSize < kDataBinHeaderSize)
            return false;

        // string blob
        if (!f.seek(hdr.stringBlobOffset))
            return false;

        QByteArray blob;
        blob.resize((int)hdr.stringBlobSize);
        if (hdr.stringBlobSize > 0)
        {
            if (f.read(blob.data(), (int)hdr.stringBlobSize) != (qint64)hdr.stringBlobSize)
                return false;
        }

        out.combinedSha1Hex = QT::QString::fromLatin1(hdr.combinedSha1Hex).trimmed();

        // types
        QVector<TypeRecBin_v1> typeBins;
        typeBins.resize((int)hdr.typeCount);

        if (!f.seek(hdr.typesOffset))
            return false;

        for (uint32_t i = 0; i < hdr.typeCount; ++i)
        {
            TypeRecBin_v1& t = typeBins[(int)i];

            quint32 u32 = 0;
            quint8 u8 = 0;
            quint16 u16 = 0;

            ds >> u32; t.moduleOff = (uint32_t)u32;
            ds >> u32; t.nameOff = (uint32_t)u32;
            ds >> u32; t.typeAttrOff = (uint32_t)u32;
            ds >> u32; t.baseOff = (uint32_t)u32;
            ds >> u32; t.countOff = (uint32_t)u32;

            ds >> u8; t.kind = (uint8_t)u8;
            ds >> u8; t.pad1 = (uint8_t)u8;
            ds >> u16; t.pad2 = (uint16_t)u16;

            ds >> u32; t.fieldIndex = (uint32_t)u32;
            ds >> u32; t.fieldCount = (uint32_t)u32;
            ds >> u32; t.enumIndex = (uint32_t)u32;
            ds >> u32; t.enumCount = (uint32_t)u32;
        }

        // fields
        QVector<FieldRecBin_v1> fieldBins;
        fieldBins.resize((int)hdr.fieldCount);

        if (!f.seek(hdr.fieldsOffset))
            return false;

        for (uint32_t i = 0; i < hdr.fieldCount; ++i)
        {
            FieldRecBin_v1& fr = fieldBins[(int)i];
            quint32 u32 = 0;

            ds >> u32; fr.nameOff = (uint32_t)u32;
            ds >> u32; fr.typeOff = (uint32_t)u32;
            ds >> u32; fr.displayOff = (uint32_t)u32;
            ds >> u32; fr.countOff = (uint32_t)u32;
        }

        // enum values
        QVector<EnumValRecBin_v1> enumBins;
        enumBins.resize((int)hdr.enumValCount);

        if (!f.seek(hdr.enumValsOffset))
            return false;

        for (uint32_t i = 0; i < hdr.enumValCount; ++i)
        {
            EnumValRecBin_v1& er = enumBins[(int)i];
            quint32 u32 = 0;

            ds >> u32; er.nameOff = (uint32_t)u32;
            ds >> u32; er.valueOff = (uint32_t)u32;
            ds >> u32; er.displayOff = (uint32_t)u32;
        }

        // functions
        QVector<FuncRecBin_v1> funcBins;
        funcBins.resize((int)hdr.funcCount);

        if (!f.seek(hdr.funcsOffset))
            return false;

        for (uint32_t i = 0; i < hdr.funcCount; ++i)
        {
            FuncRecBin_v1& fr = funcBins[(int)i];
            quint32 u32 = 0;

            ds >> u32; fr.moduleOff = (uint32_t)u32;
            ds >> u32; fr.nameOff = (uint32_t)u32;
            ds >> u32; fr.dllOff = (uint32_t)u32;
            ds >> u32; fr.convOff = (uint32_t)u32;
            ds >> u32; fr.retOff = (uint32_t)u32;
            ds >> u32; fr.linksOff = (uint32_t)u32;
            ds >> u32; fr.paramIndex = (uint32_t)u32;
            ds >> u32; fr.paramCount = (uint32_t)u32;
        }

        // params
        QVector<ParamRecBin_v1> paramBins;
        paramBins.resize((int)hdr.paramCount);

        if (!f.seek(hdr.paramsOffset))
            return false;

        for (uint32_t i = 0; i < hdr.paramCount; ++i)
        {
            ParamRecBin_v1& pr = paramBins[(int)i];
            quint32 u32 = 0;

            ds >> u32; pr.nameOff = (uint32_t)u32;
            ds >> u32; pr.typeOff = (uint32_t)u32;
            ds >> u32; pr.displayOff = (uint32_t)u32;
            ds >> u32; pr.countOff = (uint32_t)u32;
            ds >> u32; pr.dirOff = (uint32_t)u32;
        }

        if (ds.status() != QDataStream::Ok)
            return false;

        // Собираем high-level структуры.
        out.types.clear();
        out.types.reserve((int)hdr.typeCount);

        for (uint32_t i = 0; i < hdr.typeCount; ++i)
        {
            const TypeRecBin_v1& tb = typeBins[(int)i];

            TypeRecord t;
            t.moduleLower = GetStringByOffset(blob, tb.moduleOff);
            t.name = GetStringByOffset(blob, tb.nameOff);
            t.typeAttr = GetStringByOffset(blob, tb.typeAttrOff);
            t.base = GetStringByOffset(blob, tb.baseOff);
            t.count = GetStringByOffset(blob, tb.countOff);
            t.kind = (TypeKind)tb.kind;

            // fields
            t.fields.clear();
            const uint32_t fi = tb.fieldIndex;
            const uint32_t fc = tb.fieldCount;

            for (uint32_t k = 0; k < fc; ++k)
            {
                const uint32_t idx = fi + k;
                if (idx >= (uint32_t)fieldBins.size())
                    break;

                const FieldRecBin_v1& fb = fieldBins[(int)idx];
                FieldRecord fr;
                fr.name = GetStringByOffset(blob, fb.nameOff);
                fr.type = GetStringByOffset(blob, fb.typeOff);
                fr.display = GetStringByOffset(blob, fb.displayOff);
                fr.count = GetStringByOffset(blob, fb.countOff);
                t.fields.push_back(fr);
            }

            // enum values
            t.enumValues.clear();
            const uint32_t ei = tb.enumIndex;
            const uint32_t ec = tb.enumCount;

            for (uint32_t k = 0; k < ec; ++k)
            {
                const uint32_t idx = ei + k;
                if (idx >= (uint32_t)enumBins.size())
                    break;

                const EnumValRecBin_v1& eb = enumBins[(int)idx];
                EnumValueRecord ev;
                ev.name = GetStringByOffset(blob, eb.nameOff);
                ev.value = GetStringByOffset(blob, eb.valueOff);
                ev.display = GetStringByOffset(blob, eb.displayOff);
                t.enumValues.push_back(ev);
            }

            out.types.push_back(t);
        }

        out.apis.clear();
        out.apis.reserve((int)hdr.funcCount);

        for (uint32_t i = 0; i < hdr.funcCount; ++i)
        {
            const FuncRecBin_v1& fb = funcBins[(int)i];

            ApiFunctionRecord a;
            a.moduleLower = GetStringByOffset(blob, fb.moduleOff);
            a.name = GetStringByOffset(blob, fb.nameOff);
            a.dll = GetStringByOffset(blob, fb.dllOff);
            a.convention = GetStringByOffset(blob, fb.convOff);
            a.retType = GetStringByOffset(blob, fb.retOff);
            a.links = GetStringByOffset(blob, fb.linksOff);

            a.params.clear();
            const uint32_t pi = fb.paramIndex;
            const uint32_t pc = fb.paramCount;

            for (uint32_t k = 0; k < pc; ++k)
            {
                const uint32_t idx = pi + k;
                if (idx >= (uint32_t)paramBins.size())
                    break;

                const ParamRecBin_v1& pb = paramBins[(int)idx];

                ApiParamRecord p;
                p.name = GetStringByOffset(blob, pb.nameOff);
                p.type = GetStringByOffset(blob, pb.typeOff);
                p.display = GetStringByOffset(blob, pb.displayOff);
                p.count = GetStringByOffset(blob, pb.countOff);
                p.dir = GetStringByOffset(blob, pb.dirOff);
                a.params.push_back(p);
            }

            out.apis.push_back(a);
        }

        return true;
    }


} // namespace apimon