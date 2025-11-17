#include "first_window.hpp"
#include "settings.h"


//include the below additional libraries
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

#include "debug_log.h"

//use the std namespace
using namespace std;



//
///**
// * \brief \n получим адрес папки плагина и добавим к нему имя файла для сохранения записей настроек  ... \n
// */
//const QString filename = QProcessEnvironment::systemEnvironment().value("IDA76_PLUGIN_DIR").append("\\BlaBlaBla.ini");

FirstWindow::FirstWindow(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
	// если коннекторы определены и связаны на форме - здесь ничего добавлять не надо
	// все добавления Qt сделает автоматически в файле ui_filename.h
	connect(&sql_connection_form, SIGNAL(send_to_object(bool)), this, SLOT(SetTextToForm(bool)));

}

FirstWindow::~FirstWindow() {

}



void FirstWindow::closeEvent(QCloseEvent * event)
{
	if (sql_connection_form.isVisible())
	{
		sql_connection_form.close();
	}
}

void FirstWindow::CheckDebug() const
{
	TRACE_FN();
	const auto value = Settings::getStartAfterDebug();
	ui.checkBox_Start_after_debug->setChecked(value);

}

void FirstWindow::CheckColoring() const
{
	TRACE_FN();
	const auto value = Settings::getColoringEnabled();
	ui.checkBox_coloring->setChecked(value);

}
void FirstWindow::CheckPrintInfo() const
{
	TRACE_FN();
	const auto state = Settings::getPrintInfoEnabled();
	ui.checkBox_PrintInfo->setChecked(state);

	if (state)
	{
		ui.checkBox_ContainerSize->setEnabled(true);
		ui.checkBox_FunctionData->setEnabled(true);
		ui.checkBox_MangledName->setEnabled(true);
		ui.checkBox_OutputCleaning->setEnabled(true);
	}
	else
	{
		ui.checkBox_ContainerSize->setEnabled(false);
		ui.checkBox_FunctionData->setEnabled(false);
		ui.checkBox_MangledName->setEnabled(false);
		ui.checkBox_OutputCleaning->setEnabled(false);
	}

}

void FirstWindow::CheckPrintInfoFunctionData() const
{
	TRACE_FN();
	const auto state = Settings::getPrintInfoFunctionData();
	ui.checkBox_FunctionData->setChecked(state);

}

void FirstWindow::CheckPrintInfoMangledName() const
{
	TRACE_FN();
	const auto state = Settings::getPrintInfoMangledName();
	ui.checkBox_MangledName->setChecked(state);

}

void FirstWindow::CheckPrintInfoOutputCleaning() const
{
	TRACE_FN();
	const auto state = Settings::getPrintInfoOutputCleaning();
	ui.checkBox_OutputCleaning->setChecked(state);

}

void FirstWindow::CheckPrintInfoContainerSize() const
{
	TRACE_FN();
	const auto state = Settings::getPrintInfoContainerSize();
	ui.checkBox_ContainerSize->setChecked(state);

}

void FirstWindow::CheckFixedLocation() const
{
	TRACE_FN();
	const auto state = Settings::getFixedLocation();
	ui.checkBox_FixedLocation->setChecked(state);

}

void FirstWindow::showEvent(QShowEvent * event)
{
	CheckSettings();
}

/**
 * \brief \n Проверяет переменные пользовательских настроек ...
 * \param settings
 */
void FirstWindow::CheckSettings() const
{
	TRACE_FN();
	
	CheckScylla();
	CheckMSSQL();
	CheckColoring();
	CheckDebug();
	CheckPrintInfo();
	CheckPrintInfoFunctionData();
	CheckPrintInfoMangledName();
	CheckPrintInfoOutputCleaning();
	CheckPrintInfoContainerSize();
	CheckFixedLocation();
}

void FirstWindow::CheckScylla() const
{
	TRACE_FN();
	const auto state = Settings::getScyllaEnabled();
	ui.checkBox_Scylla->setChecked(state);


}

void FirstWindow::sql_connection_form_show()
{
	sql_connection_form.show();
}

