




/**
 * \brief Проверим настройки , и если нет какой либо из них - создадим ...\n
 *     - настройка bool 'start_after_debug'			: запуск плагина после остановки дебаггера
 *     - настройка bool 'plugin_started'			: был ли плагин уже открыт в текущем сеансе IDA
 *     - настройка QString 'sql_server_name'		: имя экземпляра MSSQL с базой данных
 *     - настройка bool 'scylla_hide_using'			: использование плагина scylla_hide_using
 *     - настройка bool 'color_functions'			: выделение функций Ida цветом в зависимости от их использования
 *     - настройка bool 'print_info'				: вывод информации в окно output
 *     - настройка bool 'print_info_function_data'	: вывод информации о функциях в окно output (зависит от 'print_info')
 *     - настройка bool 'print_info_mangled_name'	: вывод мангленного или размангленного имени функции
 *													  при выводе информации в окно output (зависит от 'print_info')
 *	   - настройка bool 'print_info_output_cleaning': очистка окна вывода Ida перед запуском плагина (зависит от 'print_info')
 *	   - настройка bool 'print_info_container_size' : вывод в консоль размеров контейнеров с данными плагина (зависит от 'print_info')
 *	   - настройка bool 'fixed_location'			: открывать плагин в конкретном месте - сразу за вкладкой Ida View-A
 *
 *													  
 *
 */
 /**
 * \file Settings.cpp
 * \brief Реализация подсистемы настроек плагина.
 */

#include "Settings.h"
#include <QtCore/QStandardPaths>
#include <QtCore/QDir>

QT_USE_NAMESPACE

// === Имена организации/приложения. Оставлены как в твоём проекте: "QtSetting"/"BlaBlaBla". ===
const char* Settings::ORG_NAME = "QtSetting";
const char* Settings::APP_NAME = "BlaBlaBla";

// === Группы (для справки, используются в "KEY_*") ===
const char* Settings::GROUP_FEATURES = "features/";
const char* Settings::GROUP_DB = "db/";
const char* Settings::GROUP_PATHS = "paths/";
const char* Settings::GROUP_EXPORT = "export/";
const char* Settings::GROUP_UI = "ui/";

// === Ключи (оставлены читаемыми и «плоскими», чтобы маппинг был очевиден) ===
const char* Settings::KEY_START_AFTER_DEBUG = "features/StartAfterDebug";
const char* Settings::KEY_COLORING_ENABLED = "features/Coloring";
const char* Settings::KEY_PRINT_INFO_ENABLED = "features/PrintInfo";
const char* Settings::KEY_PRINT_INFO_FUNC_DATA = "features/PrintInfo.FunctionData";
const char* Settings::KEY_PRINT_INFO_MANGLED_NAME = "features/PrintInfo.MangledName";
const char* Settings::KEY_PRINT_INFO_OUTPUT_CLEANING = "features/PrintInfo.OutputCleaning";
const char* Settings::KEY_PRINT_INFO_CONTAINER_SIZE = "features/PrintInfo.ContainerSize";

const char* Settings::KEY_FIXED_LOCATION = "features/FixedLocation";
const char* Settings::KEY_SCYLLA_ENABLED = "features/Scylla";

const char* Settings::KEY_MSSQL_INSTANCE = "db/MSSQL.Instance";

const char* Settings::KEY_NOTEPAD_FILE_PATH = "paths/NotepadFile";
const char* Settings::KEY_EXPORT_LAST_DIR = "export/LastDir";

const char* Settings::KEY_START_WINDOW_GEOM = "ui/StartWindow.Geometry";
const char* Settings::KEY_SETTINGS_WINDOW_GEOM = "ui/SettingsWindow.Geometry";
const char* Settings::KEY_NOTEPAD_WINDOW_GEOM = "ui/NotepadWindow.Geometry";

const char* Settings::KEY_NOTEPAD_AUTOSAVE_MS = "features/Notepad.AutoSaveMs";
const char* Settings::KEY_NOTEPAD_TAB_WIDTH = "features/Notepad.TabWidth";

// === Статика ===
std::unique_ptr<QSettings> Settings::qsettings_;
SettingsState Settings::state_;
std::mutex Settings::mtx_;

