#pragma once

#include "start_window.hpp"

// --- [ApiMonitorDoc] begin ---
#include "api_monitor.h"
#include "apimon_ida_apply.h"
#include <QtCore/QDir>
// --- [ApiMonitorDoc] end ---

// Определения для использования функций binexport начало
#include <base/logging.h>
#include "digest.h"
#include "flow_analysis.h"
#include "names.h"
#include "third_party/zynamics/binexport/binexport2_writer.h"
#include "third_party/zynamics/binexport/dump_writer.h"
#include "third_party/zynamics/binexport/dump_writer.h"
#include "third_party/zynamics/binexport/statistics_writer.h"
#include "third_party/zynamics/binexport/util/filesystem.h"
#include "third_party/zynamics/binexport/util/format.h"
#include "third_party/zynamics/binexport/util/timer.h"
#include "third_party/zynamics/binexport/writer.h"
#include "ui.h"
// Определения для использования функций binexport конец

#include <filesystem>
#include <name.hpp>
#include <entry.hpp>
#include "exporter.h"

#include <Psapi.h> // for print_memory_usage
#include <Windows.h> // for print_memory_usage
#include <QValidator> // для регулярки CMDLine
#include <QKeyEvent>
#include <boost/algorithm/string.hpp>

#include "pe_heders.h"
#include "debug_log.h"


#if (_MSC_VER == 1900)
namespace fs = std::experimental::filesystem;
#elif (_MSC_VER > 1920)
namespace fs = std::filesystem;
#endif


// Использовать ли эвристику, специфичную для X86, для определения функций,
// которые не имеют возврата (no return).
// Подробнее см. в разделе FlowGraph::FindBasicBlockBreaks().
bool noreturn_heuristic_ = false; // x86_noreturn_heuristic_



								  /// \brief \n Получает и выводит информацию о использовании приложением памяти \n
								  /// \return Количество используемой памяти в килобайтах
size_t print_memory_usage()
{
	TRACE_FN();
	size_t                  result = 0;
	PROCESS_MEMORY_COUNTERS info;
	GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
	result = info.WorkingSetSize;

	msg("\nmemory usage = %d kb\n", result / 1024); // в килобайках !!!
	return result;                                  // в байтах !!!
}


