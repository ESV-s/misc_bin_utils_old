

void Exporter::ParseCMDFunctionAbout(ea_t address) const
{
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
	// Например:
	const ea_t start_address = head->start_ea;
	const ea_t end_address = head->end_ea;


	/**
	 было
	// получим указатель на функцию по версии IDA 
	func_t* func = get_func(address);
	 */
	
	// [PATCH] делаем мутируемый указатель на head, чтобы звать API, где нужен func_t* (а не const)
	func_t* func = const_cast<func_t*>(head);

	

	if (func == nullptr)
	{
		msg("                    ERROR : IDA HAS NO information about %llx address \n\n", address);
		return;
	}

	// зададим количество пробелов с начала строки = 16

	const auto n_space = "                ";
	// по итогу строка
	// " 16 пробелов " + "строка любой длинны  - начало слева строки - выравненная до 40 символов "
	// записываем как msg("%s %-40s %s \n", n_space, "Строка в 40 символов", f_type.c_str());





	qstring name{};
	get_ea_name(&name, start_address);

	msg("%s %-40s %s \n", n_space, "Function", name.c_str());
	msg("%s %-40s %llx : %llx \n", n_space, "Has bounds", start_address, end_address);

	

	// [PATCH] Если текущий чанк помечен как thunk — покажем его цель (куда он прыгает).
	if (fc.this_chunk->flags & FUNC_THUNK) {
		// calc_thunk_func_target требует НЕ-const указатель на func_t.
		func_t* mutable_this = const_cast<func_t*>(fc.this_chunk);
		const ea_t tgt = ResolveThunkTarget(mutable_this); // см. function_utils.cpp

		if (tgt != BADADDR) {
			qstring tname;
			get_ea_name(&tname, tgt);
			msg("%s %-40s %s (%llx)\n", "                ", "Thunk target", tname.c_str(), tgt);
		}
		else {
			msg("%s %-40s %s\n", "                ", "Thunk target", "<not resolved>");
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
	// msg("My data from vector  = %s  :   %llx  \n", mf.name.c_str(), mf.address);
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

	// количество инструкции в функции C:\Users\Sergey\Desktop\IdaBookPro\listing_15_2_работает.idc
	msg("%s %-40s %d \n", n_space, "Function Instructions Count ", FunctionInstructionCount(start_address, end_address));

	msg("\n");

	// вызовы из функции C:\Users\Sergey\Desktop\IdaBookPro\listing_15_3_работает.idc
	FunctionCalls(start_address, end_address);

	msg("\n");

	// в какой функции вызывается текущая функция C:\Users\Sergey\Desktop\IdaBookPro\listing_15_4_работает.idc
	FunctionReference(start_address, end_address);

	msg("\n");

	// текущие переменные для функции C:\Users\Sergey\Desktop\IdaBookPro\listing_22_4_работает.idc
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

	// использование буферов для переменных C:\Users\Sergey\Desktop\IdaBookPro\listing_22_3_работает.idc



	// для функции  - место вставки шелл кода ищет C:\Users\Sergey\Desktop\IdaBookPro\opcode_scan_работает.idc


	msg("\n\n        information about function containing the address is complete \n\n");
	return;
}
