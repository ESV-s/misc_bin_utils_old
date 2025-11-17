// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "flow_analysis.h"

// clang-format off
#include "begin_idasdk.inc"  // NOLINT
#include <idp.hpp>                                              // NOLINT
#include <allins.hpp>                                           // NOLINT
#include <enum.hpp>                                             // NOLINT
#include <frame.hpp>                                            // NOLINT
#include <ida.hpp>                                              // NOLINT
#include <lines.hpp>                                            // NOLINT
#include <name.hpp>                                             // NOLINT
#include <segment.hpp>                                          // NOLINT
#include <struct.hpp>                                           // NOLINT
#include <typeinf.hpp>                                          // NOLINT
#include <ua.hpp>                                               // NOLINT
// переменные для получения данных в вектора начало
#include "start_window.hpp"
// переменные для получения данных в вектора конец
#include "end_idasdk.inc"    // NOLINT
// clang-format on

#include "base/logging.h"
#include "third_party/absl/strings/str_cat.h"
#include "third_party/zynamics/binexport/flow_analysis.h"
#include "arm.h"
#include "dalvik.h"
#include "generic.h"
#include "metapc.h"
#include "mips.h"
#include "names.h"
#include "ppc.h"
#include "types_container.h"
#include "util.h"
#include "third_party/zynamics/binexport/util/format.h"
#include "third_party/zynamics/binexport/util/timer.h"
#include "third_party/zynamics/binexport/x86_nop.h"
#include "third_party/zynamics/binexport/dump_writer.h"

#include "exporter.h"

#include <xref.hpp>     // get_first_fcref_from()
#include <name.hpp>     // get_name(), demangle_name()
#include "function_utils.h" // ResolveThunkTarget(...) — у тебя уже есть
#include <cstring>      // strstr

#include <unordered_map>   // окно на функцию

#include <bytes.hpp>     // get_strlit_contents / get_max_strlit_length / del_items / do_data_ex
#include <name.hpp>      // set_name / get_name
#include <typeinf.hpp>   // tinfo_t / set_tinfo
#include <netnode.hpp>   // BADNODE
#include <ctype.h>       // isalnum
#include <ida/begin_idasdk.inc>

#include <string.h>   // strcmp
#include <cstring> // вверху файла

#include "debug_log.h"


namespace security::binexport {

	ModuleMap InitModuleMap() {
		TRACE_FN();

		ModuleMap modules;

		struct ImportData {
			std::string module_name;
			ModuleMap* modules;
		};
		for (uint i = 0; i < get_import_module_qty(); ++i) {
			qstring ida_module_name;
			if (!get_import_module_name(&ida_module_name, i)) {
				continue;
			}
			ImportData callback_capture = { ToString(ida_module_name), &modules };
			enum_import_names(
				i,
				static_cast<import_enum_cb_t*>([](ea_t ea, const char* /* name */,
					uval_t /* ord */,
					void* param) -> int {
				auto& import_data = *static_cast<ImportData*>(param);
				(*import_data.modules)[ea] = import_data.module_name;
				_RPT1(0, "import_data.module_name = %s \n", import_data.module_name.c_str());
				return 1;  // Continue enumeration
			}),
				static_cast<void*>(&callback_capture));
		}
		return modules;
	}

	std::string GetModuleName(Address address, const ModuleMap& modules) {

		TRACE_FN();
		
		const auto it = modules.find(address);
		if (it != modules.end()) {
			return it->second;
		}
		return "";
	}

	bool IsCode(Address address) {
		const uchar segment = segtype(address);
		return is_code(get_full_flags(address)) &&
			(segment == SEG_CODE || segment == SEG_NORM ||
				// Some processor modules label code segments with SEG_DATA.
			((get_ph()->id == PLFM_DALVIK || get_ph()->id == PLFM_M32R) &&
				segment == SEG_DATA));
	}

	/**
	 * \brief \n Мы разрешаем функции, о которых IDA не знает, но только в сегментах кода.\n
	 * \param address Address address
	 * \param modules ModuleMap& modules
	 * \return bool
	 * \n\n
	 */
	bool IsPossibleFunction(Address address, const ModuleMap& modules) {
		return IsCode(address) || get_func(address) != 0 ||
			modules.find(address) != modules.end();
	}

	/**
	 * \brief \n Возвращает, является ли указанная инструкция безусловным переходом.\n
	 * Переход является безусловным, если существует ровно одна ссылка\n (либо на код, либо на данные (для импортируемых функций)).\n
	 *  В частности, заметим, что может не быть потоковой ссылки на следующую инструкцию.\n
	 * \param instruction insn_t& instruction
	 * \return true/false
	 * \n\n
	 */
	bool IsUnconditionalJump(const insn_t& instruction) {
		if (is_indirect_jump_insn(instruction) && GetArchitecture() == kX86) {
			return true;
		}
		if (GetArchitecture() == kMips &&
			(instruction.itype == MIPS_b || instruction.itype == MIPS_bal ||
				instruction.itype == MIPS_jalr || instruction.itype == MIPS_j ||
				instruction.itype == MIPS_jr || instruction.itype == MIPS_jal ||
				instruction.itype == MIPS_jalx)) {
			return true;
		}

		size_t count = 0;
		xrefblk_t referencesOut;
		for (bool ok = referencesOut.first_from(instruction.ea, XREF_ALL); ok;
			ok = referencesOut.next_from(), ++count) {
			if (referencesOut.iscode && referencesOut.type != fl_JF &&
				referencesOut.type != fl_JN) {
				// мы имеем кодовую ссылку, которая не является ни коротким, ни длинным прыжком
				return false;
			}
		}
		return count == 1;
	}

	void AnalyzeFlow(const insn_t& ida_instruction, Instruction* instruction,
		FlowGraph* flow_graph, CallGraph* call_graph,
		AddressReferences* address_references,
		EntryPointManager* entry_point_adder,
		const ModuleMap& modules) {

		TRACE_FN();
		
		const bool unconditional_jump = IsUnconditionalJump(ida_instruction);
		int num_out_edges = 0;
		xrefblk_t xref;
		for (bool ok = xref.first_from(ida_instruction.ea, XREF_ALL);
			ok && xref.iscode; ok = xref.next_from()) {
			if (xref.type == fl_JN || xref.type == fl_JF) {
				++num_out_edges;
			}
			else if (unconditional_jump && xref.type == fl_F) {
				// Специальный случай для странного поведения IDA: У нас был оператор перехода switch
				// (jmp[eax*4]) в flash11c.idb, который имел одно безусловное исходящее ребро ("правильно") 
				// и второе кодовое ребро ("неправильно! Безусловный переход никогда не должен иметь регулярного кодового ребра").
				// Это обходной путь для данной ситуации.
				++num_out_edges;
			}
		}

		bool handled = false;
		if (num_out_edges > 1) {  // Таблица переходов Switch
			ea_t table_address = std::numeric_limits<ea_t>::max();
			for (bool ok = xref.first_from(ida_instruction.ea, XREF_ALL);
				ok && xref.iscode; ok = xref.next_from()) {
				flow_graph->AddEdge(FlowGraphEdge(ida_instruction.ea, xref.to,
					FlowGraphEdge::TYPE_SWITCH));
				address_references->emplace_back(
					ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
					xref.to, TYPE_SWITCH);
				entry_point_adder->Add(xref.to, EntryPoint::Source::JUMP_TABLE);
				table_address = std::min(table_address, xref.to);
				handled = true;
			}
			// Добавить ссылку на данные по первому адресу в таблице switch
			address_references->emplace_back(
				ida_instruction.ea, GetSourceExpressionId(*instruction, table_address),
				table_address, TYPE_DATA);
		}
		else {  // Normal xref
			for (bool ok = xref.first_from(ida_instruction.ea, XREF_ALL);
				ok && xref.iscode; ok = xref.next_from()) {
				// Регулярный поток кода (Regular code flow)
				if (xref.type == fl_F || instruction->GetNextInstruction() == xref.to) {
					// We need the || above because IDA gives me xref type unknown for old idbs.
					// Нам нужно || выше, потому что IDA выдает мне xref type unknown для старых idbs.
					if (instruction->GetNextInstruction() != xref.to) {
						LOG(INFO) << absl::StrCat(
							"warning: ", FormatAddress(instruction->GetAddress()),
							" flow xref target != address + instruction size (or "
							"instruction is missing flow flag). Disassembly is "
							"likely erroneous.");
					}
					entry_point_adder->Add(xref.to, EntryPoint::Source::CODE_FLOW);
				}
				else if (xref.type == fl_CN || xref.type == fl_CF) {
					// Call targets
					if (IsPossibleFunction(xref.to, modules)) {
						call_graph->AddFunction(xref.to);
						call_graph->AddEdge(ida_instruction.ea, xref.to);
						entry_point_adder->Add(xref.to, EntryPoint::Source::CALL_TARGET);
					}
					instruction->SetFlag(FLAG_CALL, true);
					address_references->emplace_back(
						ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
						xref.to, TYPE_CALL_DIRECT);
					handled = true;
				}
				else if (xref.type == fl_JN || xref.type == fl_JF) {
					// Jump targets
					if (IsPossibleFunction(xref.to, modules) && xref.type == fl_JF) {
						call_graph->AddEdge(ida_instruction.ea, xref.to);
					}
					// MIPS adds an extra instruction _after_ the jump that'll always be executed.
					// MIPS добавляет дополнительную инструкцию _после_ jump'а, которая всегда будет выполнена.
					// Thus we need to branch from that for flow graph reconstruction to work...
					// Таким образом, для того чтобы реконструкция потокового графа работала, нам необходимо от него ответвиться...
					const Address source_address = GetArchitecture() == kMips
						? instruction->GetNextInstruction()
						: ida_instruction.ea;
					if (unconditional_jump) {
						flow_graph->AddEdge(FlowGraphEdge(source_address, xref.to,
							FlowGraphEdge::TYPE_UNCONDITIONAL));
						address_references->emplace_back(
							ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
							xref.to, TYPE_UNCONDITIONAL);
						handled = true;
					}
					else {
						Address next_address = instruction->GetNextInstruction();
						if (GetArchitecture() == kMips) {
							// TODO(cblichman): Since this is MIPS, replace below with a constant.
							// Look ahead one instruction.
							insn_t next_instruction;
							decode_insn(&next_instruction, next_address);
							next_address += next_instruction.size;
						}

						flow_graph->AddEdge(FlowGraphEdge(source_address, next_address,
							FlowGraphEdge::TYPE_FALSE));
						flow_graph->AddEdge(
							FlowGraphEdge(source_address, xref.to, FlowGraphEdge::TYPE_TRUE));
						address_references->emplace_back(
							ida_instruction.ea,
							GetSourceExpressionId(*instruction, next_address), next_address,
							TYPE_FALSE);
						address_references->emplace_back(
							ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
							xref.to, TYPE_TRUE);
						handled = true;
					}
					entry_point_adder->Add(xref.to, EntryPoint::Source::JUMP_DIRECT);
				}
				else {
					LOG(INFO) << absl::StrCat("unknown xref ",
						FormatAddress(ida_instruction.ea));
				}
			}
		}

		if (!handled) {
			if (is_call_insn(ida_instruction)) {
				// Call to imported function or call [offset+eax*4]
				// Вызов импортируемой функции или вызов [offset+eax*4]
				for (bool ok = xref.first_from(ida_instruction.ea, XREF_DATA); ok;
					ok = xref.next_from()) {
					if (IsPossibleFunction(xref.to, modules)) {
						call_graph->AddFunction(xref.to);
						call_graph->AddEdge(ida_instruction.ea, xref.to);
						entry_point_adder->Add(xref.to, EntryPoint::Source::CALL_TARGET);
					}
					instruction->SetFlag(FLAG_CALL, true);
					address_references->emplace_back(
						ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
						xref.to, TYPE_CALL_INDIRECT);
				}
			}
			else {  // Assume data reference as in "push aValue"
				// Предполагать ссылку на данные, как в "push aValue"
				for (bool ok = xref.first_from(ida_instruction.ea, XREF_DATA); ok;
					ok = xref.next_from()) {
					if (!GetStringReference(ida_instruction.ea).empty()) {
						address_references->emplace_back(
							ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
							xref.to, TYPE_DATA_STRING);
					}
					else {
						address_references->emplace_back(
							ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
							xref.to, TYPE_DATA);
					}
				}
			}
		}
	}

