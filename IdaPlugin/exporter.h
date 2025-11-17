#pragma once

#include "begin_idasdk.inc"
// переменные для получения данных в вектора начало
#include "start_window.hpp"
#include <map>
#include "settings.h"
#include <sstream>  //include this to use string streams
#include <iostream>

// [PATCH] Утилиты для классификации функций (Head/Tail/Thunk) и работы с чанками.
#include <sstream>
#include "function_utils.h"
#include <unordered_set>
// [PATCH] --- деманглинг: отключим устаревшие объявления и обеспечим верный порядок хедеров ---
#ifndef NO_OBSOLETE_FUNCS
#define NO_OBSOLETE_FUNCS 1   // не тащим старый API demangler_t/demangle
#endif

#include <ida.hpp>            // гарантируем, что pro.h уже подключён до demangle.hpp
#include <demangle.hpp>       // demangle_name(...)

#include "stack_utils.h" // [STACK]

#include <unordered_map> // нужно для map ниже

// [EFFECTS] --- begin ---
//! \brief Агрегаты побочных эффектов по функции.
struct FunctionEffects {
	uint64_t instr_total = 0;
	uint64_t stack_reads = 0;
	uint64_t stack_writes = 0;
	uint64_t global_reads = 0;
	uint64_t global_writes = 0;

	uint64_t alloc_calls = 0;
	uint64_t free_calls = 0;
	uint64_t heap_touches = 0;

	long long sp_delta_sum = 0;
	int       sp_delta_min = 0;
	int       sp_delta_max = 0;
	bool      sp_inited = false;
	// [EFFECTS] --- add field ---
	/**
	* \brief Кол-во «событий первого касания»: число аллокаций, у которых был хотя бы один mem-доступ.
	* \details В отличие от heap_touches (счётчик всех mem-операций по heap-указателю),
	*          этот счётчик растёт максимум на 1 для каждой аллокации.
	*/
	uint64_t heap_first_touch_events = 0;
	// [EFFECTS+DERIVED] --- begin ---
	/**
	* \brief Число аллокаций без локального первого касания (alloc_calls - heap_first_touch_events, не < 0).
	*/
	uint64_t alloc_no_first_touch = 0;

	/**
	* \brief Баланс аллок/фри: alloc_calls - free_calls (может быть отрицательным).
	*/
	int64_t  alloc_free_balance = 0;

	/**
	* \brief Доля «использованных» аллокаций в процентах (0..100), округление вниз.
	* \details 100 * heap_first_touch_events / max(1, alloc_calls).
	*/
	uint32_t alloc_use_rate_pct = 0;
	// [EFFECTS+DERIVED] --- end ---

	// === Wrapper/Forward/Dispatch flags ===
	/** \brief Всего вызовов внутри функции (прямых+косвенных). */
	uint32_t calls_total = 0;
	/** \brief Кол-во прямых вызовов (near/far). */
	uint32_t direct_calls = 0;
	/** \brief Кол-во косвенных вызовов (через регистр/память). */
	uint32_t indirect_calls = 0;

	/** \brief Обёртка: функция делает ровно один вызов и почти не имеет побочных эффектов. */
	bool is_wrapper = false;
	/** \brief Tailcall/thunk-поведение: последний прыжок/вызов без дальнейшего кода. */
	bool is_tailcall_thunk = false;
	/** \brief Форвардинг параметров «как есть» (эвристика). */
	bool forwards_params_only = false;
	/** \brief Диспетчер: вызывает по указателю функции, вероятно взятому из параметра. */
	bool dispatches_via_funptr = false;

	/** \brief Возвращает heap-указатель в RAX/EAX (после alloc). */
	bool returns_heap_ptr = false;
	/** \brief Пишет heap-указатель в out-параметр (store через адрес параметра). */
	bool writes_heap_to_outparam = false;

	
};
// [EFFECTS] --- end ---




/**
* \brief Класс для сбора информации о исполняемом файле , \n
* которая будет экспортирована в работу плагина ...\n
* \details Информация, добавляемая в класс, получена благодаря данным расширения binexport ...\n
* \defgroup exporter BinExport информация ...
*/
class Exporter
{

public:

	size_t  index = -1;
	// для флагов функций IDA если вдруг нам пришлось их менять по варианту БинЭкспорта
	// поля служат для временного хранения  - чтобы вывести в панель вывода
	// после чего сразу обнуляются !!!
	std::string func_old_flags = "";
	std::string func_new_flags = "";
	// для получения количества функций во flow_graph BinExport
	long long flow_graph_func_count = 0;
	long long modules_size = 0;
	size_t vector_need_size = 0;

