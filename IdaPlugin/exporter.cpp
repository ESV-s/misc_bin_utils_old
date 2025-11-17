#include "exporter.h"
#include <boost/algorithm/string.hpp>
#include<boost/tokenizer.hpp>
#include <frame.hpp>
#include <iostream>
#include <name.hpp>
#include <search.hpp>
#include <sstream>
#include <string>
#include <struct.hpp>

#include "help_functions.h"
#include "pe_heders.h"
#include "util.h"

#include "debug_log.h"


using boost::replace_all;



// реализуем конструктор инициализируем структуры ...
Exporter::Exporter()
{
	TRACE_FN();
	pe_instruction = {};
	pe_func = {};
	pe_segment = {};
}


/**
* \brief \n добавляет адреса локальных функций в мап local_func_address_ \n
*           локальная функция - любая функция в файле за исключением импортированных ...\n
* \param start_address		адрес начала функции
* \param end_address		адрес окончания функции
*/
void Exporter::AddLocalFuncAddress(const ea_t start_address, const ea_t end_address)
{
	local_func_address[start_address] = end_address;
}

/**
* \brief \n добавляет адреса импортируемых функций в мап import_func_address_ \n
*           локальная функция - любая функция в файле за исключением импортированных ...\n
* \param start_address		адрес начала функции
* \param source				цель вызова
*/
void Exporter::AddImportFuncAddress(const ea_t start_address, const std::string source)
{
	import_func_address[start_address] = source;
}

/**
* \brief \n Вывести на печать функции из мап local_func_address_
*/
void Exporter::PrintLocalFuncMap() const
{
	msg("                Print  exporter::local_func_address_  Start ##################################################### \n");
	for (const auto &pair : local_func_address)
	{
		msg("    %llx : %llx \n", pair.first, pair.second);
	}
	msg("                Print  exporter::local_func_address_  Finish ##################################################### \n");
}

/**
* \brief \n Вывести на печать функции из мап import_func_address
*/
void Exporter::PrintImportFuncMap() const
{
	msg("                Print  exporter::import_func_address_  Start ##################################################### \n");
	for (const auto &pair : import_func_address)
	{
		msg("    %llx : %s \n", pair.first, pair.second.c_str());
	}
	msg("                Print  exporter::import_func_address_  Finish ##################################################### \n");
}


/**
* \brief \n Добавить необходимое количество символов пробела к строке ...
* \param str	входная строка
* \param count сколько символов
* \return
*/
std::string AddEmptySymbol(std::string str, int count)
{


	return str;
}


/**
* \brief \n Вывести на печать функции из vector<PeFunc> function_data \n
* в данном векторе содержатся все функции рассматриваемого файла
*/
void Exporter::PrintFunctionData() const
{
	TRACE_FN();
	
	/*using std::istringstream;
	const std::string text = "library local imported exported";
	size_t pos_start = 0, pos_end;
	size_t max_length = 0;
	const std::string delimiter = " ";
	const size_t delim_len = delimiter.length();
	std::string sub_str{};
	const auto add_count = 3; // количество символов для добавления к строке


	while ((pos_end = text.find(delimiter, pos_start)) != std::string::npos) {
	sub_str = text.substr(pos_start, pos_end - pos_start);
	const auto len = sub_str.length();

	if (len > max_length)
	{
	max_length = len;
	}
	pos_start = pos_end + delim_len;
	}

	// добавим длину для пустых символов ...
	max_length += add_count;*/
	auto mangled = Settings::getPrintInfoMangledName();
	std::string ft = {};
	std::string fname = {};

	// "local     "
	// "imported  "
	// "exported  "
	for (const auto& fd : function_data)
	{

		if (fd.function_internal)
		{
			fname = exporter.CheckMangledName(fd, mangled);
			ft = "local     ";
			msg("    %llx  %s  %s\n", fd.address, ft.c_str(), fname.c_str());
		}

		if (fd.function_exported)
		{
			fname = exporter.CheckMangledName(fd, mangled);
			ft = "exported  ";
			msg("    %llx  %s  %s\n", fd.address, ft.c_str(), fname.c_str());
		}

		if (fd.function_imported)
		{
			fname = exporter.CheckMangledName(fd, mangled);
			ft = "imported  ";
			msg("    %llx  %s  %s\n", fd.address, ft.c_str(), fname.c_str());
		}

	}
}


/**
* \brief \n Вывод информации полученной плагином ...
*/
void Exporter::PrintInformation() const
{
	TRACE_FN();
	
	// получаем переменные из реестра
	auto print_function_data = Settings::getPrintInfoFunctionData();
	// auto output_cleaning = Settings::getPrintInfoOutputCleaning();
	auto print_container_size = Settings::getPrintInfoContainerSize();


	if (Settings::getPrintInfoEnabled()) { /* если стоит галка о выводе сообщений */

										   /*if(output_cleaning) //если установлено - чистим консоль
										   {
										   msg_clear();
										   }*/

										   // вывод сообщений в режиме релиз или отладка 
		msg("\n    BlaBlaBla PRINT_INFO START   +++++++++++++++++++++++++++++++++++++++++++++\n");

		// вывод сообщений если отладка
		if (mdbg) {
			PrintLocalFuncMap();
			PrintImportFuncMap();
		}

		if (print_function_data) /* если установлено - выводим данные по функциям */
		{
			PrintFunctionData();
		}


		// получим общее количество функции в файле  =  собственные функции + импортируемые 
		const auto all_func_count = (static_cast<long long>(GetLocalFuncCount())) + modules_size;

		if (all_func_count != flow_graph_func_count || vector_need_size != static_cast<size_t>(flow_graph_func_count))
		{
			msg("\n\t\t########################################################\n");
			msg("\t\tFUNCTION NUMBER INTO PLUGIN DATA CONTAINER NOT EQUAL FUNCTION NUMBER INTO BINEXPORT FLOW_GRAPH\n");
			msg("\t\tinto map is %d != %d  into flow_graph \n", all_func_count, flow_graph_func_count);
			msg("\t\t    Next entry point no was in list binexport : \n");
			for (auto item{ function_data.begin() }; item != function_data.end(); ++item)
			{
				if (item->was_checked == false)
				{
					msg("\t\t        %llx : %s \n", item->address, item->name.c_str());
				}
			}
			msg("\n\t\t########################################################\n");
		}

		if (print_container_size)
		{ // выведем размеры контейнеров 
			msg("\n");
			msg("\nvector Function_Data       , size = %d ", function_data.size());
			msg("\nmap    import_func_address , size = %d ", import_func_address.size());
			msg("\nmap    export_func_address , size = %d ", export_func_address.size());
			msg("\nmap    local_func_address  , size = %d ", local_func_address.size());
			msg("\nvector vector_pe_addr      , size = %d ", vector_pe_instructions.size());
			msg("\nmap    function_index      , size = %d ", function_index.size());
			msg("\nmap    function_naming     , size = %d ", function_naming.size());
			msg("\nvector segments_data       , size = %d ", segments_data.size());
			msg("\n");
		}

		// [PATCH] -------- Сводная статистика анализа (heads/tails/thunks/chunks) --------
		// Печатаем summary, которое мы накапливали вызовами RegisterFunctionClassify(...)
		// во время основного прохода. Метод константный, т.к. только выводит.
		
		PrintStats();
		

		msg("\n    BlaBlaBla PRINT_INFO FINISH  +++++++++++++++++++++++++++++++++++++++++++++\n");


	}

}

/**
* \brief \n Поиск функции в векторе по адресу
* \param addr искомый адрес (start_ea функции )
* \return true в случае успеха, иначе false
*/

bool Exporter::SearchFunctionAddress(const ea_t addr) const
{
	TRACE_FN();
	
	auto res = false;

	auto pred = [addr](const PeFunc& item) {
		return item.address == addr;
	};

	const auto it =
		std::find_if(std::begin(function_data),
			std::end(function_data), pred);

	if (it != std::end(function_data))
	{
		exporter.index = (it - function_data.begin());
		res = true;
	}

	return res;
}


/**
* \brief      Вернуть количество функций в карте ...
* \return     exporter->local_func_address_.size() ...
*/
int Exporter::GetLocalFuncCount() const
{
	TRACE_FN();
	
	return local_func_address.size();
}

