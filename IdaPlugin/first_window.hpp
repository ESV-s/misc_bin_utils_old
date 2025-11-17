#pragma once
#include <QtWidgets/QtWidgets>
#include "ui_first_window.h"
#include <QtNetwork/QHostInfo>


#include "pro.h"
#include "all_include.h"
#include "db_connection.hpp"




/*

Места хранения настроек в Windows

HKEY_CURRENT_USER\Software\MySoft\Star Runner
HKEY_CURRENT_USER\Software\MySoft\OrganizationDefaults
HKEY_LOCAL_MACHINE\Software\MySoft\Star Runner
HKEY_LOCAL_MACHINE\Software\MySoft\OrganizationDefaults

Note: В Windows для 32-битных программ, работающих в режиме WOW64,
настройки хранятся в следующем пути реестра:
HKEY_LOCAL_MACHINE\Software\WOW6432node.

*/

//QT_BEGIN_NAMESPACE
//class QPushButton;
//class QCheckBox;
//class QTextEdit;
//class QLineEdit;
//QT_END_NAMESPACE

class FirstWindow : public QWidget {
	Q_OBJECT

public:
	FirstWindow(QWidget * parent = Q_NULLPTR);
	~FirstWindow();


	
protected:
	void closeEvent(QCloseEvent* event) override;	// переопределим событие при закрытии блокнота
	void showEvent(QShowEvent* event) override;		// переопределим событие при открытии блокнота
	void CheckSettings() const;

	

	private slots:
	void AddScylla() const;
	void sql_connection_form_show();
	void AddMSSQL();
	void SetTextToForm(bool value) const;
	void StartAfterDebug() const;
	void ColorFunctions() const;
	void PrintInfo() const;
	void PrintInfoFunctionData() const;
	void PrintInfoMangledName() const;
	void PrintInfoOutputCleaning() const;
	void PrintInfoContainerSize() const;
	void FixedLocation() const;
	
	
	// https://habr.com/ru/articles/51650/
	// https://harrix.dev/blog/2014/connect-to-sql-server-in-qt/
	// https://russianblogs.com/article/75971552880/
	// https://evileg.com/ru/post/62/
	
	void CheckScylla() const;
	void CheckMSSQL() const;
	void CheckDebug() const;
	void CheckColoring() const;
	void CheckPrintInfo() const;
	void CheckPrintInfoFunctionData() const;
	void CheckPrintInfoMangledName() const;
	void CheckPrintInfoOutputCleaning() const;
	void CheckPrintInfoContainerSize() const;
	void CheckFixedLocation() const;

	
private:
	Ui::FirstWindow ui;
	DBConnection sql_connection_form;
};
