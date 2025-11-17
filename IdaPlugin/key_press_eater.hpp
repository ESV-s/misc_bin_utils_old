
#pragma once
#include <QtCore/QObject>

#include "pro.h"
#include <kernwin.hpp>



/**
 *  \brief \n
 * Класс для обработки нажатия клавиш в editText блокнота.\n
 * Обрабатывает нажатия клавиш Tab Space Enter и Control,\n
 * Остальные нажатия клавиш пропускает ...\n
 * Взято отсюда https://doc.qt.io/qt-5/qobject.html#installEventFilter \n
 */
class KeyPressNotepad : public QObject {
	Q_OBJECT

public:
	KeyPressNotepad(QObject * parent = Q_NULLPTR);
	~KeyPressNotepad();

	signals: // сигналы о нажатии клавиш ...

	void press_tab();
	void press_space();
	void press_enter();
	void press_ctrl_enter();
	void press_simbol();
	void mouse_press();
	
	
	

protected:
	bool eventFilter(QObject *obj, QEvent *event) override;

private:
	
};