void Exporter::ParseCMD(const std::string &cmd_command) const
{
	TRACE_FN();
	
	// если задано - чистим OUTPUT WINDOW
	{

		if (Settings::getPrintInfoEnabled())
		{
			const auto state = Settings::getPrintInfoOutputCleaning();
			if (state)
			{
				msg_clear();
			}

		}
	}

	std::vector<std::string> command{};
	boost::tokenizer<> tok(cmd_command);
	int counter = 0;

	for (auto beg = tok.begin(); beg != tok.end(); ++beg) {

		std::string  str = *beg;
		boost::algorithm::to_lower(str);
		if (beg == tok.begin() && (str != "bb"))
		{
			msg("\n\n\n"
				"        CMD Error command - not 'bb' in start position \n"
				"        write command 'bb help'\n\n\n\n");
			return;
		}
		if (counter == 0)
		{
			msg("    Parse CMD =");
			counter += 1;
		}
		command.push_back(str);

		msg(" %s", *beg);

	}
	msg("\n");

	// сохраним количество параметров в строке
	const auto nArg = static_cast<int>(command.size());
	if (nArg < 2)
	{
		msg("    The number of arguments no match... \n\n");
		return;
	}

	exporter.cmd_arg = nArg;

	if (command[1] == "help" || command[1] == "h")
	{
		CommandPrintHelp();
		return;
	}

	if (command[1] == "function" && exporter.cmd_arg > 2)
	{
		// запишем что 2ой аргумент обработан правильно ...
		exporter.arg_counter = 2;
		// и по идее при попадании в функцию уже обрабатываем 3 аргумент  - это 2 эл вектора ...
		CommandFunctionParse(command);
		return;
	}


	msg("    Unknown Argument    %s \n\n", command[1].c_str());

}

void Exporter::ParseCMDFunctionAbout(ea_t address) const
{
	TRACE_FN();
	
	msg("\n\n        information about function containing the address %llx \n\n", address);

	// [PATCH] -------- Безопасная классификация адреса функции --------
	// Классифицируем адрес: может быть голова (Head), хвост (TailChunk) или thunk.
	const FuncClassify fc = ClassifyFunction(address);

	// [if] Если IDA не видит здесь функцию — сообщаем и выходим.
	if (!fc.this_chunk) {
		msg("                    ERROR : IDA HAS NO information about %llx address \n\n", address);
		return;
	}

	// [else] head — это владелец для хвоста, либо сама голова/обёртка (thunk).
	const func_t* head = fc.head ? fc.head : fc.this_chunk;

	// [PATCH] Всю дальнейшую логику (имя, границы, фрейм, размеры) выполняем по head.
	const ea_t start_address = head->start_ea;
	const ea_t end_address = head->end_ea;

	// [PATCH] делаем мутируемый указатель на head, чтобы звать API, где нужен func_t* (а не const)
	func_t* func = const_cast<func_t*>(head);

	if (func == nullptr)
	{
		msg("                    ERROR : IDA HAS NO information about %llx address \n\n", address);
		return;
	}

	// зададим количество пробелов с начала строки = 16
	const auto n_space = "                ";

	qstring name{};
	get_ea_name(&name, start_address);

	msg("%s %-40s %s \n", n_space, "Function", name.c_str());
	msg("%s %-40s %llx : %llx \n", n_space, "Has bounds", start_address, end_address);

	// [PATCH] -------- Мини-сводка по чанкам (head + tails) + сохранение в модель --------
	// Собираем все диапазоны (первым идёт head, затем хвосты).
	const auto chunks = CollectAllChunks(head);

	// Суммируем размер кода без двойного учёта: просто сумма размеров всех диапазонов.
	asize_t total_sz = 0;
	for (const auto& r : chunks) {
		total_sz += r.size(); // r.size() — размер диапазона в байтах
	}

	// [PATCH] Локальная сводка: считаем и печатаем (хранение делаем в SetFunctionTailes).
	const uint32_t chunks_total = static_cast<uint32_t>(chunks.size());                 // всего чанков (включая head)
	const uint32_t tails_count = (chunks_total > 0 ? chunks_total - 1 : 0);            // хвостов = всего-1
	const asize_t  chunks_code_size = total_sz;                                             // общий размер кода по чанкам

																							// Вывод компактной строки со сводкой.
	msg("%s chunks: %u, total code size: %llu bytes\n",
		n_space,
		chunks_total,
		static_cast<unsigned long long>(chunks_code_size));


	// [PATCH] Если текущий чанк помечен как thunk — покажем его цель (куда он прыгает).
	if (fc.this_chunk->flags & FUNC_THUNK)
	{
		func_t* mutable_this = const_cast<func_t*>(fc.this_chunk);
		const ea_t tgt = ResolveThunkTarget(mutable_this); // см. function_utils.cpp

		if (tgt != BADADDR)
		{
			// [PATCH] Печатаем имя из модели, если SetFunctionFlags уже сохранил его.
			// В const-методе мы НИЧЕГО не записываем в модель — только читаем.
			const bool has_demangled = !pe_func.thunk_target_name_demangled.empty();
			const bool has_raw = !pe_func.thunk_target_name.empty();

			if (has_demangled)
			{
				// [if] Есть красивое демангленное имя — показываем его.
				msg("%s %-40s %s (%llx)\n",
					n_space, "Thunk target", pe_func.thunk_target_name_demangled.c_str(), tgt);
			}
			else if (has_raw)
			{
				// [else-if] Деманглинга нет, но есть сырое имя — покажем его.
				msg("%s %-40s %s (%llx)\n",
					n_space, "Thunk target", pe_func.thunk_target_name.c_str(), tgt);
			}
			else
			{
				// [else] В модели имён нет (например, SetFunctionFlags ещё не вызывался) — подстрахуемся on-the-fly.
				qstring tname;
				get_ea_name(&tname, tgt);
				if (!tname.empty())
				{
					qstring dem;
					if (demangle_name(&dem, tname.c_str(), 0) && !dem.empty())
						msg("%s %-40s %s (%llx)\n", n_space, "Thunk target", dem.c_str(), tgt);
					else
						msg("%s %-40s %s (%llx)\n", n_space, "Thunk target", tname.c_str(), tgt);
				}
				else
				{
					msg("%s %-40s %s\n", n_space, "Thunk target", "<no name>");
				}
			}
		}
		else
		{
			// [else] Цель не распознана
			msg("%s %-40s %s\n", n_space, "Thunk target", "<not resolved>");
		}
	}


	// теперь получим индекс функции в нашем векторе данных , и будем брать данные оттуда
	const auto pe_func_index = GetFunctionIndex(start_address);
	// если индекс не -1 - значит функция не найдена в векторе , по идее такого быть не может ...
	if (pe_func_index == -1)
	{
		msg("                    ERROR : function_index map HAS NO information about %llx function address \n\n", start_address);
		return;
	}
	auto mf = function_data[pe_func_index];

	// проверка что именно ту функцию получаем из вектора ...
	const auto f_type = GetFunctionType(pe_func_index);
	if (f_type.empty())
	{
		msg("%s %-40s %s \n", n_space, "Function has type", "No data in function_data");
	}
	else
	{
		msg("%s %-40s %s \n", n_space, "Function has type", f_type.c_str());
	}

	// выведем флаги функции
	msg("%s %-40s %s \n", n_space, "Function has flags", mf.func_flags.c_str());

	// выведем размер лок переменных фрейма стека
	msg("%s %-40s %llx %s \n", n_space, "Local var frame size", mf.func_frsize, "bytes\n");

	// количество байт очищаемых со стека при возврате ...
	msg("%s %s \n", n_space, "Number bytes cleared");
	msg("%s %-40s %llx \n", n_space, "    from the stack on return", mf.func_argsize);

	// количество инструкции в функции
	msg("%s %-40s %d \n", n_space, "Function Instructions Count ", FunctionInstructionCount(start_address, end_address));
	msg("\n");

	// вызовы из функции
	FunctionCalls(start_address, end_address);
	msg("\n");

	// в какой функции вызывается текущая функция
	FunctionReference(start_address, end_address);
	msg("\n");

	// текущие переменные для функции
	{
		// [PATCH] у хвоста своего фрейма нет — всегда берём у владельца (head)
		const auto frame = get_frame(head->start_ea);

		if (!frame)
		{
			msg("\n");
			msg("%s %-40s \n", n_space, "Not find information about func Frame ...");
		}
		msg("%s %-40s \n", n_space, "Information about func Frame :");

		// [PATCH] размер фрейма считаем у головы; get_func(start_address) на хвосте даст tail → будет неверно
		const auto fr_size = get_frame_size(head);
		msg("%s %-40s %d %s\n", n_space, "Function frame size = ", fr_size, " bytes");

		range_t range_loc;
		range_t range_ret;
		range_t range_savreg;
		range_t range_arg;

		get_frame_part(&range_loc, func, FPC_LVARS);
		if (!range_loc.empty())
		{
			msg("%s %-40s %d : %d bytes\n", n_space, "Function frame local vars address = ",
				range_loc.start_ea, range_loc.end_ea);
		}
		else
		{
			msg("%s %-40s \n", n_space, "Function frame local vars address = NOT HAVE");
		}

		get_frame_part(&range_ret, func, FPC_RETADDR);
		if (!range_ret.empty())
		{
			msg("%s %-40s %d : %d bytes\n", n_space, "Function frame ret address = ",
				range_ret.start_ea, range_ret.end_ea);
		}
		else
		{
			msg("%s %-40s %s\n", n_space, "Function frame ret address = ", "NOT HAVE");
		}

		get_frame_part(&range_savreg, func, FPC_SAVREGS);
		if (!range_savreg.empty())
		{
			msg("%s %-40s %d : %d bytes\n", n_space, "Function frame save registers = ",
				range_savreg.start_ea, range_savreg.end_ea);
		}
		else
		{
			msg("%s %-40s %s\n", n_space, "Function frame save registers = ", "NOT HAVE");
		}

		get_frame_part(&range_arg, func, FPC_ARGS);
		if (!range_arg.empty())
		{
			msg("%s %-40s %d : %d bytes\n", n_space, "Function frame arguments = ",
				range_arg.start_ea, range_arg.end_ea);
		}
		else
		{
			msg("%s %-40s %s\n", n_space, "Function frame arguments = ", "NOT HAVE");
		}
	}

	ParceFunctionFrame(start_address);

	msg("\n\n        information about function containing the address is complete \n\n");
	return;
}

