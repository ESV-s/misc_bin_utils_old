#pragma once
#include <QtCore/QObject>

#include "pro.h"
#include <kernwin.hpp>



///  \brief \n
///  ласс дл¤ обработки нажати¤ клавиш в editLine_CMDLine стартового окна.\n
/// ќбрабатывает нажати¤ клавиш Enter\n
/// ќстальные нажати¤ клавиш пропускает ...\n
/// ¬з¤то отсюда https://doc.qt.io/qt-5/qobject.html#installEventFilter \n
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



