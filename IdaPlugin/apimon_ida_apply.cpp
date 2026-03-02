/**
 * @file apimon_ida_apply.cpp
 * @brief Реализация применения ApiMonitorDoc к IDA: MVP (Imports).
 */

#include "apimon_ida_apply.h"

#include <QtCore/QByteArray>
#include <QtCore/QVector>
#include <QtCore/QChar>

#include <ida.hpp>
#include <name.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <bytes.hpp>
#include <funcs.hpp>

namespace apimon_ida
{
    // --------------------------------------------------------------------
    // Helpers
    // --------------------------------------------------------------------

    /**
     * @brief Trim + lower-case.
     */
    static QT::QString ToLowerTrim(const QT::QString& s)
    {
        return s.trimmed().toLower();
    }

    /**
     * @brief Сформировать ключ "dllLower\0nameLower" для точного поиска.
     * @details QChar('\0') внутри QString безопасен: строка хранит длину отдельно.
     */
    static QT::QString MakeExactKey(const QT::QString& dllLower, const QT::QString& apiNameLower)
    {
        QT::QString key = dllLower;
        key.append(QChar('\0'));
        key.append(apiNameLower);
        return key;
    }

    /**
     * @brief Построить одну строку сигнатуры: "RET Name(type p1, type p2)".
     */
    static QT::QString BuildApiSignatureLine(const apimon::ApiFunctionRecord& a)
    {
        QT::QString out;

        if (!a.retType.isEmpty())
            out += a.retType + QLatin1String(" ");
        else
            out += QLatin1String("void ");

        out += a.name;
        out += QLatin1String("(");

        for (int i = 0; i < a.params.size(); ++i)
        {
            const apimon::ApiParamRecord& p = a.params[i];

            if (i != 0)
                out += QLatin1String(", ");

            if (!p.type.isEmpty())
                out += p.type;
            else
                out += QLatin1String("/*?*/");

            if (!p.name.isEmpty())
            {
                out += QLatin1String(" ");
                out += p.name;
            }
        }

        out += QLatin1String(")");
        return out;
    }

    /**
     * @brief Сформировать текст repeatable comment.
     * @details Делаем коротко и с маркером [ApiMon], чтобы потом отличать "наши" комменты.
     */
    static QT::QString BuildRepeatableCommentText(const apimon::ApiFunctionRecord& a)
    {
        QT::QString c;

        c += QLatin1String("[ApiMon] ");
        c += a.moduleLower;
        c += QLatin1String(" :: ");
        c += a.name;

        c += QLatin1String("\n[ApiMon] ");
        c += BuildApiSignatureLine(a);

        // links пока пустые — не выводим.
        // if (!a.links.isEmpty())
        // {
        //     c += QLatin1String("\n[ApiMon] links: ");
        //     c += a.links;
        // }

        return c;
    }

    /**
     * @brief Проверить, можно ли писать наш коммент в repeatable поле.
     * @param existingExisting Существующий repeatable comment (может быть пустой).
     * @param overwriteExisting Разрешено ли перезаписывать "чужие" комменты.
     * @return true если можно писать.
     *
     * Логика:
     * - если пусто -> можно
     * - если уже есть [ApiMon] -> можно (обновить)
     * - иначе -> можно только если overwriteExisting=true
     */
    static bool CanWriteRepeatableComment(const qstring& existing, bool overwriteExisting)
    {
        if (existing.empty())
            return true;

        // если уже наш — можно обновлять всегда
        if (existing.find("[ApiMon]") != qstring::npos)
            return true;

        return overwriteExisting;
    }

    /**
     * @brief Поставить repeatable comment на адрес/функцию.
     * @param ea Адрес импорта (thunk).
     * @param text Текст коммента (UTF-8).
     * @param overwriteExisting Разрешение перезаписи чужих комментов.
     * @param outSkippedExisting [out] увеличиваем, если пропустили из-за чужого коммента.
     * @return true если коммент записали.
     */
    static bool SetRepeatableCommentAt(ea_t ea,
                                      const QT::QString& text,
                                      bool overwriteExisting,
                                      int* outSkippedExisting)
    {
        qstring existing;

        // Для функции удобнее читать func-cmt; для не-функции — обычный.
        func_t* f = get_func(ea);
        if (f != nullptr)
            get_func_cmt(&existing, f, /*repeatable=*/true);
        else
            get_cmt(&existing, ea, /*repeatable=*/true);

        if (!CanWriteRepeatableComment(existing, overwriteExisting))
        {
            if (outSkippedExisting)
                (*outSkippedExisting)++;
            return false;
        }

        const QByteArray u8 = text.toUtf8();
        bool ok = false;

        if (f != nullptr)
            ok = set_func_cmt(f, u8.constData(), /*repeatable=*/true);
        else
            ok = set_cmt(ea, u8.constData(), /*repeatable=*/true);

        return ok;
    }

    // --------------------------------------------------------------------
    // Index build (dll+name -> apiIndex)
    // --------------------------------------------------------------------