int Exporter::FunctionInstructionCount(const ea_t start_address, const ea_t end_address) const
{
	int instr_counter = 0;
	auto instr = start_address;
	//msg("\n");
	while (instr < end_address)
	{
		instr_counter++;
		//msg("Count %d = %llx \n", instr_counter, instr);
		instr = find_code(instr, SEARCH_DOWN | SEARCH_NEXT);
	}

	return instr_counter;
}

/**
* \brief \n Найти все вызовы (call) из функции ...
* \param start_address
* \param end_address
*/
void Exporter::FunctionCalls(const ea_t start_address, const ea_t end_address) const
{
	auto flags = SEARCH_DOWN | SEARCH_NEXT;
	auto func = start_address;
	xrefblk_t xref;
	qstring fname = "";

	for (auto inst = func; inst < end_address; inst = find_code(inst, flags))
	{
		for (bool ok = xref.first_from(inst, XREF_ALL);
			ok && xref.iscode; ok = xref.next_from()) {

			// получим адреса откуда делается call на другой адрес ...
			if (xref.type == fl_CN || xref.type == fl_CF)
			{
				get_func_name(&fname, xref.to);
				msg("%s %-20s %llx %s %llx %30s\n", "                ", "Call instruction", inst, "  to  ", xref.to, fname.c_str());
			}

		}
	}
}

/**
* \brief \n Найти ссылки на функцию ...
* \param start_address
* \param end_address
*/
void Exporter::FunctionReference(const ea_t start_address, const ea_t end_address) const
{
	auto flags = SEARCH_DOWN | SEARCH_NEXT;
	auto func = start_address;
	xrefblk_t xref;
	qstring fname = "";

	for (auto inst = func; inst < end_address; inst = find_code(inst, flags))
	{
		for (bool ok = xref.first_to(inst, XREF_ALL);
			ok && xref.iscode; ok = xref.next_to()) {

			// получим адреса откуда делается call на другой адрес ...
			if (xref.type == fl_CN || xref.type == fl_CF)
			{
				get_func_name(&fname, xref.from);
				msg("%s %-20s %llx %s %llx %30s\n", "                ", "Has reference ", inst, " from ", xref.from, fname.c_str());
			}

		}
	}
}

void Exporter::ParceFunctionFrame(ea_t start_address) const
{
	// получим указатель на функцию по версии IDA 
	//const func_t* func = get_func(start_address);
	//const struc_t* frame = get_frame(start_address);
	//const auto sz = func->frsize;

	//const member_t* mbrs = frame->members;KD
	//auto par1 = mbrs->soff;
	//auto par2 = mbrs->eoff;

	//msg("frame mbrs->soff = %llx \n", par1);
	//msg("frame mbrs->eoff = %llx \n", par2);


#pragma region binexport example
	struc_t* fframe = get_frame(start_address);
	if (!fframe) {
		msg("Function not frame binexport example\n");
		return;
	}

	const auto func = get_func(start_address);
	auto eip_loc = frame_off_lvars(func) + frame_off_savregs(func);

	// @bug: IDA sometimes returns excessively large offsets (billions)
	//       we must prevent looping forever in those cases
	size_t lastSuccess = 0;
	const size_t maxOffset =
		std::min(static_cast<size_t>(get_max_offset(fframe)),
			static_cast<size_t>(1024 * 64));
	//msg(" max_Offset = %d \n ", maxOffset);
	//msg(" get_offset = %d \n ", get_max_offset(fframe));

	auto fr_sz = get_struc_size(fframe);
	//msg(" frame size = %d \n ", fr_sz);


	for (size_t i = 0; i </* maxOffset && lastSuccess - i < 1024;*/ fr_sz;) {
		const member_t* member = get_member(fframe, i);
		if (!member || is_special_member(member->id)) {
			++i;
			continue;
		}

		const ea_t offset = member->soff;
		qstring ida_name(get_member_name(member->id));
		if (!ida_name.empty()) {
			msg("             %s offset %llxh \n",
				ida_name.c_str(),
				offset > eip_loc ? offset - eip_loc : eip_loc - offset); // ранее было просто offset
																		 //msg("      eip_loc = %d \n", eip_loc);
			i += std::max(static_cast<asize_t>(1), get_member_size(member));
			lastSuccess = i;
			continue;
		}

		msg("**Local vars  = %s from %d \n", ida_name.c_str(), offset);
		//local_vars[offset] = security::binexport::ToString(ida_name);
		i += std::max(static_cast<asize_t>(1), get_member_size(member));
		lastSuccess = i;
	}
#pragma endregion


	//auto prev_idx = -1;
	//msg("frame size = %d \n", sz);
	//qstring prev;

	//const auto eip_loc = frame_off_lvars(func) + frame_off_savregs(func);


	//for (ulonglong idx = 0; idx < sz; idx++)
	//{
	//	qstring mn;
	//	auto member = get_member_name(&mn, idx);
	//	if (!mn.empty())
	//	{
	//		if (prev_idx != -1)
	//		{
	//			const auto delta = idx - prev_idx;
	//			msg("%15s: %4d bytes (%4d bytes to eip)\n",
	//				prev.c_str(), delta, eip_loc - prev_idx);
	//		}
	//		prev_idx = idx;
	//		prev = mn;
	//		idx = idx + get_member_size(get_member(frame, idx));
	//	}
	//	else idx++;
	//}

	//if (prev_idx != -1) {
	//	//make sure we print the last field in the frame
	//	auto delta = func->frsize - prev_idx;
	//	msg("%15s: %4d bytes (%4d bytes to eip)\n",
	//		prev.c_str(), delta, eip_loc - prev_idx);
	//}
}

