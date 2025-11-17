#include "key_press_cmdline.h"
#include <QtGui/qevent.h>

KeyPressCMDLine::KeyPressCMDLine(QObject * parent) : QObject(parent) {

}

KeyPressCMDLine::~KeyPressCMDLine()
= default;

bool KeyPressCMDLine::eventFilter(QObject * obj, QEvent * event)
{
	try
	{
		if (event->type() == QEvent::KeyPress)
		{
			const auto keyEvent = dynamic_cast <QKeyEvent *>(event);

			/// если хотим послать сигнал enter 
			if ((keyEvent->key() == Qt::Key_Enter) || (keyEvent->key() == Qt::Key_Return))
			{
				emit press_enter();
			}
		}
	}
	catch (const std::exception& error)
	{
		msg("    KeyPressCMDLine::eventFilter: %s\n", error.what());
	}


	/// standard event processing
	return QObject::eventFilter(obj, event);
}
