#include "api_monitor.h"

#include <algorithm>
#include <utility>

#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QDateTime>
#include <QtCore/QTextStream>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QByteArray>
#include <QtCore/QCryptographicHash>

namespace apimon
{
    static QT::QString NormalizeModuleNameLower(const QT::QString& moduleName)
    {
        QT::QString s = moduleName;
        s = s.trimmed().toLower();

        const int slash1 = s.lastIndexOf('/');
        const int slash2 = s.lastIndexOf('\\');
        const int slash = (slash1 > slash2) ? slash1 : slash2;
        if (slash >= 0)
            s = s.mid(slash + 1);

        return s;
    }

    static void CollectXmlFilesRecursive(const QT::QString& rootDir, QT::QVector<QT::QString>& outFiles)
    {
        outFiles.clear();

        QDirIterator it(rootDir, QT::QStringList() << "*.xml",
                        QDir::Files, QDirIterator::Subdirectories);

        while (it.hasNext())
            outFiles.push_back(it.next());
    }

    static QT::QString MakeIncludeAbsPath(const QT::QString& apiRootDir,
                                         const QT::QString& includeFilename)
    {
        QDir root(apiRootDir);

        QT::QString rel = includeFilename;
        rel.replace('\\', '/');

        const QT::QString combined = root.filePath(rel);
        const QFileInfo fi(combined);
        return fi.absoluteFilePath();
    }

    static bool ParseOneXml_PassA(const QT::QString& filePath,
                                 const QT::QString& apiRootDir,
                                 PassAResult& out)
    {
        QFile f(filePath);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        QXmlStreamReader xr(&f);

        bool insideModule = false;
        QT::QString currentModuleLower;

        while (!xr.atEnd())
        {
            xr.readNext();

            if (!xr.isStartElement())
                continue;

            const QT::QStringRef name = xr.name();

            if (name == QLatin1String("Include"))
            {
                const QT::QString inc = xr.attributes().value(QLatin1String("Filename")).toString().trimmed();
                if (!inc.isEmpty())
                {
                    out.includesTotalRefs++;

                    const QT::QString abs = MakeIncludeAbsPath(apiRootDir, inc);
                    if (!abs.isEmpty())
                    {
                        out.includedFilesAbs.insert(abs);

                        if (!QFileInfo(abs).exists())
                        {
                            out.includesMissingFiles++;
                            if (out.missingIncludeSamples.size() < 50)
                                out.missingIncludeSamples.push_back(abs);
                        }
                    }
                }
            }
            else if (name == QLatin1String("Module"))
            {
                const QT::QString moduleName = xr.attributes().value(QLatin1String("Name")).toString();
                currentModuleLower = NormalizeModuleNameLower(moduleName);

                if (!currentModuleLower.isEmpty())
                {
                    insideModule = true;
                    out.modulesLower.insert(currentModuleLower);
                }
                else
                {
                    insideModule = false;
                    currentModuleLower.clear();
                }
            }
            else if (name == QLatin1String("Api"))
            {
                if (insideModule && !currentModuleLower.isEmpty())
                {
                    const QT::QString apiName = xr.attributes().value(QLatin1String("Name")).toString().trimmed();
                    if (!apiName.isEmpty())
                        out.apisByModule[currentModuleLower].insert(apiName);
                }
            }
            else if (name == QLatin1String("Variable"))
            {
                if (insideModule && !currentModuleLower.isEmpty())
                {
                    const QT::QString typeName = xr.attributes().value(QLatin1String("Name")).toString().trimmed();
                    if (!typeName.isEmpty())
                        out.typesByModule[currentModuleLower].insert(typeName);
                }
            }
        }

        const bool ok = !xr.hasError();
        if (!ok)
            out.filesWithErrors++;

        return ok;
    }

