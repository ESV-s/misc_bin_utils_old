#pragma once

/**
 * @file apimon_ida_apply.h
 * @brief Применение базы ApiMonitorDoc (apimon_data.bin) к текущему IDB (IDA Pro).
 * @details
 *  MVP: только Imports (импортируемые функции).
 *  Для каждого импорта (dll + name) ищем запись в apimon::DataBinDb и ставим repeatable comment.
 */

#include <QtCore/QString>
#include <QtCore/QHash>

#include "api_monitor.h" // apimon::DataBinDb, NormalizeModuleNameLower(), структуры API

namespace apimon_ida
{
    /**
     * @brief Статистика применения комментариев.
     */
    struct ApplyStats
    {
        int commentsAdded = 0;      ///< Сколько комментов реально записано.
        int matched = 0;            ///< Сколько импортов нашли в базе (матч по dll+name).
        int skippedExisting = 0;    ///< Сколько пропущено из-за существующего "чужого" коммента.
        int skippedAmbiguous = 0;   ///< Сколько пропущено из-за неоднозначности (в MVP почти не используется).
    };

    /**
     * @brief Применить комментарии ApiMon к импортам текущего IDB.
     * @param db Загруженная база из apimon_data.bin.
     * @param outStats[out] Статистика, может быть nullptr.
     * @param overwriteExisting
     *  - false: не трогать существующие комменты, если они не наши.
     *  - true : перезаписывать existing repeatable comment (осторожно).
     * @return true если обход imports прошёл без фатальных ошибок.
     */
    bool ApplyApiMonCommentsToImports(const apimon::DataBinDb& db, ApplyStats* outStats = nullptr, bool overwriteExisting = false);

} // namespace apimon_ida