void FirstWindow::AddMSSQL()
{
	TRACE_FN();
	
#pragma region Подсказки по SQL
	// https://harrix.dev/blog/2014/connect-to-sql-server-in-qt/
	// https://russianblogs.com/article/75971552880/
	// https://evileg.com/ru/post/62/
	// https://www.connectionstrings.com/sql-server-2005/
	// https://www.sqlnethub.com/blog/how-to-connect-to-sql-server-from-visual-c-plus-plus/              !!!!!!!!!!!!!!!!!!!!!!! Этот вариант работает 
	// C:\Qt563\5.6.3\Src\qtbase\src\plugins\sqldrivers\odbc
	// устойчивость соединения https://learn.microsoft.com/ru-ru/sql/connect/odbc/connection-resiliency?view=sql-server-ver16
	// Ключевые слова и атрибуты строки подключения и имени DSN https://learn.microsoft.com/ru-ru/sql/connect/odbc/dsn-connection-string-attribute?view=sql-server-ver16
	// Жестко запрограммированные инструкции SQL https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/hard-coded-sql-statements?view=sql-server-ver16
	// Инструкции SQL, сформированные во время выполнения https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/sql-statements-constructed-at-run-time?view=sql-server-ver16
	// Инструкции SQL, введенные пользователем  https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/sql-statements-entered-by-the-user?view=sql-server-ver16
	// Префиксы и суффиксы литералов https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/literal-prefixes-and-suffixes?view=sql-server-ver16
	// Escape-последовательности в ODBC https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/escape-sequences-in-odbc?view=sql-server-ver16
	// возможность LINQ запросов https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/outer-joins?view=sql-server-ver16
	// Вызовы процедур https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/procedure-calls?view=sql-server-ver16
	// Выполнение инструкций (ODBC) https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/executing-statements-odbc?view=sql-server-ver16
	// Выполнение инструкции https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/executing-a-statement?view=sql-server-ver16
	// Прямое выполнение (ODBC)  https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/direct-execution-odbc?view=sql-server-ver16
	// Подготовленное выполнение ODBC  https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/prepared-execution-odbc?view=sql-server-ver16
	// Процедуры ODBC  https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/procedures-odbc?view=sql-server-ver16
	// Пакеты инструкций SQL  https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/batches-of-sql-statements?view=sql-server-ver16
	// Инструкции, возвращающие и не возвращающие результаты https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/result-generating-and-result-free-statements?view=sql-server-ver16
	// Выполнение пакетов https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/executing-batches?view=sql-server-ver16
	// Параметры инструкции  https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/statement-parameters?view=sql-server-ver16
	// Привязка параметров (ODBC) https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/binding-parameters-odbc?view=sql-server-ver16
	// Привязка маркеров параметров https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/binding-parameter-markers?view=sql-server-ver16
	// Привязка параметров по имени (именованные параметры) https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/binding-parameters-by-name-named-parameters?view=sql-server-ver16
	// Установка значений параметров https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/setting-parameter-values?view=sql-server-ver16
	// SQLPutData, функция https://learn.microsoft.com/ru-ru/sql/odbc/reference/syntax/sqlputdata-function?view=sql-server-ver16
	// SQLManageDataSources
	// Управление источниками данных
	// Имена DSN пользователей
	// Управление драйверами
	// Параметры трассировки
	// https://learn.microsoft.com/ru-ru/sql/odbc/reference/syntax/sqlmanagedatasources?view=sql-server-ver16
	// 
	// Приложение А. Коды ошибок ODBC https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/appendix-a-odbc-error-codes?view=sql-server-ver16
	// Приложение Б. Таблицы перехода состояния ODBC https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/appendix-b-odbc-state-transition-tables?view=sql-server-ver16
	// Приложение В. Грамматика SQL https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/appendix-c-sql-grammar?view=sql-server-ver16
	// Минимальная грамматика SQL  https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/sql-minimum-grammar?view=sql-server-ver16
	// Зарезервированные слова https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/reserved-keywords?view=sql-server-ver16
	// Использование идентификаторов типов данных https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/using-data-type-identifiers?view=sql-server-ver16
	// Типы данных SQL https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/sql-data-types?view=sql-server-ver16
	// Пример результирующего набора SQLGetTypeInfo https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/example-sqlgettypeinfo-result-set?view=sql-server-ver16
	// Типы данных C https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/c-data-types?view=sql-server-ver16
	// 64-разрядные целочисленные структуры https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/64-bit-integer-structures?view=sql-server-ver16
	// Получение числовых данных с помощью SQL_NUMERIC_STRUCT https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/retrieve-numeric-data-sql-numeric-struct-kb222831?view=sql-server-ver16
	// Идентификаторы и дескрипторы типа данных https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/data-type-identifiers-and-descriptors?view=sql-server-ver16
	// Рекомендации по использованию интервальных и числовых типов данных https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/guidelines-for-interval-and-numeric-data-types?view=sql-server-ver16
	// временные типы данных https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/interval-data-types?view=sql-server-ver16
	// Числовые литералы https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/numeric-literals?view=sql-server-ver16
	// Размер столбца https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/column-size?view=sql-server-ver16
	// Десятичные цифры https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/decimal-digits?view=sql-server-ver16
	// Преобразование данных из SQL в типы данных C https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/converting-data-from-sql-to-c-data-types?view=sql-server-ver16
	// Преобразование данных из C в типы данных SQL https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/converting-data-from-c-to-sql-data-types?view=sql-server-ver16
	// Строковые функции https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/string-functions?view=sql-server-ver16
	// Числовые функции https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/numeric-functions?view=sql-server-ver16
	// Функции даты, времени и интервалов https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/time-date-and-interval-functions?view=sql-server-ver16
	// Функция явного преобразования типа данных https://learn.microsoft.com/ru-ru/sql/odbc/reference/appendixes/explicit-data-type-conversion-function?view=sql-server-ver16
	//
	// Администратор источников данных ODBC https://learn.microsoft.com/ru-ru/sql/odbc/admin/odbc-data-source-administrator?view=sql-server-ver16
	// Сценарий использования: отправка и получение большого объекта в качестве потокового входного/выходного параметра
	// https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/retrieving-output-parameters-using-sqlgetdata?view=sql-server-ver16#usage-scenario-send-and-receive-a-large-object-as-a-streamed-inputoutput-parameter
	// Привязка массивов параметров https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/binding-arrays-of-parameters?view=sql-server-ver16
	// Асинхронное выполнение (метод опроса) https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/asynchronous-execution-polling-method?view=sql-server-ver16
	// Получение данных типа Long https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/getting-long-data?view=sql-server-ver16
	//
	//
	// Сводка по функциям ODBC https://learn.microsoft.com/ru-ru/sql/odbc/reference/syntax/odbc-function-summary?view=sql-server-ver16
	// Пример приложения ODBC на C/C++, которое обращается к базе данных SQL
	// https://learn.microsoft.com/ru-ru/sql/connect/odbc/cpp-code-example-app-connect-access-sql-db?view=sql-server-ver16
	// Функция SQLBrowseConnect  https://learn.microsoft.com/ru-ru/sql/odbc/reference/syntax/sqlbrowseconnect-function?view=sql-server-ver16
	// SQLColumns, функция https://learn.microsoft.com/ru-ru/sql/odbc/reference/syntax/sqlcolumns-function?view=sql-server-ver16
	// Функция SQLConnect https://learn.microsoft.com/ru-ru/sql/odbc/reference/syntax/sqlconnect-function?view=sql-server-ver16     !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	// В следующем примере приложение выделяет среду и дескрипторы подключения. Затем он подключается к источнику данных SalesOrders
	// с идентификатором пользователя JohnS и паролем Sesame и обрабатывает данные.
	// После завершения обработки данных он отключается от источника данных и освобождает дескрипторы.
	//
	// Функция SQLDriverConnect https://learn.microsoft.com/ru-ru/sql/odbc/reference/syntax/sqldriverconnect-function?view=sql-server-ver16
	// SQLDriverConnect является альтернативой SQLConnect.
	// Он поддерживает источники данных, для которых требуется больше сведений о подключении, чем три аргумента в SQLConnect,
	// диалоговые окна для запроса всех сведений о подключении, а также источники данных, которые не определены в системных данных.
	// Дополнительные сведения см. в статье Подключение с помощью SQLDriverConnect. https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/connecting-with-sqldriverconnect?view=sql-server-ver16
	// 
	//
	// ****************************************************************************************************************
	// https://cplusplus.com/forum/windows/278370/   решение по ниже написанной функции !!!!***************************
	// ****************************************************************************************************************
	// https://h-savran.blogspot.com/2018/02/stey-by-step-running-c-in-your-web-page.html
	// ****************************************************************************************************************
	//
	//
	//
	//
	//
	//
	// 
	//
# pragma endregion Подсказки по SQL


# pragma region Qt прробные решения - этот вариант работает в QT но не работает в студии - модуль SQL не видит !!!

	//QString servername = "LOCALHOST\\PCSQL";
	//QString dbname = "BlaBlaBla";
	//QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

	//db.setConnectOptions();

	//QString dsn = QString("DRIVER={SQL Server};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes").arg(servername).arg(dbname);


	//db.setDatabaseName(dsn);

	//if (db.open())
	//{
	//	qDebug() << "Opened";
	//	db.close();
	//}
	//else
	//{
	//	qDebug() << db.lastError().text();
	//}

# pragma endregion

	//QString connectString = "Driver={SQL Server Native Client 11.0};";                     // Driver is now {SQL Server Native Client 11.0}
	//connectString.append("Server=lpc:PC\\PCSQL;");   // Hostname,SQL-Server Instance
	//connectString.append("Database=ColorRu;");  // Schema
	//connectString.append("Uid=sa;");           // User
	//connectString.append("Pwd=e7e8e9ee;");           // Pass
	//db.setDatabaseName(connectString);

	//QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");
	//db.setDatabaseName("DRIVER={SQL Server};Server=PC\\PCSQL;Database=BlaBlaBla;UID=sa;PWD=e7e8e9ee;");
	//db.open();

	//if (db.open())
	//{
	//	auto y = true;
	//}else
	//{
	//	auto y = false;
	//}

	//auto check = QSqlDatabase::drivers();

	//auto AAA = check.indexOf("ODBC");

# pragma region Рабочее решение С++

//#define SQL_RESULT_LEN 240
//#define SQL_RETURN_CODE_LEN 1000
//	//define handles and variables
//	SQLHANDLE sqlConnHandle;   // идентификатор подключения
//	SQLHANDLE sqlStmtHandle;
//	SQLHANDLE sqlEnvHandle;
//	SQLCHAR retconstring[SQL_RETURN_CODE_LEN];
//	//initializations
//	sqlConnHandle = nullptr;
//	sqlStmtHandle = nullptr;
//	//allocations
//	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle)) // ВЫДЕЛЕНИЕ ПАМЯТИ ДЛЯ ИДЕНТИФИКАТОРА
//		goto COMPLETED;
//	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) // ВЫБОР ВЕРСИИ ODBC
//		goto COMPLETED;
//	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle)) //ВЫДЕЛЕНИЕ ПАМЯТИ ДЛЯ ИДЕНТИФИКАТОРА ПОДКЛЮЧЕНИЯ
//		goto COMPLETED;
//	//output
//	msg("Attempting connection to SQL Server... \n");
//	//подключитесь к SQL Server  
//	//не имеет значения, используете ли вы экземпляр по умолчанию или именованный экземпляр
//	//просто убедитесь, что вы определили имя сервера и порт
//	//У вас есть возможность использовать имя пользователя/пароль вместо доверенного соединения. но безопаснее использовать доверенное соединение
//
//	SQLCHAR connection_str[] = "DRIVER={SQL Server};SERVER=PC\\PCSQL;DATABASE=master;Trusted=true;";
//
//
//	switch (SQLDriverConnect(sqlConnHandle,
//		NULL,
//		//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;UID=username;PWD=password;",
//		/*(SQLCHAR*)"DRIVER={SQL Server};SERVER=PC\\SQLEXPRESS;DATABASE=master;Trusted=true;",*/
//		// При подключении к поставщику источника данных, который поддерживает проверка подлинности Windows, следует указать Trusted_Connection=yes 
//		// вместо идентификатора пользователя и пароля в строке подключения.
//		connection_str,
//		SQL_NTS,
//		retconstring,
//		1024,
//		NULL,
//		SQL_DRIVER_NOPROMPT)) {
//	case SQL_SUCCESS:
//		msg("Successfully connected to SQL Server \n");
//		break;
//	case SQL_SUCCESS_WITH_INFO:
//		msg("Successfully connected to SQL Server \n");
//		break;
//	case SQL_INVALID_HANDLE:
//		msg("Could not connect to SQL Server \n");
//		goto COMPLETED;
//	case SQL_ERROR:
//		msg("Could not connect to SQL Server \n");
//		goto COMPLETED;
//	default:
//		break;
//	}
//	//if there is a problem connecting then exit application
//	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
//		goto COMPLETED;
//	//output
//	msg("Executing T-SQL query... \n");
//	//if there is a problem executing the query then exit application
//	//else display query result
//	// SQLExecDirect — это самый быстрый способ отправки инструкции SQL для однократного выполнения.
//	// https://learn.microsoft.com/ru-ru/sql/odbc/reference/syntax/sqlexecdirect-function?view=sql-server-ver16
//	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)"SELECT @@VERSION", SQL_NTS)) {
//		msg("Error querying SQL Server \n");
//		goto COMPLETED;
//	}
//	else {
//		//declare output variable and pointer
//		SQLCHAR sqlVersion[SQL_RESULT_LEN];
//		SQLLEN *ptrSqlVersion = nullptr;
//		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
//			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, sqlVersion, SQL_RESULT_LEN, ptrSqlVersion);
//			//display query result
//			msg("\nQuery Result:\n\n");
//			msg(" version = %s ", sqlVersion);
//
//			goto COMPLETED;
//		}
//	}
//	//close connection and free resources
//	//Когда вы закончите работу с базой данных, вы должны закрыть связь с ней следующим образом :
//	//Отключится от источника данных
//	//	Уничтожить идентификатор соединения
//	//	Уничтожить идентификатор окружения(если вы не желаете использовать это окружение для других соединений)
//COMPLETED:
//	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
//	SQLDisconnect(sqlConnHandle);
//	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
//	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);

# pragma endregion


//QSettings settings("QtSetting", "BlaBlaBla");

	const auto state = ui.checkBox_MSSQL->isChecked(); // для 2х вкл или выкл 

	if (state)
	{
		sql_connection_form_show();
	}
	else
	{
		Settings::setMSSQLInstance("");
		ui.checkBox_MSSQL->setText(QString("Using MSSQL db "));
	}

}

