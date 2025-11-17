#pragma once
#include <QtCore/QObject>

#include "pro.h"
#include <kernwin.hpp>


/**
*  \brief \n
* Класс для обработки нажатия клавиш в editLine_CMDLine стартового окна.\n
* Обрабатывает нажатия клавиш Enter\n
* Остальные нажатия клавиш пропускает ...\n
* Взято отсюда https://doc.qt.io/qt-5/qobject.html#installEventFilter \n
*/
class KeyPressCMDLine : public QObject {
	Q_OBJECT

public:
	KeyPressCMDLine(QObject * parent = Q_NULLPTR);
	~KeyPressCMDLine();

signals: // сигналы о нажатии клавиш ...

	void press_enter();

protected:
	bool eventFilter(QObject *obj, QEvent *event) override;

private:

};



