

#include "notepad_window.hpp"
#include <QtCore/qtextstream.h>
#include <QtGui/qtextobject.h>  // для чтения текста из блока
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/QTextEdit>


/**
 * \brief \n получим адрес папки плагина и добавим к нему имя фаила для сохранения записеи блокнота ...\n
 */
const QString filename = QProcessEnvironment::systemEnvironment().value("IDA76_PLUGIN_DIR").append("\\BlaBlaBla.txt");


/**
 * \brief \n последняя строка в тексте ... \n
 */
QString end_line;

/**
 * \brief \n строка которую будем добавлять в начало новой строки ...\n
 */
QString start_string = "\n";
QString tmp_string = "\n";

bool has_tab;
bool write_symbol;

int timer_interval = 30000; // sec = TIMER_INTERVAL/1000

NotepadWindow::NotepadWindow(QWidget* parent) : QWidget(parent) {
	ui.setupUi(this);

	// https://stackoverflow.com/questions/45880941/replace-all-tab-operations-with-inserting-four-spaces-in-qplaintextedit-widget
	ui.textEdit->setTabStopWidth(24);// ширина таба в пикселях ( по умолчанию она 80)


	 // https://doc.qt.io/qt-5/qobject.html#installEventFilter
	 // создадим фильтр событии для ui.textEdit
	 // и назначим этот фильтр на события ввода с клавиатуры в textEdit
	KeyPressNotepad* keyPressNotepad = new KeyPressNotepad(this);
	ui.textEdit->installEventFilter(keyPressNotepad);
	//setCentralWidget(ui.textEdit);


	connect(keyPressNotepad, SIGNAL(press_tab()), SLOT(add_tab()));
	connect(keyPressNotepad, SIGNAL(press_space()), SLOT(add_space()));
	connect(keyPressNotepad, SIGNAL(press_enter()), SLOT(add_enter()));
	connect(keyPressNotepad, SIGNAL(press_ctrl_enter()), SLOT(add_ctrl_enter()));
	connect(keyPressNotepad, SIGNAL(press_simbol()), SLOT(add_simbol()));
	connect(keyPressNotepad, SIGNAL(mouse_press()), SLOT(add_mouse_press()));

	timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(save_file()));

}


void NotepadWindow::resizeEvent(QResizeEvent*)
{
	QRect size = geometry();
	ui.textEdit->setGeometry(2, 40, size.width() - 4, size.height() - 40);
}

NotepadWindow::~NotepadWindow() {
	delete timer;
	if (mdbg)  msg("Timer Delete with Widget Close \n");
}

void NotepadWindow::on_findButton_clicked()
{
	// msg(" Find make\n");

	ui_findButton = findChild<QPushButton*>("findButton");
	ui_textEdit = findChild<QTextEdit*>("textEdit");
	ui_lineEdit = findChild<QLineEdit*>("lineEdit");


	QString searchString = ui.lineEdit->text();
	QTextDocument* document = ui.textEdit->document();

	//searchString = searchString.simplified();


	bool found = false;

	if (isFirstTime == false)
		document->undo();


	if (searchString.isEmpty()) {
		ui.lineEdit->setText("Empty Search Field");

	}
	else {

		QTextCursor highlightCursor(document);
		QTextCursor cursor(document);

		cursor.beginEditBlock();
		QTextCharFormat plainFormat(highlightCursor.charFormat());
		QTextCharFormat colorFormat = plainFormat;
		colorFormat.setForeground(Qt::red);

		while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
			highlightCursor = document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);

			if (!highlightCursor.isNull()) {
				found = true;
				highlightCursor.movePosition(QTextCursor::WordRight,
					QTextCursor::KeepAnchor);
				highlightCursor.mergeCharFormat(colorFormat);
			}
		}

		cursor.endEditBlock();

		isFirstTime = false;

		if (found == false) {
			ui.lineEdit->setText("The word cannot be found.");
		}
	}
	if (mdbg)  msg("Find Button Clicked \n");
}

void NotepadWindow::closeEvent(QCloseEvent* event)
{
	timer->stop();
	if (mdbg)  msg("Timer Stop in Close event \n");
	// msg("  EVENT I _____ GET IT     !!!");
	QFile file(filename);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot write file %1:\n%2.")
			.arg(QDir::toNativeSeparators(filename),
				file.errorString()));
	}

	QTextStream out(&file);
	out << ui.textEdit->toPlainText();
	file.close();
	if (mdbg)  msg("File Saved \n");
	if (mdbg)  msg("File Close \n");
	ui.textEdit->setText("");
	if (mdbg)  msg("Text Edit Text = Nothing *************************************\n");
}