void ExportIdbAdditional(SB::DumpWriter* writer) // ИЗМЕНЕНО было SB::Writer* writer
{
	TRACE_FN();
	msg("\n    ***    \n%s : starting export\n", SB::GetModuleName().c_str());
	WaitBox     wait_box("Exporting database...");
	Timer<>     timer;
	qstring     name{};
	std::string naming{};
	std::string type_func{}; // тип функции  - локальная или экспортируемая ...
	auto        modules_size = exporter.modules_size;
	auto        vector_need_size = exporter.vector_need_size;

	const auto modules = SB::InitModuleMap(); // инициализируем чтобы получить размер

	modules_size = modules.size();
	exporter.modules_size = modules_size;

	auto func_chunk_size = get_fchunk_qty(); // получим размер - количество элементов ...

											 // теперь рассчитаем какого размера нам нужен вектор ,
											 // чтобы проинициализировать его добавлять в него элементы по индексу !!!
	vector_need_size = static_cast<size_t>(modules_size) + func_chunk_size;
	exporter.vector_need_size = vector_need_size;

	// инициализируем вектор с небольшим запасом .
	exporter.function_data.reserve(vector_need_size + 100);


	// [STACK] --- begin ---
	// \brief \n Однократно разбираем PE-файл с диска, чтобы заполнить pe_image_optional_header. \n
	(void)AddDataPEHeaders();

	// синхронизируем кэш Exporter с уже разобранными полями OptionalHeader
	exporter.RefreshPeImageInfo();

	// [STACK] --- end ---


	// [PATCH] Перед началом прохода по функциям — сбрасываем статистику.
	exporter.ResetStats();

	// объявим index для сохранения позиций в векторе для вставки импортируемых функций
	// чтобы его использовать при добавлении импортированных функции по индексу в function_data .
	size_t index{};

	// получим список экспортируемых функций , по определяемым IDA экспортированными функциями
	// так же являются :
	// в dll файле -  TlsCallback и точка входа DllEntryPoint,
	// для exe файла - точка входа называется -> start .
	{
		for (auto e = 0; e < get_entry_qty(); e++)
		{
			auto ord = get_entry_ordinal(e);
			auto addr = get_entry(ord);

			// добавим экспортируемые функции в мапу
			exporter.export_func_address[addr] = ord;
		}
	}


	EntryPoints entry_points;
	{
		msg("\n");

		EntryPointManager entry_point_adder(&entry_points, "function chunks");

		// теперь бежим по всем функциям что есть в файле ...
		for (size_t i = 0; i < func_chunk_size; ++i)
		{
			if (const func_t* ida_func = getn_fchunk(i))
			{
				// [PATCH] Классифицируем адрес чанка: это может быть head, tail-chunk или thunk.
				const FuncClassify fc = ClassifyFunction(ida_func->start_ea);

				// [if] Если IDA не распознала функцию — пропускаем элемент.
				if (!fc.this_chunk)
				{
					msg("    [SKIP] no function at %llx\n", ida_func->start_ea);
					continue;
				}

				// [PATCH] Регистрируем классификацию для runtime-статистики (heads/tails/thunks).
				exporter.RegisterFunctionClassify(fc);

				// [else] Берём владельца (head). Для tail-chunk у хвоста нет своего фрейма,
				// поэтому все дальнейшие операции (фрейм, разбор) выполняем по head.
				const func_t* head = fc.head ? fc.head : ida_func;

				entry_point_adder.Add(
					ida_func->start_ea,
					(ida_func->flags & FUNC_TAIL)
					? EntryPoint::Source::FUNCTION_CHUNK
					: EntryPoint::Source::FUNCTION_PROLOGUE);

				msg("    func %llx \n", ida_func->start_ea);

				exporter.ParceFunctionFrame(head->start_ea);
				exporter.ParceFunctionFrameTwo(head->start_ea);

				auto func_start_ea = ida_func->start_ea;

				exporter.AddLocalFuncAddress(func_start_ea, ida_func->end_ea);

				get_ea_name(&name, func_start_ea);
				naming = static_cast<std::string>(name.c_str());

				exporter.function_index[func_start_ea] = i;
				exporter.function_naming[func_start_ea] = naming;

				exporter.pe_func.address = func_start_ea;
				exporter.pe_func.name = naming;

				exporter.pe_func.dem_name = naming;

				exporter.SetFunctionFlags(ida_func->flags);

				exporter.SetFunctionType(func_start_ea);

				auto tq = ida_func->tailqty;
				if (tq)
				{
					exporter.pe_func.function_tailqty = true;
					exporter.SetFunctionTailes(func_start_ea);
					exporter.pe_func.function_owner = ida_func->owner;

					func_t* func = getn_fchunk(static_cast<size_t>(ida_func->owner));
					if (func != nullptr)
					{
						auto owner_addr = func->start_ea;
						msg("    Function %llx is TAIL from %llx function \n", func_start_ea, owner_addr);
					}
				}

				exporter.pe_func.func_refqty = ida_func->refqty;
				exporter.pe_func.func_referers = ida_func->referers;

				exporter.pe_func.function_frame = ida_func->frame;

				exporter.pe_func.func_frregs = ida_func->frregs;

				exporter.pe_func.func_frsize = ida_func->frsize;

				exporter.function_data.insert(exporter.function_data.begin() + i, exporter.pe_func);

				exporter.pe_func = {};
			}
			index = i + 1;
		}
	}
	name = "";


	{
		EntryPointManager entry_point_adder(&entry_points, "calls");

		for (const auto& module : modules)
		{
			const auto address = module.first;
			get_ea_name(&name, address);
			naming = static_cast<std::string>(name.c_str());

			entry_point_adder.Add(address, EntryPoint::Source::CALL_TARGET);

			exporter.AddImportFuncAddress(address, naming);

			exporter.function_index[address] = index;
			exporter.function_naming[address] = naming;

			exporter.pe_func.address = address;
			exporter.pe_func.name = naming;
			exporter.pe_func.function_imported = true;
			exporter.function_data.insert(exporter.function_data.begin() + index, exporter.pe_func);

			index++;
		}
	}


	Instructions instructions;
	FlowGraph    flow_graph;
	CallGraph    call_graph;

	AnalyzeFlowIdaAdditional(&entry_points, modules, writer, &instructions, &flow_graph,
		&call_graph,
		noreturn_heuristic_
		? FlowGraph::NoReturnHeuristic::kNopsAfterCall
		: FlowGraph::NoReturnHeuristic::kNone,
		&exporter);

	exporter.flow_graph_func_count = flow_graph.GetFunctions().size();
	msg("%s : exported %d  functions with %d  instructions in %s \n",
		SB::GetModuleName().c_str(),
		exporter.flow_graph_func_count,
		instructions.size(),
		SB::HumanReadableDuration(timer.elapsed()).c_str());

	exporter.FinalizeFunctionEffects();
	exporter.PrintInformation();
}



