#include "db_connection.hpp"
#include "settings.h"
#include "first_window.hpp"
#include <exception>
#pragma comment(lib, "Qt5Sql.lib")

// флаг что соединение установлено успешно
// чтобы когда форма закрывается  - только в случае не успешного соединения
// срабатывал сигнал emit send_to_object(false) при событии закрытия формы ...
bool sql_connection_state = false;

/**
 * \brief \n Покажем окно для указания имени экземпляра SQL server
 * \param parent QWidget
 */
DBConnection::DBConnection(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
}

DBConnection::~DBConnection() {

}

bool DBConnection::TryConnect(const QString& instance)
{
	// Создаём временный объект, чтобы вызвать приватный метод-член.
	DBConnection tmp(nullptr);
	auto res = false;

	if (tmp.CheckSQLConnection(instance) == "CONNECTION")
	{
		res = true;
	}
	
	return (res);
}


std::vector<unsigned char> to_vector(std::string const& str)
{
	// не забываем про 0 символ в конце ... + 1   !!!
	return std::vector<unsigned char>(str.data(), str.data() + str.length() + 1);
}


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
// Привязка на уровне строки  https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/row-wise-binding?view=sql-server-ver16
// Привязка на уровне столбца https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/column-wise-binding?view=sql-server-ver16
//
// Функции работы с каталогами в ODBC https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/catalog-functions-in-odbc?view=sql-server-ver16
// Аргументы в функциях каталога  https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/arguments-in-catalog-functions?view=sql-server-ver16
// Построение инструкций SQL https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/constructing-sql-statements?view=sql-server-ver16
// Жестко запрограммированные инструкции SQL  https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/hard-coded-sql-statements?view=sql-server-ver16
// Инструкции SQL, сформированные во время выполнения
// https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/sql-statements-constructed-at-run-time?view=sql-server-ver16
// Инструкции SQL, введенные пользователем  https://learn.microsoft.com/ru-ru/sql/odbc/reference/develop-app/sql-statements-entered-by-the-user?view=sql-server-ver16
//
//																ИНТУИТ
//									***********************************************************
// Основные функции ODBC ИНТУИТ											https://intuit.ru/studies/courses/79/79/lecture/28175
// Схема доступа к источнику данных с использованием ODBC API			https://intuit.ru/studies/courses/79/79/lecture/28177
// Механизмы выборки данных												https://intuit.ru/studies/courses/79/79/lecture/28179
// Параметрические запросы												https://intuit.ru/studies/courses/79/79/lecture/28181
// Применение курсоров													https://intuit.ru/studies/courses/79/79/lecture/28183
// Реализация доступа к базам данных в среде VISUAL STUDIO.NET на языке С++ с применением MFC   https://intuit.ru/studies/courses/79/79/lecture/28191
//  Реализация доступа к базам данных в среде VISUAL STUDIO.NET на языке С++ с применением ATL  https://intuit.ru/studies/courses/79/79/lecture/28193
//  
//
//
// 
//
# pragma endregion Подсказки по SQL