void NotepadWindow::showEvent(QShowEvent* event)
{
	if (!timer->isActive()) // если таймер остановлен ...
	{
		timer->start(timer_interval); // 60 sec
		if (mdbg)  msg("Timer start in Show Event \n");
	}

	// проверка наличия фаила или его создание.

	if (!QFileInfo::exists(filename) || QDir(filename).exists()) {
		//The file doesn't exist, either the path doesn't exist or is the path of a folder
		if (mdbg)  msg("File not found \n");
		ui.textEdit->setText("This is your notepad ... This file will be located at the path \n" + filename);
		create_notepad_file(filename);
	}
	else {
		//The file exists and is not a folder
		// файл существует - читаем из него текст и устанавливаем его в textEdit
		QFile file(filename);
		if (!file.open(QFile::ReadWrite | QFile::Text)) {
			QMessageBox::warning(this, tr("Application"),
				tr("Cannot read file %1:\n%2.")
				.arg(QDir::toNativeSeparators(filename), file.errorString()));
			return;
		}
		ui.textEdit->setText("");
		ui.lineEdit->setText("");
		QTextStream in(&file);
		QString txt = in.readAll();
		ui.textEdit->setPlainText(txt);
		file.close();
		if (mdbg)  msg("File Close \n");
		if (mdbg)  msg("Text will be copy from file to text Edit *********************\n");
		// получим последнюю строку в тексте ...
		end_line = get_end_line(filename);

		// обработаем последнюю строку , если в неи есть пробелы ...
		if (end_line.startsWith("\t")) // если строка начинается с tab
		{
			const auto first_word = get_line_first_word(end_line);
			end_line = get_line_split_part(end_line, first_word, 0);
			start_string = start_string + end_line;
			// msg("\nStart string now = %s \n", start_string.toStdString().c_str());
		}
	}

	QMetaObject::connectSlotsByName(this);
	isFirstTime = true;

}

void NotepadWindow::create_notepad_file(const QString& filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadWrite)) {
		QTextStream stream(&file);
		stream << "";
		file.close();
		if (mdbg)  msg("New File Create  \n");
	}
}


/**
 * \brief \n  обработка нажатия клавиши в блокноте \n
 */
void NotepadWindow::add_tab()
{
	//msg(" tab plus \n");
	start_string = start_string.append("\t");
}

/**
 * \brief \n обработка нажатия клавиши в блокноте \n
 */
void NotepadWindow::add_space()
{
	//msg("I see space signal !!!\n");
}


/**
 * \brief \n обработка нажатия клавиши в блокноте \n
 */
void NotepadWindow::add_enter()
{
	//msg(" enter - all clear \n");
	start_string = "\n";
}

/**
* \brief \n обработка нажатия клавиши в блокноте \n
*/
void NotepadWindow::add_ctrl_enter()
{
	//msg(" ctrl_enter \n");
	ui.textEdit->insertPlainText(start_string);


}

/**
* \brief \n обработка нажатия клавиши в блокноте \n
*/
void NotepadWindow::add_simbol()
{
	//msg("I see simbol signal !!!\n");
}

void NotepadWindow::add_mouse_press()
{
	//msg(" MOUSE signal - get strings \n");
	auto current_line = ui.textEdit->textCursor().block().text();

	// обработаем последнюю строку , если в неи есть табы...
	if (current_line.startsWith("\t")) // если строка начинается с tab
	{
		//msg(" String with Tab \n");
		if (!current_line.isEmpty())
		{
			//msg(" String not Empty and have tab \n");
			const auto first_word = get_line_first_word(current_line);
			current_line = get_line_split_part(current_line, first_word, 0);
			start_string = "\n" + current_line;
		}

		// msg("\nStart string now = %s \n", start_string.toStdString().c_str());
	}
}

void NotepadWindow::save_file()
{
	QFile file(filename);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
			tr("Cannot write file %1:\n%2.")
			.arg(QDir::toNativeSeparators(filename),
				file.errorString()));
	}

	QTextStream out(&file);
	out << ui.textEdit->toPlainText();
	file.close();
	if (mdbg)  msg("Timer Save File \n");
}
