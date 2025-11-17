#pragma once
#include <QtWidgets/QWidget>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtGui/qevent.h>
#include "pro.h"
#include <kernwin.hpp>
#include "help_functions.h"
#include "all_include.h"

#include "ui_notepad_window.h"
#include "key_press_eater.hpp"

QT_BEGIN_NAMESPACE
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class NotepadWindow : public QWidget {
	Q_OBJECT

public:
	NotepadWindow(QWidget* parent = Q_NULLPTR);
	~NotepadWindow();

protected:
	void closeEvent(QCloseEvent* event) override;	// переопределим событие при закрытии блокнота
	void showEvent(QShowEvent* event) override;		// переопределим событие при открытии блокнота
	void resizeEvent(QResizeEvent*) override;		// переопределим событие изменения размера NotepadWindow

	static void create_notepad_file(const QString& filename);



private:
	Ui::NotepadWindow ui;

	QPushButton* ui_findButton;
	QTextEdit* ui_textEdit;
	QLineEdit* ui_lineEdit;
	bool isFirstTime;

	QTimer* timer; // таймер для сохранения файла ...


	private slots:
	// смотреть форму как это соединение назначено ...
	void on_findButton_clicked();


	// функции реализации нажатия клавиш в блокноте
	//************************

	static void add_tab();
	static void add_space();
	static void add_enter();
	void add_ctrl_enter();
	static void add_simbol();
	void add_mouse_press();
	// слот для сохранения файлу по срабатыванию таймера .
	void save_file();

	//************************	

};


