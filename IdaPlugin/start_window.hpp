/*! \file start_window.hpp
 *
 * \brief \n Фаил содержит описание стартового окна плагина ,  при запуске плагина в IDA ... \n
 *
 *	Описывает класс StartWindow
 *	в этом классе содержатся формы для работы с
 *	- setting_form		см \ref StartWindow::setting_form 
 *	- notepad_form		см \ref StartWindow::notepad_form 
 *	- binexport_form	см \ref StartWindow::binexport_form  
 */

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



/// \brief \n
/// Класс главного (__стартового__) окна плагина \n
/// Отображается при запуске, выполняет функции \ref ReadIdaDB...
///
/// в этом классе содержатся формы для работы с
/// - setting_form  см \ref StartWindow::setting_form
/// - notepad_form  см \ref StartWindow::notepad_form
/// - binexport_form см \ref StartWindow::binexport_form
///
/// \n\n
/// \ingroup VIEW_W UI_W
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