/**
* \brief Разбор кадровой структуры (frame) функции.
* \details Безопасно берёт frame только у головного чанка (head), т.к. у tail-чunks
*          собственного фрейма не существует. Также добавлены проверки на nullptr.
*
* \param start_address Адрес внутри функции/чанка, по которому вызывается разбор.
* \return Ничего не возвращает; печатает информацию в msg().
*
* \note Требует function_utils.h (ClassifyFunction), т.к. используется классификация head/tail.
*/
void Exporter::ParceFunctionFrameTwo(ea_t start_address) const
{
	// [PATCH] -------- Шаг 1: Классифицируем адрес и получаем голову (head) --------
	// Классифицируем адрес: может быть голова (Head), хвост (TailChunk) или thunk.
	const FuncClassify fc = ClassifyFunction(start_address);

	// [if] Если IDA не видит здесь функцию — печатаем и выходим, чтобы не обращаться к nullptr.
	if (!fc.this_chunk)
	{
		msg("                No function at address %llx ...\n", start_address);
		return;
	}
	// [else] Адрес попал в функцию (в head/thunk или в хвост). Берём владельца:
	// - если адрес в хвосте, fc.head укажет на реальную голову;
	// - если адрес в голове/обёртке, fc.head совпадает с this_chunk (или равен nullptr),
	//   поэтому выбираем «head ? head : this_chunk».
	const func_t* head_const = fc.head ? fc.head : fc.this_chunk;

	// [PATCH] Некоторые IDA API (frame_off_*, get_frame_part) принимают НЕ-const func_t*,
	// поэтому делаем внеопасный const_cast.
	func_t* head = const_cast<func_t*>(head_const);

	// [PATCH] -------- Шаг 2: Берём frame ИМЕННО у головы (head) --------
	// [if] У хвоста фрейма нет — поэтому всегда get_frame(head->start_ea).
	const struc_t* frame = get_frame(head->start_ea);
	if (!frame)
	{
		// [else] Если фрейм отсутствует (редко, но бывает) — аккуратно сообщаем и выходим.
		msg("                No frame information for head @ %llx ...\n", head->start_ea);
		return;
	}

	// Размер фрейма: можно брать либо через поле frsize, либо через get_frame_size(head).
	// frsize быстрее и у нас под рукой.
	const int sz = head->frsize;

	// -------- Дальше идёт твоя исходная логика обхода, сохранённая и дополненная пояснениями --------

	// msg() и вспомогательные переменные
	auto prev_idx = -1;                  ///< Индекс предыдущего найденного члена (для расчёта delta).
	msg("frame size = %d \n", sz);
	qstring prev;                        ///< Имя предыдущего найденного члена для печати.

										 // Адрес «до eip» (сумма смещений локальных + сохранённых регистров)
										 // Эти API требуют НЕ-const func_t*, поэтому используем 'head'.
	const auto eip_loc = frame_off_lvars(head) + frame_off_savregs(head);

	// -------- Шаг 3: Линейный обход индексов в пределах размера frame --------
	// Логика сохранена: двигаем idx, ищем имя члена на каждом смещении.
	for (ulonglong idx = 0; idx < static_cast<ulonglong>(sz); /* см. управление индексом ниже */)
	{
		qstring mn;
		// get_member_name(&mn, idx) — заполняет mn, если по этому смещению есть член.
		// Возвращаемое значение нам не критично, достаточно проверить mn.empty().
		get_member_name(&mn, static_cast<uval_t>(idx));

		if (!mn.empty())
		{
			// [if] Имя найдено — значит по этому смещению есть член frame.
			if (prev_idx != -1)
			{
				// delta — размер предыдущего члена = текущее_смещение - предыдущее_смещение
				const auto delta = static_cast<int>(idx - static_cast<ulonglong>(prev_idx));
				msg("%15s: %4d bytes (%4d bytes to eip)\n",
					prev.c_str(), delta, static_cast<int>(eip_loc - prev_idx));
			}

			// Сохраняем «текущий» как «предыдущий» для следующей итерации печати.
			prev_idx = static_cast<int>(idx);
			prev = mn;

			// Попытаемся перепрыгнуть сразу на следующий член, прибавив размер текущего.
			// Для этого вытаскиваем member_t по смещению 'idx'.
			const member_t* m = get_member(frame, static_cast<uval_t>(idx));
			if (m != nullptr)
			{
				const asize_t msz = get_member_size(m);
				// [if] Размер > 0 — увеличим idx на размер текущего члена.
				if (msz > 0)
				{
					idx += static_cast<ulonglong>(msz);
					continue; // перейти к следующему члену без дополнительного ++idx
				}
				// [else] размер странный/0 — откатимся на безопасное поведение «шагать по одному байту».
			}

			// Если член не найден через get_member(), либо размер неопределён — шагнём на 1.
			idx += 1;
		}
		else
		{
			// [else] Имя пустое — по этому смещению члена нет. Шагаем на 1 байт вправо.
			idx += 1;
		}
	}

	// После цикла печатаем «последний» член, если он был.
	if (prev_idx != -1)
	{
		// delta для последнего = (полный размер фрейма - смещение последнего члена)
		const auto delta = head->frsize - prev_idx;
		msg("%15s: %4d bytes (%4d bytes to eip)\n",
			prev.c_str(), delta, static_cast<int>(eip_loc - prev_idx));
	}
}


/**
* \brief      Вернуть количество функций в карте ...
* \return     exporter->import_func_address_.size() ...
*/
int Exporter::GetImportFuncCount() const
{
	return import_func_address.size();
}


/**
* \brief	\n Установить тип функции  - экспортируемая или локальная
* \param pe_func_index индекс данных в векторе
*/
std::string Exporter::GetFunctionType(const int pe_func_index) const
{
	std::string  func_type = "";
	if (function_data[pe_func_index].function_internal)
	{
		func_type = "local";
	}
	if (function_data[pe_func_index].function_exported)
	{
		func_type = "exported";
	}
	if (function_data[pe_func_index].function_imported)
	{
		func_type = "imported";
	}

	return func_type;
}

/**
* \brief	определяет флаги , которые нужно установить для функции
* \param func_flag  значение func_t::flags
*/
void Exporter::SetFunctionFlags(const ulonglong func_flag)
{
	pe_func.func_flag = func_flag;

	pe_func.func_flags = "";

	if ((func_flag & FUNC_NORET))
	{
		AddFlagToField("FUNC_NORET");
	}

	if ((func_flag & FUNC_FAR))
	{
		AddFlagToField("FUNC_FAR");
	}

	if ((func_flag & FUNC_LIB))
	{

		AddFlagToField("FUNC_LIB");
	}

	if ((func_flag & FUNC_STATICDEF))
	{
		AddFlagToField("FUNC_STATICDEF");
	}

	if ((func_flag & FUNC_FRAME))
	{
		AddFlagToField("FUNC_FRAME");
	}

	if ((func_flag & FUNC_HIDDEN))
	{
		AddFlagToField("FUNC_HIDDEN");
	}

	// [PATCH] Обработка флага FUNC_THUNK: функция-обёртка, сохраняем адрес/имя цели и делаем деманглинг
	if (func_flag & FUNC_THUNK)
	{
		AddFlagToField("FUNC_THUNK");

		// [PATCH] Получаем func_t* текущей функции
		func_t* f = get_func(pe_func.address);
		if (f != nullptr)
		{
			const ea_t tgt = ResolveThunkTarget(f);   // пытаемся развернуть thunk → цель
			pe_func.thunk_target = tgt;
			pe_func.thunk_target_name.clear();
			pe_func.thunk_target_name_demangled.clear(); // [PATCH] очищаем демангленную строку

			if (tgt != BADADDR)
			{
				// 1) Сначала берём «сырое» имя (mangled/декорированное) цели
				qstring tn;
				get_ea_name(&tn, tgt);                  // может вернуть пустую строку — это ок
				pe_func.thunk_target_name = tn.c_str(); // сохраняем сырой вариант как std::string

														// 2) Пробуем деманглинг через IDA SDK
														// demangle_name(out, name, flags) → bool. Для начала флаги = 0 (максимум информации).
				if (!tn.empty())
				{
					qstring dem;
					const bool ok = demangle_name(&dem, tn.c_str(), 0 /* флаги деманглинга */);

					if (ok && !dem.empty())
					{
						// [if] Деманглинг удался → сохраним человекочитаемый вариант
						pe_func.thunk_target_name_demangled = dem.c_str();
					}
					else
					{
						// [else] Деманглинг не удался → можно попробовать упростить stdcall-вариант:
						// имена вида _Function@8 → Function
						// Это не «настоящий» деманглинг, но полезный фолбэк для WinAPI stdcall.
						const std::string raw = pe_func.thunk_target_name;
						std::string simple = raw;

						// Снимем лидирующий '_' если есть.
						if (!simple.empty() && simple[0] == '_')
							simple.erase(simple.begin());

						// Уберём трейлинг '@<число>' если есть.
						const auto at = simple.rfind('@');
						if (at != std::string::npos)
						{
							bool all_digits = true;
							for (size_t k = at + 1; k < simple.size(); ++k)
								if (simple[k] < '0' || simple[k] > '9') { all_digits = false; break; }

							if (all_digits)
								simple.erase(at); // отрезаем "@<число>"
						}

						// Если после упрощения имя стало «приятнее» — сохраним как демангленное.
						if (simple != raw)
							pe_func.thunk_target_name_demangled = std::move(simple);
					}
				}
				// [else] tn пустое — оставим demangled пустым
			}
			// [else] tgt == BADADDR — цель не определили: имён нет, всё остаётся пустым
		}
		// [else] f == nullptr — не смогли получить func_t по адресу; ничего не делаем
	}



	if ((func_flag & FUNC_BOTTOMBP))
	{
		AddFlagToField("FUNC_BOTTOMBP");
	}

	if ((func_flag & FUNC_NORET_PENDING))
	{
		AddFlagToField("FUNC_NORET_PENDING");
	}

	if ((func_flag & FUNC_SP_READY))
	{
		AddFlagToField("FUNC_SP_READY");
	}

	if ((func_flag & FUNC_FUZZY_SP))
	{
		AddFlagToField("FUNC_FUZZY_SP");
	}

	if ((func_flag & FUNC_PROLOG_OK))
	{
		AddFlagToField("FUNC_PROLOG_OK");
	}

	if ((func_flag & FUNC_PURGED_OK))
	{
		AddFlagToField("FUNC_PURGED_OK");
	}

	if ((func_flag & FUNC_TAIL))
	{
		AddFlagToField("FUNC_TAIL");
	}

	if ((func_flag & FUNC_LUMINA))
	{
		AddFlagToField("FUNC_LUMINA");
	}

}

