#pragma once
#include "all_include.h"


//#include <memory>
//
//#include <cstdio>
//#include <cstdlib>



/// Структура содержащая данные о секциях PE
struct PE_SECTION {
	std::string     name;
	DWORD		virtual_size;
	DWORD		virtual_address;
	DWORD       size_of_raw_data;
	DWORD		pointer_to_raw_data;
	DWORD		pointer_to_relocations;
	DWORD		pointer_to_line_numbers;
	WORD		number_of_relocations;
	WORD		number_of_line_numbers;
	DWORD	    characteristics;
};

/// Структура с данными DOS HEADER исследуемого файла 
struct PE_IMAGE_DOS_HEADER {
	WORD e_magic;    //0X00  ※Magic DOS signature MZ(4Dh 5Ah): MZ mark: used to mark whether it is an executable file
	WORD e_cblp;     //0X02  Bytes on last page of file
	WORD e_cp;       //0X04  Pages in file
	WORD e_crlc;     //0X06  Relocations
	WORD e_cparhdr;  //0X08 Size of header in paragraphs
	WORD e_minalloc; //0X0A Minimum extra paragraphs needs
	WORD e_maxalloc; //0X0C maximum extra paragraphs needs
	WORD e_ss;       //0X0E initial(relative)SS value
	WORD e_sp;       //0X10 initial SP value
	WORD e_csum;     //0X12 Checksum
	WORD e_ip;       //0X14 initial IP value
	WORD e_cs;       //0X16 initial(relative)CS value
	WORD e_lfarlc;   //0X18 File Address of relocation table
	WORD e_ovno;     //0X1A Overlay number
	WORD e_res[4];   //0x1C Reserved words
	WORD e_oemid;    //0x24 OEM identifier(for e_oeminfo)
	WORD e_oeminfo;  //0x26 OEM information;e_oemid specific
	WORD e_res2[10]; //0x28 Reserved words
	DWORD e_lfanew;  //0x3C ※Offset to start of PE header: locate the PE file, the offset of the PE header relative to the file
};

/// Структура с данными OPTIONAL HEADER
//Optional PE header
struct PE_IMAGE_OPTIONAL_HEADER {
	WORD Magic;                    // 0x00 ※Magic number (magic number), 0x0107: ROM image, 0x010B: 32-bit PE, 0X020B: 64-bit PE 
								   //0x02 BYTE MajorLinkerVersion; //Connector major version number
								   //0x03 BYTE MinorLinkerVersion; //Connector minor version number
	DWORD SizeOfCode;              //0x04   The total size of all code segments, note: must be an integer multiple of FileAlignment, exists but is useless
	DWORD SizeOfInitializedData;   //0x08   The size of the data has been initialized. Note: It must be an integer multiple of FileAlignment, which exists but is useless
	DWORD SizeOfUninitializedData; //0x0c   The size of uninitialized data, note: must be an integer multiple of FileAlignment, exists but is useless
	DWORD AddressOfEntryPoint;     //0x10   ※ Program entry address OEP, this is an RVA (Relative Virtual Address), usually in .textsection, this field is applicable to DLLs/EXEs.
	DWORD BaseOfCode;              //0x14   The starting address of the code segment (code base address), (the beginning of the code is not necessarily related to the program)
	DWORD BaseOfData;              //0x18   Start address of the data segment (data base address)
	DWORD ImageBase;               //0x1c   ※Base address of memory mirror (default loading start address), default is 4000H
	DWORD SectionAlignment;        //0x20   ※Memory alignment: Once mapped into memory, each section is guaranteed to start with a "multiple of this value" virtual address
	DWORD FileAlignment;           //0x24   ※ Document alignment: initially 200H, now 1000H
								   //0x28 WORD MajorOperatingSystemVersion; //Required operating system major version number
								   //0x2a WORD MinorOperatingSystemVersion; //Required operating system minor version number
								   //0x2c WORD MajorImageVersion; //Custom major version number, use the parameter setting of the connector, eg:LINK /VERSION:2.0 myobj.obj
								   //0x2e WORD MinorImageVersion; //Custom sub-version number, use the parameter settings of the connector
								   //0x30 WORD MajorSubsystemVersion; //The major version number of the required subsystem, typical value 4.0 (Windows 4.0/Windows 95)
								   //0x32 WORD MinorSubsystemVersion; //Subsystem version number required
								   //0x34 DWORD Win32VersionValue; //Always 0
	DWORD SizeOfImage;         //0x38   ※The total size of the image of the PE file in memory, sizeof(ImageBuffer), multiple of SectionAlignment
	DWORD SizeOfHeaders;       //0x3c   ※DOS header (64B) + PE mark (4B) + standard PE header (20B) + optional PE header + total size of section table, according to file alignment (multiple of FileAlignment)
	DWORD CheckSum;            //0x40   The CRC checksum of the PE file to determine whether the file has been modified
							   //0x44 WORD Subsystem; //Subsystem type used by user interface
							   //0x46 WORD DllCharacteristics; //Always 0
	DWORD SizeOfStackReserve;  //0x48   The reserved size of the default thread initialization stack
	DWORD SizeOfStackCommit;   //0x4c   The size of the thread stack actually submitted during initialization
	DWORD SizeOfHeapReserve;   //0x50   The virtual memory size reserved for the initialized process heap by default
	DWORD SizeOfHeapCommit;    //0x54   The actual process heap size submitted during initialization
							   //0x58 DWORD LoaderFlags; //Always 0
	DWORD NumberOfRvaAndSizes; //0x5c   Number of directory items: always 0X00000010H(16)
};

/// Структура описывающая функции исследуемого файла
struct PE_FUNCTION_DATA {
	qstring function_name;
	ea_t    function_address;

};



