#include "key_press_eater.hpp"


#include <QtGui/qevent.h>


KeyPressNotepad::KeyPressNotepad(QObject * parent) : QObject(parent) {

}

KeyPressNotepad::~KeyPressNotepad()
{

}



bool KeyPressNotepad::eventFilter(QObject * obj, QEvent * event)
{

	if (event->type() == QEvent::KeyPress) {
		const auto keyEvent = dynamic_cast <QKeyEvent *>(event);

		// msg("Ate key press %d \n", keyEvent->key());

		if (keyEvent->key() == Qt::Key_Space)
		{
			///msg("Space = %d \n", keyEvent->key());
			emit press_space();

		}

		if (keyEvent->key() == Qt::Key_Tab)
		{
			///msg("Tab = %d \n", keyEvent->key());
			emit press_tab();

		}

		/// если хотим послать сигнал enter 
		if ((keyEvent->key() == Qt::Key_Enter) || (keyEvent->key() == Qt::Key_Return))
		{
			/// если не нажата клавиши Control то идет сигнал Enter
			/// иначе будут идти 2 сигнала друг за другом
			/// enter а потом ctrl_enter
			if (!(keyEvent->modifiers() & Qt::ControlModifier)) {
				///msg("Enter = %d \n", keyEvent->key());
				emit press_enter();
			}

		}

		// https://russianblogs.com/article/1775498419/

		if (keyEvent->key() == Qt::Key_Return && (keyEvent->modifiers() & Qt::ControlModifier))
		{
			
			///msg("Control + Enter Press !!!\n");
			emit press_ctrl_enter();

		}

		if ((32 < keyEvent->key()) && (keyEvent->key() < 127))
		{
			///msg("Symbol = %d \n", keyEvent->key());
			emit press_simbol();

		}

		if ((1039 < keyEvent->key()) && (keyEvent->key() < 1072))
		{
			///msg("Symbol = %d \n", keyEvent->key());
			emit press_simbol();

		}
			// этот сигнал всегда испускается !!!
			emit mouse_press();
	}


	/// standard event processing
	return QObject::eventFilter(obj, event);
}