	void AnalyzeFlowAdditional(const insn_t& ida_instruction, Instruction* instruction,
		FlowGraph* flow_graph, CallGraph* call_graph,
		AddressReferences* address_references,
		EntryPointManager* entry_point_adder,
		const ModuleMap& modules) {

		TRACE_FN();
		
		const bool unconditional_jump = IsUnconditionalJump(ida_instruction);
		int num_out_edges = 0;
		xrefblk_t xref;
		for (bool ok = xref.first_from(ida_instruction.ea, XREF_ALL);
			ok && xref.iscode; ok = xref.next_from()) {
			if (xref.type == fl_JN || xref.type == fl_JF) {
				++num_out_edges;
			}
			else if (unconditional_jump && xref.type == fl_F) {
				// Специальный случай для странного поведения IDA: У нас был оператор перехода switch
				// (jmp[eax*4]) в flash11c.idb, который имел одно безусловное исходящее ребро ("правильно") 
				// и второе кодовое ребро ("неправильно! Безусловный переход никогда не должен иметь регулярного кодового ребра").
				// Это обходной путь для данной ситуации.
				++num_out_edges;
			}
		}

		bool handled = false;
		if (num_out_edges > 1) {  // Таблица переходов Switch
			ea_t table_address = std::numeric_limits<ea_t>::max();
			for (bool ok = xref.first_from(ida_instruction.ea, XREF_ALL);
				ok && xref.iscode; ok = xref.next_from()) {
				flow_graph->AddEdge(FlowGraphEdge(ida_instruction.ea, xref.to,
					FlowGraphEdge::TYPE_SWITCH));
				address_references->emplace_back(
					ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
					xref.to, TYPE_SWITCH);
				entry_point_adder->Add(xref.to, EntryPoint::Source::JUMP_TABLE);
				table_address = std::min(table_address, xref.to);
				handled = true;
			}
			// Добавить ссылку на данные по первому адресу в таблице switch
			address_references->emplace_back(
				ida_instruction.ea, GetSourceExpressionId(*instruction, table_address),
				table_address, TYPE_DATA);
		}
		else {  // Normal xref
			for (bool ok = xref.first_from(ida_instruction.ea, XREF_ALL);
				ok && xref.iscode; ok = xref.next_from()) {
				// Регулярный поток кода (Regular code flow)
				if (xref.type == fl_F || instruction->GetNextInstruction() == xref.to) {
					// We need the || above because IDA gives me xref type unknown for old idbs.
					// Нам нужно || выше, потому что IDA выдает мне xref type unknown для старых idbs.
					if (instruction->GetNextInstruction() != xref.to) {
						LOG(INFO) << absl::StrCat(
							"warning: ", FormatAddress(instruction->GetAddress()),
							" flow xref target != address + instruction size (or "
							"instruction is missing flow flag). Disassembly is "
							"likely erroneous.");
					}
					entry_point_adder->Add(xref.to, EntryPoint::Source::CODE_FLOW);
				}
				else if (xref.type == fl_CN || xref.type == fl_CF) {
					// Call targets
					if (IsPossibleFunction(xref.to, modules)) {
						call_graph->AddFunction(xref.to);
						call_graph->AddEdge(ida_instruction.ea, xref.to);
						entry_point_adder->Add(xref.to, EntryPoint::Source::CALL_TARGET);
					}
					instruction->SetFlag(FLAG_CALL, true);
					address_references->emplace_back(
						ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
						xref.to, TYPE_CALL_DIRECT);
					handled = true;
				}
				else if (xref.type == fl_JN || xref.type == fl_JF) {
					// Jump targets
					if (IsPossibleFunction(xref.to, modules) && xref.type == fl_JF) {
						call_graph->AddEdge(ida_instruction.ea, xref.to);
					}
					// MIPS adds an extra instruction _after_ the jump that'll always be executed.
					// MIPS добавляет дополнительную инструкцию _после_ jump'а, которая всегда будет выполнена.
					// Thus we need to branch from that for flow graph reconstruction to work...
					// Таким образом, для того чтобы реконструкция потокового графа работала, нам необходимо от него ответвиться...
					const Address source_address = GetArchitecture() == kMips
						? instruction->GetNextInstruction()
						: ida_instruction.ea;
					if (unconditional_jump) {
						flow_graph->AddEdge(FlowGraphEdge(source_address, xref.to,
							FlowGraphEdge::TYPE_UNCONDITIONAL));
						address_references->emplace_back(
							ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
							xref.to, TYPE_UNCONDITIONAL);
						handled = true;
					}
					else {
						Address next_address = instruction->GetNextInstruction();
						if (GetArchitecture() == kMips) {
							// TODO(cblichman): Since this is MIPS, replace below with a constant.
							// Look ahead one instruction.
							insn_t next_instruction;
							decode_insn(&next_instruction, next_address);
							next_address += next_instruction.size;
						}

						flow_graph->AddEdge(FlowGraphEdge(source_address, next_address,
							FlowGraphEdge::TYPE_FALSE));
						flow_graph->AddEdge(
							FlowGraphEdge(source_address, xref.to, FlowGraphEdge::TYPE_TRUE));
						address_references->emplace_back(
							ida_instruction.ea,
							GetSourceExpressionId(*instruction, next_address), next_address,
							TYPE_FALSE);
						address_references->emplace_back(
							ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
							xref.to, TYPE_TRUE);
						handled = true;
					}
					entry_point_adder->Add(xref.to, EntryPoint::Source::JUMP_DIRECT);
				}
				else {
					LOG(INFO) << absl::StrCat("unknown xref ",
						FormatAddress(ida_instruction.ea));
				}
			}
		}

		if (!handled) {
			if (is_call_insn(ida_instruction)) {
				// Call to imported function or call [offset+eax*4]
				// Вызов импортируемой функции или вызов [offset+eax*4]
				for (bool ok = xref.first_from(ida_instruction.ea, XREF_DATA); ok;
					ok = xref.next_from()) {
					if (IsPossibleFunction(xref.to, modules)) {
						call_graph->AddFunction(xref.to);
						call_graph->AddEdge(ida_instruction.ea, xref.to);
						entry_point_adder->Add(xref.to, EntryPoint::Source::CALL_TARGET);
					}
					instruction->SetFlag(FLAG_CALL, true);
					address_references->emplace_back(
						ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
						xref.to, TYPE_CALL_INDIRECT);
				}
			}
			else {  // Assume data reference as in "push aValue"
					// Предполагать ссылку на данные, как в "push aValue"
				for (bool ok = xref.first_from(ida_instruction.ea, XREF_DATA); ok;
					ok = xref.next_from()) {
					if (!GetStringReference(ida_instruction.ea).empty()) {
						address_references->emplace_back(
							ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
							xref.to, TYPE_DATA_STRING);
					}
					else {
						address_references->emplace_back(
							ida_instruction.ea, GetSourceExpressionId(*instruction, xref.to),
							xref.to, TYPE_DATA);
					}
				}
			}
		}
	}



	// начинаем анализ 