/// \n
/// \n
/// Структура с данными функций из загружаемых в процессе отладки модулей \n
/// Это имена экспортируемых из модуля функций и адреса этих функций \n
/// Это функции модуля (dll например), которые загружаются в исследуемую программу ... \n
/// - mod_function_name         qstring         - Имя функции из загружаемого модуля (dll например)\n
/// Следующие два поля заполняются  или или
/// - mod_function_address      ea_t            - Адрес по которому вызывается функция
/// - mod_function_redirection  qstring         - Перенаправление на другую функцию (ws2_32.gethostbyaddr -> gethostbyaddr)
/// \n
/// \n
struct MODULE_FUNCTION_DATA {
	ushort      mod_function_ordinal;
	qstring     mod_function_name;
	ea_t        mod_function_address;
	qstring     mod_function_redirection;
};

/// Структура с данными модулей , загружаемых исследуемым файлом
/// в процессе отладки \n
/// - qstring module_name       полное имя модуля
/// - ea_t module_base             базовый адрес модуля. если неизвестно - #BADADDR
/// - asize_t module_size          размер модуля. если неизвестно - 0
/// - ea_t module_rebase_to     если не #BADADDR, то выполняет перезагрузку модуля по указанному адресу
/// - qvector function_list         вектор структур MODULE_FUNCTION_DATA \n \n
struct MODULE_DATA {
	qstring     module_name;                                ///< полное имя модуля
	ea_t        module_base;                                   ///< базовый адрес модуля. если неизвестно - #BADADDR
	asize_t     module_size;                                ///< размер модуля. если неизвестно - 0
	ea_t        module_rebase_to;                              ///< если не #BADADDR, то выполняет перезагрузку модуля по указанному адресу
	qvector<MODULE_FUNCTION_DATA> function_list;        ///< вектор структур MODULE_FUNCTION_DATA
														///< - mod_function_name    (qstring)
														///< - mod_function_address (ea_t)
};


/// <summary>
/// Преобразовать массив BYTE в std::string
/// </summary>
/// <param name="ptr"> Указатель на массив</param>
/// <param name="Size">Размер массива (sizeof)</param>
/// <returns>std::string</returns>
std::string byte_to_str(BYTE const* ptr, size_t Size);

/// <summary>
/// Читаем заголовок исследуемого PE файла и записываем полученные данные\n
///
/// Данные записываются в созданные хранилища ...
///
/// </summary>
/// <returns>
/// - true      ALL OK
/// - false     INVALID_HANDLE_VALUE
/// - false     ERROR ReadFile (считывания байтов файла в память не удалось )    
/// </returns>
bool AddDataPEHeaders();

/// <summary>
/// Проитерируемся по всем функциям, исследуемого в Ida файла, \n
/// и получим для них данные  
///  - Address
///  - Name\n
/// и занесем эти данные в вектор - <code>         vec_pe_function_data</code>
/// </summary>
/// <returns>true</returns>
bool GetFunctionData();



/// <summary>
/// \n
/// \n
/// Читаем данные из загружаемого в процессе отладки модуля (dll например) \n
/// Маппим файл в память и получаем имена экспортируемых из файла функций и адреса этих функций ...\n
/// После чего заносим данные о функции в структуру MODULE_FUNCTION_DATA и ее уже \n
/// в qvector<MODULE_DATA> function_list  ...
/// \n
/// </summary>
/// <param name="f_name">		Имя загруженной в процессе отладки dll</param>
/// <param name="function_list">		Вектор экспортируемых из модуля функций с их адресами</param>
/// <param name="module_base">		Адрес базовой загрузки длл из коллбека Ida. Он нам нужен для расчета адреса функции\n </param>
/// <returns> - true		- dll обработана 
///           - false		- не удалось загрузить dll ...\n\n</returns>
bool ReadModuleSections(const char* f_name, qvector<MODULE_FUNCTION_DATA>& function_list, const ea_t module_base);

/// <summary>
/// \n
/// Получаем данные из загружаемых в процессе отладки модулей \n
/// (dll например)\n
/// </summary>
/// <param name="modules_data"> Указатель на вектор с именами загружаемых модулей </param>
/// <returns> - true если Ок\n  - false если Err</returns>
bool  GetDataFromModule(qvector<MODULE_DATA>& modules_data);

/// <summary>
/// Проецируем фаил в память ...\n
/// </summary>
/// <param name="lpszFileName">const char*</param>
/// <returns>указатель на массив байт (unsigned char*)</returns>
LPBYTE OpenPEFile(const char* lpszFileName);


/// Закроем фаил (освободим память) 
void ClosePEFile(LPBYTE pBase);

/// Пробежим по заголовкам и получим имя секции ...
IMAGE_SECTION_HEADER* GetSection(IMAGE_NT_HEADERS* pHeader, DWORD dwRVA);

///Получим указатель на заголовок PE ...
IMAGE_NT_HEADERS* GetHeader(LPBYTE pBase);

/// <summary>
/// 
/// </summary>
/// <param name="pBase"></param>
/// <param name="dwRVA"></param>
/// <returns></returns>
LPBYTE GetFilePointer(LPBYTE pBase, DWORD dwRVA);

void get_current_plugin_directory();

void get_collection_api_files(const std::string& path);

// [STACK] --- begin ---
/**
* \brief Получить OptionalHeader.SizeOfStackReserve из уже разобранного PE.
* \return Значение в байтах; 0 если заголовок ещё не разобран/нет данных.
*/
DWORD GetPeSizeOfStackReserve();

/**
* \brief Получить OptionalHeader.SizeOfStackCommit из уже разобранного PE.
* \return Значение в байтах; 0 если заголовок ещё не разобран/нет данных.
*/
DWORD GetPeSizeOfStackCommit();
// [STACK] --- end ---