	// счетчик обработанных функциями аргументов в выражении CMD строки
	int arg_counter = 0;
	// количество параметров в векторе для анализа 
	int cmd_arg = 0;

	/**
	* \brief \n Структура с данными об инструкции функций в pe файле...
	*/
	struct PeInstruction
	{
		ea_t address;       ///< адрес непосредственно ...
		ea_t func_address;  ///< Функция к которой он принадлежит
		ea_t addr_put;      ///< ложит что то куда то 
		ea_t addr_take;     ///< берет что то откуда то 
		ea_t addr_jmp_flag; ///< вариант инструкции j...
		ea_t addr_jmp;      ///< безусловный jmp
		ea_t addr_call_out; ///< вызывает что то 
		ea_t addr_call_get; ///< вызывается откуда то 
		ea_t addr_value;    ///< содержит переменную
		bool addr_code;     ///< содержит код
		bool addr_return;   ///< return из функции

		// ===== [NEW] детект по операндам/эффектам инструкции =====

		/**
		* \brief Инструкция читает данные со стека (операнд через SP/BP/RSP/RBP).
		* \details Эвристика: o_displ/o_phrase с базовым регистром {SP,BP,ESP,EBP,RSP,RBP},
		*          и флаг CF_USE* для соответствующего операнда.
		*/
		bool reads_stack = false;

		/**
		* \brief Инструкция пишет данные в стек.
		* \details Эвристика: как выше, но с флагом CF_CHG* для операнда.
		*/
		bool writes_stack = false;

		/**
		* \brief Инструкция читает глобальную/статическую память (о_mem или адрес из .data/.rdata).
		*/
		bool reads_global = false;

		/**
		* \brief Инструкция пишет в глобальную/статическую память.
		*/
		bool writes_global = false;

		/**
		* \brief Изменение стека (SP-дельта) на этой инструкции.
		* \details Значение из calc_sp_delta()/аналогов IDA: push => -ptrsize, pop => +ptrsize, prologue/epilogue — крупные сдвиги.
		*          0 если неизвестно или не меняет SP.
		*/
		int  sp_delta = 0;

		/**
		* \brief Признак «работы с кучей» по месту: чтение/запись по указателю, полученному из известного аллокатора.
		* \details Устанавливается, если в пределах функции ранее зафиксирован вызов malloc/new/HeapAlloc и
		*          текущая инструкция разыменует тот же регистр/локальную, куда вернулся указатель.
		*          Это эвристика, даёт сигнал для трекинга heap-переменных.
		*/
		bool touches_heap = false;

		/**
		* \brief Инструкция сама является вызовом известного аллокатора (malloc/new/HeapAlloc/...).
		*/
		bool is_alloc_call = false;
	} pe_instruction;

	/**
	* \brief \n Структура, содержащая данные о функции - см funcs.hpp func_t class
	* - смотреть funcs.hpp func_t class так как есть поля структуры, доступ на прямую к которым, запрещен \n\n
	* - address		- адрес начала функции
	* - name			- не размангленное имя функции
	* - dem_name		- demangled имя функции (типа размангленное)
	* - addr_call_out		- вызывает что то в теле
	* - addr_call_get		- вызывается откуда то
	* - before_entry_point	- выполняется до точки входа pe файла ...
	* - function_internal	- внутренняя функция
	* - function_exported	- экспортируемая функция
	* - function_imported	- импортируемая функция
	*/
	struct PeFunc
	{
		size_t address{};					///< адрес функции
		std::string name{};				///< имя функции
		std::string dem_name{};			///< demangled имя функции
		std::string func_flags{};		///< флаги функции через разделитель '|'
		std::string func_tail_ea{};		///< \n if (function_tailqty) проверка сначала \n
										///< потом уже начинаем использовать это поле \n
										///< -адреса хвостов функции через разделитель '|' 
		asize_t func_frsize;			///< размер части локальных переменных кадра в байтах.\n
										///< If #FUNC_FRAME установлен и #fpd==0, то предполагается что \n
										///< the frame pointer (EBP) указывает на верхнюю границу диапазона локальных переменных.\n\n
		asize_t func_argsize;			///< количество байт, очищаемых из стека при возврате
		asize_t func_fpd;				///< frame pointer delta. (обычно 0, то есть realBP==typicalBP)
										///< используйте update_fpd() для его изменения.
		ulonglong func_flag{};			///< значение func_t::flags
		ea_t addr_call_out{};			///< вызывает что то 
		ea_t addr_call_get{};			///< вызывается откуда то 
		ea_t function_owner{};			///< \n Это атрибуты хвостового блока функции \n
										///< \n if (function_tailqty) проверка сначала \n 
										///< потом уже начинаем использовать это поле \n
										///< - адрес главной функции, обладающей этим хвостом \n\n
		uval_t function_frame{};		///< id netnode of frame структуры - see frame.hpp
		uval_t function_ordinal{};		///< ординал функции (принимать во внимание если только экспортируемая функция)
		ea_t *func_referers{};			///< \n Это атрибуты хвостового блока функции \n\n
										///< массив ссылающихся (адреса начала функции).\n
										///< используйте func_parent_iterator_t для доступа к ссылающимся.\n\n
		int func_refqty{};				///< \n Это атрибуты хвостового блока функции \n\n
										///< - количество ссылающихся \n\n
		ushort func_frregs{};			///< размер сохраняемых регистров во frame.
		bool function_tailqty{};		///< функция хвост ...
		bool before_entry_point{};		///< выполняется до точки входа pe файла ...
		bool function_internal{};		///< внутренняя функция 
		bool function_exported{};		///< экспортируемая функция (если истина - то есть и ординал)
		bool function_imported{};		///< импортируемая функция
		bool was_checked{};				///< была проверена binexport - служит для контроля, есть ли такая функция в данных БинЭкспорта