    bool BuildPassA(const Settings& s, PassAResult& out)
    {
        out = PassAResult();

        const QDir root(s.apiMonitorRootDir);
        if (!root.exists())
            return false;

        QT::QVector<QT::QString> files;
        CollectXmlFilesRecursive(s.apiMonitorRootDir, files);

        for (int i = 0; i < files.size(); ++i)
        {
            (void)ParseOneXml_PassA(files[i], s.apiMonitorRootDir, out);
            out.filesProcessed++;
        }

        out.includesUnique = (uint32_t)out.includedFilesAbs.size();
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

        ts << "ApiMonitorDoc Pass A log\n";
        ts << "Generated: " << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n\n";

        ts << "RootDir: " << s.apiMonitorRootDir << "\n";
        ts << "OutputDir: " << s.outputDir << "\n\n";

        ts << "FilesProcessed: " << r.filesProcessed << "\n";
        ts << "FilesWithXmlErrors: " << r.filesWithErrors << "\n\n";

        ts << "IncludesRefsTotal: " << r.includesTotalRefs << "\n";
        ts << "IncludesUnique: " << r.includesUnique << "\n";
        ts << "IncludesMissingFiles: " << r.includesMissingFiles << "\n\n";

        if (!r.missingIncludeSamples.isEmpty())
        {
            ts << "=== Missing include samples (max 50) ===\n";
            for (int i = 0; i < r.missingIncludeSamples.size(); ++i)
                ts << r.missingIncludeSamples[i] << "\n";
            ts << "\n";
        }

        ts << "ModulesTotal: " << r.modulesLower.size() << "\n";

        uint64_t totalApis = 0;
        uint64_t totalTypes = 0;

        QT::QVector<QT::QString> modules = r.modulesLower.values().toVector();
        std::sort(modules.begin(), modules.end());

        for (int i = 0; i < modules.size(); ++i)
        {
            const QT::QString& m = modules[i];
            const int apiCount = r.apisByModule.contains(m) ? r.apisByModule.value(m).size() : 0;
            const int typeCount = r.typesByModule.contains(m) ? r.typesByModule.value(m).size() : 0;

            totalApis += (uint64_t)apiCount;
            totalTypes += (uint64_t)typeCount;
        }

        ts << "ApisTotal: " << totalApis << "\n";
        ts << "TypesTotal: " << totalTypes << "\n\n";

        ts << "=== Per-module summary (module | apis | types) ===\n";
        for (int i = 0; i < modules.size(); ++i)
        {
            const QT::QString& m = modules[i];
            const int apiCount = r.apisByModule.contains(m) ? r.apisByModule.value(m).size() : 0;
            const int typeCount = r.typesByModule.contains(m) ? r.typesByModule.value(m).size() : 0;

            ts << m << " | " << apiCount << " | " << typeCount << "\n";
        }

        ts << "\nDone.\n";
        ts.flush();
        return true;
    }

    // ---------------------------------------
    // Pass B-1: TypeKind
    // ---------------------------------------

    static TypeKind KindFromVariableTypeAttr(const QT::QString& t)
    {
        const QT::QString s = t.trimmed();

        if (s.compare(QLatin1String("Alias"),     Qt::CaseInsensitive) == 0) return TypeKind::Alias;
        if (s.compare(QLatin1String("Pointer"),   Qt::CaseInsensitive) == 0) return TypeKind::Pointer;
        if (s.compare(QLatin1String("Array"),     Qt::CaseInsensitive) == 0) return TypeKind::Array;
        if (s.compare(QLatin1String("Struct"),    Qt::CaseInsensitive) == 0) return TypeKind::Struct;
        if (s.compare(QLatin1String("Union"),     Qt::CaseInsensitive) == 0) return TypeKind::Union;
        if (s.compare(QLatin1String("Interface"), Qt::CaseInsensitive) == 0) return TypeKind::Interface; ///< COM/interface типы.

        return TypeKind::Unknown;
    }

