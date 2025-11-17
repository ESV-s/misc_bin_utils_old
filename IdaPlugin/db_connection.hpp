#pragma once
#include <QtWidgets/QWidget>
#include <QtCore/qsettings.h>

#include "ui_db_connection.h"
#include "pro.h"
#include <QtCore/QString>

#include <windows.h>
#include <kernwin.hpp>
#include "all_include.h"


#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>


#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

#include "settings.h"

class DBConnection : public QWidget {
	Q_OBJECT

public:
	/// \brief Публичная проверка соединения, обёртка вокруг приватного CheckSQLConnection().
	/// \param instance Имя экземпляра MSSQL.
	/// \return true при успешном соединении, иначе false.
	static bool TryConnect(const QString& instance);

	DBConnection(QWidget * parent = Q_NULLPTR);
	~DBConnection();
private:
	Ui::DBConnection ui;

	void closeEvent(QCloseEvent *event)override;


	QString CheckSQLConnection(const QString &instance_name);

	private slots:
	void AddSetting();
	void FormSetHelp() const;

signals:
	void send_to_object(bool); //будем отправлять величину типа bool

};
