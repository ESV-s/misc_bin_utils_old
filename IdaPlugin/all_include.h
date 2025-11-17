#pragma once
#include <QtWidgets/QtWidgets>
#include "Windows.h"
#include <iostream>
#include <ida.hpp>
#include <idp.hpp>
#include <nalt.hpp>
#include <netnode.hpp>
#include <fpro.h>
#include <pro.h>
#include <kernwin.hpp> // For get_screen_ea() definition
#include <funcs.hpp>
#include <loader.hpp>
#include <kernwin.hpp>
#include <memory>
#include <sstream>
#include <tuple>
#include <utility>
#include <map>
#include <functional>
#include <cstdarg>
#include <QtCore/QSet>
#include <filesystem>
#include <string>
#include <QtCore/QFile>
#include <loader.hpp>
#include <dbg.hpp>
#include <vector>


// определения для получения текущей директории 
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <process.h>
#include <direct.h>
#define GET_CURRENT_DIR _getcwd
#endif

/**
 * \brief \n Определим псевдоним security::binexport ...
 */
#define SB security::binexport


extern bool mdbg;
extern std::string PLUGIN_CURRENT_DIRECTORY;


/*                       РЕГИОН С ПОДСКАЗКАМИ ИЗ IDA include                    */

#pragma region Hints
/*
*      struct idainfo          ida.hpp                         параметры базы данных
*                                                              в структуре определены параметры для текущей программы и ещё много чего ...
*
*                                                              uval_t baseaddr;      ///< базовый адрес программы (абзацы)
*                                                              sel_t start_ss;       ///< селектор начального сегмента стека
*                                                              sel_t start_cs;       ///< селектор сегмента с основной точкой входа
*                                                              ea_t start_ip;        ///< Значение регистра IP в начале выполнения программы
*                                                              ea_t start_ea;        ///< Линейный адрес точки входа в программу
*                                                              ea_t start_sp;        ///< Значение регистра SP в начале выполнения программы
*                                                              ea_t main;            ///< адрес main()
*                                                              ea_t min_ea;          ///< текущие ограничения программы
*                                                              ea_t max_ea;          ///< maxEA исключен
*                                                              ea_t omin_ea;         ///< исходный minEA (устанавливается после загрузки входного файла)
*                                                              ea_t omax_ea;         ///< исходный maxEA (устанавливается после загрузки входного файла)

*                                                              ea_t lowoff;          ///< Нижний предел для смещений (используется при вычислении 'void' операндов)
*                                                              ea_t highoff;         ///< Верхний предел для смещений (используется при вычислении 'void' операндов)

*                                                              uval_t maxref;        ///< Макс хвост для справок

*                                                              range_t privrange;    ///< Диапазон адресов зарезервирован для внутреннего использования. Первоначально (MAXADDR, MAXADDR + 0x800000)
*                                                              sval_t netdelta;      ///< Значение дельты, которое будет добавлено ко всем адресам для сопоставления с сетевыми узлами. Первоначально 0

*                                                              /// ПЕРЕКРЕСТНЫЕ ССЫЛКИ

*                                                              uchar xrefnum;        ///< Количество ссылок для создания в листинге дизассемблирования
///< 0 - внешние ссылки не будут создаваться вообще

*                                                              uchar type_xrefnum;   ///< Количество ссылок для генерации в окнах struct и enum
///< 0 - внешние ссылки не будут создаваться вообще

*                                                              uchar refcmtnum;      ///< Количество строк комментариев, создаваемых для ссылок на строковые литералы или размеченные имена
///< 0 - такие комментарии генерироваться не будут

*                                                              uchar s_xrefflag;     ///< \ref SW_X
*
*  фаилы ресурсов             https://docs.microsoft.com/en-us/cpp/windows/resource-files-visual-studio?view=msvc-160
*                    ***      https://stackoverflow.com/questions/49033046/embedding-xml-string-resource-in-c-project
*                    ***      https://stackoverflow.com/questions/9240188/how-to-load-a-custom-binary-resource-in-a-vc-static-library-as-part-of-a-dll
*                    ***      https://stackoverflow.com/questions/531502/vc-resources-in-a-static-library
*                             https://docs.microsoft.com/en-us/windows/win32/menurc/using-resources
*
*
*  основные функции с примерами по адресу      http://www.openrce.org/reference_library/ida_sdk
*
*  события отладчика при загрузке библиотеки или любого другого модуля       https://hex-rays.com/products/ida/support/idadoc/1413.shtml
*                                   ЗДЕСЬ                                  https://habr.com/ru/post/435002/
*                                                                            https://temofeev.ru/info/articles/pishem-plagin-otladchik-dlya-snes-igr-v-ida-v7/
*
* Ida help                       https://hex-rays.com/products/ida/support/idadoc/
* Idc.idc                        https://hex-rays.com/products/ida/support/idadoc/162.shtml
*
*
*
*
* MSG PRINTF ОПРЕДЕЛЕНИЯ по адресу
* https://docs.microsoft.com/ru-ru/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions
*
*#define 	DOPT_LOAD_DINFO   0x00008000      автоматически загружать файлы отладки (pdb)
*
*
*
*
*        // https://cpp.hotexamples.com/examples/-/-/hook_to_notification_point/cpp-hook_to_notification_point-function-examples.html
// https://github.com/nihilus  https://github.com/nihilus/ScyllaHide
*
*/


#pragma endregion Hints

/*                       РЕГИОН ДЛЯ ОПРЕДЕЛЕНИЯ USING                    */

#pragma region Usings  

using string = QString;

template <typename T> using vector = std::vector<T>;

template <typename T1, typename T2> using pair = std::pair<T1, T2>;

template <typename ... Args> using tuple = std::tuple<Args...>;

using u_short_int = unsigned short int;


#pragma endregion Usings


/*                       ПРЕДВАРИТЕЛЬНЫЕ ОБЪЯВЛЕНИЯ ПЕРЕМЕННЫХ           */

#pragma region VARIABLES

const int MAX_FILEPATH = 255;		///< максимальная длина имени файла (PATH)

#pragma endregion VARIABLES


									/*                       SUPPORT FUNCTIONS REGION                        */

#pragma region SUPPORT FUNCTIONS



#pragma endregion SUPPORT FUNCTIONS

