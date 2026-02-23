#pragma once


/// \file Settings.h
/// \brief \n Заголовок подсистемы настроек плагина: единая точка доступа к QSettings. \n
///
/// Подсистема инкапсулирует хранение и чтение настроек через класс Settings.
/// При первой инициализации считывается снапшот (SettingsState), далее доступ идёт из памяти.
/// Сеттеры немедленно синхронизируют изменения в QSettings.
///
/// Важно: Qt у тебя собран с -qtnamespace QT, поэтому подключается QT_USE_NAMESPACE.

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


/// \struct SettingsState
/// \brief \n Снимок (кэш) текущих настроек, с которыми работает плагин в рантайме. \n
///
/// Хранит все опции, к которым нужен быстрый доступ без постоянного чтения QSettings.
/// При запуске плагина заполняется из QSettings (Settings::init()), далее геттеры читают из этой структуры.
/// Сеттеры обновляют структуру и немедленно пишут в QSettings.
struct SettingsState
{
	// === Группа features ===
	bool start_after_debug = false;          ///< \brief \n Автозапуск логики после старта отладчика. \n
	bool coloring_enabled = false;           ///< \brief \n Включена ли подсветка вызовов/элементов в графах. \n
	bool print_info_enabled = false;         ///< \brief \n Главный флаг "Print info". \n
	bool print_info_function_data = false;   ///< \brief \n Детализация: печатать FunctionData. \n
	bool print_info_mangled_name = false;    ///< \brief \n Детализация: печатать MangledName. \n
	bool print_info_output_cleaning = false; ///< \brief \n Детализация: очищать/нормализовать вывод. \n
	bool print_info_container_size = false;  ///< \brief \n Детализация: печатать размеры контейнеров. \n

	bool fixed_location = false;             ///< \brief \n Фиксировать положение окна относительно основного вида. \n
	bool scylla_enabled = false;             ///< \brief \n Флаг интеграции со Scylla (зарезервировано). \n

											 // === Группа db ===
	QString mssql_instance;                  ///< \brief \n Имя экземпляра MSSQL (строка подключения/алиас). \n

											 // === Группа paths ===
	QString notepad_file_path;               ///< \brief \n Полный путь к файлу заметок (если пусто — будет определён по умолчанию). \n

											 // === Группа export ===
	QString export_last_dir;                 ///< \brief \n Последний каталог экспорта (BinExport/прочие выгрузки). \n

											 // === Группа ui ===
	QByteArray start_window_geometry;        ///< \brief \n Геометрия стартового окна (saveGeometry()). \n
	QByteArray settings_window_geometry;     ///< \brief \n Геометрия окна настроек. \n
	QByteArray notepad_window_geometry;      ///< \brief \n Геометрия окна заметок. \n

											 // === Прочее ===
	int notepad_autosave_ms = 10000;         ///< \brief \n Интервал автосохранения заметок в миллисекундах. \n
	int notepad_tab_width = 4;               ///< \brief \n Ширина табуляции для заметок (кол-во пробелов). \n
};


/// \class Settings
/// \brief \n Единая точка доступа к настройкам плагина. \n
///
/// Класс скрывает QSettings внутри реализации, предоставляет строго типизированные
/// геттеры/сеттеры, хранит кэш (SettingsState) и синхронизирует изменения.
///
/// Использование:
/// \code
///   Settings::init();                  // при старте плагина
///   bool coloring = Settings::getColoringEnabled();
///   Settings::setColoringEnabled(true);
///   Settings::shutdown();              // при выгрузке плагина
/// \endcode
class SETTINGS_EXPORT Settings
{
public:

/// \brief \n Инициализирует подсистему настроек и заполняет кэш из QSettings. \n
///
/// Безопасно вызывать повторно: повторный вызов перезагрузит снапшот из хранилища.
/// Использует группировку ключей (ui/, features/, db/, paths/, export/).
	static void init();


/// \brief \n Финализирует подсистему (синхронизирует и освобождает ресурсы). \n
///
/// Вызывать при завершении работы плагина. Если изменений не было — безопасно.
	static void shutdown();

	// === Геттеры ===

	/// \brief \n Включён ли автозапуск после старта отладчика. \n
	static bool getStartAfterDebug();

	/// \brief \n Включена ли подсветка элементов (highlight). \n
	static bool getColoringEnabled();

	/// \brief \n Главный флаг печати служебной информации. \n
	static bool getPrintInfoEnabled();

	/// \brief \n Детализация печати: FunctionData. \n
	static bool getPrintInfoFunctionData();

	/// \brief \n Детализация печати: MangledName. \n
	static bool getPrintInfoMangledName();