    static const char* KindToString(TypeKind k)
    {
        switch (k)
        {
            case TypeKind::Unknown:   return "Unknown";
            case TypeKind::Alias:     return "Alias";
            case TypeKind::Pointer:   return "Pointer";
            case TypeKind::Array:     return "Array";
            case TypeKind::Struct:    return "Struct";
            case TypeKind::Union:     return "Union";
            case TypeKind::Interface: return "Interface";
            case TypeKind::Enum:      return "Enum";
            case TypeKind::Flags:     return "Flags";
            case TypeKind::Count:     break;
        }
        return "Unknown";
    }

    static void IncKindCount(PassB1Result& out, TypeKind k)
    {
        const uint32_t idx = (uint32_t)k;
        if (idx < (uint32_t)TypeKind::Count)
            out.kindCounts[idx]++;
    }

    static uint32_t GetKindCount(const PassB1Result& r, TypeKind k)
    {
        const uint32_t idx = (uint32_t)k;
        if (idx < (uint32_t)TypeKind::Count)
            return r.kindCounts[idx];
        return 0;
    }

    static void RecordUnknownTypeAttr(PassB1Result& out, const QT::QString& rawTypeAttr)
    {
        QT::QString raw = rawTypeAttr.trimmed(); ///< Исходная строка Type (обрезаем пробелы).
        if (raw.isEmpty())
            raw = QLatin1String("<empty>"); ///< Пустое значение Type тоже фиксируем явно.

        QT::QString key = raw.toLower(); ///< Ключ для агрегации (case-insensitive).

        out.unknownTypeAttrCounts[key]++; ///< Счётчик попаданий Unknown по конкретной строке Type.

        if (!out.unknownTypeAttrOriginal.contains(key))
            out.unknownTypeAttrOriginal.insert(key, raw); ///< Запоминаем первое оригинальное написание.
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
        TypeRecord cur;          ///< Текущая собираемая запись Variable.
        bool sawEnum = false;    ///< Внутри Variable встретился <Enum>.
        bool sawFlag = false;    ///< Внутри Variable встретился <Flag>.

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
                        sawEnum = false;
                        sawFlag = false;

                        cur = TypeRecord();
                        cur.moduleLower = currentModuleLower;

                        cur.name  = xr.attributes().value(QLatin1String("Name")).toString().trimmed();
                        cur.base  = xr.attributes().value(QLatin1String("Base")).toString().trimmed();
                        cur.count = xr.attributes().value(QLatin1String("Count")).toString().trimmed();

                        const QT::QString t = xr.attributes().value(QLatin1String("Type")).toString();
                        cur.typeAttr = t.trimmed(); ///< Сохраняем исходную строку Type для диагностики.
                        cur.kind = KindFromVariableTypeAttr(cur.typeAttr);
                    }
                    else
                    {
                        insideVariable = false;
                    }
                }
                else if (insideVariable)
                {
                    if (name == QLatin1String("Enum"))
                        sawEnum = true;
                    else if (name == QLatin1String("Flag"))
                        sawFlag = true;
                }
            }
            else if (xr.isEndElement())
            {
                const QT::QStringRef name = xr.name();

                if (name == QLatin1String("Variable") && insideVariable)
                {
                    if (sawFlag)
                        cur.kind = TypeKind::Flags;
                    else if (sawEnum)
                        cur.kind = TypeKind::Enum;

                    if (cur.kind == TypeKind::Unknown)
                        RecordUnknownTypeAttr(out, cur.typeAttr);

                    if (!cur.name.isEmpty())
                    {
                        out.types.push_back(cur);
                        IncKindCount(out, cur.kind);
                    }

                    insideVariable = false;
                }
            }
        }

        const bool ok = !xr.hasError();
        if (!ok)
            out.filesWithErrors++;

        return ok;
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

        ts << "ApiMonitorDoc Pass B-1 (Type kind) log\n";
        ts << "Generated: " << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n\n";

        ts << "RootDir: " << s.apiMonitorRootDir << "\n";
        ts << "OutputDir: " << s.outputDir << "\n\n";

        ts << "FilesProcessed: " << r.filesProcessed << "\n";
        ts << "FilesWithXmlErrors: " << r.filesWithErrors << "\n\n";

        ts << "TypesTotal: " << r.types.size() << "\n\n";

        ts << "=== Kind counts ===\n";
        ts << "Unknown: "   << GetKindCount(r, TypeKind::Unknown)   << "\n";
        ts << "Alias: "     << GetKindCount(r, TypeKind::Alias)     << "\n";
        ts << "Pointer: "   << GetKindCount(r, TypeKind::Pointer)   << "\n";
        ts << "Array: "     << GetKindCount(r, TypeKind::Array)     << "\n";
        ts << "Struct: "    << GetKindCount(r, TypeKind::Struct)    << "\n";
        ts << "Union: "     << GetKindCount(r, TypeKind::Union)     << "\n";
        ts << "Interface: " << GetKindCount(r, TypeKind::Interface) << "\n";
        ts << "Enum: "      << GetKindCount(r, TypeKind::Enum)      << "\n";
        ts << "Flags: "     << GetKindCount(r, TypeKind::Flags)     << "\n";

        const uint32_t unknownTotal = GetKindCount(r, TypeKind::Unknown);
        if (unknownTotal > 0 && !r.unknownTypeAttrCounts.isEmpty())
        {
            ts << "\n=== Unknown Variable@Type strings (top 50) ===\n";
            ts << "UnknownTotal: " << unknownTotal << "\n";
            ts << "UnknownDistinct: " << r.unknownTypeAttrCounts.size() << "\n\n";

            QT::QVector<std::pair<QT::QString, uint32_t>> items;
            items.reserve(r.unknownTypeAttrCounts.size());

            for (auto it = r.unknownTypeAttrCounts.constBegin(); it != r.unknownTypeAttrCounts.constEnd(); ++it)
                items.push_back(std::make_pair(it.key(), it.value()));

            std::sort(items.begin(), items.end(),
                      [](const std::pair<QT::QString, uint32_t>& a, const std::pair<QT::QString, uint32_t>& b)
                      {
                          if (a.second != b.second)
                              return a.second > b.second;
                          return a.first < b.first;
                      });

            const int maxItems = 50;
            for (int i = 0; i < items.size() && i < maxItems; ++i)
            {
                const QT::QString& key = items[i].first;
                const uint32_t cnt = items[i].second;

                const QT::QString shown = r.unknownTypeAttrOriginal.contains(key)
                                              ? r.unknownTypeAttrOriginal.value(key)
                                              : key;

                ts << cnt << " | " << shown << "\n";
            }
        }

        ts << "\n=== Samples (first 40 records) ===\n";
        const int maxSamples = 40;
        for (int i = 0; i < r.types.size() && i < maxSamples; ++i)
        {
            const TypeRecord& tr = r.types[i];
            ts << tr.moduleLower << " | " << KindToString(tr.kind) << " | " << tr.name;

            if (tr.kind == TypeKind::Unknown)
                ts << " | Type=" << (tr.typeAttr.isEmpty() ? QLatin1String("<empty>") : tr.typeAttr);

            if (!tr.base.isEmpty())
                ts << " | Base=" << tr.base;

            if (!tr.count.isEmpty())
                ts << " | Count=" << tr.count;

            ts << "\n";
        }

        ts << "\nDone.\n";
        ts.flush();
        return true;
    }

    // ---------------------------------------
    // Pass B-2: Fields Struct/Union
    // ---------------------------------------

    static void RecordFieldType(PassB2Result& out, const QT::QString& rawFieldType)
    {
        QT::QString raw = rawFieldType.trimmed(); ///< Field@Type как есть (trim).
        if (raw.isEmpty())
            raw = QLatin1String("<empty>"); ///< Даже пустое значение Type учитываем.

        QT::QString key = raw.toLower(); ///< Ключ для агрегации.
        out.fieldTypeCounts[key]++;      ///< Инкремент счётчика по типу поля.

        if (!out.fieldTypeOriginal.contains(key))
            out.fieldTypeOriginal.insert(key, raw); ///< Первое оригинальное написание.
    }

    static bool ParseOneXml_PassB2(const QT::QString& filePath, PassB2Result& out)
    {
        QFile f(filePath);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        QXmlStreamReader xr(&f);

        bool insideModule = false;
        QT::QString currentModuleLower;

        bool insideVarStructUnion = false; ///< Внутри Variable типа Struct/Union.
        TypeKind currentVarKind = TypeKind::Unknown; ///< Struct/Union.
        QT::QString currentVarName; ///< Variable@Name текущего Struct/Union.

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
                    insideVarStructUnion = false;
                    currentVarKind = TypeKind::Unknown;
                    currentVarName.clear();

                    if (insideModule && !currentModuleLower.isEmpty())
                    {
                        const QT::QString varType = xr.attributes().value(QLatin1String("Type")).toString().trimmed();
                        const TypeKind k = KindFromVariableTypeAttr(varType);

                        if (k == TypeKind::Struct || k == TypeKind::Union)
                        {
                            insideVarStructUnion = true;
                            currentVarKind = k;
                            currentVarName = xr.attributes().value(QLatin1String("Name")).toString().trimmed();

                            if (k == TypeKind::Struct)
                                out.structTypes++;
                            else
                                out.unionTypes++;
                        }
                    }
                }
                else if (insideVarStructUnion && name == QLatin1String("Field"))
                {
                    const QT::QString fieldType = xr.attributes().value(QLatin1String("Type")).toString();
                    const QT::QString fieldName = xr.attributes().value(QLatin1String("Name")).toString();
                    const QT::QString fieldDisp = xr.attributes().value(QLatin1String("Display")).toString();
                    const QT::QString fieldCnt  = xr.attributes().value(QLatin1String("Count")).toString();

                    out.fieldsTotal++;
                    if (!fieldDisp.trimmed().isEmpty()) out.fieldsWithDisplay++;
                    if (!fieldCnt.trimmed().isEmpty())  out.fieldsWithCount++;

                    RecordFieldType(out, fieldType);

                    if (out.fieldSamples.size() < 60)
                    {
                        QT::QString line;
                        line.reserve(256);

                        line += currentModuleLower;
                        line += QLatin1String(" | ");
                        line += (currentVarKind == TypeKind::Struct) ? QLatin1String("Struct") : QLatin1String("Union");
                        line += QLatin1String(" | ");
                        line += currentVarName;
                        line += QLatin1String(" | Field ");
                        line += fieldType.trimmed();
                        line += QLatin1String(" ");
                        line += fieldName.trimmed();

                        if (!fieldDisp.trimmed().isEmpty())
                        {
                            line += QLatin1String(" | Display=");
                            line += fieldDisp.trimmed();
                        }

                        if (!fieldCnt.trimmed().isEmpty())
                        {
                            line += QLatin1String(" | Count=");
                            line += fieldCnt.trimmed();
                        }

                        out.fieldSamples.push_back(line);
                    }
                }
            }
            else if (xr.isEndElement())
            {
                const QT::QStringRef name = xr.name();
                if (name == QLatin1String("Variable"))
                {
                    insideVarStructUnion = false;
                    currentVarKind = TypeKind::Unknown;
                    currentVarName.clear();
                }
            }
        }

        const bool ok = !xr.hasError();
        if (!ok)
            out.filesWithErrors++;

        return ok;
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

        ts << "ApiMonitorDoc Pass B-2 (Fields Struct/Union) log\n";
        ts << "Generated: " << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n\n";

        ts << "RootDir: " << s.apiMonitorRootDir << "\n";
        ts << "OutputDir: " << s.outputDir << "\n\n";

        ts << "FilesProcessed: " << r.filesProcessed << "\n";
        ts << "FilesWithXmlErrors: " << r.filesWithErrors << "\n\n";

        ts << "StructTypes: " << r.structTypes << "\n";
        ts << "UnionTypes: " << r.unionTypes << "\n";
        ts << "FieldsTotal: " << r.fieldsTotal << "\n";
        ts << "FieldsWithDisplay: " << r.fieldsWithDisplay << "\n";
        ts << "FieldsWithCount: " << r.fieldsWithCount << "\n";
        ts << "DistinctFieldTypes: " << r.fieldTypeCounts.size() << "\n\n";

        if (!r.fieldTypeCounts.isEmpty())
        {
            ts << "=== Top Field@Type (top 40) ===\n";

            QT::QVector<std::pair<QT::QString, uint32_t>> items;
            items.reserve(r.fieldTypeCounts.size());

            for (auto it = r.fieldTypeCounts.constBegin(); it != r.fieldTypeCounts.constEnd(); ++it)
                items.push_back(std::make_pair(it.key(), it.value()));

            std::sort(items.begin(), items.end(),
                      [](const std::pair<QT::QString, uint32_t>& a, const std::pair<QT::QString, uint32_t>& b)
                      {
                          if (a.second != b.second)
                              return a.second > b.second;
                          return a.first < b.first;
                      });

            const int maxItems = 40;
            for (int i = 0; i < items.size() && i < maxItems; ++i)
            {
                const QT::QString& key = items[i].first;
                const uint32_t cnt = items[i].second;

                const QT::QString shown = r.fieldTypeOriginal.contains(key)
                                              ? r.fieldTypeOriginal.value(key)
                                              : key;

                ts << cnt << " | " << shown << "\n";
            }

            ts << "\n";
        }

        if (!r.fieldSamples.isEmpty())
        {
            ts << "=== Field samples (max 60) ===\n";
            for (int i = 0; i < r.fieldSamples.size(); ++i)
                ts << r.fieldSamples[i] << "\n";
            ts << "\n";
        }

        ts << "Done.\n";
        ts.flush();
        return true;
    }

    // --------------------------------------------------------------------
    // Pass SIG-1: input signature
    // --------------------------------------------------------------------

    static QT::QString NormalizeRelPath(const QT::QString& rel)
    {
        QT::QString s = rel;
        s.replace('\\', '/'); ///< Стабильный вид пути.
        return s;
    }

    static void AppendInt64LE(QCryptographicHash& h, int64_t v)
    {
        const char* p = reinterpret_cast<const char*>(&v); ///< Пишем как есть (LE на Windows).
        h.addData(p, (int)sizeof(v));
    }

    static bool HashFileSha1Hex(const QT::QString& filePath, QT::QString& outHex)
    {
        QFile f(filePath);
        if (!f.open(QIODevice::ReadOnly))
            return false;

        QCryptographicHash h(QCryptographicHash::Sha1);
        while (!f.atEnd())
        {
            const QByteArray chunk = f.read(1024 * 128); ///< 128 KB.
            if (chunk.isEmpty() && f.error() != QFile::NoError)
                return false;
            h.addData(chunk);
        }

        outHex = QT::QString::fromLatin1(h.result().toHex());
        return true;
    }

    bool BuildInputSignature(const Settings& s, InputSignatureResult& out)
    {
        out = InputSignatureResult();

        const QDir root(s.apiMonitorRootDir);
        if (!root.exists())
            return false;

        QT::QVector<QT::QString> files;
        CollectXmlFilesRecursive(s.apiMonitorRootDir, files);
        std::sort(files.begin(), files.end()); ///< Стабильный порядок.

        QCryptographicHash combined(QCryptographicHash::Sha1);

        for (int i = 0; i < files.size(); ++i)
        {
            const QT::QString& absPath = files[i];

            InputFileSignature rec;
            rec.relPath = NormalizeRelPath(root.relativeFilePath(absPath));

            const QFileInfo fi(absPath);
            rec.sizeBytes = (int64_t)fi.size();
            rec.mtimeUtcMs = (int64_t)fi.lastModified().toUTC().toMSecsSinceEpoch();

            out.totalBytes += rec.sizeBytes;
            out.filesProcessed++;

            QT::QString sha1Hex;
            if (!HashFileSha1Hex(absPath, sha1Hex))
            {
                out.filesWithErrors++;
                rec.sha1Hex = QLatin1String("<error>");
            }
            else
            {
                rec.sha1Hex = sha1Hex;
            }

            out.files.push_back(rec);

            // --- combined hash ---
            const QByteArray pathUtf8 = rec.relPath.toUtf8();
            combined.addData(pathUtf8);
            combined.addData("\0", 1);

            AppendInt64LE(combined, rec.sizeBytes);
            AppendInt64LE(combined, rec.mtimeUtcMs);

            const QByteArray shaBytes = QByteArray::fromHex(rec.sha1Hex.toLatin1());
            combined.addData(shaBytes);
        }

        out.combinedSha1Hex = QT::QString::fromLatin1(combined.result().toHex());
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

        const QT::QString logPath = outDir.filePath(QLatin1String("apimon_inputs_sig.txt"));

        QFile lf(logPath);
        if (!lf.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

        QTextStream ts(&lf);
        ts.setCodec("UTF-8");

        ts << "ApiMonitorDoc Inputs Signature log\n";
        ts << "Generated: " << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n\n";

        ts << "RootDir: " << s.apiMonitorRootDir << "\n";
        ts << "OutputDir: " << s.outputDir << "\n\n";

        ts << "FilesProcessed: " << r.filesProcessed << "\n";
        ts << "FilesWithErrors: " << r.filesWithErrors << "\n";
        ts << "TotalBytes: " << r.totalBytes << "\n";
        ts << "CombinedSHA1: " << r.combinedSha1Hex << "\n\n";

        const int maxSamples = 40;
        ts << "=== Samples (first " << maxSamples << " files) ===\n";
        for (int i = 0; i < r.files.size() && i < maxSamples; ++i)
        {
            const InputFileSignature& f = r.files[i];
            ts << f.relPath
               << " | Size=" << f.sizeBytes
               << " | MTimeUtcMs=" << f.mtimeUtcMs
               << " | SHA1=" << f.sha1Hex
               << "\n";
        }

        ts << "\nDone.\n";
        ts.flush();
        return true;
    }

    // --------------------------------------------------------------------
    // Cache BIN-0: header-only cache рядом с плагином
    // --------------------------------------------------------------------

    static uint32_t MakeMagic_APMC()
    {
        // 'A''P''M''C' little-endian -> 0x434D5041
        return 0x434D5041U;
    }

    static void WriteU32LE(QFile& f, uint32_t v)
    {
        char b[4];
        b[0] = (char)(v & 0xFF);
        b[1] = (char)((v >> 8) & 0xFF);
        b[2] = (char)((v >> 16) & 0xFF);
        b[3] = (char)((v >> 24) & 0xFF);
        f.write(b, 4);
    }

    static void WriteI64LE(QFile& f, int64_t v)
    {
        char b[8];
        const uint64_t u = (uint64_t)v;
        b[0] = (char)(u & 0xFF);
        b[1] = (char)((u >> 8) & 0xFF);
        b[2] = (char)((u >> 16) & 0xFF);
        b[3] = (char)((u >> 24) & 0xFF);
        b[4] = (char)((u >> 32) & 0xFF);
        b[5] = (char)((u >> 40) & 0xFF);
        b[6] = (char)((u >> 48) & 0xFF);
        b[7] = (char)((u >> 56) & 0xFF);
        f.write(b, 8);
    }

    static bool ReadU32LE(QFile& f, uint32_t& out)
    {
        char b[4];
        if (f.read(b, 4) != 4)
            return false;

        out = (uint32_t)((uint8_t)b[0])
            | ((uint32_t)((uint8_t)b[1]) << 8)
            | ((uint32_t)((uint8_t)b[2]) << 16)
            | ((uint32_t)((uint8_t)b[3]) << 24);
        return true;
    }

    static bool ReadI64LE(QFile& f, int64_t& out)
    {
        char b[8];
        if (f.read(b, 8) != 8)
            return false;

        uint64_t u = 0;
        u |= (uint64_t)(uint8_t)b[0];
        u |= (uint64_t)(uint8_t)b[1] << 8;
        u |= (uint64_t)(uint8_t)b[2] << 16;
        u |= (uint64_t)(uint8_t)b[3] << 24;
        u |= (uint64_t)(uint8_t)b[4] << 32;
        u |= (uint64_t)(uint8_t)b[5] << 40;
        u |= (uint64_t)(uint8_t)b[6] << 48;
        u |= (uint64_t)(uint8_t)b[7] << 56;

        out = (int64_t)u;
        return true;
    }

    QT::QString GetCacheBinPath(const Settings& s)
    {
        QDir d(s.idaPluginsDir);
        return d.filePath(QLatin1String("apimon_cache.bin"));
    }

    bool BuildCacheHeaderFromSignature(const InputSignatureResult& sig, CacheHeader& out)
    {
        out = CacheHeader();

        out.magic = MakeMagic_APMC(); ///< Магия APMC.
        out.version = 1;              ///< header-only v1.
        out.headerSize = (uint32_t)sizeof(CacheHeader);

        out.filesProcessed = sig.filesProcessed;
        out.totalBytes = sig.totalBytes;

        const QByteArray sha = QByteArray::fromHex(sig.combinedSha1Hex.toLatin1());
        if (sha.size() != 20)
            return false;

        for (int i = 0; i < 20; ++i)
            out.combinedSha1[i] = (uint8_t)sha[i];

        out.createdUtcMs = (int64_t)QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
        out.reserved0 = 0;
        out.reserved1 = 0;
        return true;
    }

    bool WriteCacheHeaderBin(const Settings& s, const CacheHeader& ch)
    {
        const QT::QString path = GetCacheBinPath(s);

        QFile f(path);
        if (!f.open(QIODevice::WriteOnly))
            return false;

        WriteU32LE(f, ch.magic);
        WriteU32LE(f, ch.version);
        WriteU32LE(f, ch.headerSize);
        WriteU32LE(f, ch.filesProcessed);
        WriteI64LE(f, ch.totalBytes);

        f.write(reinterpret_cast<const char*>(ch.combinedSha1), 20);

        WriteI64LE(f, ch.createdUtcMs);
        WriteU32LE(f, ch.reserved0);
        WriteU32LE(f, ch.reserved1);

        return (f.error() == QFile::NoError);
    }

    bool ReadCacheHeaderBin(const Settings& s, CacheHeader& out)
    {
        out = CacheHeader();

        const QT::QString path = GetCacheBinPath(s);

        QFile f(path);
        if (!f.open(QIODevice::ReadOnly))
            return false;

        if (!ReadU32LE(f, out.magic)) return false;
        if (!ReadU32LE(f, out.version)) return false;
        if (!ReadU32LE(f, out.headerSize)) return false;
        if (!ReadU32LE(f, out.filesProcessed)) return false;
        if (!ReadI64LE(f, out.totalBytes)) return false;

        if (f.read(reinterpret_cast<char*>(out.combinedSha1), 20) != 20)
            return false;

        if (!ReadI64LE(f, out.createdUtcMs)) return false;
        if (!ReadU32LE(f, out.reserved0)) return false;
        if (!ReadU32LE(f, out.reserved1)) return false;

        return true;
    }

    bool IsCacheHeaderValidForSignature(const CacheHeader& ch, const InputSignatureResult& sig)
    {
        if (ch.magic != MakeMagic_APMC())
            return false;

        if (ch.version != 1)
            return false;

        if (ch.headerSize < (uint32_t)sizeof(CacheHeader))
            return false;

        if (ch.filesProcessed != sig.filesProcessed)
            return false;

        if (ch.totalBytes != sig.totalBytes)
            return false;

        const QByteArray sha = QByteArray::fromHex(sig.combinedSha1Hex.toLatin1());
        if (sha.size() != 20)
            return false;

        for (int i = 0; i < 20; ++i)
        {
            if (ch.combinedSha1[i] != (uint8_t)sha[i])
                return false;
        }

        return true;
    }

} // namespace apimon