    /**
     * @brief Построить индекс точного поиска: dllLower+nameLower -> index in db.apis.
     */
    static void BuildExactIndex(const apimon::DataBinDb& db, QHash<QT::QString, int>& outExactIndex)
    {
        outExactIndex.clear();
        outExactIndex.reserve(db.apis.size() * 2);

        for (int i = 0; i < db.apis.size(); ++i)
        {
            const apimon::ApiFunctionRecord& a = db.apis[i];

            const QT::QString dllLower  = ToLowerTrim(a.moduleLower); // в базе уже lower, но на всякий
            const QT::QString nameLower = ToLowerTrim(a.name);

            if (dllLower.isEmpty() || nameLower.isEmpty())
                continue;

            const QT::QString key = MakeExactKey(dllLower, nameLower);

            // MVP: при дубле оставляем первую запись.
            if (!outExactIndex.contains(key))
                outExactIndex.insert(key, i);
        }
    }

    // --------------------------------------------------------------------
    // IDA imports enumeration
    // --------------------------------------------------------------------

    struct ImportEnumCtx
    {
        const apimon::DataBinDb* db = nullptr;         ///< База apimon.
        const QHash<QT::QString, int>* exactIndex = nullptr; ///< Индекс точного поиска.
        QT::QString curDllLower;                        ///< Текущий dllLower (для enum_import_names).
        ApplyStats stats;                              ///< Статистика.
        bool overwriteExisting = false;                 ///< Разрешено ли перезаписывать чужие комменты.
    };

    /**
     * @brief Callback IDA для enum_import_names().
     * @return 1 чтобы продолжать перечисление.
     */
    static int idaapi EnumImportCb(ea_t ea, const char* name, uval_t /*ordinal*/, void* userData)
    {
        ImportEnumCtx* ctx = (ImportEnumCtx*)userData;
        if (ctx == nullptr || ctx->db == nullptr || ctx->exactIndex == nullptr)
            return 1;

        if (name == nullptr || name[0] == '\0')
            return 1;

        const QT::QString apiNameLower = ToLowerTrim(QT::QString::fromLatin1(name));
        const QT::QString key = MakeExactKey(ctx->curDllLower, apiNameLower);

        const auto it = ctx->exactIndex->find(key);
        if (it == ctx->exactIndex->end())
            return 1;

        ctx->stats.matched++;

        const int apiIndex = it.value();
        if (apiIndex < 0 || apiIndex >= ctx->db->apis.size())
            return 1;

        const apimon::ApiFunctionRecord& a = ctx->db->apis[apiIndex];

        const QT::QString cmt = BuildRepeatableCommentText(a);

        // Пишем comment, если можно (и считаем пропуски).
        const bool wrote = SetRepeatableCommentAt(ea, cmt, ctx->overwriteExisting, &ctx->stats.skippedExisting);
        if (wrote)
        {
            ctx->stats.commentsAdded++;

            // В консоль — адреса ВСЕХ добавленных комментов, чтобы можно было просмотреть.
            // %a — формат адреса IDA
            msg("[ApiMon] cmt: %a  %s!%s\n",
                ea,
                ctx->curDllLower.toUtf8().constData(),
                name);
        }

        return 1;
    }

    // --------------------------------------------------------------------
    // Public entry
    // --------------------------------------------------------------------

    bool ApplyApiMonCommentsToImports(const apimon::DataBinDb& db, ApplyStats* outStats, bool overwriteExisting)
    {
        if (outStats)
            *outStats = ApplyStats();

        // 1) Индекс по базе
        QHash<QT::QString, int> exactIndex;
        BuildExactIndex(db, exactIndex);

        // 2) Перебор import-модулей IDA
        const int qty = get_import_module_qty();
        if (qty <= 0)
        {
            msg("[ApiMon] imports: none\n");
            return true;
        }

        ImportEnumCtx ctx;
        ctx.db = &db;
        ctx.exactIndex = &exactIndex;
        ctx.overwriteExisting = overwriteExisting;

        for (int i = 0; i < qty; ++i)
        {
			qstring modName;
			if (!get_import_module_name(&modName, i))
				continue;

            // IDA возвращает "KERNEL32" / "KERNEL32.DLL" / "kernel32.dll" и т.п.
            ctx.curDllLower = apimon::NormalizeModuleNameLower(QString::fromLatin1(modName.c_str()));
            if (ctx.curDllLower.isEmpty())
                continue;

            // enum_import_names вызывает callback для каждого импорта
            enum_import_names(i, EnumImportCb, &ctx);
        }

        // Итог в консоль
        msg("[ApiMon] imports: matched=%d, commentsAdded=%d, skippedExisting=%d\n",
            ctx.stats.matched,
            ctx.stats.commentsAdded,
            ctx.stats.skippedExisting);

        if (outStats)
            *outStats = ctx.stats;

        return true;
    }

} // namespace apimon_ida