void DisplayError(SQLSMALLINT t, SQLHSTMT h) {

	//Получение информации об ошибке SQL
	SQLCHAR       SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER    NativeError;
	SQLSMALLINT   i, MsgLen;
	SQLRETURN     rc;

	SQLLEN numRecs = 0;
	SQLGetDiagField(t, h, 0, SQL_DIAG_NUMBER, &numRecs, 0, 0);

	i = 1;
	while (i <= numRecs && (rc = SQLGetDiagRec(t, h, i, SqlState, &NativeError,
		Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA) {
		wprintf(L"Error %d: %p\n", NativeError, Msg);
		i++;
	}
}



void DBConnection::closeEvent(QCloseEvent * event)
{
	if (!sql_connection_state)
	{
		emit send_to_object(false);
	}


	QWidget::closeEvent(event);
}

QString DBConnection::CheckSQLConnection(const QString &instance_name)
{

#pragma region  SSSS

	// https://ru.stackoverflow.com/questions/998161
	// http://smallsoft2.blogspot.com/2022/04/odbc.html


#include <stdio.h>
#include <Windows.h>
#include <sqlext.h>
#include <locale.h>

	//unsigned char connect_str[] = "Driver={SQL Server};DSN='';SERVER=.\\pcsql;DATABASE=ColorRu;";
	//unsigned char query[] = "SELECT * FROM AspNetUsers";
	unsigned char connect_str[] = "Driver={SQL Server};DSN='';SERVER=.\\pcsql;DATABASE=BlaBlaBla;";
	unsigned char query[] = "SELECT * FROM account";


	HENV    hEnv = NULL;
	HDBC    hDbc = NULL;
	HSTMT hStmt = NULL;
	short iConnStrLength2Ptr;
	unsigned char connect_str_out[256];
	SQLINTEGER rowCount = 0;
	short fieldCount = 0, currentField = 0;
	unsigned char buf[128], col_name[128];
	SQLLEN ret;

	RETCODE rc; //Код статуса ODBC API


	/* Выделение дескриптора среды */
	rc = SQLAllocEnv(&hEnv);
	/* Выделение дескриптора соединения */
	rc = SQLAllocConnect(hEnv, &hDbc);

	/* Подключение к БД */
	rc = SQLDriverConnect(hDbc, NULL, connect_str,
		SQL_NTS, connect_str_out,
		255, &iConnStrLength2Ptr, SQL_DRIVER_NOPROMPT);

	if (SQL_SUCCEEDED(rc))
	{
		/* Подготовка запроса SQL */
		rc = SQLAllocStmt(hDbc, &hStmt);
		rc = SQLPrepare(hStmt, query, SQL_NTS);

		/* Выполнение запроса */
		rc = SQLExecute(hStmt);
		if (SQL_SUCCEEDED(rc))
		{
			msg("\n- Columns -\n");

			SQLNumResultCols(hStmt, &fieldCount);
			if (fieldCount > 0)
			{
				for (currentField = 1; currentField <= fieldCount; currentField++)
				{
					SQLDescribeCol(hStmt, currentField,
						col_name, sizeof(col_name), 0, 0, 0, 0, 0);
					msg("%d: %s\n", currentField, col_name);
				}
				msg("\n");

				/* Получение записей из результатов запроса */

				rc = SQLFetch(hStmt);
				while (SQL_SUCCEEDED(rc))
				{
					msg("- Record #%d -\n", rowCount);

					for (currentField = 1; currentField <= fieldCount; currentField++)
					{
						rc = SQLGetData(hStmt, currentField, SQL_C_CHAR, buf, sizeof(buf), &ret);

						if (SQL_SUCCEEDED(rc) == FALSE) {
							msg("%d: SQLGetData failed\n", currentField);
							continue;
						}

						if (ret <= 0) {
							msg("%d: (no data)\n", currentField);
							continue;
						}

						msg("%d: %s\n", currentField, buf);
						msg("Row is %d  Column is %d \n", rowCount, currentField);
					}

					msg("\n");
					rc = SQLFetch(hStmt);
					rowCount++;
				};

				rc = SQLFreeStmt(hStmt, SQL_DROP);

			}
			else
			{
				msg("Error: Number of fields in the result set is 0.\n");
			}

		}
		else {
			msg("SQL Failed\n");
			DisplayError(SQL_HANDLE_STMT, hStmt);
		}
	}
	else
	{
		msg("Couldn't connect to %s\n", connect_str);
		DisplayError(SQL_HANDLE_DBC, hDbc);
	}

	/* Отключение соединения и очистка дескрипторов */
	SQLDisconnect(hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);


#pragma endregion 


#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1024
	//define handles and variables
	SQLHANDLE sqlConnHandle;   // идентификатор подключения
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLCHAR retconstring[SQL_RETURN_CODE_LEN];
	//initializations
	sqlConnHandle = nullptr;
	sqlStmtHandle = nullptr;



	SQLCHAR sqlVersion[SQL_RESULT_LEN];
	QString res = "ERROR";

	const QString dbname = "BlaBlaBla";
	QString dsn = QString("DRIVER={SQL Server};SERVER=%1;DATABASE=%2;Trusted=true;").arg(instance_name).arg(dbname);
	ui.label_link->setText(dsn);

	const std::string current_locale_text = dsn.toLocal8Bit().constData();

	const auto connection_str = (SQLCHAR *)current_locale_text.c_str();

	//allocations
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle)) // ВЫДЕЛЕНИЕ ПАМЯТИ ДЛЯ ИДЕНТИФИКАТОРА
		goto COMPLETED;
	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) // ВЫБОР ВЕРСИИ ODBC
		goto COMPLETED;
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle)) //ВЫДЕЛЕНИЕ ПАМЯТИ ДЛЯ ИДЕНТИФИКАТОРА ПОДКЛЮЧЕНИЯ
		goto COMPLETED;
	//output
	msg("Attempting connection to SQL Server... \n");

	//подключитесь к SQL Server  
	//не имеет значения, используете ли вы экземпляр по умолчанию или именованный экземпляр
	//просто убедитесь, что вы определили имя сервера и порт
	//У вас есть возможность использовать имя пользователя/пароль вместо доверенного соединения. но безопаснее использовать доверенное соединение
	//SQLCHAR connection_str[] = "DRIVER={SQL Server};SERVER=LOCALHOST\\PCSQL;DATABASE=BlaBlaBla;Trusted=true;";


	if (mdbg) msg(" Connect str = %s", connection_str);

	switch (SQLDriverConnect(sqlConnHandle,
		NULL,
		connection_str,
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {
		
	case SQL_SUCCESS:
	case SQL_SUCCESS_WITH_INFO:
		msg("Successfully connected to SQL Server \n");
		break;
	//case SQL_SUCCESS_WITH_INFO:
	//	msg("Successfully connected to SQL Server \n");
	//	break;
	case SQL_INVALID_HANDLE:
		msg("Could not connect to SQL Server SQL_INVALID_HANDLE \n");
		goto COMPLETED;
	case SQL_ERROR:
		msg("Could not connect to SQL Server SQL_ERROR \n");
		goto COMPLETED;
	default:
		break;
	}
	//if there is a problem connecting then exit application
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
	{
		goto COMPLETED;
	}
	//output
	msg("Executing T-SQL query... \n");
	// если возникла проблема с выполнением запроса, то выйдите из приложения
	// в противном случае отобразить результат запроса
	// SQLExecDirect — это самый быстрый способ отправки инструкции SQL для однократного выполнения.
	// https://learn.microsoft.com/ru-ru/sql/odbc/reference/syntax/sqlexecdirect-function?view=sql-server-ver16
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)"SELECT @@VERSION", SQL_NTS)) {
		msg("Error querying SQL Server \n");
		goto COMPLETED;
	}
	else {
		// https://learn.microsoft.com/en-us/sql/odbc/reference/develop-app/connecting-with-sqlconnect?redirectedfrom=MSDN&view=sql-server-ver16
		if (SQL_SUCCESS == SQLExecDirectA(sqlStmtHandle,
			(SQLCHAR*)"CREATE TABLE mytable ",
			SQL_NTS))
		{
			msg("CREATE TABLE for  SQL Server !!! \n");
		}


		// объявить выходную переменную и указатель
		SQLLEN *ptrSqlVersion = nullptr;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, sqlVersion, SQL_RESULT_LEN, ptrSqlVersion);
			//display query result
			msg("\nQuery Result:\n\n");
			msg(" version = %s ", sqlVersion);
			res = "CONNECTION";
			goto COMPLETED;
		}
	}
	//close connection and free resources
	//Когда вы закончите работу с базой данных, вы должны закрыть связь с ней следующим образом :
	//Отключится от источника данных
	//	Уничтожить идентификатор соединения
	//	Уничтожить идентификатор окружения(если вы не желаете использовать это окружение для других соединений)
