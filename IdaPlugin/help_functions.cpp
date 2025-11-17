#include "help_functions.h"

#include <QtCore/qtextstream.h>


bool file_txt_exists(const QString & file_name)
{
	QFile file(file_name);
	if (file.open(QFile::ReadWrite | QFile::Text))
	{
		return true;
	}

	return false;
}

QString get_end_line(const QString & file_name)
{
	QString line = "";
	QFile inputFile(file_name);
	if (inputFile.open(QIODevice::ReadOnly))
	{
		QTextStream in(&inputFile);
		while (!in.atEnd())
		{
			line = in.readLine();
			// здесь обрабатываем строку 
		}
		inputFile.close();
	}
	return line;
}

QString get_line_first_word(const QString & line)
{
	//QString str = "\tDo    re\nmi"; // tabs and newlines and spaces, oh my!
	QString firstWord = line.section(QRegExp("\\s+"), 0, 0,
		QString::SectionSkipEmpty);
	return firstWord;
}

QString get_line_split_part(const QString & line, const QString &word, const int index)
{
	QString str = line.split(word).at(index);
	return str;
}

bool IsHexadecimal(const std::string & str)
{
	auto tmp_str = str;
	if (tmp_str[0]== '0' && tmp_str[1] =='x' )
	{
		tmp_str.erase(0, 2);
	}
	if (tmp_str.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos) {
		return false;
	}

	return true;
}
