#pragma once
/**
* @file apimon_ida_apply.h
* @brief Применение базы ApiMonitorDoc (apimon_data.bin) к текущему IDB (IDA Pro).
* @details
* MVP: Imports (импортируемые функции), Exports (entry points) и call-сайты на импорты.
* Для каждого совпадения (dll/module + name) ищем запись в apimon::DataBinDb и ставим repeatable comment.
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
		int commentsAdded = 0;     ///< Сколько комментов реально записано.
		int matched = 0;           ///< Сколько сущностей нашли в базе (матч по module+name).
		int skippedExisting = 0;   ///< Сколько пропущено из-за существующего "чужого" коммента.
		int skippedAmbiguous = 0;  ///< Сколько пропущено из-за неоднозначности (в текущей логике почти не используется).
	};

	/**
	* @brief Применить комментарии ApiMon к импортам текущего IDB.
	* @param db Загруженная база из apimon_data.bin.
	* @param outStats[out] Статистика, может быть nullptr.
	* @param overwriteExisting
	* - false: не трогать существующие комменты, если они не наши.
	* - true : перезаписывать existing repeatable comment (осторожно).
	* @return true если обход imports прошёл без фатальных ошибок.
	*/
	bool ApplyApiMonCommentsToImports(const apimon::DataBinDb& db, ApplyStats* outStats = nullptr, bool overwriteExisting = false);

	/**
	* @brief Применить комментарии ApiMon к экспортам (entry points) текущего IDB.
	* @details Берём entry points (get_entry_qty/get_entry) и матчим по moduleLower (имя текущего файла) + name.
	* @param db Загруженная база из apimon_data.bin.
	* @param outStats[out] Статистика, может быть nullptr.
	* @param overwriteExisting см. ApplyApiMonCommentsToImports().
	* @return true если обход прошёл без фатальных ошибок.
	*/
	bool ApplyApiMonCommentsToExports(const apimon::DataBinDb& db, ApplyStats* outStats = nullptr, bool overwriteExisting = false);

	/**
	* @brief Применить комментарии ApiMon к call-сайтам, которые вызывают импортируемые функции.
	* @details
	* Находим импорт (thunk) как в ApplyApiMonCommentsToImports(), но вместо thunk-адреса
	* обходим все code-xref'ы на thunk и ставим коммент в месте вызова (xb.from).
	* @param db Загруженная база из apimon_data.bin.
	* @param outStats[out] Статистика, может быть nullptr.
	* @param overwriteExisting см. ApplyApiMonCommentsToImports().
	* @return true если обход прошёл без фатальных ошибок.
	*/
	bool ApplyApiMonCommentsToImportCalls(const apimon::DataBinDb& db, ApplyStats* outStats = nullptr, bool overwriteExisting = false);

} // namespace apimon_ida