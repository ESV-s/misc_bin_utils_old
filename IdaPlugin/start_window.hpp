#pragma once
#include <QtWidgets/QtWidgets>



#include "first_window.hpp"
#include "notepad_window.hpp"
#include "binexport_class.hpp"
#include "ui_start_window.h"
#include "key_press_cmdline.h"
#include "function_utils.h"


QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE


/**
 * \brief \n 
 * Класс главного (стартового ) окна плагина \n
 * Отображается при запуске, выполняет функции ReadIdaDB()...
 */
class StartWindow : public QWidget {
	Q_OBJECT

public:

	StartWindow(QWidget * parent = Q_NULLPTR);
	~StartWindow();
protected:
	// void keyPressEvent(QKeyEvent *event) override;
	
private:
	Ui::StartWindow ui;
	FirstWindow setting_form;
	NotepadWindow notepad_form;
	BinExportClass binexport_form;

    std::vector<func_t*> function_vector{};
	std::vector<std::string> string_vector{};
	int ReadIdaDB();



	QLineEdit* ui_CMDLine;

	
	private slots:

	void setting_form_show();
	void notepad_form_show();
	void binexport_form_show();

	void PressEnter();
	
};