COMPLETED:
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);

	return res;
}

/**
 * \brief \n Выведем в панель вывода сообщения о том , как пользоваться
 * и настроить доступ с помощью ODBC драйвера к SQL базе данных ...
 */
void DBConnection::FormSetHelp() const
{
	msg("\n\n");
	msg("\t\tAbout Create ODBC connection +++++++++++++++++++++++++++++++++++\n");
	msg("\t\tMESSAGE STRING ONE\n");
	msg("\t\tMESSAGE STRING TWO\n");
	msg("\t\tMESSAGE STRING NEXT...\n");
	msg("\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	msg("\n\n");
}





#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>



void DBConnection::AddSetting()
{
	auto instance_name = (ui.lineEdit->text()).trimmed();

	if (instance_name == "")
	{
		msg("\nSQL server connection error - not an instance name\n");
		emit send_to_object(false);
		sql_connection_state = false;
		this->close();
		return;
	}


	instance_name = QString("LOCALHOST").append("\\").append(instance_name);
	ui.label_link->setText(instance_name);


	const auto res = CheckSQLConnection(instance_name);

	if (res == "ERROR")
	{
		msg("SQL server connection error ");
		Settings::setMSSQLInstance( "");
		emit send_to_object(false);
		return;
	}
	if (res == "CONNECTION")
	{
		Settings::setMSSQLInstance( instance_name);
		emit send_to_object(true);
		sql_connection_state = true;
	}
	msg("There is a connection to the SQL server !!!! \n");

	this->close();



	// msg(" Drivers SQL Database is : %s", (QSqlDatabase::drivers().join(",")).toStdString().c_str());

	QString servername = "LOCALHOST\\PCSQL";
	QString dbname = "BlaBlaBla";
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "connection");
	// QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");

	db.setConnectOptions();

	QString dsn = QString("DRIVER={SQL Server};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes").arg(servername).arg(dbname);


	db.setDatabaseName(dsn);

	if (db.open())
	{
		msg ("\nOpened  - QT DataBase Method OPEN BBB DATABASE !!!! ");
		// db.close();
	}


	// https://russianblogs.com/article/97831455452/ или локально  file:///D:/Documents/HelpAndManual%20Projects/Projects/Ida%20Plugin/HTML/Qt_usingDB.html
	QSqlDatabase db2 = QSqlDatabase::database("connection");
	QSqlQuery query2(db2);

	query2.exec("create table demo (id int primary key,"
		"name varchar(20))");
	query2.exec("insert into demo values(0, 'Mike')");
	query2.exec("insert into demo values(1, 'Lili')");
	query2.exec("insert into demo values(2, 'Jame')");

	query2.exec("create table student (id int primary key,"
		"name varchar(20))");
	query2.exec("insert into student values(0, 'Mike')");
	query2.exec("insert into student values(1, 'Lili')");
	query2.exec("insert into student values(2, 'Jame')");

	//QSqlTableModel model;
	//model.setTable("student");
	//QTableView *view = new QTableView;
	//view->setModel(&model);
	//view->show();
	
	


	// Удаляем таблицу перед выходом
	// query.exec("DROP TABLE User");
	
	msg("\nALL Make into DB");
	// Не обязательно, но в крупной системе лучше закрывать соединение с БД, когда оно больше не требуется
	db.close();
	

}