void Exporter::SetFunctionType(const ea_t start_address)
{
	if (export_func_address.find(start_address) != export_func_address.end()) {
		// found
		pe_func.function_exported = true;
	}
	else {
		// not found
		pe_func.function_internal = true;
	}
}



/**
* \brief \n Установим хвосты функции \n
* https://stackoverflow.com/questions/5290089/how-to-convert-a-number-to-string-and-vice-versa-in-c \n
* преобразуем число в строку \n
* добавим адрес хвоста функции в строку через разделитель '|'  \n
* \param start_address
*/
void Exporter::SetFunctionTailes(const ea_t start_address)
{
	// [PATCH] -------- Собираем хвосты строго через head --------
	const FuncClassify fc = ClassifyFunction(start_address);
	func_t* base = const_cast<func_t*>(fc.head ? fc.head : fc.this_chunk);
	if (!base) return;
	// [PATCH] --------
	// Сохраняем владельца (head) в модель — пригодится вне этой функции.
	pe_func.function_owner = base->start_ea;




	std::ostringstream ostr; //output string stream
	int counter = 0;		// счетчик для первой строки - остальные через разделитель добавлять

	func_tail_iterator_t fti(base);

	for (bool ok = fti.first(); ok; ok = fti.next()) {
		const range_t& r = fti.chunk();
		if (counter++ == 0) ostr << r.start_ea;
		else                ostr << "|" << r.start_ea;
	}
	if (pe_func.func_tail_ea.empty())
	{
		pe_func.func_tail_ea = ostr.str();
	}
	else
	{	// по идее строка должна быть пустой перед занесением в нее значения
		// так как для каждой функции экземпляр структуры инициализируется по новой 
		msg("\n\n    pe_func.func_tail_ea DON'T EMPTY !!! \n\n");
	}

}

void Exporter::CommandPrintHelp() const
{
	TRACE_FN();
	
	msg("\n\n\n"
		"        **************************************************************************************************\n\n"
		"        bb - always the first argument \n"
		"        next expressions can be second argument : \n"
		"        - 'function' \n"
		"        - 'instruction' \n"
		"        - 'segment' \n"
		"        - 'module' \n"
		"        - 'capstone' \n"
		"\n\n"
		"        next expressions can serve as the third argument : \n"
		"            with 'function' \n"
		"                - any hexadecimal address of the function you are interested \n"
		"                exmpl:    'bb function xxxxxxxx '            print information about function \n"
		"                - 'all' argument displays information about all functions in the file \n"
		"                exmpl:    'bb function all'            including the start address and function name \n"
		""
		""
		"\n\n        **************************************************************************************************"
		"\n\n\n"

	);
}

void Exporter::CommandFunctionParse(std::vector<std::string>& command) const
{
	TRACE_FN();
	
	if (command[1] != "function")
	{
		msg("        Exporter::CommandFunctionParse - ERROR: get argument that doesn't equal 'function' \n");
		return;
	}

	if ((command[2].size() > 2) && IsHexadecimal(command[2]))
	{

		// получим число из строки
		ulonglong address = std::stoul(command[2], nullptr, 16);

		// теперь пошли что то делать с этим адресом
		msg("    Arg hexadecimal number = %llx \n", address);
		// запишем что обработали правильно ещё один аргумент
		exporter.arg_counter += 1;
		// если это последний аргумент  - то выводим все данные о функции ...
		if (exporter.arg_counter == exporter.cmd_arg)
		{
			ParseCMDFunctionAbout(address);

			return;
		}

		// иначе парсим аргументы далее 
		msg("    Arg 4 need parse Here !!! \n");

		return;
	}

	if (command[2] == "all")
	{

		msg("\n\n\n        bb functions all start ************************************************************\n\n");
		PrintFunctionData();
		msg("\n        bb functions all finish ***********************************************************\n\n\n");
		return;
	}



	// иначе неизвестный аргумент
	msg("    Unknown  arg %s...\n", command[2].c_str());

}


/**
* \brief	устанавливает (добавляет) флаги в параметр func_flags , указанные функцией ::SetFunctionFlags()
* \param value
*/
void Exporter::AddFlagToField(const std::string& value)
{
	if (pe_func.func_flags.empty())
	{
		pe_func.func_flags = value;
	}
	else
	{
		pe_func.func_flags.append("|").append(value);
	}
}


/**
* \brief \n BinExport проводит анализ типов функций Ida, и как у них написано : \n
*  - "глупый шаг пост обработки, но IDA иногда выдаёт ломаные ребра (направленные в никуда)" \n\n
* поэтому мы доверимся BinExport и изменим флаги функции на указанные ими после их обработки данных \n
* \param start_address адрес начала функции
* \param func_flag		флаг BinExport , установленный для данной функции
*						на основании которого мы изменим наш флаг , \n	        полученный ранее в
*						ExportIdbAdditional функции файла start_window.cpp
*/
void Exporter::ChangeFunctionFlags(const ea_t start_address, const ulonglong func_flag)
{
	const auto i = function_index.find(start_address);

	if (i != function_index.end()) {
		// found

		// по идентификатору получим экземпляр для данной функции (адреса )
		auto f = function_data[i->second];

		// и зададим (изменим) значение для нее 
		f.func_flag = func_flag;
		func_old_flags = f.func_flags;
		f.func_flags = FlagsToString(func_flag);
		func_new_flags = f.func_flags;

	}
	else {
		//not found
		msg("When replacing flags wasn't found  function with address %llx \n", start_address);
		func_new_flags = "false";
	}
}