	/// \brief \n Детализация печати: OutputCleaning. \n
	static bool getPrintInfoOutputCleaning();

	/// \brief \n Детализация печати: ContainerSize. \n
	static bool getPrintInfoContainerSize();

	/// \brief \n Фиксировать ли положение окна. \n
	static bool getFixedLocation();

	/// \brief \n Флаг интеграции со Scylla (зарезервировано). \n
	static bool getScyllaEnabled();

	/// \brief \n Имя экземпляра MSSQL. \n
	static QString getMSSQLInstance();

	/// \brief \n Полный путь к файлу заметок. \n
	static QString getNotepadFilePath();

	/// \brief \n Последний каталог экспорта. \n
	static QString getExportLastDir();

	/// \brief \n Геометрия стартового окна. \n
	static QByteArray getStartWindowGeometry();

	/// \brief \n Геометрия окна настроек. \n
	static QByteArray getSettingsWindowGeometry();

	/// \brief \n Геометрия окна заметок. \n
	static QByteArray getNotepadWindowGeometry();

	/// \brief \n Интервал автосохранения заметок (мс). \n
	static int getNotepadAutosaveMs();

	/// \brief \n Ширина табуляции (кол-во пробелов). \n
	static int getNotepadTabWidth();

	// === Сеттеры ===

	/// \brief \n Устанавливает флаг автозапуска после старта отладчика. \n
	static void setStartAfterDebug(bool value);

	/// \brief \n Включает/выключает подсветку. \n
	static void setColoringEnabled(bool value);

	/// \brief \n Устанавливает главный флаг печати служебной информации. \n
	static void setPrintInfoEnabled(bool value);

	/// \brief \n Устанавливает детализацию печати: FunctionData. \n
	static void setPrintInfoFunctionData(bool value);

	/// \brief \n Устанавливает детализацию печати: MangledName. \n
	static void setPrintInfoMangledName(bool value);

	/// \brief \n Устанавливает детализацию печати: OutputCleaning. \n
	static void setPrintInfoOutputCleaning(bool value);

	/// \brief \n Устанавливает детализацию печати: ContainerSize. \n
	static void setPrintInfoContainerSize(bool value);

	/// \brief \n Фиксировать ли положение окна. \n
	static void setFixedLocation(bool value);

	/// \brief \n Включает/выключает Scylla-интеграцию (зарезервировано). \n
	static void setScyllaEnabled(bool value);

	/// \brief \n Сохраняет имя MSSQL-инстанса. \n
	static void setMSSQLInstance(const QString& instance);

	/// \brief \n Путь к файлу заметок. \n
	static void setNotepadFilePath(const QString& path);

	/// \brief \n Последний каталог экспорта. \n
	static void setExportLastDir(const QString& dir);

	/// \brief \n Сохраняет геометрию стартового окна. \n
	static void setStartWindowGeometry(const QByteArray& geometry);

	/// \brief \n Сохраняет геометрию окна настроек. \n
	static void setSettingsWindowGeometry(const QByteArray& geometry);

	/// \brief \n Сохраняет геометрию окна заметок. \n
	static void setNotepadWindowGeometry(const QByteArray& geometry);

	/// \brief \n Интервал автосохранения заметок (мс). \n
	static void setNotepadAutosaveMs(int ms);

	/// \brief \n Ширина табуляции (кол-во пробелов). \n
	static void setNotepadTabWidth(int width);


/// \brief \n Возвращает текущий снапшот настроек (копия). \n
/// \return Копия структуры SettingsState.
	static SettingsState state();

private:
	// Закрытый конструктор: используем только статический интерфейс
	Settings() = default;

	// === Внутренние помощники ===
	static void ensureInited_();                 ///< \brief \n Гарантирует, что init() уже вызывался. \n
	static void loadFromQSettings_();            ///< \brief \n Загружает state_ из QSettings. \n
	static void writeToQSettings_();             ///< \brief \n Полная синхронизация state_ -> QSettings. \n
	static void setAndSync_(const char* key, const QVariant& value); ///< \brief \n Запись одного ключа в QSettings с sync(). \n

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
	static std::unique_ptr<QSettings> qsettings_;  ///< \brief \n Реальный backend QSettings. \n
	static SettingsState state_;                   ///< \brief \n Кэш настроек, актуальный в рантайме. \n
	static std::mutex mtx_;                        ///< \brief \n Защита доступа к state_/qsettings_. \n

												   // === Параметры QSettings ===
	static const char* ORG_NAME;                   ///< \brief \n Организация (пример: "QtSetting" из твоего кода). \n
	static const char* APP_NAME;                   ///< \brief \n Приложение (пример: "BlaBlaBla" из твоего кода). \n
};