void FirstWindow::SetTextToForm(const bool value) const
{
	TRACE_FN();
	
	if (value)
	{
		const auto str_value = Settings::getMSSQLInstance();
		ui.checkBox_MSSQL->setText(QString("Using MSSQL db into ").append(str_value));
	}
	else
	{
		ui.checkBox_MSSQL->setChecked(false);
	}
}

void FirstWindow::StartAfterDebug() const
{
	TRACE_FN();
	const auto state = ui.checkBox_Start_after_debug->isChecked(); // для 2х  - вкл или выкл 
	Settings::setStartAfterDebug(state);

}

void FirstWindow::ColorFunctions() const
{
	TRACE_FN();
	const auto state = ui.checkBox_coloring->isChecked(); // для 2х  - вкл или выкл 
	Settings::setColoringEnabled(state);
}

void FirstWindow::PrintInfo() const
{
	TRACE_FN();
	
	const auto state = ui.checkBox_PrintInfo->isChecked(); // для 2х вкл или выкл 
	Settings::setPrintInfoEnabled(state);


	if (state)
	{
		ui.checkBox_ContainerSize->setEnabled(true);
		ui.checkBox_FunctionData->setEnabled(true);
		ui.checkBox_MangledName->setEnabled(true);
		ui.checkBox_OutputCleaning->setEnabled(true);

	}
	else
	{
		ui.checkBox_ContainerSize->setEnabled(false);
		ui.checkBox_FunctionData->setEnabled(false);
		ui.checkBox_MangledName->setEnabled(false);
		ui.checkBox_OutputCleaning->setEnabled(false);
	}



}