std::string Exporter::FlagsToString(const ulonglong func_flag)
{
	std::string flags{};
	int counter = 0;

	if ((func_flag & FUNC_NORET))
	{
		if (flags.empty())
		{
			flags = "FUNC_NORET";
		}
		else
		{
			flags.append("|").append("FUNC_NORET");
		}
	}

	if ((func_flag & FUNC_FAR))
	{
		if (flags.empty())
		{
			flags = "FUNC_FAR";
		}
		else
		{
			flags.append("|").append("FUNC_FAR");
		}
	}

	if ((func_flag & FUNC_LIB))
	{

		if (flags.empty())
		{
			flags = "FUNC_LIB";
		}
		else
		{
			flags.append("|").append("FUNC_LIB");
		}
	}

	if ((func_flag & FUNC_STATICDEF))
	{
		if (flags.empty())
		{
			flags = "FUNC_STATICDEF";
		}
		else
		{
			flags.append("|").append("FUNC_STATICDEF");
		}
	}

	if ((func_flag & FUNC_FRAME))
	{
		if (flags.empty())
		{
			flags = "FUNC_FRAME";
		}
		else
		{
			flags.append("|").append("FUNC_FRAME");
		}
	}

	if ((func_flag & FUNC_HIDDEN))
	{
		if (flags.empty())
		{
			flags = "FUNC_HIDDEN";
		}
		else
		{
			flags.append("|").append("FUNC_HIDDEN");
		}
	}

	if ((func_flag & FUNC_THUNK))
	{
		if (flags.empty())
		{
			flags = "FUNC_THUNK";
		}
		else
		{
			flags.append("|").append("FUNC_THUNK");
		}
	}

	if ((func_flag & FUNC_BOTTOMBP))
	{
		if (flags.empty())
		{
			flags = "FUNC_BOTTOMBP";
		}
		else
		{
			flags.append("|").append("FUNC_BOTTOMBP");
		}
	}

	if ((func_flag & FUNC_NORET_PENDING))
	{
		if (flags.empty())
		{
			flags = "FUNC_NORET_PENDING";
		}
		else
		{
			flags.append("|").append("FUNC_NORET_PENDING");
		}
	}

	if ((func_flag & FUNC_SP_READY))
	{
		if (flags.empty())
		{
			flags = "FUNC_SP_READY";
		}
		else
		{
			flags.append("|").append("FUNC_SP_READY");
		}
	}

	if ((func_flag & FUNC_FUZZY_SP))
	{
		if (flags.empty())
		{
			flags = "FUNC_FUZZY_SP";
		}
		else
		{
			flags.append("|").append("FUNC_FUZZY_SP");
		}
	}

	if ((func_flag & FUNC_PROLOG_OK))
	{
		if (flags.empty())
		{
			flags = "FUNC_PROLOG_OK";
		}
		else
		{
			flags.append("|").append("FUNC_PROLOG_OK");
		}
	}

	if ((func_flag & FUNC_PURGED_OK))
	{
		if (flags.empty())
		{
			flags = "FUNC_PURGED_OK";
		}
		else
		{
			flags.append("|").append("FUNC_PURGED_OK");
		}
	}

	if ((func_flag & FUNC_TAIL))
	{
		if (flags.empty())
		{
			flags = "FUNC_TAIL";
		}
		else
		{
			flags.append("|").append("FUNC_TAIL");
		}
	}

	if ((func_flag & FUNC_LUMINA))
	{
		if (flags.empty())
		{
			flags = "FUNC_LUMINA";
		}
		else
		{
			flags.append("|").append("FUNC_LUMINA");
		}
	}

	return flags;
}

std::string Exporter::CheckMangledName(const PeFunc& fd, const bool mangled) const
{
	std::string fname{};
	if (mangled)
	{
		fname = fd.name;
	}
	else
	{
		fname = fd.dem_name;
		if (fname.empty())
		{
			fname = fd.name;
		}
	}

	return fname;
}

int Exporter::GetFunctionIndex(const ea_t start_address) const
{

	int index = -1;

	// ищем индекс функции по ключу - стартовому адресу в мапе 
	const auto i = function_index.find(start_address);

	if (i != function_index.end()) {
		// found

		// по ключу получим индекс функции в векторе 
		index = static_cast<int>(i->second);

	}

	return index;
}




/**
* \brief Сброс статистики Exporter::stats_.
*/
void Exporter::ResetStats()
{
	TRACE_FN();
	
	// [PATCH] Обнуляем счётчики и очищаем множество уникальных head'ов.
	stats_.total_chunks = 0;
	stats_.unique_heads = 0;
	stats_.total_tails = 0;
	stats_.total_thunks = 0;
	stats_.seen_heads.clear();
}

/**
* \brief Регистрация классификации чанка/функции.
* \param fc Структура FuncClassify, полученная через ClassifyFunction(ea).
*/
void Exporter::RegisterFunctionClassify(const FuncClassify &fc)
{
	// [if] Если вообще нет информации — не инкрементируем.
	if (!fc.this_chunk) {
		return;
	}

	// Всегда инкрементируем общее число обработанных чанков.
	stats_.total_chunks++;

	// Проверяем конкретные виды.
	if (fc.kind == FuncKind::TailChunk) {
		// [if] Это tail-chunk — увеличиваем число tail'ов.
		stats_.total_tails++;
		// Также хотим учесть его owner в unique_heads — owner может быть в fc.head.
		if (fc.head) {
			// Попытка вставить owner в множество. insert вернёт pair<it,bool>,
			// second == true если элемент был добавлен впервые.
			auto pr = stats_.seen_heads.insert(fc.head->start_ea);
			if (pr.second) {
				// [if] Новая голова — увеличиваем unique_heads.
				stats_.unique_heads++;
			}
		}
	}
	else if (fc.kind == FuncKind::Thunk) {
		// [else-if] Это thunk — считаем их отдельно.
		stats_.total_thunks++;

		// Для thunk'ов тоже возможен head (fc.head может указывать на сам thunk как head).
		if (fc.head) {
			auto pr = stats_.seen_heads.insert(fc.head->start_ea);
			if (pr.second) {
				stats_.unique_heads++;
			}
		}
	}
	else if (fc.kind == FuncKind::Head) {
		// [else] Обычная голова: считаем уникальность по start_ea.
		if (fc.head) {
			auto pr = stats_.seen_heads.insert(fc.head->start_ea);
			if (pr.second) {
				stats_.unique_heads++;
			}
		}
	}
	else {
		// fc.kind == None — ничего не делаем.
	}
}

