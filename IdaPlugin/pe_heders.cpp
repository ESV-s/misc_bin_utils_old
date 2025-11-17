#include "pe_heders.h"



/// Вектор модулей (dll) загруженных в процессе отладки
///
/// Содержит: \n
/// - qstring    module_name - имя модуля загруженного в процесс при запуске и выполнении отладчика
/// - ea_t       module_base 
/// - asize_t    module_size
/// - ea_t       module_rebase_to \n
///   получает данные из функции dbg_callback() \n
/// - qvector<MODULE_FUNCTION_DATA> function_list - список функций модуля с адресами загрузки \n 
///   получает данные из PeLibrary.dll \n
qvector<MODULE_DATA> modules_data{};


std::string PLUGIN_CURRENT_DIRECTORY{};

/// Экземпляр Структуры с данными DOS HEADER исследуемого файла 
PE_IMAGE_DOS_HEADER pe_image_dos_header;

/// Экземпляр структуры PE_IMAGE_OPTIONAL_HEADER с данными исследуемого фаила 
PE_IMAGE_OPTIONAL_HEADER pe_image_optional_header;

/// вектор с данными о секциях PE исследуемого файла .
qvector<PE_SECTION> vec_pe_sections;

/// вектор с описанием функций исследуемого PE файла
qvector<PE_FUNCTION_DATA> vec_pe_function_data;

std::string byte_to_str(BYTE const* ptr, size_t Size) {
	std::stringstream str;
	size_t const BuffSize = 10;
	char Buff[BuffSize];

	for (size_t i = 0; i < Size; ++i)
	{
		sprintf_s(Buff, BuffSize, "0x%.2lx", ptr[i]);
		str << Buff;

		if (i != (Size - 1))
		{
			str << " ";
		}
	}

	return (str.str());
}