/**
* \brief Гарантирует, что init() уже был вызван.
*
* Если init() не вызывался, то Settings не имеют валидного backend-а QSettings.
* В таком случае этот метод вызывает init() автоматически.
*/
void Settings::ensureInited_()
{
	// if: если backend ещё не создан, то инициализируем
	if (!qsettings_) // объяснение условия: проверяем, создан ли объект QSettings (инициализирована ли подсистема)
	{
		Settings::init();
	}
}

/**
* \brief Инициализация подсистемы и загрузка state_ из QSettings.
*/
void Settings::init()
{
	std::lock_guard<std::mutex> lock(mtx_);

	// if: если QSettings ещё нет — создаём с заданными ORG/APP (как в твоём проекте)
	if (!qsettings_)
	{
		qsettings_.reset(new QSettings(QString::fromUtf8(ORG_NAME),
			QString::fromUtf8(APP_NAME)));
	}

	// Загружаем все ключи в state_ (с дефолтами).
	loadFromQSettings_();

	// Если путь к файлу заметок не задан — назначим разумный дефолт и сохраним.
	if (state_.notepad_file_path.isEmpty())
	{
		const QString base = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
		QDir dir(base.isEmpty() ? QDir::tempPath() : base);
		dir.mkpath("."); // создаём директорию при необходимости
		const QString fallback = dir.absoluteFilePath(QStringLiteral("BlaBlaBla.txt"));
		state_.notepad_file_path = fallback;
		setAndSync_(KEY_NOTEPAD_FILE_PATH, state_.notepad_file_path);
	}
}

/**
* \brief Финализация подсистемы (опциональная: на всякий случай синхронизируемся).
*/
void Settings::shutdown()
{
	std::lock_guard<std::mutex> lock(mtx_);
	if (qsettings_)
	{
		qsettings_->sync();
		qsettings_.reset();
	}
}

/**
* \brief Полная загрузка state_ из QSettings с дефолтами и валидацией.
*/
void Settings::loadFromQSettings_()
{
	// Примечание: здесь и далее явные дефолты подобраны с оглядкой на твой текущий UX.
	state_.start_after_debug = qsettings_->value(KEY_START_AFTER_DEBUG, false).toBool();
	state_.coloring_enabled = qsettings_->value(KEY_COLORING_ENABLED, false).toBool();

	state_.print_info_enabled = qsettings_->value(KEY_PRINT_INFO_ENABLED, false).toBool();
	state_.print_info_function_data = qsettings_->value(KEY_PRINT_INFO_FUNC_DATA, false).toBool();
	state_.print_info_mangled_name = qsettings_->value(KEY_PRINT_INFO_MANGLED_NAME, false).toBool();
	state_.print_info_output_cleaning = qsettings_->value(KEY_PRINT_INFO_OUTPUT_CLEANING, false).toBool();
	state_.print_info_container_size = qsettings_->value(KEY_PRINT_INFO_CONTAINER_SIZE, false).toBool();

	state_.fixed_location = qsettings_->value(KEY_FIXED_LOCATION, false).toBool();
	state_.scylla_enabled = qsettings_->value(KEY_SCYLLA_ENABLED, false).toBool();

	state_.mssql_instance = qsettings_->value(KEY_MSSQL_INSTANCE, QString()).toString();

	state_.notepad_file_path = qsettings_->value(KEY_NOTEPAD_FILE_PATH, QString()).toString();
	state_.export_last_dir = qsettings_->value(KEY_EXPORT_LAST_DIR, QString()).toString();

	state_.start_window_geometry = qsettings_->value(KEY_START_WINDOW_GEOM, QByteArray()).toByteArray();
	state_.settings_window_geometry = qsettings_->value(KEY_SETTINGS_WINDOW_GEOM, QByteArray()).toByteArray();
	state_.notepad_window_geometry = qsettings_->value(KEY_NOTEPAD_WINDOW_GEOM, QByteArray()).toByteArray();

	state_.notepad_autosave_ms = qsettings_->value(KEY_NOTEPAD_AUTOSAVE_MS, 10000).toInt();
	// if: валидация интервала автосохранения (слишком малые/большие значения ограничиваем)
	if (state_.notepad_autosave_ms < 500)  // пояснение: меньше 0.5 сек — слишком часто, увеличим до минимума
		state_.notepad_autosave_ms = 500;
	if (state_.notepad_autosave_ms > 10 * 60 * 1000) // пояснение: больше 10 минут — ограничим
		state_.notepad_autosave_ms = 10 * 60 * 1000;

	state_.notepad_tab_width = qsettings_->value(KEY_NOTEPAD_TAB_WIDTH, 4).toInt();
	// if: валидация ширины таба (разумные пределы 1..16)
	if (state_.notepad_tab_width < 1)
		state_.notepad_tab_width = 1; // пояснение: таб не может быть меньше 1 пробела
	else if (state_.notepad_tab_width > 16)
		state_.notepad_tab_width = 16; // пояснение: слишком большой таб ухудшит читаемость
}