		/**
		* \brief Адрес целевой функции для thunk (алиаса).
		* \details Если текущая функция помечена как FUNC_THUNK, сюда записывается
		*          адрес «реальной» цели. Если определить не удалось — BADADDR.
		*/
		ea_t thunk_target = BADADDR;

		/**
		* \brief Человекочитаемое имя целевой функции thunk.
		* \details Для удобства отображения. Может быть пустой строкой, если имя нельзя получить.
		*/
		std::string thunk_target_name;

		/**
		* \brief Количество всех чанков функции (head + tails).
		* \details Значение 0 означает, что функция не распознана.
		*          Значение 1 означает, что хвостов нет (только головной чанк).
		*/
		uint32_t chunks_total = 0;

		/**
		* \brief Количество хвостовых чанков (без головы).
		* \details tails_count = (chunks_total > 0 ? chunks_total - 1 : 0).
		*/
		uint32_t tails_count = 0;

		/**
		* \brief Суммарный размер кода по всем чанкам, байт.
		* \details Считается как сумма r.size() для каждого range_t из CollectAllChunks(head).
		*          Храним как asize_t (тип из IDA SDK).
		*/
		asize_t chunks_code_size = 0;

		/**
		* \brief Демангленное (человекочитаемое) имя целевой функции thunk.
		* \details Сохраняем отдельно от исходного mangled-имени, чтобы при необходимости
		*          печатать оба варианта (сырой и демангленый).
		*          Может быть пустым, если деманглинг не удался или имя уже не требует его.
		*/
		std::string thunk_target_name_demangled;



	} pe_func;

	struct PeSegment
	{
		std::string name{};				///< имя сегмента
		std::string s_class{};			///< класс сегмента
		ea_t start_address{};			///< адрес начала включая
		ea_t end_address{};				///< адрес окончания исключая
	} pe_segment;

	/**
	* \brief Простая статистика по анализу функций/чанков.
	*
	* \details Используется для быстрого подсчёта:
	*  - общего числа обработанных чанков (включая head и tail),
	*  - количества уникальных head-функций,
	*  - количества tail-чанков,
	*  - количества thunk-функций (обёрток).
	*
	* \note Храним множество seen_heads, чтобы уникальные головы считались 1 раз
	*       даже если мы встречаем их несколько раз (например, при обходе чанков).
	*/
	struct Stats
	{
		uint64_t total_chunks = 0;            ///< Общее число обработанных чанков (head + tails)
		uint64_t unique_heads = 0;            ///< Количество уникальных head-функций
		uint64_t total_tails = 0;             ///< Число tail-чанков (включая дубли, если встретились)
		uint64_t total_thunks = 0;            ///< Число функций помеченных FUNC_THUNK

	  /**
	  * \brief Вспомогательное множество для отслеживания уже встреченных head'ов.
	  * \details Хранит start EA головы каждой уникальной head-функции. Это позволяет
	  *          отличать повторы и корректно считать unique_heads.
	  */
		std::unordered_set<ea_t> seen_heads;
	};