bool AddDataPEHeaders() {

	char f_name[MAX_FILEPATH] = { 0 };

	// получим имя текущего файла 
	const auto s1 = get_input_file_path(f_name, MAX_FILEPATH);

	// переменная имени фиала 
	char fileName[MAX_FILEPATH] = { 0 };

	// перемещаем в имя фаила для анализа заголовков - имя нашего исследуемого фаила 
	memcpy_s(&fileName, MAX_FILEPATH, f_name, MAX_FILEPATH);

	HANDLE file = nullptr;
	DWORD fileSize = NULL;
	DWORD bytesRead = NULL;
	LPVOID fileData = nullptr;
	PIMAGE_DOS_HEADER dosHeader = {};
	PIMAGE_NT_HEADERS imageNTHeaders = {};
	PIMAGE_SECTION_HEADER sectionHeader = {};
	PIMAGE_SECTION_HEADER importSection = {};
	IMAGE_IMPORT_DESCRIPTOR* importDescriptor = {};
	PIMAGE_THUNK_DATA thunkData = {};
	DWORD thunk = NULL;
	DWORD rawOffset = NULL;

	// open file
	file = CreateFileA(fileName,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (file == INVALID_HANDLE_VALUE)
	{
		msg("Could not read file");
		return false;
	}
	// allocate heap
	fileSize = GetFileSize(file, nullptr);
	fileData = HeapAlloc(GetProcessHeap(), 0, fileSize);

	// read file bytes to memory
	const auto b = ReadFile(file, fileData, fileSize, &bytesRead, nullptr);

	if (b)
	{
		// IMAGE_DOS_HEADER
		dosHeader = static_cast<PIMAGE_DOS_HEADER>(fileData);

		pe_image_dos_header.e_magic = dosHeader->e_magic;

		pe_image_dos_header.e_cblp = dosHeader->e_cblp;

		pe_image_dos_header.e_cp = dosHeader->e_cp;

		pe_image_dos_header.e_crlc = dosHeader->e_crlc;

		pe_image_dos_header.e_cparhdr = dosHeader->e_cparhdr;

		pe_image_dos_header.e_minalloc = dosHeader->e_minalloc;

		pe_image_dos_header.e_maxalloc = dosHeader->e_maxalloc;

		pe_image_dos_header.e_ss = dosHeader->e_ss;

		pe_image_dos_header.e_sp = dosHeader->e_sp;

		pe_image_dos_header.e_csum = dosHeader->e_csum;

		pe_image_dos_header.e_ip = dosHeader->e_ip;

		pe_image_dos_header.e_cs = dosHeader->e_cs;

		pe_image_dos_header.e_lfarlc = dosHeader->e_lfarlc;

		pe_image_dos_header.e_ovno = dosHeader->e_ovno;

		pe_image_dos_header.e_oemid = dosHeader->e_oemid;

		pe_image_dos_header.e_oeminfo = dosHeader->e_oeminfo;

		pe_image_dos_header.e_lfanew = dosHeader->e_lfanew;

		if (mdbg)
		{
			msg("******* DOS HEADER *******\n");
			msg("\t0x%x\t\tMagic number\n", dosHeader->e_magic);
			msg("\t0x%x\t\tBytes on last page of file\n", dosHeader->e_cblp);
			msg("\t0x%x\t\tPages in file\n", dosHeader->e_cp);
			msg("\t0x%x\t\tRelocations\n", dosHeader->e_crlc);
			msg("\t0x%x\t\tSize of header in paragraphs\n", dosHeader->e_cparhdr);
			msg("\t0x%x\t\tMinimum extra paragraphs needed\n", dosHeader->e_minalloc);
			msg("\t0x%x\t\tMaximum extra paragraphs needed\n", dosHeader->e_maxalloc);
			msg("\t0x%x\t\tInitial (relative) SS value\n", dosHeader->e_ss);
			msg("\t0x%x\t\tInitial SP value\n", dosHeader->e_sp);
			msg("\t0x%x\t\tChecksum\n", dosHeader->e_csum);
			msg("\t0x%x\t\tInitial IP value\n", dosHeader->e_ip);
			msg("\t0x%x\t\tInitial (relative) CS value\n", dosHeader->e_cs);
			msg("\t0x%x\t\tFile address of relocation table\n", dosHeader->e_lfarlc);
			msg("\t0x%x\t\tOverlay number\n", dosHeader->e_ovno);
			msg("\t0x%x\t\tOEM identifier (for e_oeminfo)\n", dosHeader->e_oemid);
			msg("\t0x%x\t\tOEM information; e_oemid specific\n", dosHeader->e_oeminfo);
			msg("\t0x%x\t\tFile address of new exe header\n", dosHeader->e_lfanew);
		}


		// IMAGE_NT_HEADERS
		imageNTHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<DWORD>(fileData) + dosHeader->e_lfanew);
		if (mdbg)
		{
			msg("\n******* NT HEADERS *******\n");
			msg("\t%x\t\tSignature\n", imageNTHeaders->Signature);
		}


		// FILE_HEADER
		if (mdbg)
		{
			msg("\n******* FILE HEADER *******\n");
			msg("\t0x%x\t\tMachine\n", imageNTHeaders->FileHeader.Machine);
			msg("\t0x%x\t\tNumber of Sections\n", imageNTHeaders->FileHeader.NumberOfSections);
			msg("\t0x%x\tTime Stamp\n", imageNTHeaders->FileHeader.TimeDateStamp);
			msg("\t0x%x\t\tPointer to Symbol Table\n", imageNTHeaders->FileHeader.PointerToSymbolTable);
			msg("\t0x%x\t\tNumber of Symbols\n", imageNTHeaders->FileHeader.NumberOfSymbols);
			msg("\t0x%x\t\tSize of Optional Header\n", imageNTHeaders->FileHeader.SizeOfOptionalHeader);
			msg("\t0x%x\t\tCharacteristics\n", imageNTHeaders->FileHeader.Characteristics);
		}


		// OPTIONAL_HEADER

		pe_image_optional_header.Magic = imageNTHeaders->OptionalHeader.Magic;

		pe_image_optional_header.SizeOfCode = imageNTHeaders->OptionalHeader.SizeOfCode;

		pe_image_optional_header.SizeOfInitializedData = imageNTHeaders->OptionalHeader.SizeOfInitializedData;

		pe_image_optional_header.SizeOfUninitializedData = imageNTHeaders->OptionalHeader.SizeOfUninitializedData;

		pe_image_optional_header.AddressOfEntryPoint = imageNTHeaders->OptionalHeader.AddressOfEntryPoint;

		pe_image_optional_header.BaseOfCode = imageNTHeaders->OptionalHeader.BaseOfCode;

		pe_image_optional_header.ImageBase = imageNTHeaders->OptionalHeader.ImageBase;

		pe_image_optional_header.SectionAlignment = imageNTHeaders->OptionalHeader.SectionAlignment;

		pe_image_optional_header.FileAlignment = imageNTHeaders->OptionalHeader.FileAlignment;

		pe_image_optional_header.SizeOfImage = imageNTHeaders->OptionalHeader.SizeOfImage;

		pe_image_optional_header.SizeOfHeaders = imageNTHeaders->OptionalHeader.SizeOfHeaders;

		pe_image_optional_header.CheckSum = imageNTHeaders->OptionalHeader.CheckSum;

		pe_image_optional_header.SizeOfStackReserve = imageNTHeaders->OptionalHeader.SizeOfStackReserve;

		pe_image_optional_header.SizeOfStackCommit = imageNTHeaders->OptionalHeader.SizeOfStackCommit;

		pe_image_optional_header.SizeOfHeapReserve = imageNTHeaders->OptionalHeader.SizeOfHeapReserve;

		pe_image_optional_header.SizeOfHeapCommit = imageNTHeaders->OptionalHeader.SizeOfHeapCommit;

		pe_image_optional_header.NumberOfRvaAndSizes = imageNTHeaders->OptionalHeader.NumberOfRvaAndSizes;

		if (mdbg)
		{


			msg("\n******* OPTIONAL HEADER *******\n");
			msg("\t0x%x\t\tMagic\n", imageNTHeaders->OptionalHeader.Magic);
			msg("\t0x%x\t\tMajor Linker Version\n", imageNTHeaders->OptionalHeader.MajorLinkerVersion);
			msg("\t0x%x\t\tMinor Linker Version\n", imageNTHeaders->OptionalHeader.MinorLinkerVersion);
			msg("\t0x%x\t\tSize Of Code\n", imageNTHeaders->OptionalHeader.SizeOfCode);
			msg("\t0x%x\t\tSize Of Initialized Data\n", imageNTHeaders->OptionalHeader.SizeOfInitializedData);
			msg("\t0x%x\t\tSize Of UnInitialized Data\n", imageNTHeaders->OptionalHeader.SizeOfUninitializedData);
			msg("\t0x%x\t\tAddress Of Entry Point (.text)\n", imageNTHeaders->OptionalHeader.AddressOfEntryPoint);
			msg("\t0x%x\t\tBase Of Code\n", imageNTHeaders->OptionalHeader.BaseOfCode);
			//msg("\t0x%x\t\tBase Of Data\n", imageNTHeaders->OptionalHeader.BaseOfData);
			msg("\t0x%x\t\tImage Base\n", imageNTHeaders->OptionalHeader.ImageBase);
			msg("\t0x%x\t\tSection Alignment\n", imageNTHeaders->OptionalHeader.SectionAlignment);
			msg("\t0x%x\t\tFile Alignment\n", imageNTHeaders->OptionalHeader.FileAlignment);
			msg("\t0x%x\t\tMajor Operating System Version\n", imageNTHeaders->OptionalHeader.MajorOperatingSystemVersion);
			msg("\t0x%x\t\tMinor Operating System Version\n", imageNTHeaders->OptionalHeader.MinorOperatingSystemVersion);
			msg("\t0x%x\t\tMajor Image Version\n", imageNTHeaders->OptionalHeader.MajorImageVersion);
			msg("\t0x%x\t\tMinor Image Version\n", imageNTHeaders->OptionalHeader.MinorImageVersion);
			msg("\t0x%x\t\tMajor Subsystem Version\n", imageNTHeaders->OptionalHeader.MajorSubsystemVersion);
			msg("\t0x%x\t\tMinor Subsystem Version\n", imageNTHeaders->OptionalHeader.MinorSubsystemVersion);
			msg("\t0x%x\t\tWin32 Version Value\n", imageNTHeaders->OptionalHeader.Win32VersionValue);
			msg("\t0x%x\t\tSize Of Image\n", imageNTHeaders->OptionalHeader.SizeOfImage);
			msg("\t0x%x\t\tSize Of Headers\n", imageNTHeaders->OptionalHeader.SizeOfHeaders);
			msg("\t0x%x\t\tCheckSum\n", imageNTHeaders->OptionalHeader.CheckSum);
			msg("\t0x%x\t\tSubsystem\n", imageNTHeaders->OptionalHeader.Subsystem);
			msg("\t0x%x\t\tDllCharacteristics\n", imageNTHeaders->OptionalHeader.DllCharacteristics);
			msg("\t0x%x\t\tSize Of Stack Reserve\n", imageNTHeaders->OptionalHeader.SizeOfStackReserve);
			msg("\t0x%x\t\tSize Of Stack Commit\n", imageNTHeaders->OptionalHeader.SizeOfStackCommit);
			msg("\t0x%x\t\tSize Of Heap Reserve\n", imageNTHeaders->OptionalHeader.SizeOfHeapReserve);
			msg("\t0x%x\t\tSize Of Heap Commit\n", imageNTHeaders->OptionalHeader.SizeOfHeapCommit);
			msg("\t0x%x\t\tLoader Flags\n", imageNTHeaders->OptionalHeader.LoaderFlags);
			msg("\t0x%x\t\tNumber Of Rva And Sizes\n", imageNTHeaders->OptionalHeader.NumberOfRvaAndSizes);
		}



		// DATA_DIRECTORIES
		if (mdbg)
		{
			msg("\n******* DATA DIRECTORIES *******\n");
			msg("\tExport Directory Address: 0x%x; Size: 0x%x\n", imageNTHeaders->OptionalHeader.DataDirectory[0].VirtualAddress, imageNTHeaders->OptionalHeader.DataDirectory[0].Size);
			msg("\tImport Directory Address: 0x%x; Size: 0x%x\n", imageNTHeaders->OptionalHeader.DataDirectory[1].VirtualAddress, imageNTHeaders->OptionalHeader.DataDirectory[1].Size);

			// SECTION_HEADERS
			msg("\n******* SECTION HEADERS *******\n");
		}

		// get offset to first section header
		DWORD sectionLocation = reinterpret_cast<DWORD>(imageNTHeaders) + sizeof(DWORD) + static_cast<DWORD>(sizeof(IMAGE_FILE_HEADER)) + static_cast<DWORD>(imageNTHeaders->FileHeader.SizeOfOptionalHeader);
		const auto sectionSize = static_cast<DWORD>(sizeof(IMAGE_SECTION_HEADER));

		// get offset to the import directory RVA
		const auto importDirectoryRVA = imageNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;

		PE_SECTION pe_sections;

		// get and print section data
		for (auto i = 0; i < imageNTHeaders->FileHeader.NumberOfSections; i++)
		{

			sectionHeader = reinterpret_cast<PIMAGE_SECTION_HEADER>(sectionLocation);

			pe_sections.name = byte_to_str(sectionHeader->Name, sizeof(sectionHeader->Name));

			pe_sections.virtual_size = sectionHeader->Misc.VirtualSize;

			pe_sections.virtual_address = sectionHeader->VirtualAddress;

			pe_sections.size_of_raw_data = sectionHeader->SizeOfRawData;

			pe_sections.pointer_to_raw_data = sectionHeader->PointerToRawData;

			pe_sections.pointer_to_relocations = sectionHeader->PointerToRelocations;

			pe_sections.pointer_to_line_numbers = sectionHeader->PointerToLinenumbers;

			pe_sections.number_of_relocations = sectionHeader->NumberOfRelocations;

			pe_sections.number_of_line_numbers = sectionHeader->NumberOfLinenumbers;

			pe_sections.characteristics = sectionHeader->Characteristics;

			if (mdbg)
			{
				msg("\t%s\n", sectionHeader->Name);
				msg("\t\t0x%x\t\tVirtual Size\n", sectionHeader->Misc.VirtualSize);
				msg("\t\t0x%x\t\tVirtual Address\n", sectionHeader->VirtualAddress);
				msg("\t\t0x%x\t\tSize Of Raw Data\n", sectionHeader->SizeOfRawData);
				msg("\t\t0x%x\t\tPointer To Raw Data\n", sectionHeader->PointerToRawData);
				msg("\t\t0x%x\t\tPointer To Relocations\n", sectionHeader->PointerToRelocations);
				msg("\t\t0x%x\t\tPointer To Line Numbers\n", sectionHeader->PointerToLinenumbers);
				msg("\t\t0x%x\t\tNumber Of Relocations\n", sectionHeader->NumberOfRelocations);
				msg("\t\t0x%x\t\tNumber Of Line Numbers\n", sectionHeader->NumberOfLinenumbers);
				msg("\t\t0x%x\tCharacteristics\n", sectionHeader->Characteristics);

			}


			// добавим данные секции в вектор 
			vec_pe_sections.push_back(pe_sections);

			// save section that contains import directory table
			if (importDirectoryRVA >= sectionHeader->VirtualAddress && importDirectoryRVA < sectionHeader->VirtualAddress + sectionHeader->Misc.VirtualSize)
			{
				importSection = sectionHeader;
			}
			sectionLocation += sectionSize;
		}

		// get file offset to import table
		rawOffset = (DWORD)fileData + importSection->PointerToRawData;

		// get pointer to import descriptor's file offset.
		// Note that the formula for calculating file offset is:
		// imageBaseAddress + pointerToRawDataOfTheSectionContainingRVAofInterest + (RVAofInterest - SectionContainingRVAofInterest.VirtualAddress)
		importDescriptor = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(rawOffset + (imageNTHeaders->OptionalHeader.DataDirectory[
			IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress - importSection->VirtualAddress));

		msg("\n******* DLL IMPORTS *******\n");
		for (; importDescriptor->Name != 0; importDescriptor++)
		{
			// imported dll modules
			msg("\t%s\n", rawOffset + (importDescriptor->Name - importSection->VirtualAddress));
			thunk = importDescriptor->OriginalFirstThunk == 0 ? importDescriptor->FirstThunk : importDescriptor->OriginalFirstThunk;
			thunkData = reinterpret_cast<PIMAGE_THUNK_DATA>(rawOffset + (thunk - importSection->VirtualAddress));

			// dll exported functions
			for (; thunkData->u1.AddressOfData != 0; thunkData++)
			{
				//a cheap and probably non-reliable way of checking if the function is imported via its ordinal number ¯\_(ツ)_/¯
				if (thunkData->u1.AddressOfData > 0x80000000)
				{
					//show lower bits of the value to get the ordinal ¯\_(ツ)_/¯
					msg("\t\tOrdinal: %x\n", static_cast<WORD>(thunkData->u1.AddressOfData));
				}
				else
				{
					msg("\t\t%s\n", (rawOffset + (thunkData->u1.AddressOfData - importSection->VirtualAddress + 2)));
				}
			}
		}

	}

	else
	{
		CloseHandle(file);
		return false;
	}
	CloseHandle(file);
	return true;
}

bool  GetFunctionData() {
	msg("\n\n\t\tNumber of functions in disassembled file = %d\n", get_func_qty());

	PE_FUNCTION_DATA func_data;
	// Buffer where the function name will be stored
	qstring funcName;

	// Пройдитесь по всем функциям
	for (auto i = 0; i < get_func_qty(); i++)
	{
		func_t* curFunc = getn_func(i);
		//msg("Function at: %a\n", curFunc->start_ea);
		func_data.function_address = curFunc->start_ea;
		const auto counter = get_func_name(&funcName, func_data.function_address);
		if (counter > 0)
		{
			func_data.function_name = funcName;
			if (mdbg)
			{
				msg("Function %a at: %s\n", curFunc->start_ea, funcName.c_str());
			}
		}
		else
		{
			func_data.function_name = "has_no_name";
		}

		vec_pe_function_data.push_back(func_data);
	}

	return true;
}

void ClosePEFile(LPBYTE pBase) {
	if (pBase != nullptr)
		UnmapViewOfFile(pBase);
}

IMAGE_SECTION_HEADER* GetSection(IMAGE_NT_HEADERS* pHeader, DWORD dwRVA) {
	// Проверка правильности аргументов.
	if (pHeader == nullptr)
		return nullptr;
	// Перебор всех заголовков секций.
	IMAGE_SECTION_HEADER* pSectHeader = IMAGE_FIRST_SECTION(pHeader);
	for (UINT i = 0; i < pHeader->FileHeader.NumberOfSections; i++, pSectHeader++)
	{
		// Если RVA находится внутри секции, то возвращаем указатель на ее заголовок.
		if (dwRVA >= pSectHeader->VirtualAddress && dwRVA < pSectHeader->VirtualAddress + pSectHeader->Misc.VirtualSize)
			return pSectHeader;
	}
	return nullptr; // секция не найдена
}

LPBYTE OpenPEFile(const char* lpszFileName) {
	const HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
		return nullptr;
	const HANDLE hMapping = CreateFileMapping(hFile, nullptr, PAGE_READONLY, 0, 0, nullptr);
	CloseHandle(hFile);
	LPBYTE pBase = nullptr;
	if (hMapping != nullptr)
	{
		pBase = static_cast<unsigned char*>(MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0));
		CloseHandle(hMapping);
	}
	return pBase;
}