/// \brief \n Начинаем чтение данных из ida DB открытого PE файла ...\n
/// \return eOk
int StartWindow::ReadIdaDB()
{
	TRACE_FN();
	auto memory_start = print_memory_usage();

	std::string fname = "\\dumptxt.log";
	std::string temporary_file = getenv("TEMP") + fname;

#ifdef _DEBUG
	const char* filename = "debug.txt";
#else
	const char* filename = temporary_file.c_str();  // C:\Temp\dumptxt.log
#endif

	try
	{
		std::ofstream  file(filename);
		SB::DumpWriter writer{ file };
		ExportIdbAdditional(&writer);
	}
	catch (const std::exception& error)
	{
		LOG(INFO) << "    Error exporting: " << error.what();
		warning("    Error exporting: %s\n", error.what());
		return 666;
	}

	auto memory_finish = print_memory_usage();
	auto memory_usage = (memory_finish - memory_start) / 1024;
	msg("\nAmount memory used to store data = %d kb  =  %d mb\n", memory_usage, memory_usage / 1024);

	return eOk;
}


// --- [ApiMonitorDoc] begin ---
/// \brief Внутренний вызов: применить комменты к импортам по уже загруженному db.
void StartWindow::ApplyApiMonComments_Imports(const apimon::DataBinDb& db)
{
	apimon_ida::ApplyStats st;
	apimon_ida::ApplyApiMonCommentsToImports(db, &st, /*overwriteExisting=*/false);

	msg("[ApiMon] UI: imports done. matched=%d, added=%d, skippedExisting=%d\n",
		st.matched, st.commentsAdded, st.skippedExisting);
}

/// \brief Внутренний вызов: применить комменты к экспортам (entry points) по уже загруженному db.
void StartWindow::ApplyApiMonComments_Exports(const apimon::DataBinDb& db)
{
	apimon_ida::ApplyStats st;
	apimon_ida::ApplyApiMonCommentsToExports(db, &st, /*overwriteExisting=*/false);

	msg("[ApiMon] UI: exports done. matched=%d, added=%d, skippedExisting=%d\n",
		st.matched, st.commentsAdded, st.skippedExisting);
}

/// \brief Внутренний вызов: применить комменты к call-сайтам на импорты по уже загруженному db.
void StartWindow::ApplyApiMonComments_ImportCalls(const apimon::DataBinDb& db)
{
	apimon_ida::ApplyStats st;
	apimon_ida::ApplyApiMonCommentsToImportCalls(db, &st, /*overwriteExisting=*/false);

	msg("[ApiMon] UI: calls done. matched=%d, added=%d, skippedExisting=%d\n",
		st.matched, st.commentsAdded, st.skippedExisting);
}

/// \brief Загрузить apimon_data.bin и применить комменты к импортам.
void StartWindow::ApplyApiMonComments_Imports_FromLoadedDb()
{
	apimon::Settings s;

	// Папка плагинов (где лежит apimon_data.bin / apimon_cache.bin)
	QString pluginDir = static_cast<QString>(PLUGIN_CURRENT_DIRECTORY.c_str());
	s.idaPluginsDir = pluginDir;

	// XML путь (на будущее; для применения imports он не обязателен, но Settings пусть будет заполнен)
	const std::string API_MONITOR_FOLDER = "\\ApiMonitorDoc";
	QString apiFolder = static_cast<QString>(API_MONITOR_FOLDER.c_str());
	s.apiMonitorRootDir = pluginDir + apiFolder;

	// Логи/статистика
	s.outputDir = "D:/Documents/Visual Studio 2015/Projects/IdaPlugin - VS2015/ApiMonitorDoc/NewParsing";

	apimon::DataBinDb db;
	if (!apimon::ReadDataBin(s, db))
	{
		msg("[ApiMon] UI: ReadDataBin FAILED (apimon_data.bin not found?)\n");
		return;
	}

	msg("[ApiMon] UI: data loaded. types=%d, apis=%d, sha=%s\n",
		(int)db.types.size(),
		(int)db.apis.size(),
		db.combinedSha1Hex.toUtf8().constData());

	ApplyApiMonComments_Imports(db);
}

/// \brief Загрузить apimon_data.bin и применить всё (imports/exports/calls).
void StartWindow::ApplyApiMonComments_All_FromLoadedDb()
{
	apimon::Settings s;

	// Папка плагинов (где лежит apimon_data.bin / apimon_cache.bin)
	QString pluginDir = static_cast<QString>(PLUGIN_CURRENT_DIRECTORY.c_str());
	s.idaPluginsDir = pluginDir;

	// XML путь (на будущее; для применения не обязателен, но Settings пусть будет заполнен)
	const std::string API_MONITOR_FOLDER = "\\ApiMonitorDoc";
	QString apiFolder = static_cast<QString>(API_MONITOR_FOLDER.c_str());
	s.apiMonitorRootDir = pluginDir + apiFolder;

	// Логи/статистика
	s.outputDir = "D:/Documents/Visual Studio 2015/Projects/IdaPlugin - VS2015/ApiMonitorDoc/NewParsing";

	apimon::DataBinDb db;
	if (!apimon::ReadDataBin(s, db))
	{
		msg("[ApiMon] UI: ReadDataBin FAILED (apimon_data.bin not found?)\n");
		return;
	}

	msg("[ApiMon] UI: data loaded. types=%d, apis=%d, sha=%s\n",
		(int)db.types.size(),
		(int)db.apis.size(),
		db.combinedSha1Hex.toUtf8().constData());

	ApplyApiMonComments_Imports(db);
	ApplyApiMonComments_Exports(db);
	// ApplyApiMonComments_ImportCalls(db); // <-- отключили call-сайты (иначе может подвисать)
}

