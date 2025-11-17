#pragma once

/**
* \file Settings.h
* \brief Заголовок подсистемы настроек плагина: единая точка доступа к QSettings.
*
* Подсистема инкапсулирует хранение и чтение настроек через класс Settings.
* При первой инициализации считывается снапшот (SettingsState), далее доступ идёт из памяти.
* Сеттеры немедленно синхронизируют изменения в QSettings.
*
* Важно: Qt у тебя собран с -qtnamespace QT, поэтому подключается QT_USE_NAMESPACE.
*/

#include <memory>
#include <mutex>
#include <string>
#include <cstdint>
#include <vector>

#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QVariant>

#ifndef SETTINGS_EXPORT
#define SETTINGS_EXPORT
#endif

// Учитываем -qtnamespace QT (Qt 5.6.3): макрос подключит using namespace QT;
QT_USE_NAMESPACE

/**
* \struct SettingsState
* \brief Снимок (кэш) текущих настроек, с которыми работает плагин в рантайме.
*
* Хранит все опции, к которым нужен быстрый доступ без постоянного чтения QSettings.
* При запуске плагина заполняется из QSettings (Settings::init()), далее геттеры читают из этой структуры.
* Сеттеры обновляют структуру и немедленно пишут в QSettings.
*/
struct SettingsState
{
	// === Группа features ===
	bool start_after_debug = false;          ///< \brief Автозапуск логики после старта отладчика.
	bool coloring_enabled = false;           ///< \brief Включена ли подсветка вызовов/элементов в графах.
	bool print_info_enabled = false;         ///< \brief Главный флаг "Print info".
	bool print_info_function_data = false;   ///< \brief Детализация: печатать FunctionData.
	bool print_info_mangled_name = false;    ///< \brief Детализация: печатать MangledName.
	bool print_info_output_cleaning = false; ///< \brief Детализация: очищать/нормализовать вывод.
	bool print_info_container_size = false;  ///< \brief Детализация: печатать размеры контейнеров.

	bool fixed_location = false;             ///< \brief Фиксировать положение окна относительно основного вида.
	bool scylla_enabled = false;             ///< \brief Флаг интеграции со Scylla (зарезервировано).

											 // === Группа db ===
	QString mssql_instance;                  ///< \brief Имя экземпляра MSSQL (строка подключения/алиас).

											 // === Группа paths ===
	QString notepad_file_path;               ///< \brief Полный путь к файлу заметок (если пусто — будет определён по умолчанию).

											 // === Группа export ===
	QString export_last_dir;                 ///< \brief Последний каталог экспорта (BinExport/прочие выгрузки).

											 // === Группа ui ===
	QByteArray start_window_geometry;        ///< \brief Геометрия стартового окна (saveGeometry()).
	QByteArray settings_window_geometry;     ///< \brief Геометрия окна настроек.
	QByteArray notepad_window_geometry;      ///< \brief Геометрия окна заметок.

											 // === Прочее ===
	int notepad_autosave_ms = 10000;         ///< \brief Интервал автосохранения заметок в миллисекундах.
	int notepad_tab_width = 4;               ///< \brief Ширина табуляции для заметок (кол-во пробелов).
};

/**
* \class Settings
* \brief Единая точка доступа к настройкам плагина.
*
* Класс скрывает QSettings внутри реализации, предоставляет строго типизированные
* геттеры/сеттеры, хранит кэш (SettingsState) и синхронизирует изменения.
*
* Использование:
* \code
*   Settings::init();                  // при старте плагина
*   bool coloring = Settings::getColoringEnabled();
*   Settings::setColoringEnabled(true);
*   Settings::shutdown();              // при выгрузке плагина
* \endcode
*/
class SETTINGS_EXPORT Settings
{
public:
	/**
	* \brief Инициализирует подсистему настроек и заполняет кэш из QSettings.
	*
	* Безопасно вызывать повторно: повторный вызов перезагрузит снапшот из хранилища.
	* Использует группировку ключей (ui/, features/, db/, paths/, export/).
	*/
	static void init();

	/**
	* \brief Финализирует подсистему (синхронизирует и освобождает ресурсы).
	*
	* Вызывать при завершении работы плагина. Если изменений не было — безопасно.
	*/
	static void shutdown();

	// === Геттеры ===

	/// \brief Включён ли автозапуск после старта отладчика.
	static bool getStartAfterDebug();

	/// \brief Включена ли подсветка элементов (highlight).
	static bool getColoringEnabled();

	/// \brief Главный флаг печати служебной информации.
	static bool getPrintInfoEnabled();

	/// \brief Детализация печати: FunctionData.
	static bool getPrintInfoFunctionData();

	/// \brief Детализация печати: MangledName.
	static bool getPrintInfoMangledName();

	/// \brief Детализация печати: OutputCleaning.
	static bool getPrintInfoOutputCleaning();

	/// \brief Детализация печати: ContainerSize.
	static bool getPrintInfoContainerSize();

	/// \brief Фиксировать ли положение окна.
	static bool getFixedLocation();

	/// \brief Флаг интеграции со Scylla (зарезервировано).
	static bool getScyllaEnabled();

	/// \brief Имя экземпляра MSSQL.
	static QString getMSSQLInstance();

	/// \brief Полный путь к файлу заметок.
	static QString getNotepadFilePath();

	/// \brief Последний каталог экспорта.
	static QString getExportLastDir();

	/// \brief Геометрия стартового окна.
	static QByteArray getStartWindowGeometry();

	/// \brief Геометрия окна настроек.
	static QByteArray getSettingsWindowGeometry();

	/// \brief Геометрия окна заметок.
	static QByteArray getNotepadWindowGeometry();