IMAGE_NT_HEADERS* GetHeader(LPBYTE pBase) {
	// Проверка правильности аргументов.
	if (pBase == nullptr)
		return nullptr;
	// Получаем указатель на заголовок DOS.
	auto* pDosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(pBase);
	// Проверяем корректность указателя.
	if (IsBadReadPtr(pDosHeader, sizeof(IMAGE_DOS_HEADER)))
		return nullptr;
	// Сначала проверяем сигнатуру DOS.
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return nullptr;
	// Берем указатель на заголовок PE.
	// ReSharper disable once CppCStyleCast
	auto* pHeader = (IMAGE_NT_HEADERS*)(pBase + pDosHeader->e_lfanew);
	// Проверяем корректность указателя.
	if (IsBadReadPtr(pHeader, sizeof(IMAGE_NT_HEADERS)))
		return nullptr;
	// Наконец проверяем сигнатуру PE.
	if (pHeader->Signature != IMAGE_NT_SIGNATURE)
		return nullptr;
	return pHeader;
}

LPBYTE GetFilePointer(LPBYTE pBase, DWORD dwRVA) {
	// Проверка правильности аргументов.
	if (pBase == nullptr)
		return nullptr;
	// Ищем секцию, содержащий данный RVA.
	IMAGE_SECTION_HEADER* pSectHeader = GetSection(GetHeader(pBase), dwRVA);
	if (pSectHeader == nullptr) // Если секция не найдена,
		return pBase + dwRVA; // то RVA равно смещению в файле,
							  // иначе вычисляем смещение относительно начала секции в файле.
	return pBase + pSectHeader->PointerToRawData + (dwRVA - pSectHeader->VirtualAddress);
}

