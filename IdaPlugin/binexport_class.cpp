#include "binexport_class.hpp"

// Определения для использования функций binexport начало
#include <base/logging.h>
#include "digest.h"
#include "flow_analysis.h"
#include "names.h"
#include "third_party/zynamics/binexport/binexport2_writer.h"
#include "third_party/zynamics/binexport/dump_writer.h"
#include "third_party/zynamics/binexport/statistics_writer.h"
#include "third_party/zynamics/binexport/util/filesystem.h"
#include "third_party/zynamics/binexport/util/format.h"
#include "third_party/zynamics/binexport/util/timer.h"
#include "third_party/zynamics/binexport/writer.h"
#include "ui.h"
// Определения для использования функций binexport конец


// Использовать ли эвристику, специфичную для X86, для определения функций,
// которые не имеют возврата (no return).
// Подробнее см. в разделе FlowGraph::FindBasicBlockBreaks().
bool x86_noreturn_heuristic_ = false;


void ExportIdb(SB::Writer* writer) {
	_RPT1(0, "FuncName ExportIdb\n", "");
	msg("\n    ***    \n%s : starting export\n", SB::GetModuleName().c_str());
	WaitBox wait_box("Exporting database...");
	Timer<> timer;
	EntryPoints entry_points;
	{
		EntryPointManager entry_point_adder(&entry_points, "function chunks");
		for (size_t i = 0; i < get_fchunk_qty(); ++i) {
			if (const func_t* ida_func = getn_fchunk(i)) {
				entry_point_adder.Add(ida_func->start_ea,
					(ida_func->flags & FUNC_TAIL)
					? EntryPoint::Source::FUNCTION_CHUNK
					: EntryPoint::Source::FUNCTION_PROLOGUE);
			}
		}
	}

	// Добавьте импортированные функции (чтобы мы не пропустили импортированные, но на которые нет ссылок).
	const auto modules = SB::InitModuleMap();
	{
		EntryPointManager entry_point_adder(&entry_points, "calls");
		for (const auto& module : modules) {
			entry_point_adder.Add(module.first, EntryPoint::Source::CALL_TARGET);
		}
	}



	// контеинеры и классы для хранения данных начало **********************
	_RPT1(0, "\tInstructions\n", "");
	Instructions instructions;
	_RPT1(0, "\tFlowGraph\n", "");
	FlowGraph flow_graph;
	_RPT1(0, "\tCallGraph\n", "");
	CallGraph call_graph;
	// контеинеры и классы для хранения данных конец **********************



	// начинаем анализ !!!
	_RPT1(0, "\tAnalyzeFlowIda START\n", "");
	AnalyzeFlowIda(&entry_points, modules, writer, &instructions, &flow_graph,
		&call_graph,
		x86_noreturn_heuristic_
		? FlowGraph::NoReturnHeuristic::kNopsAfterCall
		: FlowGraph::NoReturnHeuristic::kNone);
	_RPT1(0, "\tAnalyzeFlowIda FINISH\n", "");
	//BM->	закончили анализ !!!
	// закончили анализ !!!
	msg("%s : exported %d  functions with %d  instructions in %s \n",
		SB::GetModuleName().c_str(),
		flow_graph.GetFunctions().size(),
		instructions.size(),
		SB::HumanReadableDuration(timer.elapsed()).c_str());
	//LOG(INFO) << absl::StrCat(
	//	SB::GetModuleName(), ": exported ", flow_graph.GetFunctions().size(),
	//	" functions with ", instructions.size(), " instructions in ",
	//	SB::HumanReadableDuration(timer.elapsed()));
}

int ExportBinary(const std::string& filename) {
	_RPT1(0, "FuncName ExportBinary \n", "");
	try {
		const std::string hash =
			SB::GetInputFileSha256().value_or(SB::GetInputFileMd5().value_or(""));
		SB::BinExport2Writer writer(filename, SB::GetModuleName(), hash,
			SB::GetArchitectureName().value());
		ExportIdb(&writer);
	}
	catch (const std::exception& error) {
		LOG(INFO) << "Error exporting: " << error.what();
		warning("Error exporting: %s\n", error.what());
		return 666;
	}
	catch (...) {
		LOG(INFO) << "Error exporting.";
		warning("Error exporting.\n");
		return 666;
	}
	return eOk;
}