void FirstWindow::PrintInfoFunctionData() const
{
	TRACE_FN();
	const auto state = ui.checkBox_FunctionData->isChecked(); // для 2х вкл или выкл 
	Settings::setPrintInfoFunctionData(state);
}

void FirstWindow::PrintInfoMangledName() const
{
	TRACE_FN();
	const auto state = ui.checkBox_MangledName->isChecked(); // для 2х вкл или выкл 
	Settings::setPrintInfoMangledName(state);
}

void FirstWindow::PrintInfoOutputCleaning() const
{
	TRACE_FN();
	const auto state = ui.checkBox_OutputCleaning->isChecked(); // для 2х вкл или выкл 
	Settings::setPrintInfoOutputCleaning(state);
}
// container_size
void FirstWindow::PrintInfoContainerSize() const
{
	TRACE_FN();
	const auto state = ui.checkBox_ContainerSize->isChecked(); // для 2х вкл или выкл 
	Settings::setPrintInfoContainerSize(state);
}

void FirstWindow::FixedLocation() const
{
	TRACE_FN();
	const auto state = ui.checkBox_FixedLocation->isChecked(); // для 2х вкл или выкл 
	Settings::setFixedLocation(state);
}


void FirstWindow::CheckMSSQL() const
{
	TRACE_FN();
	
	const auto value = Settings::getMSSQLInstance();
	if (Settings::getMSSQLInstance() == "")
	{
		ui.checkBox_MSSQL->setChecked(false);
	}
	else
	{

		//TODO: здесь проверка нужна подключения 
		ui.checkBox_MSSQL->setChecked(true);
		ui.checkBox_MSSQL->setText(QString("Using MSSQL db into ").append(value));
	}


}

void FirstWindow::AddScylla() const
{
	TRACE_FN();
	
	// auto state = ui.checkBox->checkState(); // для трех состояний
	const auto state = ui.checkBox_Scylla->isChecked(); // для 2х вкл или выкл 
	Settings::setScyllaEnabled(state);


}