bool ReadModuleSections(const char* f_name, qvector<MODULE_FUNCTION_DATA>& function_list, const ea_t module_base) {

	const LPBYTE pBase = OpenPEFile(f_name);
	if (pBase == nullptr)
	{
		msg("File not found !!!\t%s\n", f_name);
		return false;
	}
	IMAGE_NT_HEADERS* pHeader = GetHeader(pBase);
	if (pHeader == nullptr)
	{
		msg("It is not a PE File !!!\t%s\n", f_name);
		return false;
	}

	msg("\t\t\t\tFile %s was opened, function data was be get\n", f_name);

	if (mdbg)
	{
		msg("ORD\tRVA\tNAME\n");
	}



	// Извлекаем параметры каталога данных экспорта.
	IMAGE_DATA_DIRECTORY& ExportDataDir = pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
	const DWORD dwExportDirStart = ExportDataDir.VirtualAddress;
	const DWORD dwExportDirEnd = dwExportDirStart + ExportDataDir.Size;
	// Получаем указатели на таблицу экспорта и все связанные с ней таблицы.
	auto* pExportDir = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(GetFilePointer(pBase, dwExportDirStart));
	auto pAddrTable = reinterpret_cast<LPDWORD>(GetFilePointer(pBase, pExportDir->AddressOfFunctions));
	const auto pNameTable = reinterpret_cast<LPDWORD>(GetFilePointer(pBase, pExportDir->AddressOfNames));
	const auto pOrdTable = reinterpret_cast<LPWORD>(GetFilePointer(pBase, pExportDir->AddressOfNameOrdinals));
	// Итерация по всем элементам таблицы адресов.
	for (UINT i = 0; i < pExportDir->NumberOfFunctions; i++)
	{
		const DWORD dwRVA = *pAddrTable++;
		// Не печатаем пропущенные элементы.
		if (dwRVA == 0)
			continue;

		MODULE_FUNCTION_DATA func_data; // создаем объект структуры
										// ординал функции 
		if (mdbg)
		{
			msg("%d\t", i + pExportDir->Base);
		}

		func_data.mod_function_ordinal = static_cast<ushort>(i + pExportDir->Base);

		// Проверяем тип очередного RVA.
		if (dwRVA >= dwExportDirStart && dwRVA < dwExportDirEnd)
		{
			// если это RVA перенаправления
			if (mdbg)
			{
				msg("%s\t", reinterpret_cast<char*>(GetFilePointer(pBase, dwRVA)));
			}

			func_data.mod_function_redirection = reinterpret_cast<char*>(GetFilePointer(pBase, dwRVA));
		}
		else
		{
			// обычный RVA
			if (mdbg)
			{
				msg("0x%x\t", dwRVA + module_base);
			}

			func_data.mod_function_address = dwRVA + module_base;
		}
		// Итерация по всем элементам таблицы номеров.
		for (UINT j = 0; j < pExportDir->NumberOfNames; j++)
		{
			// Если номер найден, выводим соответствующее имя из таблицы имен.
			if (pOrdTable[j] == i)
			{
				if (mdbg)
				{
					msg("%s", reinterpret_cast<char*>(GetFilePointer(pBase, pNameTable[j])));
				}

				func_data.mod_function_name = reinterpret_cast<char*>(GetFilePointer(pBase, pNameTable[j]));
				break;
			}
		}

		// Добавим данные о функции в вектор данных о функция модуля (dll)
		function_list.push_back(func_data);

		msg("\n");
	}

	msg("\t\t\t\tFile was be close \n");
	ClosePEFile(pBase);
	return true;
}