int ExportText(const std::string& filename) {
	_RPT1(0, "FuncName ExportText \n", "");
	try {
		std::ofstream file(filename);
		SB::DumpWriter writer{ file };
		ExportIdb(&writer);
	}
	catch (const std::exception& error) {
		LOG(INFO) << "Error exporting: " << error.what();
		warning("Error exporting: %s\n", error.what());
		return 666;
	}
	catch (...) {
		LOG(INFO) << "Error exporting.";
		warning("Error exporting.\n");
		return 666;
	}
	return eOk;
}

int ExportStatistics(const std::string& filename) {
	_RPT1(0, "FuncName ExportStatistics \n", "");
	try {
		std::ofstream file(filename);
		SB::StatisticsWriter writer{ file };
		ExportIdb(&writer);
	}
	catch (const std::exception& error) {
		LOG(INFO) << "Error exporting: " << error.what();
		warning("Error exporting: %s\n", error.what());
		return 666;
	}
	catch (...) {
		LOG(INFO) << "Error exporting.";
		warning("Error exporting.\n");
		return 666;
	}
	return eOk;
}

BinExportClass::BinExportClass(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
}

BinExportClass::~BinExportClass() = default;


void BinExportClass::binary_export()
{
	// BM ->	Информация о  _RPT макросах
	// https://stackoverflow.com/questions/3179199
	// https://learn.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-6.0/aa298568(v=vs.60)?redirectedfrom=MSDN
	// https://www.cprogramming.com/tutorial/visual_studio_trace_log_messages.html
	_RPT1(0, "binary_export\n", "");
	const std::string extension = ".BinExport";       // расширение файла
	const std::string name = ReplaceFileExtension(
		security::binexport::GetModuleName(),
		extension);

	const char* filename = ask_file(
		/*for_saving=*/true, name.c_str(), "%s",
		"FILTER BinExport v2 files|*.BinExport\nExport to BinExport v2");
	if (!filename) {
		return;
	}

	if (FileExists(filename) &&
		ask_yn(0, "'%s' already exists - overwrite?", filename) != 1) {
		return;
	}
	msg("\n    ***    Export Binary\n");
	ExportBinary(filename);
	this->close();
	msg("\n    ***    \n");
}


void BinExportClass::text_export()
{
	_RPT1(0, "text_export\n", "");
	const std::string extension = ".txt";       // расширение файла
	const std::string name = ReplaceFileExtension(
		security::binexport::GetModuleName(),
		extension);
	/**
	 * \brief \n имя текстового файла в который сохраняются данные в текстовом виде ...
	 * 
	 */
	const char* filename = ask_file(
		/*for_saving=*/true, name.c_str(), "%s",
		"FILTER Text files|*.txt\nExport to Text");
	if (!filename) {
		return;
	}

	if (FileExists(filename) &&
		ask_yn(0, "'%s' already exists - overwrite?", filename) != 1) {
		return;
	}
	msg("\n    ***    Export Text\n");
	ExportText(filename);
	this->close();
	msg("\n    ***    \n");
}


void BinExportClass::statistic_export()
{
	_RPT1(0, "statistic_export\n", "");
	// new_extension = ".statistics";
	const std::string extension = ".statistics";       // расширение файла
	const std::string name = ReplaceFileExtension(
		security::binexport::GetModuleName(),
		extension);

	const char* filename = ask_file(
		/*for_saving=*/true, name.c_str(), "%s",
		"FILTER BinExport Statistics|*.statistics\nExport Statistics");
	if (!filename) {
		return;
	}

	if (FileExists(filename) &&
		ask_yn(0, "'%s' already exists - overwrite?", filename) != 1) {
		return;
	}

	msg("\n    ***    Export Statistics\n");
	ExportStatistics(filename);
	this->close();
	msg("\n    ***    \n");
}