/**
* \brief Полная запись state_ в QSettings (используется редко; сеттеры пишут точечно).
*/
void Settings::writeToQSettings_()
{
	setAndSync_(KEY_START_AFTER_DEBUG, state_.start_after_debug);
	setAndSync_(KEY_COLORING_ENABLED, state_.coloring_enabled);

	setAndSync_(KEY_PRINT_INFO_ENABLED, state_.print_info_enabled);
	setAndSync_(KEY_PRINT_INFO_FUNC_DATA, state_.print_info_function_data);
	setAndSync_(KEY_PRINT_INFO_MANGLED_NAME, state_.print_info_mangled_name);
	setAndSync_(KEY_PRINT_INFO_OUTPUT_CLEANING, state_.print_info_output_cleaning);
	setAndSync_(KEY_PRINT_INFO_CONTAINER_SIZE, state_.print_info_container_size);

	setAndSync_(KEY_FIXED_LOCATION, state_.fixed_location);
	setAndSync_(KEY_SCYLLA_ENABLED, state_.scylla_enabled);

	setAndSync_(KEY_MSSQL_INSTANCE, state_.mssql_instance);

	setAndSync_(KEY_NOTEPAD_FILE_PATH, state_.notepad_file_path);
	setAndSync_(KEY_EXPORT_LAST_DIR, state_.export_last_dir);

	setAndSync_(KEY_START_WINDOW_GEOM, state_.start_window_geometry);
	setAndSync_(KEY_SETTINGS_WINDOW_GEOM, state_.settings_window_geometry);
	setAndSync_(KEY_NOTEPAD_WINDOW_GEOM, state_.notepad_window_geometry);

	setAndSync_(KEY_NOTEPAD_AUTOSAVE_MS, state_.notepad_autosave_ms);
	setAndSync_(KEY_NOTEPAD_TAB_WIDTH, state_.notepad_tab_width);
}

/**
* \brief Записывает один ключ в QSettings и синхронизирует хранилище.
* \param key Полный ключ (например, "features/Coloring").
* \param value Значение для записи.
*/
void Settings::setAndSync_(const char* key, const QVariant& value)
{
	// if: гарантируем наличие backend-а перед записью
	if (!qsettings_) // объяснение: если кто-то вызвал сеттер до init(), создадим QSettings на лету
		qsettings_.reset(new QSettings(QString::fromUtf8(ORG_NAME),
			QString::fromUtf8(APP_NAME)));

	qsettings_->setValue(QString::fromUtf8(key), value);
	qsettings_->sync();
}

// === Публичные методы доступа ===

void Settings::setStartAfterDebug(bool value)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.start_after_debug = value;
	setAndSync_(KEY_START_AFTER_DEBUG, value);
}
bool Settings::getStartAfterDebug()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.start_after_debug;
}

void Settings::setColoringEnabled(bool value)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.coloring_enabled = value;
	setAndSync_(KEY_COLORING_ENABLED, value);
}
bool Settings::getColoringEnabled()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.coloring_enabled;
}

void Settings::setPrintInfoEnabled(bool value)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.print_info_enabled = value;
	setAndSync_(KEY_PRINT_INFO_ENABLED, value);
}
bool Settings::getPrintInfoEnabled()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.print_info_enabled;
}

void Settings::setPrintInfoFunctionData(bool value)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.print_info_function_data = value;
	setAndSync_(KEY_PRINT_INFO_FUNC_DATA, value);
}
bool Settings::getPrintInfoFunctionData()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.print_info_function_data;
}

void Settings::setPrintInfoMangledName(bool value)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.print_info_mangled_name = value;
	setAndSync_(KEY_PRINT_INFO_MANGLED_NAME, value);
}
bool Settings::getPrintInfoMangledName()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.print_info_mangled_name;
}