/// \brief Slot-заглушка (может не использоваться).
void StartWindow::OnApplyApiMonImports()
{
	ApplyApiMonComments_All_FromLoadedDb();
}
// --- [ApiMonitorDoc] end ---


StartWindow::StartWindow(QWidget* parent)
	: QWidget(parent)
{
	TRACE_FN();
	ui.setupUi(this);

	connect(ui.setting_button, SIGNAL(clicked()), SLOT(setting_form_show()));
	connect(ui.notepad_button, SIGNAL(clicked()), SLOT(notepad_form_show()));
	connect(ui.binexport_button, SIGNAL(clicked()), SLOT(binexport_form_show()));


	// секция для регулярки lineEdit_CMDLine начало http://blog.kislenko.net/show.php?id=1692#8530
	const QRegExp RegExp("^[a-zA-Z0-9 (\s)]+$");
	QValidator*   Validator = new QRegExpValidator(RegExp, this);
	// секция для регулярки lineEdit_CMDLine конец


	KeyPressCMDLine* keyPressCMDLine = new KeyPressCMDLine(this);
	connect(keyPressCMDLine, SIGNAL(press_enter()), SLOT(PressEnter()));


	ui.lineEdit_CMDLine->setValidator(Validator);
	ui.lineEdit_CMDLine->installEventFilter(keyPressCMDLine);


	if (mdbg) // в режиме отладки ввод символов в поле CMD вызывает падение IDA ...
	{
		ui.lineEdit_CMDLine->setEnabled(false);
	}

	// секция для регулярки lineEdit_CMDLine конец
	ReadIdaDB(); // выполняем при открытии формы ...

				 // --- [ApiMonitorDoc] begin ---
	msg("[ApiMon] UI: Apply comments (Imports/Exports/Calls)...\n");
	ApplyApiMonComments_All_FromLoadedDb();
	// --- [ApiMonitorDoc] end ---
}

void ClearDataConteiners()
{
	TRACE_FN();
	exporter.pe_func = {};
	exporter.pe_instruction = {};
	exporter.pe_segment = {};

	exporter.import_func_address.clear();
	exporter.export_func_address.clear();
	exporter.local_func_address.clear();
	exporter.vector_pe_instructions.clear();
	exporter.function_index.clear();
	exporter.function_naming.clear();
	exporter.function_data.clear();
	exporter.segments_data.clear();
}

StartWindow::~StartWindow()
{
	if (notepad_form.isVisible()) { notepad_form.close(); } // иначе будет сохранять даже если окно закрыто
	ClearDataConteiners();

	if (Settings::getPrintInfoEnabled())
	{
		msg("\n");
		msg("\nvector Function_Data       will be clear, now its size = %d ", exporter.function_data.size());
		msg("\nmap    import_func_address will be clear, now its size = %d ", exporter.import_func_address.size());
		msg("\nmap    export_func_address will be clear, now its size = %d ", exporter.export_func_address.size());
		msg("\nmap    local_func_address  will be clear, now its size = %d ", exporter.local_func_address.size());
		msg("\nvector vector_pe_addr      will be clear, now its size = %d ", exporter.vector_pe_instructions.size());
		msg("\nmap    function_index      will be clear, now its size = %d ", exporter.function_index.size());
		msg("\nmap    function_naming     will be clear, now its size = %d ", exporter.function_naming.size());
		msg("\nvector segments_data       will be clear, now its size = %d ", exporter.segments_data.size());
		msg("\n\n\n");
	}
}

void StartWindow::notepad_form_show()
{
	TRACE_FN();
	notepad_form.show();
}

void StartWindow::binexport_form_show()
{
	TRACE_FN();
	binexport_form.show();
}

void StartWindow::PressEnter()
{
	TRACE_FN();
	auto cmd_command = ui.lineEdit_CMDLine->text().toStdString();
	boost::trim(cmd_command);

	if (!cmd_command.empty())
	{
		ui.lineEdit_CMDLine->clear();
		exporter.ParseCMD(cmd_command);
	}
}

void StartWindow::setting_form_show()
{
	TRACE_FN();
	setting_form.show();
}