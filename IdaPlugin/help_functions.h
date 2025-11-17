#pragma once
#include "QtCore/QString"
#include "QtCore/QFile"
#include <string.h>

#pragma region File
/// проверить существование текстового файла
/// 
bool file_txt_exists(const QString &file_name);

QString get_end_line(const QString &file_name);

#pragma endregion File


#pragma region QString

/// получить первое слово в строке без учета спец символов \n
/// 
/// например если есть в строке пробелы в начале или tab ... \n
/// str = "\tDo    re\nmi";   \n вернет  "Do"
QString get_line_first_word(const QString &line);

/// получить по индексу часть строки после применения функции split \n

/// line - строка \n
/// word - слово или символ в строке \n
QString get_line_split_part(const QString &line, const QString &word,const int index);

#pragma endregion QString

#pragma region String

bool IsHexadecimal(const std::string& s) ;


#pragma endregion String