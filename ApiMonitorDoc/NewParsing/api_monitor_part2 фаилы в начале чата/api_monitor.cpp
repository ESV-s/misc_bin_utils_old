#include "api_monitor.h"

#include <QTCore/QDir>
#include <QTCore/QDirIterator>
#include <QTCore/QFile>
#include <QTCore/QFileInfo>
#include <QTCore/QDateTime>
#include <QTCore/QTextStream>
#include <QTCore/QXmlStreamReader>

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

    static TypeKind KindFromVariableTypeAttr(const QT::QString& t)
    {
        const QT::QString s = t.trimmed();

        if (s.compare(QLatin1String("Alias"),   Qt::CaseInsensitive) == 0) return TypeKind::Alias;
        if (s.compare(QLatin1String("Pointer"), Qt::CaseInsensitive) == 0) return TypeKind::Pointer;
        if (s.compare(QLatin1String("Array"),   Qt::CaseInsensitive) == 0) return TypeKind::Array;
        if (s.compare(QLatin1String("Struct"),  Qt::CaseInsensitive) == 0) return TypeKind::Struct;
        if (s.compare(QLatin1String("Union"),   Qt::CaseInsensitive) == 0) return TypeKind::Union;

        return TypeKind::Unknown;
    }

    static const char* KindToString(TypeKind k)
    {
        switch (k)
        {
            case TypeKind::Unknown: return "Unknown";
            case TypeKind::Alias:   return "Alias";
            case TypeKind::Pointer: return "Pointer";
            case TypeKind::Array:   return "Array";
            case TypeKind::Struct:  return "Struct";
            case TypeKind::Union:   return "Union";
            case TypeKind::Enum:    return "Enum";
            case TypeKind::Flags:   return "Flags";
            case TypeKind::Count:   break;
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
                        cur.kind = KindFromVariableTypeAttr(t);
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
        ts << "Unknown: " << GetKindCount(r, TypeKind::Unknown) << "\n";
        ts << "Alias: "   << GetKindCount(r, TypeKind::Alias)   << "\n";
        ts << "Pointer: " << GetKindCount(r, TypeKind::Pointer) << "\n";
        ts << "Array: "   << GetKindCount(r, TypeKind::Array)   << "\n";
        ts << "Struct: "  << GetKindCount(r, TypeKind::Struct)  << "\n";
        ts << "Union: "   << GetKindCount(r, TypeKind::Union)   << "\n";
        ts << "Enum: "    << GetKindCount(r, TypeKind::Enum)    << "\n";
        ts << "Flags: "   << GetKindCount(r, TypeKind::Flags)   << "\n";

        ts << "\n=== Samples (first 40 records) ===\n";
        const int maxSamples = 40;
        for (int i = 0; i < r.types.size() && i < maxSamples; ++i)
        {
            const TypeRecord& tr = r.types[i];
            ts << tr.moduleLower << " | " << KindToString(tr.kind) << " | " << tr.name;

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

} // namespace apimon