/**
* \brief Печать сводной статистики в msg().
* \details Формат вывода аккуратный и одноразовый: heads/tails/thunks/total chunks.
*/
void Exporter::PrintStats() const
{

	TRACE_FN();
	
	msg("\n\n================ Plugin analysis summary ================\n");
	msg("  Total chunks processed: %llu\n", static_cast<unsigned long long>(stats_.total_chunks));
	msg("  Unique head functions : %llu\n", static_cast<unsigned long long>(stats_.unique_heads));
	msg("  Total tail-chunks     : %llu\n", static_cast<unsigned long long>(stats_.total_tails));
	msg("  Total thunk functions : %llu\n", static_cast<unsigned long long>(stats_.total_thunks));
	msg("========================================================\n\n");

	
	// \brief Печать размеров стека из PE OptionalHeader, разобранного в pe_heders.cpp.
	// [STACK] --- begin ---
	// [STACK] печать из кэша Exporter::pe_image_info_
	{
		const unsigned long long reserveB = static_cast<unsigned long long>(pe_image_info_.stack_reserve);
		const unsigned long long commitB = static_cast<unsigned long long>(pe_image_info_.stack_commit);

		if (reserveB != 0ULL || commitB != 0ULL) {
			const unsigned long long reserveKB = reserveB / 1024ULL;
			const unsigned long long commitKB = commitB / 1024ULL;
			msg("  PE Stack (static): reserve=%llu bytes (%llu KB), commit=%llu bytes (%llu KB)\n\n",
				reserveB, reserveKB, commitB, commitKB);
		}
		else {
			msg("  PE Stack: not available (no header parsed or non-PE)\n\n");
		}
	}

	// [STACK] --- end ---

	// [INSTR-SUMMARY] --- begin ---
	// \brief Сводка по инструкциям (stack/global/alloc/sp-delta), чтобы проверить заполнение флагов.
	{
		unsigned long long total_insn = static_cast<unsigned long long>(vector_pe_instructions.size());
		unsigned long long cnt_reads_stack = 0;
		unsigned long long cnt_writes_stack = 0;
		unsigned long long cnt_reads_global = 0;
		unsigned long long cnt_writes_global = 0;
		unsigned long long cnt_alloc_calls = 0;
		long long          sp_delta_sum = 0;
		int                sp_delta_min = 0;
		int                sp_delta_max = 0;
		bool               sp_delta_inited = false;

		for (const auto &pi : vector_pe_instructions)
		{
			if (pi.reads_stack)   ++cnt_reads_stack;
			if (pi.writes_stack)  ++cnt_writes_stack;
			if (pi.reads_global)  ++cnt_reads_global;
			if (pi.writes_global) ++cnt_writes_global;
			if (pi.is_alloc_call) ++cnt_alloc_calls;

			// \brief аккумулируем sp_delta и отслеживаем min/max
			sp_delta_sum += static_cast<long long>(pi.sp_delta);
			if (!sp_delta_inited) {
				sp_delta_min = sp_delta_max = pi.sp_delta;
				sp_delta_inited = true;
			}
			else {
				if (pi.sp_delta < sp_delta_min) sp_delta_min = pi.sp_delta;
				if (pi.sp_delta > sp_delta_max) sp_delta_max = pi.sp_delta;
			}
		}

		msg("---- Instruction summary --------------------------------\n");
		msg("  Total instructions    : %llu\n", total_insn);
		msg("  Stack  reads / writes : %llu / %llu\n", cnt_reads_stack, cnt_writes_stack);
		msg("  Global reads / writes : %llu / %llu\n", cnt_reads_global, cnt_writes_global);
		msg("  Alloc calls (malloc/..): %llu\n", cnt_alloc_calls);
		msg("  SP delta: sum/min/max  : %lld / %d / %d\n",
			sp_delta_sum, sp_delta_min, sp_delta_max);
		msg("----------------------------------------------------------\n\n");
	}
	// [INSTR-SUMMARY] --- end ---

	// [EFFECTS-SUMMARY] --- begin ---
	// \brief Сводка агрегатов побочных эффектов по функциям.

	// 1) Общая сумма по всем функциям
	unsigned long long F_total = 0, F_instr = 0;
	unsigned long long F_stack_r = 0, F_stack_w = 0;
	unsigned long long F_glob_r = 0, F_glob_w = 0;
	unsigned long long F_alloc = 0, F_free = 0, F_heap = 0;
	unsigned long long F_heap_events = 0;

	for (const auto &kv : func_effects_) {
		const FunctionEffects &fx = kv.second;
		++F_total;
		F_instr += fx.instr_total;
		F_stack_r += fx.stack_reads;
		F_stack_w += fx.stack_writes;
		F_glob_r += fx.global_reads;
		F_glob_w += fx.global_writes;
		F_alloc += fx.alloc_calls;
		F_free += fx.free_calls;
		F_heap += fx.heap_touches;
		F_heap_events += fx.heap_first_touch_events;
	}

	msg("---- Function-effects summary ---------------------------\n");
	msg("  Functions analyzed     : %llu\n", F_total);
	msg("  Instructions (sum)     : %llu\n", F_instr);
	msg("  Stack   R/W (sum)      : %llu / %llu\n", F_stack_r, F_stack_w);
	msg("  Globals R/W (sum)      : %llu / %llu\n", F_glob_r, F_glob_w);
	msg("  Alloc/Free/Heap touches: %llu / %llu / %llu\n", F_alloc, F_free, F_heap);
	msg("  Heap first-touch events : %llu\n", F_heap_events);

	// 2) Топ-10 функций по глобальным записям и по вызовам аллокаторов
	struct Row { ea_t fva; const FunctionEffects* fx; };

	std::vector<Row> rows; rows.reserve(func_effects_.size());
	for (const auto &kv : func_effects_) rows.push_back({ kv.first, &kv.second });

	// helper: имя функции (демангл краткий)
	auto get_fn_name = [](ea_t fva) -> qstring {
		qstring n, dem;
		if (get_name(&n, fva) > 0) {
			if (demangle_name(&dem, n.c_str(), MNG_SHORT_FORM) > 0) n = dem;
		}
		else {
			n.sprnt("sub_%llX", static_cast<unsigned long long>(fva));
		}
		return n;
	};

	// Топ по глобальным записям
	std::sort(rows.begin(), rows.end(), [](const Row& a, const Row& b) {
		// if/else: первичный ключ — global_writes, вторичный — instr_total (стабильнее)
		if (a.fx->global_writes != b.fx->global_writes)
			return a.fx->global_writes > b.fx->global_writes;
		return a.fx->instr_total > b.fx->instr_total;
	});

	msg("\n  Top-10 by global writes\n");
	{
		const size_t N = rows.size() < 10 ? rows.size() : 10;
		for (size_t i = 0; i < N; ++i) {
			const auto &r = rows[i];
			qstring name = get_fn_name(r.fva);
			msg("   %2zu) %s  @%llX  gw=%llu  gr=%llu  sw=%llu  sr=%llu  ins=%llu\n",
				i + 1,
				name.c_str(),
				static_cast<unsigned long long>(r.fva),
				static_cast<unsigned long long>(r.fx->global_writes),
				static_cast<unsigned long long>(r.fx->global_reads),
				static_cast<unsigned long long>(r.fx->stack_writes),
				static_cast<unsigned long long>(r.fx->stack_reads),
				static_cast<unsigned long long>(r.fx->instr_total));
		}
	}

	// Топ по аллокаторам
	std::sort(rows.begin(), rows.end(), [](const Row& a, const Row& b) {
		if (a.fx->alloc_calls != b.fx->alloc_calls)
			return a.fx->alloc_calls > b.fx->alloc_calls;
		return a.fx->instr_total > b.fx->instr_total;
	});

	msg("\n  Top-10 by allocator calls\n");
	{
		const size_t N = rows.size() < 10 ? rows.size() : 10;
		for (size_t i = 0; i < N; ++i) {
			const auto &r = rows[i];
			qstring name = get_fn_name(r.fva);
			// \brief показываем alloc/free, чтобы видеть «симметрию» в пределах функции
			msg("   %2zu) %s  @%llX  alloc=%llu  free=%llu  heap=%llu  first=%llu  use=%u%%  nofirst=%llu  bal=%lld  ins=%llu\n",
				i + 1,
				name.c_str(),
				static_cast<unsigned long long>(r.fva),
				static_cast<unsigned long long>(r.fx->alloc_calls),
				static_cast<unsigned long long>(r.fx->free_calls),
				static_cast<unsigned long long>(r.fx->heap_touches),
				static_cast<unsigned long long>(r.fx->heap_first_touch_events),
				r.fx->alloc_use_rate_pct,
				static_cast<unsigned long long>(r.fx->alloc_no_first_touch),
				static_cast<long long>(r.fx->alloc_free_balance),
				static_cast<unsigned long long>(r.fx->instr_total));

		}
	}

	msg("----------------------------------------------------------\n\n");
	// [EFFECTS-SUMMARY] --- end ---

	// [WRAPPERS/DISPATCHERS] --- begin ---
	{
		// helper: имя функции (демангл краткий)
		auto get_fn_name = [](ea_t fva) -> qstring {
			qstring n, dem;
			if (get_name(&n, fva) > 0) {
				if (demangle_name(&dem, n.c_str(), MNG_SHORT_FORM) > 0) n = dem;
			}
			else {
				n.sprnt("sub_%llX", static_cast<unsigned long long>(fva));
			}
			return n;
		};

		struct RowWD { ea_t fva; const FunctionEffects* fx; };

		std::vector<RowWD> wrappers;
		std::vector<RowWD> dispatchers;

		// Собираем кандидатов
		for (const auto &kv : func_effects_) {
			const auto fva = kv.first;
			const FunctionEffects* fx = &kv.second;

			if (fx->is_wrapper || fx->is_tailcall_thunk || fx->forwards_params_only) {
				wrappers.push_back({ fva, fx });
			}
			if (fx->dispatches_via_funptr || (fx->indirect_calls > 0 && fx->calls_total >= 1)) {
				dispatchers.push_back({ fva, fx });
			}
		}

		// Сортировка: обёртки — по «минимальности» (instr_total ↑, затем calls_total ↑)
		std::sort(wrappers.begin(), wrappers.end(),
			[](const RowWD& a, const RowWD& b) {
			if (a.fx->instr_total != b.fx->instr_total) return a.fx->instr_total < b.fx->instr_total;
			return a.fx->calls_total < b.fx->calls_total;
		});

		// Сортировка: диспетчеры — по «степени косвенности» (indirect_calls ↓, затем calls_total ↓)
		std::sort(dispatchers.begin(), dispatchers.end(),
			[](const RowWD& a, const RowWD& b) {
			if (a.fx->indirect_calls != b.fx->indirect_calls) return a.fx->indirect_calls > b.fx->indirect_calls;
			return a.fx->calls_total > b.fx->calls_total;
		});

		// Печать: WRAPPERS
		msg("\n  Top-10 wrappers/forwarders\n");
		{
			const size_t N = wrappers.size() < 10 ? wrappers.size() : 10;
			for (size_t i = 0; i < N; ++i) {
				const auto &r = wrappers[i];
				qstring name = get_fn_name(r.fva);

				// пометки-флаги
				char t_wrap = r.fx->is_wrapper ? 'W' : '-';
				char t_tail = r.fx->is_tailcall_thunk ? 'T' : '-';
				char t_fwd = r.fx->forwards_params_only ? 'F' : '-';

				// производные локально (на случай, если финализацию забыли вызвать)
				const uint64_t alloc = r.fx->alloc_calls;
				const uint64_t first = r.fx->heap_first_touch_events;
				const uint64_t frees = r.fx->free_calls;
				const uint32_t usepct = alloc ? static_cast<uint32_t>((first * 100ULL) / alloc) : 0;

				msg("   %2zu) %s  @%llX  [ %c %c %c ]  calls=%u (dir=%u ind=%u)  ins=%llu  alloc=%llu free=%llu use=%u%%\n",
					i + 1,
					name.c_str(),
					static_cast<unsigned long long>(r.fva),
					t_wrap, t_tail, t_fwd,
					r.fx->calls_total, r.fx->direct_calls, r.fx->indirect_calls,
					static_cast<unsigned long long>(r.fx->instr_total),
					static_cast<unsigned long long>(alloc),
					static_cast<unsigned long long>(frees),
					usepct);
			}
		}

		// Печать: DISPATCHERS
		msg("\n  Top-10 dispatchers via function pointer\n");
		{
			const size_t N = dispatchers.size() < 10 ? dispatchers.size() : 10;
			for (size_t i = 0; i < N; ++i) {
				const auto &r = dispatchers[i];
				qstring name = get_fn_name(r.fva);

				// метка диспетчера
				char t_disp = r.fx->dispatches_via_funptr ? 'D' : '-';

				// полезные индикаторы владения
				char t_ret_heap = r.fx->returns_heap_ptr ? 'R' : '-';
				char t_out_heap = r.fx->writes_heap_to_outparam ? 'O' : '-';

				msg("   %2zu) %s  @%llX  [%c | %c%c]  calls=%u (dir=%u ind=%u)  ins=%llu\n",
					i + 1,
					name.c_str(),
					static_cast<unsigned long long>(r.fva),
					t_disp, t_ret_heap, t_out_heap,
					r.fx->calls_total, r.fx->direct_calls, r.fx->indirect_calls,
					static_cast<unsigned long long>(r.fx->instr_total));
			}
		}
		msg("----------------------------------------------------------\n\n");
	}
	// [WRAPPERS/DISPATCHERS] --- end ---

	// [SUSPECTS] --- begin ---
	struct RowS { ea_t fva; const FunctionEffects* fx; };


	std::vector<RowS> suspects_transfer; // alloc>0 && free==0 && use<50%
	std::vector<RowS> suspects_growth;   // alloc_free_balance >> 0 (порог >= 3)

	for (const auto &kv : func_effects_) {
		const auto fva = kv.first;
		const FunctionEffects* fx = &kv.second;

		const bool c1 = (fx->alloc_calls > 0) && (fx->free_calls == 0) && (fx->alloc_use_rate_pct < 50);
		if (c1) suspects_transfer.push_back({ fva, fx });

		const bool c2 = (fx->alloc_free_balance >= 3); // «заметный рост» — можно поднять/опустить порог
		if (c2) suspects_growth.push_back({ fva, fx });
	}

	// сортируем для удобства
	std::sort(suspects_transfer.begin(), suspects_transfer.end(),
		[](const RowS& a, const RowS& b) {
		// первично: alloc_calls ↓, вторично: use% ↑ (хуже вверху)
		if (a.fx->alloc_calls != b.fx->alloc_calls) return a.fx->alloc_calls > b.fx->alloc_calls;
		return a.fx->alloc_use_rate_pct < b.fx->alloc_use_rate_pct;
	});

	std::sort(suspects_growth.begin(), suspects_growth.end(),
		[](const RowS& a, const RowS& b) {
		// первично: баланс ↓, вторично: alloc_calls ↓
		if (a.fx->alloc_free_balance != b.fx->alloc_free_balance) return a.fx->alloc_free_balance > b.fx->alloc_free_balance;
		return a.fx->alloc_calls > b.fx->alloc_calls;
	});

	msg("\n  Suspects: transfer-ownership or potential leaks (alloc>0, free=0, use<50%%)\n");
	{
		const size_t N = suspects_transfer.size() < 10 ? suspects_transfer.size() : 10;
		for (size_t i = 0; i < N; ++i) {
			const auto &r = suspects_transfer[i];
			qstring name = get_fn_name(r.fva);
			msg("   %2zu) %s  @%llX  alloc=%llu  first=%llu  use=%u%%  free=%llu\n",
				i + 1, name.c_str(),
				static_cast<unsigned long long>(r.fva),
				static_cast<unsigned long long>(r.fx->alloc_calls),
				static_cast<unsigned long long>(r.fx->heap_first_touch_events),
				r.fx->alloc_use_rate_pct,
				static_cast<unsigned long long>(r.fx->free_calls));
		}
	}

	msg("\n  Suspects: net growth of allocations (alloc_free_balance >= 3)\n");
	{
		const size_t N = suspects_growth.size() < 10 ? suspects_growth.size() : 10;
		for (size_t i = 0; i < N; ++i) {
			const auto &r = suspects_growth[i];
			qstring name = get_fn_name(r.fva);
			msg("   %2zu) %s  @%llX  alloc=%llu  free=%llu  bal=%lld  use=%u%%\n",
				i + 1, name.c_str(),
				static_cast<unsigned long long>(r.fva),
				static_cast<unsigned long long>(r.fx->alloc_calls),
				static_cast<unsigned long long>(r.fx->free_calls),
				static_cast<long long>(r.fx->alloc_free_balance),
				r.fx->alloc_use_rate_pct);
		}
	}
	msg("----------------------------------------------------------\n\n");
	// [SUSPECTS] --- end ---

}