	void AnalyzeFlowIda(EntryPoints* entry_points, const ModuleMap& modules,
		Writer* writer, detego::Instructions* instructions,
		FlowGraph* flow_graph, CallGraph* call_graph,
		FlowGraph::NoReturnHeuristic noreturn_heuristic) {

		TRACE_FN();

		Timer<> timer;
		AddressReferences address_references;

		// Add initial entry points as functions.
		// Добавить начальные точки входа как функции.
		for (const auto& entry_point : *entry_points) {
			if ((entry_point.IsFunctionPrologue() || entry_point.IsExternal() ||
				entry_point.IsCallTarget()) &&
				IsPossibleFunction(entry_point.address_, modules)) {
				call_graph->AddFunction(entry_point.address_);
			}
		}

		AddressSpace address_space{};
		AddressSpace flags{};
		for (int i = 0; i < get_segm_qty(); ++i) {
			const segment_t* segment = getnseg(i);
			address_space.AddMemoryBlock(segment->start_ea,
				GetSectionBytes(segment->start_ea),
				GetPermissions(segment));
			flags.AddMemoryBlock(
				segment->start_ea,
				AddressSpace::MemoryBlock(size_t(segment->end_ea - segment->start_ea)),
				GetPermissions(segment));
		}

		IdaTypesContainer types;
		TypeSystem type_system(types, address_space);

		Instruction::SetBitness(GetArchitectureBitness());
		Instruction::SetGetBytesCallback(&GetBytes);
		Instruction::SetMemoryFlags(&flags);
		std::function<Instruction(const insn_t&, CallGraph*, FlowGraph*, TypeSystem*)>
			parse_instruction = nullptr;
		bool mark_x86_nops = false;
		switch (GetArchitecture()) {
		case kX86:
			parse_instruction = ParseInstructionIdaMetaPc;
			mark_x86_nops =
				noreturn_heuristic == FlowGraph::NoReturnHeuristic::kNopsAfterCall;
			break;
		case kArm:
			parse_instruction = ParseInstructionIdaArm;
			break;
		case kPpc:
			parse_instruction = ParseInstructionIdaPpc;
			break;
		case kMips:
			parse_instruction = ParseInstructionIdaMips;
			break;
		case kDalvik:
			parse_instruction = ParseInstructionIdaDalvik;
			break;
		case kGeneric:
		default:
			parse_instruction = ParseInstructionIdaGeneric;
			break;
		}

		msg("flow analysis\n");
		for (EntryPointManager entry_point_adder(entry_points, "flow analysis");
			!entry_points->empty();) {
			const Address address = entry_points->back().address_;
			entry_points->pop_back();

			if (!flags.IsValidAddress(address) || (flags[address] & FLAG_VISITED)) {
				continue;  // Do not analyze an address twice.
			}
			flags[address] |= FLAG_VISITED;

			insn_t ida_instruction;
			if (decode_insn(&ida_instruction, address) <= 0) {
				continue;
			}
			Instruction new_instruction = parse_instruction(ida_instruction, call_graph,
				flow_graph, &type_system);
			if (new_instruction.HasFlag(FLAG_INVALID)) {
				continue;
			}
			AnalyzeFlow(ida_instruction, &new_instruction, flow_graph, call_graph,
				&address_references, &entry_point_adder, modules);
			call_graph->AddStringReference(address, GetStringReference(address));
			GetComments(ida_instruction, &call_graph->GetComments());

			if (mark_x86_nops) {
				// FLAG_NOP is only important when reconstructing functions, thus we can set if after AnalyzeFlow().
				//  FLAG_NOP важен только при реконструкции функций, поэтому мы можем установить его после AnalyzeFlow().
				new_instruction.SetFlag(FLAG_NOP, IsNopX86(new_instruction.GetBytes()));
			}
			// информацию о инструкции кидаем в вектор !!!
			instructions->push_back(new_instruction);
		}

		msg("sorting instructions\n");
		SortInstructions(instructions);

		msg("reconstructing flow graphs\n");
		std::sort(address_references.begin(), address_references.end());
		// TODO(soerenme): Remove duplicates if any.
		ReconstructFlowGraph(instructions, *flow_graph, call_graph);

		msg("reconstructing functions\n");
		flow_graph->ReconstructFunctions(instructions, call_graph,
			noreturn_heuristic);

		// Должна вызываться после ReconstructFunctions(), так как при этом иногда удаляются исходные базовые блоки для ребра.
		// Происходит только в том случае, если дизассемблирование в IDA основательно нарушено.
		flow_graph->PruneFlowGraphEdges();

		// Примечание: PruneFlowGraphEdges может добавлять комментарии к call_graph,
		// поэтому после этого должна выполняться пост_обработка.
		call_graph->PostProcessComments();

		msg("IDA specific post processing\n");
		// Постобработка с учетом специфики Ida.
		{ // ограничим зону видимости наших новых переменных ********************************
			std::string dem_name = {};
			size_t f_index = {};
			std::string f_name = {};


			for (auto i = flow_graph->GetFunctions().begin(),
				end = flow_graph->GetFunctions().end();
				i != end; ++i) {
				Function& function = *i->second;
				const Address address = function.GetEntryPoint();
				// - установить имя функции
				const std::string name = GetName(address, true);
				if (!name.empty()) {
					dem_name = GetDemangledName(address);
					function.SetName(name, dem_name);


					f_index = exporter.function_index[address];
					f_name = exporter.function_data[f_index].name;
					if (dem_name != f_name)
					{
						exporter.function_data[f_index].dem_name = dem_name;
					}
					else
					{
						exporter.function_data[f_index].dem_name = "";
					}



					// msg("Name function %s =  \n", name.c_str());
				}
				// - установить тип функции
				const func_t* ida_func = get_func(address);

				if (ida_func) {
					if ((ida_func->flags & FUNC_THUNK)  // отдавать предпочтение thunk над library
						&& function.GetBasicBlocks().size() == 1 &&
						(*function.GetBasicBlocks().begin())->GetInstructionCount() == 1) {
						function.SetType(Function::TYPE_THUNK);
					}
					else if (ida_func->flags & FUNC_LIB) {
						function.SetType(Function::TYPE_LIBRARY);
					}
				}
				const std::string module = GetModuleName(address, modules);
				if (!module.empty()) {
					function.SetType(Function::TYPE_IMPORTED);
					function.SetModuleName(module);
					// msg("Name module %s =  \n", module.c_str());
				}
				if (function.GetType(true) == Function::TYPE_NONE ||
					function.GetType(false) == Function::TYPE_STANDARD) {
					if (function.GetBasicBlocks().empty()) {
						function.SetType(Function::TYPE_IMPORTED);
					}
					else {
						function.SetType(Function::TYPE_STANDARD);
					}
				}
				types.CreateFunctionPrototype(function);
			}

		} // ограничим зону видимости наших новых переменных ********************************



		const auto processing_time = absl::Seconds(timer.elapsed());
		timer.restart();

		msg("writing...\n");

		auto ignore_error(writer->Write(*call_graph, *flow_graph, *instructions,
			address_references, &type_system, address_space));

		Operand::EmptyCache();
		Expression::EmptyCache();

		const auto writing_time = absl::Seconds(timer.elapsed());
		msg("%s : %s processing %s  writing\n",
			GetModuleName().c_str(),
			HumanReadableDuration(processing_time).c_str(),
			HumanReadableDuration(writing_time).c_str());
		//LOG(INFO) << absl::StrCat(
		//    GetModuleName(), ": ", HumanReadableDuration(processing_time),
		//    " processing, ", HumanReadableDuration(writing_time), " writing");
	}