void Settings::setPrintInfoOutputCleaning(bool value)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.print_info_output_cleaning = value;
	setAndSync_(KEY_PRINT_INFO_OUTPUT_CLEANING, value);
}
bool Settings::getPrintInfoOutputCleaning()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.print_info_output_cleaning;
}

void Settings::setPrintInfoContainerSize(bool value)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.print_info_container_size = value;
	setAndSync_(KEY_PRINT_INFO_CONTAINER_SIZE, value);
}
bool Settings::getPrintInfoContainerSize()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.print_info_container_size;
}

void Settings::setFixedLocation(bool value)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.fixed_location = value;
	setAndSync_(KEY_FIXED_LOCATION, value);
}
bool Settings::getFixedLocation()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.fixed_location;
}


void Settings::setScyllaEnabled(bool value)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.scylla_enabled = value;
	setAndSync_(KEY_SCYLLA_ENABLED, value);
}
bool Settings::getScyllaEnabled()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.scylla_enabled;
}

void Settings::setMSSQLInstance(const QString& instance)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	QString trimmed = instance.trimmed();
	state_.mssql_instance = trimmed;
	setAndSync_(KEY_MSSQL_INSTANCE, state_.mssql_instance);
}
QString Settings::getMSSQLInstance()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.mssql_instance;
}

void Settings::setNotepadFilePath(const QString& path)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	QString p = path.trimmed();
	// if: если путь пустой — не принимаем, оставляем предыдущий
	if (p.isEmpty())
	{
		// пояснение: пустой путь приведёт к ошибкам I/O — игнорируем запись
		return;
	}
	state_.notepad_file_path = p;
	setAndSync_(KEY_NOTEPAD_FILE_PATH, state_.notepad_file_path);
}
QString Settings::getNotepadFilePath()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.notepad_file_path;
}

void Settings::setExportLastDir(const QString& dir)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	QString d = dir.trimmed();
	state_.export_last_dir = d;
	setAndSync_(KEY_EXPORT_LAST_DIR, state_.export_last_dir);
}
QString Settings::getExportLastDir()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.export_last_dir;
}

void Settings::setStartWindowGeometry(const QByteArray& geometry)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.start_window_geometry = geometry;
	setAndSync_(KEY_START_WINDOW_GEOM, state_.start_window_geometry);
}
QByteArray Settings::getStartWindowGeometry()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.start_window_geometry;
}

void Settings::setSettingsWindowGeometry(const QByteArray& geometry)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.settings_window_geometry = geometry;
	setAndSync_(KEY_SETTINGS_WINDOW_GEOM, state_.settings_window_geometry);
}
QByteArray Settings::getSettingsWindowGeometry()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.settings_window_geometry;
}

void Settings::setNotepadWindowGeometry(const QByteArray& geometry)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	state_.notepad_window_geometry = geometry;
	setAndSync_(KEY_NOTEPAD_WINDOW_GEOM, state_.notepad_window_geometry);
}
QByteArray Settings::getNotepadWindowGeometry()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.notepad_window_geometry;
}

void Settings::setNotepadAutosaveMs(int ms)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	// if: приводим интервал к допустимому диапазону (500..600000 мс)
	if (ms < 500) ms = 500; // пояснение: слишком частое сохранение создаст нагрузку на диск
	if (ms > 10 * 60 * 1000) ms = 10 * 60 * 1000; // пояснение: больше 10 минут — автосохранение теряет смысл
	state_.notepad_autosave_ms = ms;
	setAndSync_(KEY_NOTEPAD_AUTOSAVE_MS, state_.notepad_autosave_ms);
}
int Settings::getNotepadAutosaveMs()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.notepad_autosave_ms;
}

void Settings::setNotepadTabWidth(int width)
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	// if: ограничиваем ширину таба разумными пределами
	if (width < 1)  width = 1;   // пояснение: минимум 1 пробел
	if (width > 16) width = 16;  // пояснение: сверхбольшой таб ухудшает читаемость
	state_.notepad_tab_width = width;
	setAndSync_(KEY_NOTEPAD_TAB_WIDTH, state_.notepad_tab_width);
}
int Settings::getNotepadTabWidth()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_.notepad_tab_width;
}

/**
* \brief Возвращает копию текущего снапшота.
*/
SettingsState Settings::state()
{
	std::lock_guard<std::mutex> lock(mtx_);
	ensureInited_();
	return state_;
}