/**
* \brief Перечитать OptionalHeader.SizeOfStackReserve/Commit .
*/
bool Exporter::RefreshPeImageInfo()
{
	TRACE_FN();
	
	// Берём значения из уже разобранного pe_heders.cpp
	const unsigned long long reserveB = static_cast<unsigned long long>(GetPeSizeOfStackReserve());
	const unsigned long long commitB = static_cast<unsigned long long>(GetPeSizeOfStackCommit());

	pe_image_info_.stack_reserve = reserveB;
	pe_image_info_.stack_commit = commitB;

	// true, если что-то реально прочитали (для PE обычно оба поля заданы)
	return (reserveB != 0ULL) || (commitB != 0ULL);
}


// [EFFECTS] --- begin ---
FunctionEffects& Exporter::GetOrCreateFuncEffects(ea_t fva) {
	return func_effects_[fva]; // создаст по умолчанию, если нет
}

const FunctionEffects* Exporter::FindFuncEffects(ea_t fva) const {
	auto it = func_effects_.find(fva);
	return (it == func_effects_.end()) ? nullptr : &it->second;
}
// [EFFECTS] --- end ---

// [EFFECTS+DERIVED] --- begin ---
void Exporter::FinalizeFunctionEffects()
{
	for (auto &kv : func_effects_)
	{
		FunctionEffects &fx = kv.second;

		// alloc_no_first_touch = max(0, alloc - first)
		if (fx.alloc_calls >= fx.heap_first_touch_events)
			fx.alloc_no_first_touch = fx.alloc_calls - fx.heap_first_touch_events;
		else
			fx.alloc_no_first_touch = 0;

		// баланс аллокаций/фри
		fx.alloc_free_balance =
			static_cast<int64_t>(fx.alloc_calls) - static_cast<int64_t>(fx.free_calls);

		// процент использования (avoid div by 0)
		if (fx.alloc_calls > 0)
			fx.alloc_use_rate_pct =
			static_cast<uint32_t>((fx.heap_first_touch_events * 100ULL) / fx.alloc_calls);
		else
			fx.alloc_use_rate_pct = 0;

		// --- wrapper/forwarder/dispatch эвристики (расчёт на финализации) ---
		fx.is_wrapper =
			(fx.calls_total == 1) &&
			(fx.global_writes == 0) &&
			(fx.stack_writes <= 1) &&     // допускаем один стек-запис (пролог/эпилог)
			(fx.alloc_calls == 0 && fx.free_calls == 0);

		fx.is_tailcall_thunk =
			(fx.calls_total == 1) &&
			(fx.instr_total < 16) &&
			(fx.stack_writes == 0);

		fx.forwards_params_only =
			fx.is_wrapper &&
			(fx.dispatches_via_funptr || fx.direct_calls == 1);
		// --------------------------------------------------------------------
	}
}
// [EFFECTS+DERIVED] --- end ---