	/// \brief Интервал автосохранения заметок (мс).
	static int getNotepadAutosaveMs();

	/// \brief Ширина табуляции (кол-во пробелов).
	static int getNotepadTabWidth();

	// === Сеттеры ===

	/// \brief Устанавливает флаг автозапуска после старта отладчика.
	static void setStartAfterDebug(bool value);

	/// \brief Включает/выключает подсветку.
	static void setColoringEnabled(bool value);

	/// \brief Устанавливает главный флаг печати служебной информации.
	static void setPrintInfoEnabled(bool value);

	/// \brief Устанавливает детализацию печати: FunctionData.
	static void setPrintInfoFunctionData(bool value);

	/// \brief Устанавливает детализацию печати: MangledName.
	static void setPrintInfoMangledName(bool value);

	/// \brief Устанавливает детализацию печати: OutputCleaning.
	static void setPrintInfoOutputCleaning(bool value);

	/// \brief Устанавливает детализацию печати: ContainerSize.
	static void setPrintInfoContainerSize(bool value);

	/// \brief Фиксировать ли положение окна.
	static void setFixedLocation(bool value);

	/// \brief Включает/выключает Scylla-интеграцию (зарезервировано).
	static void setScyllaEnabled(bool value);

	/// \brief Сохраняет имя MSSQL-инстанса.
	static void setMSSQLInstance(const QString& instance);

	/// \brief Путь к файлу заметок.
	static void setNotepadFilePath(const QString& path);

	/// \brief Последний каталог экспорта.
	static void setExportLastDir(const QString& dir);

	/// \brief Сохраняет геометрию стартового окна.
	static void setStartWindowGeometry(const QByteArray& geometry);

	/// \brief Сохраняет геометрию окна настроек.
	static void setSettingsWindowGeometry(const QByteArray& geometry);

	/// \brief Сохраняет геометрию окна заметок.
	static void setNotepadWindowGeometry(const QByteArray& geometry);

	/// \brief Интервал автосохранения заметок (мс).
	static void setNotepadAutosaveMs(int ms);

	/// \brief Ширина табуляции (кол-во пробелов).
	static void setNotepadTabWidth(int width);

	/**
	* \brief Возвращает текущий снапшот настроек (копия).
	* \return Копия структуры SettingsState.
	*/
	static SettingsState state();

private:
	// Закрытый конструктор: используем только статический интерфейс
	Settings() = default;

	// === Внутренние помощники ===
	static void ensureInited_();                 ///< \brief Гарантирует, что init() уже вызывался.
	static void loadFromQSettings_();            ///< \brief Загружает state_ из QSettings.
	static void writeToQSettings_();             ///< \brief Полная синхронизация state_ -> QSettings.
	static void setAndSync_(const char* key, const QVariant& value); ///< \brief Запись одного ключа в QSettings с sync().

																	 // === Ключи/группы в QSettings (оставлены читаемыми; при необходимости поправишь строки) ===
	static const char* GROUP_FEATURES;           ///< "features/"
	static const char* GROUP_DB;                 ///< "db/"
	static const char* GROUP_PATHS;              ///< "paths/"
	static const char* GROUP_EXPORT;             ///< "export/"
	static const char* GROUP_UI;                 ///< "ui/"

	static const char* KEY_START_AFTER_DEBUG;            ///< "features/StartAfterDebug"
	static const char* KEY_COLORING_ENABLED;             ///< "features/Coloring"
	static const char* KEY_PRINT_INFO_ENABLED;           ///< "features/PrintInfo"
	static const char* KEY_PRINT_INFO_FUNC_DATA;         ///< "features/PrintInfo.FunctionData"
	static const char* KEY_PRINT_INFO_MANGLED_NAME;      ///< "features/PrintInfo.MangledName"
	static const char* KEY_PRINT_INFO_OUTPUT_CLEANING;   ///< "features/PrintInfo.OutputCleaning"
	static const char* KEY_PRINT_INFO_CONTAINER_SIZE;    ///< "features/PrintInfo.ContainerSize"

	static const char* KEY_FIXED_LOCATION;               ///< "features/FixedLocation"
	static const char* KEY_SCYLLA_ENABLED;               ///< "features/Scylla"

	static const char* KEY_MSSQL_INSTANCE;               ///< "db/MSSQL.Instance"

	static const char* KEY_NOTEPAD_FILE_PATH;            ///< "paths/NotepadFile"
	static const char* KEY_EXPORT_LAST_DIR;              ///< "export/LastDir"

	static const char* KEY_START_WINDOW_GEOM;            ///< "ui/StartWindow.Geometry"
	static const char* KEY_SETTINGS_WINDOW_GEOM;         ///< "ui/SettingsWindow.Geometry"
	static const char* KEY_NOTEPAD_WINDOW_GEOM;          ///< "ui/NotepadWindow.Geometry"

	static const char* KEY_NOTEPAD_AUTOSAVE_MS;          ///< "features/Notepad.AutoSaveMs"
	static const char* KEY_NOTEPAD_TAB_WIDTH;            ///< "features/Notepad.TabWidth"

														 // === Состояние и синхронизация ===
	static std::unique_ptr<QSettings> qsettings_;  ///< \brief Реальный backend QSettings.
	static SettingsState state_;                   ///< \brief Кэш настроек, актуальный в рантайме.
	static std::mutex mtx_;                        ///< \brief Защита доступа к state_/qsettings_.

												   // === Параметры QSettings ===
	static const char* ORG_NAME;                   ///< \brief Организация (пример: "QtSetting" из твоего кода).
	static const char* APP_NAME;                   ///< \brief Приложение (пример: "BlaBlaBla" из твоего кода).
};