bool GetDataFromModule(qvector<MODULE_DATA>& modules_data) {
	for (auto& i : modules_data)
	{
		std::string path = i.module_name.c_str();
		qvector<MODULE_FUNCTION_DATA> ptr_vector = i.function_list;


		if (mdbg)
		{
			msg("\t\tModule Data is : %s\n", path.c_str());
		}

		const auto res = ReadModuleSections(path.c_str(), ptr_vector, i.module_base);
		if (!res)
		{
			msg("\t\tBBB ERROR:\n\t\tPLUGIN WAS NOT TO READ THE DATA FROM FILE %s!!!\n", path.c_str());
		}

		if (mdbg)
		{
			msg("\t\tClose Module Data : %s\n", path.c_str());
		}

	}

	return true;
}

void get_current_plugin_directory() {
	// IDA76_DIR
	char tmp[_MAX_PATH];

	DWORD dwRet = GetEnvironmentVariable("IDA76_PLUGIN_DIR", tmp, sizeof(tmp));

	if (0 == dwRet)
	{
		DWORD dwErr = GetLastError();
		if (ERROR_ENVVAR_NOT_FOUND == dwErr)
		{
			msg("\n\n\t\t\tENVIRONMENT VARIABLE FOR BLABLABLA DOES NOT EXIST.\n\t\t\tYou need set EnvironmentVariable IDA76_PLUGIN_DIR = Ida_dir\\plugin\n\n");
		}
	}
	else
	{
		PLUGIN_CURRENT_DIRECTORY = tmp;
		if (mdbg)
		{
			msg("\n\nCurrent Directory = %s\n\n", PLUGIN_CURRENT_DIRECTORY.c_str());
		}
	}
	//const auto abc = GET_CURRENT_DIR(tmp, sizeof(tmp));
}