	// при добавлении новых структур - не забыть их инициализировать
	// в конструкторе exporter.cpp файла 
	Exporter();

	void AddLocalFuncAddress(const ea_t start_address, const ea_t end_address);
	void AddImportFuncAddress(const ea_t start_address, const std::string source);
	void AddFlagToField(const std::string& value);
	void ChangeFunctionFlags(const ea_t start_address, const ulonglong func_flag);
	std::string FlagsToString(const ulonglong func_flag);
	std::string CheckMangledName(const PeFunc& fd, const bool mangled) const;
	int GetFunctionIndex(const ea_t start_address) const;
	std::string GetFunctionType(const int pe_func_index) const;
	int  GetImportFuncCount() const;
	int  GetLocalFuncCount() const;
	void PrintLocalFuncMap() const;
	void PrintImportFuncMap() const;
	void PrintFunctionData() const;
	void PrintInformation() const;
	void SetFunctionFlags(const ulonglong func_flag);
	void SetFunctionType(const ea_t start_address);
	void SetFunctionTailes(const ea_t start_address);



	/**
	* \brief Сбросить статистику.
	* \details Устанавливает все счётчики в ноль и очищает множество seen_heads.
	*/
	void ResetStats();

	/**
	* \brief Зарегистрировать классификацию одного чанка/функции.
	* \param fc Результат ClassifyFunction(ea).
	* \details Метод инкрементирует соответствующие поля stats_ в зависимости
	*          от fc.kind. Если это head — добавляет head->start_ea в seen_heads
	*          и при новом вставлении увеличивает unique_heads.
	*/
	void RegisterFunctionClassify(const FuncClassify &fc);

	/**
	* \brief Вывести сводную статистику через msg().
	* \details Используется в конце прохода (или по требованию) для вывода аккуратного summary.
	*/
	void PrintStats() const;


	void ParseCMD(const std::string &cmd_command) const;
	void CommandPrintHelp() const;
	void CommandFunctionParse(std::vector<std::string> &command) const;
	void ParseCMDFunctionAbout(ea_t address) const;
	int FunctionInstructionCount(const ea_t start_address, const ea_t end_address) const;
	void FunctionCalls(const ea_t start_address, const ea_t end_address) const;
	void FunctionReference(const ea_t start_address, const ea_t end_address) const;
	void ParceFunctionFrame(ea_t start_address) const;
	void ParceFunctionFrameTwo(ea_t start_address) const;


	// https://stackoverflow.com/questions/14225932/search-for-a-struct-item-in-a-vector-by-member-data
	// https://www.geeksforgeeks.org/how-to-find-index-of-a-given-element-in-a-vector-in-cpp/
	bool SearchFunctionAddress(const ea_t addr) const;
	/**
	* \brief \n map с информацией об импортируемых функциях \n
	* - адрес начала функции
	* - имя функции
	*/
	std::map<ea_t, std::string> import_func_address;

	/**
	* \brief \n map с информацией об экспортируемых функциях \n
	* - адрес начала функции
	* - ординал функции
	*   \n\n
	*	если ord == addr - это или точка входа или TlsCallback \n
	*	если addr == inf_get_start_ea() - то это точка входа \n
	*	Например : \n
	*	Entry point found at: 6BFA7970 = TlsCallback_0 ord = 6BFA7970 \n
	*	Entry point found at: 6BFA7940 = TlsCallback_1 ord = 6BFA7940 \n
	*	Entry point found at: 6BF813D0 = DllEntryPoint ord = 6BF813D0 \n
	*/
	std::map<ea_t, uval_t> export_func_address;

	/**
	* \brief \n map с информацией о локальных функциях \n
	* - key -  адрес начала функции включая
	* - item - адрес окончания функции исключая
	*/
	std::map<ea_t, ea_t> local_func_address;

	/**
	* \brief \n вектор структур PeInstruction  \n
	* содержит структуры pe_instruction с данными по инструкциям функций программы ...
	*/
	std::vector<PeInstruction> vector_pe_instructions;

	/**
	* \brief \n map с информацией о локальных функциях \n
	* - key -  адрес начала функции
	* - item - индекс функции в порядке добавления в вектор vector<PeFunc> function_data,\n
	* начинается с 0 функции \n
	* сначала добавляются основные функции , потом идут функции импортированные \n\n
	* по ключу (стартовый адрес функции) получим индекс с данными о функции в векторе function_data \n
	*
	*/
	std::map<ea_t, size_t> function_index;