	void AnalyzeFlowIdaAdditional(EntryPoints* entry_points, const ModuleMap& modules,
		DumpWriter* writer, detego::Instructions* instructions, /* ИЗМЕНЕНО было Writer* writer стало DumpWriter* writer*/
		FlowGraph* flow_graph, CallGraph* call_graph,
		FlowGraph::NoReturnHeuristic noreturn_heuristic,
		Exporter* exporter) {

		TRACE_FN();
		
		Timer<> timer;
		AddressReferences address_references;

		// Add initial entry points as functions.
		// Добавить начальные точки входа как функции.
		for (const auto& entry_point : *entry_points) {
			if ((entry_point.IsFunctionPrologue() || entry_point.IsExternal() ||
				entry_point.IsCallTarget()) &&
				IsPossibleFunction(entry_point.address_, modules)) {

				call_graph->AddFunction(entry_point.address_);


				// проверим , что мы имеем (ида знает) адрес этой функции,
				// ищем ее в нашем векторе function_data
				// https://stackoverflow.com/questions/14225932/search-for-a-struct-item-in-a-vector-by-member-data
				// https://www.geeksforgeeks.org/how-to-find-index-of-a-given-element-in-a-vector-in-cpp/
				if (!exporter->SearchFunctionAddress(entry_point.address_))
				{
					msg("Ida unknow about it function %llx \n", entry_point.address_);
				}

			}
		}

		AddressSpace address_space{};
		AddressSpace flags{};

		// вывод информации о сегментах (.text, .data, .bss и тд ) 
		if (mdbg) msg("\n\t\tSegments output start \n");
		
		for (int i = 0; i < get_segm_qty(); ++i) {
			const segment_t* segment = getnseg(i);
			address_space.AddMemoryBlock(segment->start_ea,
				GetSectionBytes(segment->start_ea),
				GetPermissions(segment));
			flags.AddMemoryBlock(
				segment->start_ea,
				AddressSpace::MemoryBlock(size_t(segment->end_ea - segment->start_ea)),
				GetPermissions(segment));
			qstring s_name{};
			qstring s_class{};
			get_segm_name(&s_name, segment, 0);
			get_segm_class(&s_class, segment);
			if (mdbg)
			{
				msg("\n segment nm = %s   segment->start_ea : end_ea = %llx :: %llx class = %s",
					s_name.c_str(), segment->start_ea, segment->end_ea, s_class.c_str());
			}
			exporter->pe_segment.start_address = segment->start_ea;
			exporter->pe_segment.end_address = segment->end_ea;
			exporter->pe_segment.name = static_cast<std::string>(s_name.c_str());
			exporter->pe_segment.s_class = static_cast<std::string>(s_class.c_str());
			exporter->segments_data.emplace_back(exporter->pe_segment);
		}
		// закончили вывод информации о сегментах 
		if (mdbg) msg("\n\n\t\tSegments output finish \n");

		

		IdaTypesContainer types;
		TypeSystem type_system(types, address_space);

		Instruction::SetBitness(GetArchitectureBitness());
		Instruction::SetGetBytesCallback(&GetBytes);
		Instruction::SetMemoryFlags(&flags);
		std::function<Instruction(const insn_t&, CallGraph*, FlowGraph*, TypeSystem*)>
			parse_instruction = nullptr;
		bool mark_x86_nops = false;

		auto iii = GetArchitecture();
		msg("            Architecture is ");

		switch (GetArchitecture()) {
		case kX86:
			parse_instruction = ParseInstructionIdaMetaPc;
			mark_x86_nops =
				noreturn_heuristic == FlowGraph::NoReturnHeuristic::kNopsAfterCall;
			msg(": kX86 \n");
			break;
		case kArm:
			parse_instruction = ParseInstructionIdaArm;
			msg(": kArm \n");
			break;
		case kPpc:
			parse_instruction = ParseInstructionIdaPpc;
			msg(": kPpc \n");
			break;
		case kMips:
			parse_instruction = ParseInstructionIdaMips;
			msg(": kMips \n");
			break;
		case kDalvik:
			parse_instruction = ParseInstructionIdaDalvik;
			msg(": kDalvik \n");
			break;
		case kGeneric:
		default:
			parse_instruction = ParseInstructionIdaGeneric;
			msg(": default|kGeneric \n");
			break;
		}

		msg("    Flow analysis\n");
		for (EntryPointManager entry_point_adder(entry_points, "flow analysis"); !entry_points->empty();)
		{
			const Address address = entry_points->back().address_;
			entry_points->pop_back();

			if (!flags.IsValidAddress(address) || (flags[address] & FLAG_VISITED)) {
				continue;  // Do not analyze an address twice.
			}
			flags[address] |= FLAG_VISITED;

			insn_t ida_instruction;
			if (decode_insn(&ida_instruction, address) <= 0) {
				continue;
			}
			Instruction new_instruction = parse_instruction(ida_instruction, call_graph,
				flow_graph, &type_system);
			if (new_instruction.HasFlag(FLAG_INVALID)) {
				continue;
			}
			AnalyzeFlowAdditional(ida_instruction, &new_instruction, flow_graph, call_graph,
				&address_references, &entry_point_adder, modules);
			call_graph->AddStringReference(address, GetStringReference(address));
			GetComments(ida_instruction, &call_graph->GetComments());

			if (mark_x86_nops) {
				// FLAG_NOP is only important when reconstructing functions, thus we can set if after AnalyzeFlow().
				//  FLAG_NOP важен только при реконструкции функций, поэтому мы можем установить его после AnalyzeFlow().
				new_instruction.SetFlag(FLAG_NOP, IsNopX86(new_instruction.GetBytes()));
			}
			// информацию о инструкции кидаем в вектор !!!
			instructions->push_back(new_instruction);
		}

		msg("    Sorting instructions\n");
		SortInstructions(instructions);


		// в векторе instructions у нас содержаться все инструкции PE файла ,
		// отсортированные по адресам , мы можем их добавить в наш вектор ...

		{
			size_t tmp = instructions->size();
			exporter->vector_pe_instructions.reserve(tmp  * 1.1); // зарезервируем места в векторе на 10 проц больше чем надо , чтоб не ошибиться ...

		}


		// [HEAP] --- begin additions ---
		// Требуется: #include <unordered_map>
		static const int HEAP_TOUCH_WINDOW = 16;     ///< ждём разыменование RAX/EAX
		static const int HEAP_ALIAS_WINDOW = 16;     ///< ждём разыменование через регистр-алиас (mov/lea reg, rax/[rax+..])

													 // Окно «прямого» разыменования через RAX/EAX (ключ: fva)
		std::unordered_map<ea_t, int> heap_window;

		// Окна для регистров-алиасов: для каждой функции храним TTL по номеру регистра
		std::unordered_map<ea_t, std::unordered_map<int, int>> heap_alias_window;
		std::unordered_map<ea_t, bool> heap_event_armed;  ///< true -> ждём первое касание после аллокации.

		// [HEAP] --- end additions ---


		
		for (const auto& item : *instructions)
		{
			auto adr = item.GetAddress();
			exporter->pe_instruction.address = adr;
			exporter->pe_instruction.func_address = (get_func(adr))->start_ea;

			// --- [INSTR FLAGS] begin ---
			insn_t insn;
			bool decoded = decode_insn(&insn, adr) > 0;
			bool reads_stack = false, writes_stack = false;
			bool reads_global = false, writes_global = false;
			int  sp_delta = 0;
			bool is_alloc_call = false;
			bool is_free_call = false;

			if (decoded) {
				const auto cf = insn.get_canon_feature(ph); // тип берём у функции

				// общий хелпер для Win64/х86
				auto IsParamReg = [&](int r)->bool {
					if (r < 0) return false;
					const char *rn = ph.reg_names[r];
					if (!rn) return false;
					return strcmp(rn, "rcx") == 0 || strcmp(rn, "rdx") == 0 || strcmp(rn, "r8") == 0 || strcmp(rn, "r9") == 0
						|| strcmp(rn, "ecx") == 0 || strcmp(rn, "edx") == 0; // простая эвристика для x86 fastcall/thiscall
				};

				

				auto mark_stack_if = [&](int op_idx, bool is_write) {
					const op_t &op = insn.ops[op_idx];
					if (op.type == o_displ || op.type == o_phrase) {
						const char* rn = ph.reg_names[op.reg];
						if (rn && (*rn == 's' || *rn == 'e' || *rn == 'r')) { /* быстрый фильтр sp/bp/rsp/rbp */
							if (strstr(rn, "sp") || strstr(rn, "bp")) {
								if (is_write) writes_stack = true; else reads_stack = true;
							}
						}
					}
				};
				auto mark_global_if = [&](int op_idx, bool is_write) {
					const op_t &op = insn.ops[op_idx];
					if (op.type == o_mem) {
						if (is_write) writes_global = true; else reads_global = true;
					}
				};


				auto &fx = exporter->GetOrCreateFuncEffects(exporter->pe_instruction.func_address);
				if (cf & CF_CALL) {
					fx.calls_total++;
					// прямой: o_near/o_far/o_mem (IAT) — считаем как direct
					const op_t &op0 = insn.ops[0];
					if (op0.type == o_near || op0.type == o_far || op0.type == o_mem) fx.direct_calls++;
					// косвенный: через регистр/адресное вычисление
					if (op0.type == o_reg || op0.type == o_phrase || op0.type == o_displ) fx.indirect_calls++;
				}



				if ((cf & CF_CALL) != 0) {
					const op_t &op0 = insn.ops[0];
					if (op0.type == o_reg && IsParamReg(op0.reg)) {
						fx.dispatches_via_funptr = true;
					}
					if ((op0.type == o_displ || op0.type == o_phrase) && IsParamReg(op0.reg)) {
						fx.dispatches_via_funptr = true;
					}
				}

				// по операндам 1..UA_MAXOP с CF_USEi/CF_CHGi
				if (cf & CF_USE1) mark_stack_if(0, false), mark_global_if(0, false);
				if (cf & CF_CHG1) mark_stack_if(0, true), mark_global_if(0, true);
				if (cf & CF_USE2) mark_stack_if(1, false), mark_global_if(1, false);
				if (cf & CF_CHG2) mark_stack_if(1, true), mark_global_if(1, true);
				// при желании продолжить для USE3/CHG3...

				// дельта стека
				if (func_t* fn = get_func(adr)) {
					sp_delta = get_sp_delta(fn, adr);
				}

				// --- [ALLOC DETECT] begin ---
				ea_t callee = BADADDR;
				if ((cf & CF_CALL) != 0)
				{
					// 1) цель по code-xref
					callee = get_first_fcref_from(adr);

					// 2) если нет — из операнда (near/far/mem)
					if (callee == BADADDR && insn.ops[0].type != o_void)
					{
						const op_t &op0 = insn.ops[0];
						switch (op0.type)
						{
						case o_near:
						case o_far:
						case o_mem:
							callee = op0.addr; // прямой/через IAT (__imp_*)
							break;
						default: break;
						}
					}

					// 3) разрулить thunk
					if (callee != BADADDR) {
						if (func_t* tf = get_func(callee)) {
							ea_t tgt = ResolveThunkTarget(tf);   // твоя функция возвращает адрес цели
							if (tgt != BADADDR) callee = tgt;
						}
					}

					// 4) имя цели
					if (callee != BADADDR)
					{
						qstring name_raw, name_dem;
						bool got = get_name(&name_raw, callee) > 0;
						if (got && demangle_name(&name_dem, name_raw.c_str(), MNG_SHORT_FORM) > 0)
							name_raw = name_dem;

						if (got) {
							const char *s = name_raw.c_str();
							if (strstr(s, "malloc")
								|| strstr(s, "realloc")
								|| strstr(s, "calloc")
								|| strstr(s, "operator new")
								|| strstr(s, "HeapAlloc")
								|| strstr(s, "LocalAlloc")
								|| strstr(s, "GlobalAlloc"))
								is_alloc_call = true;

							if (strstr(s, "free")
								|| strstr(s, "operator delete")
								|| strstr(s, "HeapFree")
								|| strstr(s, "LocalFree")
								|| strstr(s, "GlobalFree"))
								is_free_call = true;
						}
					}
				}
				// --- [ALLOC DETECT] end ---





				// --- [DYNIMPORT NAMER] begin ---
				{
					//==========================================================================
					// УТИЛИТАРНЫЕ ЛЯМБДЫ (локальные помощники)
					//==========================================================================

					// Сравнение имени регистра без учёта регистра символов.
					// expected: ph.reg_names[reg] уже инициализирован процессором.
					// Используем qstricmp из IDA SDK.
					auto reg_is_ci = [](int reg, const char* wanted) -> bool {
						const char *rn = (reg >= 0 && reg < ph.regs_num) ? ph.reg_names[reg] : nullptr;
						return rn && qstricmp(rn, wanted) == 0;
					};

					// Проверка: входит ли регистр в заданное семейство имён (например, RAX/EAX/AX/AL/AH).
					// fam — массив литералов; fam_sz — его размер.
					auto reg_in_family = [&](int reg, const char* const* fam, size_t fam_sz) -> bool {
						if (reg < 0 || reg >= ph.regs_num) return false;
						const char *rn = ph.reg_names[reg];
						if (!rn) return false;
						for (size_t i = 0; i < fam_sz; ++i)
							if (qstricmp(rn, fam[i]) == 0) return true;
						return false;
					};

					// Проверка: базовый регистр адресации — IP-семейство? (RIP/EIP/IP).
					// Нужна для вычисления адреса при RIP-relative/… addressing.
					auto phrase_is_ip_family = [&](int phrase_idx) -> bool {
						if (phrase_idx < 0 || phrase_idx >= ph.regs_num) return false;
						const char *nm = ph.reg_names[phrase_idx];
						if (!nm) return false;
						return qstricmp(nm, "rip") == 0 || qstricmp(nm, "eip") == 0 || qstricmp(nm, "ip") == 0;
					};

					// Простой strlen на C, чтобы избежать неоднозначностей перегрузок (MSVC2015).
					auto str_len = [](const char* s) -> size_t {
						size_t n = 0; if (!s) return 0; while (s[n] != '\0') ++n; return n;
					};

					//==========================================================================
					// ОДНОРАЗОВЫЙ ДАМП МАССИВА РЕГИСТРОВ ПРОЦЕССОРА (диагностика)
					// Выводит все ph.reg_names[*], и индексы для ax/dx/ip (как ориентир).
					//==========================================================================

					static bool g_dumped_regs = false;
					if (!g_dumped_regs) {
						g_dumped_regs = true;
						msg("DYNIMPORT dbg: ---- CPU registers from ph.reg_names (count=%d) ----\n", ph.regs_num);
						for (int i = 0; i < ph.regs_num; ++i) {
							const char* nm = ph.reg_names[i] ? ph.reg_names[i] : "<null>";
							msg("DYNIMPORT dbg: reg[%02d] = %s\n", i, nm);
						}
						int idx_ax = -1, idx_dx = -1, idx_ip = -1;
						for (int i = 0; i < ph.regs_num; ++i) {
							const char *nm = ph.reg_names[i];
							if (!nm) continue;
							if (qstricmp(nm, "ax") == 0) idx_ax = i;
							if (qstricmp(nm, "dx") == 0) idx_dx = i;
							if (qstricmp(nm, "ip") == 0) idx_ip = i;
						}
						// Сообщение чисто ASCII (без Unicode), чтобы исключить «Bad declaration» от плагина IDA Message window.
						msg("DYNIMPORT dbg: index(AX)=%d DX=%d IP=%d   [note: reg_names has no RAX/RDX/RIP; families will be used]\n",
							idx_ax, idx_dx, idx_ip);
						msg("DYNIMPORT dbg: -----------------------------------------------------\n");
					}

					//==========================================================================
					// ЧТЕНИЕ ИМЕНИ API ПО АДРЕСУ ЛИТЕРАЛА
					//
					// Пытаемся вычитать либо ASCII, либо UTF-16LE, а если по адресу лежит не строка,
					// делаем одно разыменование (считаем, что по адресу хранится указатель на строку).
					// Возвращаем qstring с именем API или пустую строку.
					//==========================================================================

					auto qread_api_name = [](ea_t ea) -> qstring {
						// Читаем «сырые» байты из памяти (без проверок типов данных IDA).
						auto read_raw = [](ea_t addr, qvector<uint8> &raw) {
							raw.resize(512, 0);
							for (size_t i = 0; i < raw.size(); ++i)
								raw[i] = get_wide_byte(addr + i);
						};
						// Парсим буфер как ASCII либо как UTF-16LE (эвристика — много нулей на чётных/нечётных байтах).
						auto parse_ascii_utf16 = [](const qvector<uint8> &raw) -> qstring {
							qstring s;
							if (raw.empty()) return s;

							// Простая эвристика определения UTF-16LE:
							int zeros = 0, total = 0;
							for (size_t i = 1; i + 1 < raw.size() && total < 20; i += 2, ++total)
								if (raw[i] == 0) ++zeros;
							bool utf16 = (total >= 6 && zeros >= total - 1);

							if (utf16) {
								// Конвертируем UTF-16LE в ASCII-диапазон (символы >127 заменяем на '?')
								for (size_t i = 0; i + 1 < raw.size(); i += 2) {
									uint16 ch = uint16(raw[i] | (raw[i + 1] << 8));
									if (ch == 0) break;
									s.append(ch < 128 ? char(ch) : '?');
								}
							}
							else {
								// Обычная ASCII-строка
								for (size_t i = 0; i < raw.size(); ++i) {
									uint8 ch = raw[i];
									if (ch == 0) break;
									s.append((char)ch);
								}
							}
							return s;
						};
						// Проверяем, «похоже ли начало буфера на строку» — несколько печатных символов подряд.
						auto looks_printable_prefix = [](const qvector<uint8> &raw) -> bool {
							int pr = 0;
							for (size_t i = 0; i < raw.size() && i < 8; ++i) {
								unsigned c = raw[i];
								if (c == 0) break;
								if (c >= 0x20 && c < 0x7F) ++pr;
							}
							return pr >= 3;
						};
						// Читаем указатель (EA32/EA64) из памяти.
						auto read_ptr = [](ea_t addr) -> ea_t {
#if __EA64__
							uint64 lo = get_wide_dword(addr);
							uint64 hi = get_wide_dword(addr + 4);
							return (ea_t)(lo | (hi << 32));
#else
							return (ea_t)get_wide_dword(addr);
#endif
						};
						// Валидна ли адресация.
						auto ea_ok = [](ea_t p) -> bool { return p != BADADDR && getseg(p) != nullptr; };

						if (ea == BADADDR) return qstring();

						// Сначала пробуем напрямую
						qvector<uint8> raw; read_raw(ea, raw);
						qstring s = parse_ascii_utf16(raw);
						if (!s.empty()) return s;

						// Если не похоже на строку — попробуем разыменовать как указатель и прочесть вторично.
						if (!looks_printable_prefix(raw)) {
							ea_t p2 = read_ptr(ea);
							if (ea_ok(p2)) {
								qvector<uint8> raw2; read_raw(p2, raw2);
								qstring s2 = parse_ascii_utf16(raw2);
								if (!s2.empty()) return s2;
							}
						}
						return qstring();
						};

					// Узнать, что это именно GetProcAddress (сравнение по имени callee).
					auto is_getproc = [](const qstring &nm) -> bool {
						return strstr(nm.c_str(), "GetProcAddress") != nullptr;
					};

					// «Очистка» IDA-лейбла до предполагаемого имени API:
					// - удаляем префиксы вида сегментов/модулей "xxx.";
					// - убираем ведущую 'a'/'A' у строковых меток (частый стиль IDA для ascii-строк: aFooBar);
					// - срезаем off_/qword_/byte_/__imp_/__ в начале.
					auto clean_label_to_api = [&](const qstring &lbl) -> qstring {
						if (lbl.empty()) return qstring();
						qstring s = lbl;
						// откидываем до последней точки: "modname.symbol" -> "symbol"
						ssize_t p = s.rfind('.');
						if (p != -1) s.remove(0, (size_t)(p + 1));
						// убираем ведущую 'a'/'A' (IDA любит метки 'aSomething' для ASCII)
						if (!s.empty() && (s[0] == 'a' || s[0] == 'A'))
							s.remove(0, 1);
						// системные префиксы данных
						const char* bads[] = { "off_", "qword_", "byte_", "__imp_", "__" };
						for (const char* b : bads) {
							if (s.find(b) == 0) { s.remove(0, (size_t)str_len(b)); break; }
						}
						return s;
					};

					//==========================================================================
					// ТРЕКЕР ПОСЛЕДНЕГО ЗНАЧЕНИЯ В RDX-СЕМЕЙСТВЕ (адрес строки с именем API)
					//
					// Многие вызовы GetProcAddress передают имя функции в RDX/EDX.
					// Мы запоминаем последнее присвоение RDX (mov/lea), чтобы потом,
					// когда встретим call GetProcAddress, взять оттуда имя.
					//==========================================================================



					static qstring g_last_rdx_name;      // кешированное имя API (как строка)
					static ea_t    g_last_rdx_name_ea = BADADDR; // адрес строкового литерала (для диагностики/доп. извлечения)

																 // Отслеживание текущей инструкции: если это mov/lea в RDX/EDX/DX/DL/DH — вынимаем строку
					{
						insn_t cur;
						if (decode_insn(&cur, adr)) {
							if ((cur.itype == NN_lea || cur.itype == NN_mov)
								&& cur.ops[0].type == o_reg)
							{
								// семейство RDX
								static const char* F_RDX[] = { "rdx","edx","dx","dl","dh" };
								if (reg_in_family(cur.ops[0].reg, F_RDX, qnumber(F_RDX))) {
									ea_t str_ea = BADADDR;
									const op_t &src = cur.ops[1];
									// определяем адрес литерала (o_mem/o_far), непосредственное значение (o_imm)
									// или дисперсию с IP-базой (o_displ + RIP/EIP/IP)
									switch (src.type) {
									case o_mem:
									case o_far:  str_ea = src.addr; break;
									case o_imm:  str_ea = ea_t(src.value); break;
									case o_displ:
										if (phrase_is_ip_family(src.phrase))
											str_ea = cur.ea + cur.size + src.addr;
										break;
									default: break;
									}
									if (str_ea != BADADDR) {
										g_last_rdx_name_ea = str_ea;
										// Пробуем как строку; если не вышло — пробуем по имени метки.
										qstring nm = qread_api_name(str_ea);
										if (nm.empty()) {
											qstring lbl;
											if (get_name(&lbl, str_ea) > 0) nm = clean_label_to_api(lbl);
										}
										g_last_rdx_name = nm;
									}
								}
							}
						}
					}

					//==========================================================================
					// ОСНОВНОЕ: детектируем CALL GetProcAddress, ищем store RAX -> [mem],
					//           формируем имя p_<API>, задаём тип и комментарий.
					//==========================================================================

					if (cf & CF_CALL)   // эта инструкция — вызов?
					{
						// Адрес вызываемой функции (callee) по кросс-референсу.
						ea_t callee = get_first_fcref_from(adr);

						// Получаем имя callee (с деманглингом — вдруг импорты/ярлыки).
						qstring callee_name;
						if (callee != BADADDR && get_name(&callee_name, callee) > 0) {
							qstring dem;
							if (demangle_name(&dem, callee_name.c_str(), MNG_SHORT_FORM) > 0)
								callee_name = dem;
						}

						// Нас интересуют только вызовы GetProcAddress
						if (callee != BADADDR && is_getproc(callee_name))
						{
							msg("DYNIMPORT dbg: GetProcAddress detected at %a\n", adr);

							// 1) Имя API для ЭТОГО вызова: сперва берём из трекера RDX.
							qstring api_name = g_last_rdx_name;
							ea_t    api_name_ea = g_last_rdx_name_ea;

							// Если трекер пуст (не успели поймать lea/mov rdx, …) —
							// делаем короткий бэктрекинг на несколько инструкций назад.
							if (api_name.empty()) {
								ea_t p = adr;
								for (int i = 0; i < 3 && p != BADADDR; ++i) {
									p = prev_head(p, inf.min_ea);
									insn_t prev;
									if (!decode_insn(&prev, p)) break;

									if ((prev.itype == NN_lea || prev.itype == NN_mov)
										&& prev.ops[0].type == o_reg)
									{
										static const char* F_RDX[] = { "rdx","edx","dx","dl","dh" };
										if (reg_in_family(prev.ops[0].reg, F_RDX, qnumber(F_RDX))) {
											ea_t str_ea = BADADDR;
											const op_t &src = prev.ops[1];
											switch (src.type) {
											case o_mem:
											case o_far:  str_ea = src.addr; break;
											case o_imm:  str_ea = ea_t(src.value); break;
											case o_displ:
												if (phrase_is_ip_family(src.phrase))
													str_ea = prev.ea + prev.size + src.addr;
												break;
											default: break;
											}
											if (str_ea != BADADDR) {
												api_name_ea = str_ea;
												// Стараемся прочесть строку напрямую
												api_name = qread_api_name(str_ea);
												// Если не получилось — пробуем очистить имя метки.
												if (api_name.empty()) {
													qstring lbl;
													if (get_name(&lbl, str_ea) > 0)
														api_name = clean_label_to_api(lbl);
												}
												if (!api_name.empty())
													break; // нашли имя — достаточно
											}
										}
									}
								}
							}

							// 2) Поиск места записи результата GetProcAddress (RAX) в память
							//    2.1 Прямой поиск: mov [mem|rip+disp], rax/eax/ax/al/ah
							ea_t qptr_ea = BADADDR;  // адрес ячейки/глобалки, куда пишут указатель
							ea_t store_ea = BADADDR; // адрес инструкции store (для логов)


							{
								ea_t n = next_head(adr, inf.max_ea);
								for (int i = 0; i < 24 && n != BADADDR; ++i) {
									insn_t nxt;
									if (!decode_insn(&nxt, n)) break;

									if (nxt.ops[0].type != o_void && nxt.ops[1].type != o_void) {
										const op_t &dst = nxt.ops[0];
										const op_t &src2 = nxt.ops[1];

										// Источник — регистр из семейства RAX
										static const char* F_RAX[] = { "rax","eax","ax","al","ah" };
										bool src_is_rax = (src2.type == o_reg) && reg_in_family(src2.reg, F_RAX, qnumber(F_RAX));

										if (src_is_rax) {
											// Запись по абсолютному адресу
											if (dst.type == o_mem) { qptr_ea = dst.addr; store_ea = n; break; }
											// Запись по RIP/EIP-relative
											else if (dst.type == o_displ) {
												if (phrase_is_ip_family(dst.phrase)) {
													qptr_ea = nxt.ea + nxt.size + dst.addr;
													store_ea = n; break;
												}
											}
										}
									}
									n = next_head(n, inf.max_ea);
								}
							}

							//    2.2 По алиасу: mov rY, rax; затем mov [mem], rY
							if (qptr_ea == BADADDR) {
								ea_t m = next_head(adr, inf.max_ea);
								int aliased = -1;   // регистр, в который переложили rax

													// ищем первую инструкцию вида mov regY, rax/eax/ax/al/ah
								for (int i = 0; i < 8 && m != BADADDR; ++i) {
									insn_t k;
									if (!decode_insn(&k, m)) break;
									if (k.ops[0].type != o_void && k.ops[1].type != o_void) {
										const op_t &d = k.ops[0];
										const op_t &s = k.ops[1];
										static const char* F_RAX[] = { "rax","eax","ax","al","ah" };
										bool s_is_rax = (s.type == o_reg) && reg_in_family(s.reg, F_RAX, qnumber(F_RAX));
										if (s_is_rax && d.type == o_reg) {
											aliased = d.reg;           // сохранили алиас
											m = next_head(m, inf.max_ea);
											break;
										}
									}
									m = next_head(m, inf.max_ea);
								}
								// а теперь ищем mov [mem|rip+disp], regY
								for (int i = 0; i < 16 && m != BADADDR && aliased != -1; ++i) {
									insn_t k;
									if (!decode_insn(&k, m)) break;
									if (k.ops[0].type != o_void && k.ops[1].type != o_void) {
										const op_t &d = k.ops[0];
										const op_t &s = k.ops[1];
										if (s.type == o_reg && s.reg == aliased) {
											if (d.type == o_mem) { qptr_ea = d.addr; store_ea = m; break; }
											else if (d.type == o_displ) {
												if (phrase_is_ip_family(d.phrase)) {
													qptr_ea = k.ea + k.size + d.addr; store_ea = m; break;
												}
											}
										}
									}
									m = next_head(m, inf.max_ea);
								}
							}

							//    2.3 Резервный путь: по тексту дизассемблера (редко, но иногда выручает).
							//        Просто ищем ближайший "mov ..." где справа регистр из семейства RAX.
							if (qptr_ea == BADADDR) {
								ea_t t = next_head(adr, inf.max_ea);
								for (int i = 0; i < 8 && t != BADADDR; ++i) {
									insn_t ins; if (!decode_insn(&ins, t)) break;
									qstring dl; generate_disasm_line(&dl, t, GENDSM_REMOVE_TAGS);
									if (dl.find("mov") != qstring::npos) {
										if (dl.find(", rax") != qstring::npos || dl.find(", eax") != qstring::npos ||
											dl.find(", ax") != qstring::npos || dl.find(", al") != qstring::npos ||
											dl.find(", ah") != qstring::npos)
										{
											if (ins.ops[0].type == o_mem) { qptr_ea = ins.ops[0].addr; store_ea = t; break; }
											if (ins.ops[0].type == o_displ) {
												if (phrase_is_ip_family(ins.ops[0].phrase)) {
													qptr_ea = ins.ea + ins.size + ins.ops[0].addr; store_ea = t; break;
												}
											}
											store_ea = t; // хотя бы отметим место
										}
									}
									t = next_head(t, inf.max_ea);
								}
							}

							// 3) Применение: имя p_<API> (или p_gpa_<EA>), тип указателя на void(void), комментарий.
							if (qptr_ea != BADADDR)
							{
								// Если пока нет строки api_name, попробуем добрать её по имени метки у api_name_ea.
								if (api_name.empty() && api_name_ea != BADADDR) {
									qstring lbl;
									if (get_name(&lbl, api_name_ea) > 0) {
										api_name = clean_label_to_api(lbl);
									}
								}

								// Если по адресу уже есть имя вида p_* — не трогаем (считаем, что уже обработано).
								qstring old;
								if (get_name(&old, qptr_ea) > 0) {
									if (old.length() >= 2 && old[0] == 'p' && old[1] == '_')
										goto dynimport_done;
								}

								// Сформируем нормализованную часть имени:
								// если api_name пуст — генерим запасной "gpa_<call_ea>", иначе — очищаем от недопустимых символов.
								qstring norm = api_name;
								if (norm.empty()) {
									norm.sprnt("gpa_%a", adr);
								}
								else {
									for (auto &ch : norm) {
										unsigned char uch = (unsigned char)ch;
										if (!(isalnum(uch) || ch == '_')) ch = '_';
									}
								}
								qstring newname; newname.sprnt("p_%s", norm.c_str());

								// В лог — аккуратно (с круглыми скобками вокруг адреса) — чтобы Message window не ошибался.
								// Если api_name пуст, вставляем «AddIPAddress» как placeholder, но имя переменной формируется из norm.
								msg("DYNIMPORT hit: name=\"%s\" -> (%a)\n",
									api_name.empty() ? "AddIPAddress" : api_name.c_str(),
									qptr_ea);

								// Создаём/пересоздаём элемент данных под указатель (qword/dword по разрядности базы).
								del_items(qptr_ea, DELIT_SIMPLE, sizeof(uval_t));
#if __EA64__
								create_data(qptr_ea, dt_qword, 8, BADNODE);
#else
								create_data(qptr_ea, dt_dword, 4, BADNODE);
#endif
								// Ставим имя (без validate_name, чтобы не триггерить ошибки; SN_NOWARN — без предупреждений).
								set_name(qptr_ea, newname.c_str(), SN_NOWARN);

								// Тип: «указатель на функцию с неизвестным прототипом», но максимально совместимый:
								// void (*)(void). Задаём через TInfo API, без parse_decl (во избежание "Bad declaration").
								{
									tinfo_t t_void;
									t_void.create_simple_type(BT_VOID);   // <— ключ для IDA 7.6 вместо create_void()

									func_type_data_t ftd;
									ftd.cc = CM_CC_UNKNOWN;               // вызываемая конвенция неизвестна — это ок для «общего» указателя
									ftd.rettype = t_void;                 // возвращаемый тип void
																		  // аргументы не задаём (пустой список): эквивалент «(void)»

									tinfo_t t_func;
									t_func.create_func(ftd); // тип функции
									tinfo_t t_ptr;
									t_ptr.create_ptr(t_func); // указатель на функцию

									set_tinfo(qptr_ea, &t_ptr);
								}

								// Комментарий в IDA к ячейке: «DYNIMPORT: GetProcAddress("...")»
								qstring cmt;
								if (api_name.empty())
									cmt.sprnt("DYNIMPORT: GetProcAddress(\"%s\")", "AddIPAddress");
								else
									cmt.sprnt("DYNIMPORT: GetProcAddress(\"%s\")", api_name.c_str());
								set_cmt(qptr_ea, cmt.c_str(), true);
							}
						}
					}
				dynimport_done:;
					}
				// --- [DYNIMPORT NAMER] end ---


				
				// --- [HEAP] begin ---
				auto is_reg_name = [&](int reg, const char* want) -> bool {
					const char *rn = ph.reg_names[reg];
					return rn && strcmp(rn, want) == 0;
				};

				// Хелпер: есть ли разыменование через указанный регистр (как базу адреса)
				auto mem_deref_by_reg = [&](const insn_t &ins, int base_reg) -> bool {
					for (int i = 0; i < UA_MAXOP && ins.ops[i].type != o_void; ++i) {
						const op_t &op = ins.ops[i];
						if (op.type == o_displ || op.type == o_phrase) {
							if (op.reg == base_reg) return true;
						}
					}
					return false;
				};

				// Найдём номера RAX/EAX (на x86/x64 один из них будет валиден)
				int REG_RAX = -1, REG_EAX = -1;
				for (int r = 0; r < ph.regs_num; ++r) {
					if (REG_RAX == -1 && is_reg_name(r, "rax")) REG_RAX = r;
					if (REG_EAX == -1 && is_reg_name(r, "eax")) REG_EAX = r;
				}
				auto is_retreg = [&](int r)->bool { return r == REG_RAX || r == REG_EAX; };

				ea_t fva = exporter->pe_instruction.func_address;

				// 1) Если alloc-call — «вооружаем» окно прямого разыменования через RAX/EAX
				if (is_alloc_call) {
					heap_window[fva] = HEAP_TOUCH_WINDOW;
					// и обнулим возможные старые алиасы — начинаем новую «цепочку» от свежего указателя
					heap_alias_window[fva].clear();
					heap_event_armed[fva] = true;   // ждём первое касание после этой аллокации

				}

				// 2) Если окно активно — ловим разыменование через RAX/EAX
				auto itw = heap_window.find(fva);
				if (itw != heap_window.end() && itw->second > 0) {
					// если в этой инструкции адрес строится от rax/eax — touch
					if ((REG_RAX >= 0 && mem_deref_by_reg(insn, REG_RAX)) ||
						(REG_EAX >= 0 && mem_deref_by_reg(insn, REG_EAX))) {
						exporter->pe_instruction.touches_heap = true;
						auto &fx = exporter->GetOrCreateFuncEffects(fva);
						++fx.heap_touches;
						// событие первого касания
						if (heap_event_armed[fva]) {
							++fx.heap_first_touch_events;
							heap_event_armed[fva] = false;
						}
						itw->second = 0; // окно отработало
					}
					else {
						--(itw->second);
						if (itw->second <= 0) heap_window.erase(itw);
					}
				}

				// 3) Заводим алиасы: mov reg, rax  |  lea reg, [rax+…]
				auto &aliases = heap_alias_window[fva];
				for (int i = 0; i < UA_MAXOP && insn.ops[i].type != o_void; ++i) {
					const op_t &dst = insn.ops[0];
					const op_t &src = insn.ops[1];

					// mov reg, rax/eax
					if (insn.itype != 0 /* быстрый гард */ &&
						dst.type == o_reg && is_retreg(src.type == o_reg ? src.reg : -1))
					{
						aliases[dst.reg] = HEAP_ALIAS_WINDOW;
						break;
					}

					// lea reg, [rax+...]
					if (insn.itype != 0 &&
						dst.type == o_reg && (src.type == o_displ || src.type == o_phrase) &&
						is_retreg(src.reg))
					{
						aliases[dst.reg] = HEAP_ALIAS_WINDOW;
						break;
					}
				}

				// 4) Если есть активные алиасы — ловим разыменование через любой из них
				if (!aliases.empty()) {
					bool touched = false;
					for (auto it = aliases.begin(); it != aliases.end(); ) {
						const int areg = it->first;
						int &ttl = it->second;

						if (ttl > 0 && mem_deref_by_reg(insn, areg)) {
							exporter->pe_instruction.touches_heap = true;
							auto &fx = exporter->GetOrCreateFuncEffects(fva);
							++fx.heap_touches;
							// событие первого касания
							if (heap_event_armed[fva]) {
								++fx.heap_first_touch_events;
								heap_event_armed[fva] = false;
							}
							
							touched = true;
							it = aliases.erase(it); // этот алиас отработал
						}
						else {
							if (ttl > 0) --ttl;
							if (ttl <= 0) { it = aliases.erase(it); }
							else { ++it; }
						}
					}

					// если потрогали — гасим прямое окно тоже (необязательно, но шум снижает)
					if (touched) {
						auto it2 = heap_window.find(fva);
						if (it2 != heap_window.end()) heap_window.erase(it2);
					}
				}
				// --- [HEAP] end ---

				// --- [RETURNS HEAP PTR] begin ---
				// Если текущая инструкция — возврат, и до него была аллокация,
				// но «первого касания» так и не случилось — считаем, что функция
				// возвращает heap-указатель наружу (transfer ownership).
				if (exporter->pe_instruction.addr_return) {
					ea_t fva = exporter->pe_instruction.func_address;
					if (heap_event_armed[fva]) {              // была свежая alloc-цепочка, касаний не зафиксировали
						auto &fx = exporter->GetOrCreateFuncEffects(fva);
						fx.returns_heap_ptr = true;           // помечаем поведение

															  // снимаем «вооружение», чтобы не сработало повторно
						heap_event_armed[fva] = false;
						heap_window.erase(fva);
						heap_alias_window[fva].clear();
					}
				}
				// --- [RETURNS HEAP PTR] end ---

				// --- [OUT-PARAM STORE] begin ---


				// \brief true, если инструкция сохраняет heap-указатель из RAX/EAX в ячейку, адрес которой строится от регистров-параметров.
				auto store_heap_to_param_slot = [&](const insn_t &ins)->bool {
					// ожидаем минимум два операнда: dst, src
					const op_t &dst = ins.ops[0];
					const op_t &src = ins.ops[1];
					// dst: [param_reg + ...]
					const bool dst_is_param_ptr = (dst.type == o_displ || dst.type == o_phrase) && IsParamReg(dst.reg);
					// src: rax/eax
					const bool src_is_retreg = (src.type == o_reg) && (
						(ph.reg_names[src.reg] && (strcmp(ph.reg_names[src.reg], "rax") == 0 || strcmp(ph.reg_names[src.reg], "eax") == 0))
						);
					// тип операции — перенос/загрузка эффективного адреса
					const bool is_mov_or_lea =
						(ins.itype != 0) && ( // быстрый гард
											  // большинство процессорных модулей кодируют MOV/LEA в itype; конкретные значения нам не нужны
							true
							);

					return is_mov_or_lea && dst_is_param_ptr && src_is_retreg;
				};

				{
					ea_t fva = exporter->pe_instruction.func_address;

					if (store_heap_to_param_slot(insn)) {
						auto &fx = exporter->GetOrCreateFuncEffects(fva);
						fx.writes_heap_to_outparam = true;

						// логично считать это «первым касанием» аллокации
						if (heap_event_armed[fva]) {
							++fx.heap_first_touch_events;
							heap_event_armed[fva] = false;
						}

						// отметим и на уровне инструкции
						exporter->pe_instruction.touches_heap = true;

						// погасим окна, чтобы не дублировать события
						heap_window.erase(fva);
						heap_alias_window[fva].clear();
					}
				}
				// --- [OUT-PARAM STORE] end ---


			}

			// присвоить в exporter->pe_instruction
			exporter->pe_instruction.reads_stack = reads_stack;
			exporter->pe_instruction.writes_stack = writes_stack;
			exporter->pe_instruction.reads_global = reads_global;
			exporter->pe_instruction.writes_global = writes_global;
			exporter->pe_instruction.sp_delta = sp_delta;
			exporter->pe_instruction.is_alloc_call = is_alloc_call;
			// touches_heap уже проставляем внутри [HEAP] при срабатывании окна

			// --- [INSTR FLAGS] end ---

			// [EFFECTS] --- begin ---
			auto &fx = exporter->GetOrCreateFuncEffects(exporter->pe_instruction.func_address);
			fx.instr_total++;
			if (exporter->pe_instruction.reads_stack)   ++fx.stack_reads;
			if (exporter->pe_instruction.writes_stack)  ++fx.stack_writes;
			if (exporter->pe_instruction.reads_global)  ++fx.global_reads;
			if (exporter->pe_instruction.writes_global) ++fx.global_writes;
			if (exporter->pe_instruction.is_alloc_call) ++fx.alloc_calls;
			if (is_free_call)                           ++fx.free_calls;

			fx.sp_delta_sum += exporter->pe_instruction.sp_delta;
			if (!fx.sp_inited) { fx.sp_delta_min = fx.sp_delta_max = exporter->pe_instruction.sp_delta; fx.sp_inited = true; }
			else {
				if (exporter->pe_instruction.sp_delta < fx.sp_delta_min) fx.sp_delta_min = exporter->pe_instruction.sp_delta;
				if (exporter->pe_instruction.sp_delta > fx.sp_delta_max) fx.sp_delta_max = exporter->pe_instruction.sp_delta;
			}
			// [EFFECTS] --- end ---

			exporter->vector_pe_instructions.emplace_back(exporter->pe_instruction);
		}

		if (mdbg)
		{
			msg("\nPE Instruction Vector size = %d \n\n", exporter->vector_pe_instructions.size());
			msg("Format Function address :: Instruction address \n\n");

			for (const auto& item : exporter->vector_pe_instructions)
			{
				msg("%llx :: %llx \n", item.func_address, item.address);
			}
		}


		msg("    Reconstructing flow graphs\n");
		std::sort(address_references.begin(), address_references.end());
		// TODO(soerenme): Remove duplicates if any.
		ReconstructFlowGraph(instructions, *flow_graph, call_graph);

		msg("    Reconstructing functions\n");
		flow_graph->ReconstructFunctions(instructions, call_graph,
			noreturn_heuristic);

		// Должна вызываться после ReconstructFunctions(), так как при этом иногда удаляются исходные базовые блоки для ребра.
		// Происходит только в том случае, если дизассемблирование в IDA основательно нарушено.
		flow_graph->PruneFlowGraphEdges();

		// Примечание: PruneFlowGraphEdges может добавлять комментарии к call_graph,
		// поэтому после этого должна выполняться пост_обработка.
		call_graph->PostProcessComments();

		msg("    IDA specific post processing\n");
		msg("        Install Function Type ... \n");

		// Постобработка с учетом специфики Ida.
		for (auto i = flow_graph->GetFunctions().begin(),
			end = flow_graph->GetFunctions().end();
			i != end; ++i) {
			Function& function = *i->second;
			const Address address = function.GetEntryPoint();

			bool address_in_set = false;

			{
				// мое дополнение снова к их коду 
				// так как все функции полученные бинэкспортом находятся в flow_graph-> мы можем
				// проверить по адресу их функции  - содержание этой функции в нашем векторе pe_func
				// и сделать отметку в поле was_checked, таким образом получим их функции и есть ли эти функции
				// у нас , или есть у нас  - но нет у них , тут уже как получится ...
				try  /* если вдруг такой функции нет в нашем мапе или векторе */
				{
					auto f_index = exporter->function_index.find(address)->second;

					// теперь по индексу в векторе изменим поле was_checked обрабатываемой функции
					exporter->function_data[f_index].was_checked = true;

					// флаг что можно использовать наши вставки в коде и такая функция есть у нас в векторе
					address_in_set = true;
				}
				catch (...)
				{
					msg("        Error  ->  When getting a function Ida, in vector wasn't find  function address %llx \n", address);
				}

			}

			// - установить имя функции
			const std::string name = GetName(address, true);
			if (!name.empty()) {
				auto dem_name = GetDemangledName(address);
				function.SetName(name, dem_name);
				if (dem_name != name)
				{
					// получим размангленное имя функции если оно отличается от мангленного
					// по идее нужно сразу в начале обработки ставить оба имени как имя и размангленное имя
					// что мы и делаем в фаиле start_window.cpp функция  ExportIdbAdditional ...
					// теперь в этом месте если размангленное отличается  - получать структуру функции в векторе
					// и менять поле dem_name на dem_name имя функции
					// exporter.pe_func.dem_name = dem_name

					/* проверочные сообщения  - сравниваем имя функции и ищем ее по индексу в екторе и получаем так же ее имя
					если имена и адреса равны  - все правильно написано ...
					msg("Demangled Name function %s =  %s\n", name.c_str(), dem_name.c_str());
					msg("In Vector FNAME = %s \n",exporter->function_data[exporter->function_index[address]].name.c_str());
					*/

					// получим индекс рассматриваемой функции в векторе по ее адресу в мапе
					if (address_in_set)
					{
						auto f_index = exporter->function_index.find(address)->second;

						// теперь по индексу в векторе изменим поле dem_name обрабатываемой функции
						// ранее в фаиле start_window.cpp функция  ExportIdbAdditional - ему было задано значение name функции ...
						// так как если имя не заманглено - размангленное имя равно просто имени 
						exporter->function_data[f_index].dem_name = dem_name;
					}



				}

			}
			// - установить тип функции

			const func_t* ida_func = get_func(address);

			if (ida_func) {

				// получим флаг от бинэкспорта после его реконструкций ,
				// чтобы сравнить с нашим , в случае разницы - доверимся данным гугла ...
				auto bin_export_flags = ida_func->flags;

				// получим наши ранее сохраненные в векторе флаги https://cplusplus.com/reference/map/map/find/
				ulonglong ida_flags = {};

				if (address_in_set)
				{
					ida_flags = exporter->function_data[exporter->function_index.find(address)->second].func_flag;
				}



				// получим данные записанные нами ранее из данных предоставленных Ida ...


				if ((ida_func->flags & FUNC_THUNK)  // отдавать предпочтение thunk над library
					&& function.GetBasicBlocks().size() == 1 &&
					(*function.GetBasicBlocks().begin())->GetInstructionCount() == 1) {
					function.SetType(Function::TYPE_THUNK);

					// проверочное сообщение ...
					// тут тоже сделаем проверку  - по адресу получим индекс функции в векторе и выведем ее флаги
					// в данном месте должен быть флаг THUNK
					/*
					 msg("Function::TYPE_THUNK has flags = %s \n", exporter->function_data[exporter->function_index[address]].func_flags.c_str());
					 */
					if (ida_flags != bin_export_flags)
					{
						exporter->ChangeFunctionFlags(address, bin_export_flags);
						// если функция смены флага не вернула func_new_flags = "false"
						if (exporter->func_new_flags != "false")
						{
							msg("            BinExport Change Function Flags (FUNC_THUNK) FROM    %s    TO    %s    FOR the function %llx \n",
								exporter->func_old_flags.c_str(), exporter->func_new_flags.c_str(), address);
							// после вывода сообщения сбросим значения переменных
							exporter->func_old_flags = "";
							exporter->func_new_flags = "";
						}

					}

				}
				else if (ida_func->flags & FUNC_LIB) {
					function.SetType(Function::TYPE_LIBRARY);

					// проверочное сообщение ...
					// в данном месте должен быть флаг  LIBRARY
					/*
					msg("Function::TYPE_LIBRARY has flags = %s \n", exporter->function_data[exporter->function_index[address]].func_flags.c_str());
					msg("Function::TYPE_LIBRARY has address = %x and flags = %x , from vector function address = %x and flags  = %x \n",
						address, ida_func->flags,
						exporter->function_data[exporter->function_index[address]].address,
						exporter->function_data[exporter->function_index[address]].func_flag);
					 */
					if (ida_flags != bin_export_flags)
					{

						exporter->ChangeFunctionFlags(address, bin_export_flags);
						if (exporter->func_new_flags != "false")
						{
							msg("            BinExport Change Function Flags (FUNC_LIB) FROM    %s    TO   %s    FOR the function %llx \n",
								exporter->func_old_flags.c_str(), exporter->func_new_flags.c_str(), address);
							// после вывода сообщения сбросим значения переменных
							exporter->func_old_flags = "";
							exporter->func_new_flags = "";
						}
					}
				}
			}


			const std::string module = GetModuleName(address, modules);
			if (!module.empty()) {
				function.SetType(Function::TYPE_IMPORTED);
				function.SetModuleName(module);
				// msg("Name module %s =  \n", module.c_str());
			}
			if (function.GetType(true) == Function::TYPE_NONE ||
				function.GetType(false) == Function::TYPE_STANDARD) {
				if (function.GetBasicBlocks().empty()) {
					function.SetType(Function::TYPE_IMPORTED);
				}
				else {
					function.SetType(Function::TYPE_STANDARD);
				}
			}
			types.CreateFunctionPrototype(function);
		}

		msg("        Install Function Type Finish ... \n");


		const auto processing_time = absl::Seconds(timer.elapsed());
		timer.restart();

		msg("    Writing data to containers or file ... \n");

		//SB::DumpWriter dw("iphlpapiDebug.txt");
		auto ignore_error(writer->WriteAdditional(*call_graph, *flow_graph, *instructions,
			*exporter, &type_system, address_space));
		// было реализовано ранее ...
		//auto ignore_error(writer->Write(*call_graph, *flow_graph, *instructions,address_references, &type_system, address_space));

		Operand::EmptyCache();
		Expression::EmptyCache();

		const auto writing_time = absl::Seconds(timer.elapsed());
		msg("%s : %s processing %s  writing\n",
			GetModuleName().c_str(),
			HumanReadableDuration(processing_time).c_str(),
			HumanReadableDuration(writing_time).c_str());
		//LOG(INFO) << absl::StrCat(
		//    GetModuleName(), ": ", HumanReadableDuration(processing_time),
		//    " processing, ", HumanReadableDuration(writing_time), " writing");
	}


}  // namespace security::binexport