vector<std::string> files_list{};

void get_collection_api_files(const std::string& path) {

	vector<std::string> folder_list{};

	WIN32_FIND_DATA findFileData;

	struct FILEMODEL {
		std::string absolute_path{}, filename{};
	};

	const auto handle = FindFirstFile((path + "\\*").c_str(), &findFileData);

	do
	{
		auto* tmp = new FILEMODEL{};
		tmp->filename = findFileData.cFileName;

		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// здесь получаем имя папки и ложим имя папки в вектор с именами папок в директории ...
			tmp->absolute_path = path + "\\" + tmp->filename;

			if (tmp->filename != "." && tmp->filename != "..")
			{
				folder_list.push_back(path + "\\" + tmp->filename);
			}
		}
		else
		{
			// иначе имя файла и ложим имя файла в вектор с именами фаилов директории ...
			tmp->absolute_path = path + "\\" + tmp->filename;

			if (tmp->filename != "." && tmp->filename != "..")
			{
				files_list.push_back(path + "\\" + tmp->filename);
			}
		}

		//std::cout << "\n\t One file data    ***********" << std::endl;
		//std::wcout << "cFileName        " << findFileData.cFileName << std::endl;
		//std::wcout << "absolute_path    " << tmp->absolute_path << std::endl;
		//std::wcout << "filename         " << tmp->filename << std::endl;

		delete tmp;
		tmp = nullptr;

	} while (FindNextFile(handle, &findFileData));
	FindClose(handle);

	while (!folder_list.empty())
	{
		auto folder = folder_list.back();
		folder_list.pop_back();
		get_collection_api_files(folder);

	}
}

// [STACK] --- begin ---
DWORD GetPeSizeOfStackReserve() {
	return pe_image_optional_header.SizeOfStackReserve; // if: не инициализирован -> 0
}

DWORD GetPeSizeOfStackCommit() {
	return pe_image_optional_header.SizeOfStackCommit;  // if: не инициализирован -> 0
}
// [STACK] --- end ---