	/**
	* \brief \n map с информацией о локальных функциях \n
	* - key -  адрес начала функции
	* - item - имя функции (не размангленное)
	*/
	std::map<ea_t, std::string> function_naming;

	/**
	* \brief \n Вектор структур <PeFunc>, содержащих данные о функции \n
	* чтобы получить индекс функции в векторе по ее стартовому адресу \n
	* нужно обратиться к мапе function_index \n
	* где
	* - key -  адрес начала функции
	* - item - индекс функции \n
	* итого i = function_index[pe_func.address]
	* инициализируем вектор с небольшим запасом -
	* exporter.function_data.reserve(vector_need_size + 100) \n
	* в файле start_window.cpp
	*/
	std::vector<PeFunc> function_data;

	/**
	* \brief
	*/
	std::vector<PeSegment> segments_data;

	// [STACK] --- begin ---
	/**
	* \brief Статическая PE-информация о стеке процесса/потоков по умолчанию.
	* \details Значения берутся из OptionalHeader PE-файла (поля SizeOfStackReserve/Commit).
	*  - \b reserve: объём \e зарезервированного виртуального адресного пространства под стек главного
	*    потока (и потоков по умолчанию). Резервирование не потребляет RAM/подкачку, это верхний предел
	*    автодорастания стека. При достижении предела ОС выдаёт переполнение стека.
	*  - \b commit: объём \e изначально закоммиченной памяти стека при старте потока (обычно 1 страница = 4 KB).
	*    Ниже располагается guard-страница; при её касании ОС докоммичивает следующую страницу и сдвигает guard,
	*    тем самым стек растёт ступенчато до предела \c reserve.
	*
	* \note Для Windows/MSVC типичные значения по умолчанию — \c /STACK:1048576,4096 (reserve=1 MB, commit=4 KB).
	*       Для дополнительных потоков CreateThread/_beginthreadex: если \c dwStackSize==0, берутся те же дефолты,
	*       если \c dwStackSize>0 — это обычно начальный commit; флаг \c STACK_SIZE_PARAM_IS_A_RESERVATION трактует
	*       \c dwStackSize как reserve.
	*/
	struct PeImageInfo
	{
		/**
		* \brief OptionalHeader.SizeOfStackReserve, байт.
		* \details Максимальный размер стека (верхняя граница автодорастания).
		*  Резервирует адресное пространство, но не расходует физическую память,
		*  пока страницы не будут закоммичены по мере роста стека.
		*/
		uint64_t stack_reserve = 0;

		/**
		* \brief OptionalHeader.SizeOfStackCommit, байт.
		* \details Изначально обеспеченный (закоммиченный) объём стека при старте потока.
		*  Обычно равен размеру страницы (4 KB). Дальнейший рост идёт по страницам
		*  через механизм guard-страницы до значения \c stack_reserve.
		*/
		uint64_t stack_commit = 0;
	};


	/**
	* \brief Вернуть закэшированную PE-информацию о стеке.
	* \return Ссылка на структуру с полями reserve/commit (0, если не PE или не прочитали).
	*/
	const PeImageInfo& GetPeImageInfo() const { return pe_image_info_; }

	/**
	* \brief Перечитать статическую PE-информацию о стеке из заголовка файла.
	* \return true, если это PE и удалось извлечь поля; false иначе.
	*/
	bool RefreshPeImageInfo();
	// [STACK] --- end ---

	// [EFFECTS] --- begin ---
	/**
	* \brief Доступ/создание агрегатов по адресу функции.
	*/
	FunctionEffects& GetOrCreateFuncEffects(ea_t fva);

	/**
	* \brief Найти агрегаты по адресу функции; nullptr, если нет.
	*/
	const FunctionEffects* FindFuncEffects(ea_t fva) const;
	// [EFFECTS] --- end ---

	// [EFFECTS+DERIVED] --- begin ---
	/**
	* \brief Завершение расчётов по эффектам: заполнить производные поля для всех функций.
	* \details Вызывать после того, как собраны счётчики (в конце анализа или перед печатью).
	*/
	void FinalizeFunctionEffects();
	// [EFFECTS+DERIVED] --- end ---


	
private:

	Stats stats_; ///< Runtime statistics for functions/chunks/thunks
				  // [STACK] --- begin ---
	PeImageInfo pe_image_info_; ///< \brief Кэш статических полей стека из PE OptionalHeader.
								// [STACK] --- end ---
								// [EFFECTS] --- begin ---
	std::unordered_map<ea_t, FunctionEffects> func_effects_;
	// [EFFECTS] --- end ---


};

static Exporter exporter;
