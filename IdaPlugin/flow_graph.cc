// Copyright 2011-2021 Google LLC
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

#include "third_party/zynamics/binexport/flow_graph.h"

#include <algorithm>
#include <cinttypes>
#include <iterator>
#include <list>
#include <stack>
#include <unordered_map>

#include "base/logging.h"
#include "third_party/absl/container/flat_hash_set.h"
#include "third_party/absl/strings/str_cat.h"
#include "third_party/zynamics/binexport/call_graph.h"
#include "third_party/zynamics/binexport/comment.h"
#include "third_party/zynamics/binexport/virtual_memory.h"

#include "debug_log.h"

FlowGraph::~FlowGraph() {
	for (auto function : functions_) {
		delete function.second;
	}
}

void FlowGraph::Render(std::ostream* stream,
	const CallGraph& call_graph) const {
	_RPT0(0,"\nFlowGraph::Render::1 Function render Start from \n");
	for (const auto& function : functions_) {
		function.second->Render(stream, call_graph, *this);//BM->    FlowGraph::Render
		*stream << std::endl;
	}
}

void FlowGraph::RenderAdditional(std::ostream* stream,
	const CallGraph& call_graph,
	Exporter& exporter) const {
#ifdef _DEBUG
	*stream << "		Start Rendering FUNCTIONS from FlowGraph::RenderAdditional \n" ;
#endif
	for (const auto& function : functions_) {
		function.second->RenderAdditional(stream, call_graph, *this, exporter);

		*stream << "\n";
	}
}

void FlowGraph::AddEdge(const FlowGraphEdge& edge) { edges_.push_back(edge); }

const Function* FlowGraph::GetFunction(Address address) const {
	Functions::const_iterator i = functions_.find(address);
	return i != functions_.end() ? i->second : 0;
}

Function* FlowGraph::GetFunction(Address address) {
	Functions::iterator i = functions_.find(address);
	return i != functions_.end() ? i->second : 0;
}


void FlowGraph::MarkOrphanInstructions(Instructions* instructions) const {
	// Первое: Пометьте все инструкции как недействительные.
	for (auto& instruction : *instructions) {
		instruction.SetFlag(FLAG_INVALID, true);
	}
	// Во-вторых: пометьте инструкции, на которые все еще ссылаются, как действительные.
	for (auto& function : functions_) {
		for (auto* basic_block : function.second->GetBasicBlocks()) {
			for (auto& instruction : *basic_block) {
				if (instruction.GetMnemonic().empty()) {
					LOG(WARNING) << absl::StrCat(
						absl::Hex(instruction.GetAddress(), absl::kZeroPad8),
						" is reachable from function ",
						absl::Hex(function.second->GetEntryPoint(), absl::kZeroPad8),
						" basic block ",
						absl::Hex(basic_block->GetEntryPoint(), absl::kZeroPad8),
						" but invalid!");
					continue;
				}
				instruction.SetFlag(FLAG_INVALID, false);
			}
		}
	}
}

void FlowGraph::AddExpressionSubstitution(Address address, uint8_t operator_num,
	int expression_id,
	const std::string& substitution) {
	substitutions_[std::make_tuple(address, operator_num, expression_id)] =
		&*string_cache_.insert(substitution).first;
}


std::vector<Address> FlowGraph::FindBasicBlockBreaks(
	detego::Instructions* instructions, CallGraph* call_graph,
	NoReturnHeuristic noreturn_heuristic) {
	// Поиск невозвратных вызовов. Мы просто считаем, что любой вызов, за которым следует недопустимая инструкция
	// или инструкцией многобайтовой подстановки (nop), является невозвратным.
	// Обоснование инструкции nop приведено в b/24084521.
	// TODO(soerenme) Пометить целевую функцию как невозвращающуюся и использовать эту информацию для всех последующих вызовов функции,
	// даже если за этими вызовами не следует инструкция invalid или nop. 
	// Это несколько опасно, так как вводит зависимость порядка от дизассемблирования
	// - к моменту обнаружения вызова функции мы уже знаем, является ли она невозвратной или нет?
	for (auto call_instruction = instructions->begin();
		call_instruction != instructions->end(); ++call_instruction) {
		if (!call_instruction->HasFlag(FLAG_CALL)) {
			continue;
		}
		int num_nop_bytes = 0;
		auto last_nop = instructions->end();
		for (auto instruction = GetNextInstruction(instructions, call_instruction);
			instruction != instructions->end();
			instruction = GetNextInstruction(instructions, instruction)) {
			if (instruction->HasFlag(FLAG_INVALID)) {
				call_instruction->SetFlag(FLAG_FLOW, false);
				break;
			}
			if (!instruction->HasFlag(FLAG_NOP)) {
				break;
			}
			num_nop_bytes += instruction->GetSize();
			last_nop = instruction;
		}
		if (noreturn_heuristic == NoReturnHeuristic::kNopsAfterCall &&
			num_nop_bytes > 1) {
			// Однобайтовое значение nop может указывать или не указывать на невозврат вызова.
			// http://reverseengineering.stackexchange.com/questions/8030/purpose-of-nop-immediately-after-call-instruction
			call_instruction->SetFlag(FLAG_FLOW, false);

			/**
			 * \brief \n Если последний nop перетекает в инструкцию с in-степенью 1,\n
			 * то это единственный входящий поток кода и необходимо создать функцию.
			 */
			auto potential_entry_point = GetNextInstruction(instructions, last_nop);
			if (potential_entry_point->GetInDegree() == 1) {
				call_graph->AddFunction(potential_entry_point->GetAddress());
			}
		}
	}

	/**
	 * \brief \n Адреса, где должен произойти break базового блока.
	 */
	std::vector<Address> basic_block_breaks;

	// Поиск точек ресинхронизации. Как правило, на одну инструкцию должен приходиться только один входящий поток кода. 
	// За исключением случаев, когда инструкции пересекаются.
	// Точка синхронизации - это когда две такие последовательности перекрывающихся инструкций
	// в конечном итоге снова выравниваются и сливаются в один поток инструкций.
	// Мы отслеживаем только 32 байта, чтобы сохранить карту маленькой и
	// потому что инструкции x86 не могут быть больше этого размера (и, предположительно, ни один другой набор инструкций).
	// Поскольку мы делаем это глобально, не имея функций, мы можем получить базовые разрывы блоков,
	// которые не оправданы ни одной из функций в конечном дизассемблере.
	// Это досадно, но не опасно, так как разборка все равно корректна, просто с ложными гранями.
	// Замечание: здесь нельзя использовать [flat, node]_hash_map, поскольку мы повторяем итерацию по карте,
	// из которой (возможно) было удалено много элементов.
	// Это имеет сложность O(num_elements) для unordered_map,
	// но имеет сложность O(num_deleted_elements + num_elements) для остальных карт.
	// TODO(jannewger): производительность приведенного ниже алгоритма неидеальна и должна быть улучшена.
	std::unordered_map<Address, int> incoming_code_flows;
	for (const auto& instruction : *instructions) {
		const Address address = instruction.GetAddress();
		const Address flow_address = instruction.GetNextInstruction();
		for (auto it = incoming_code_flows.begin(), end = incoming_code_flows.end();
			it != end;) {
			if (it->second > 1) {
				// В эту инструкцию поступает более одного потока входящего кода ->
				// предшествующие инструкции должны были перекрываться.
				basic_block_breaks.emplace_back(it->first);
			}
			else if (it->first + 32 > address) {
				// Мы все еще находимся в пределах 32-байтового окна для текущей инструкции,
				// поэтому мы сохраняем инструкцию в карте, так как потенциально она еще может перекрываться.
				break;
			}
			it = incoming_code_flows.erase(it);
		}
		if (instruction.IsFlow()) {
			++incoming_code_flows[flow_address];
		}
	}

	// Если в последних байтах исполняемого файла был перекрывающийся код, то вышеприведенный цикл его пропустит.
	// Поэтому здесь мы работаем с этими последними байтами.
	for (const auto incoming_code_flow : incoming_code_flows) {
		if (incoming_code_flow.second > 1) {
			basic_block_breaks.emplace_back(incoming_code_flow.first);
		}
	}

	// Поиск целей ветвления.
	for (const auto& edge : edges_) {
		basic_block_breaks.emplace_back(edge.target);
	}

	// Найти адреса call инструкции (точки входа в функцию).
	for (Address entry_point : call_graph->GetFunctions()) {
		basic_block_breaks.emplace_back(entry_point);
	}

	// Сделайте базовые breaks блоков уникальными и отсортируйте их.
	std::sort(basic_block_breaks.begin(), basic_block_breaks.end());
	basic_block_breaks.erase(
		std::unique(basic_block_breaks.begin(), basic_block_breaks.end()),
		basic_block_breaks.end());

	return basic_block_breaks;
}

void FlowGraph::CreateBasicBlocks(Instructions* instructions,
	CallGraph* call_graph,
	NoReturnHeuristic noreturn_heuristic) {
	// Сортируем ребра (edges) по адресу источника.
	std::sort(edges_.begin(), edges_.end());
	call_graph->SortEdges();
	
	// При разбиении базовых блоков добавляются новые синтетические (безусловные) ребра.
	// Они будут добавлены сюда.
	Edges new_edges;

	const auto basic_block_breaks =
		FindBasicBlockBreaks(instructions, call_graph, noreturn_heuristic);

	// Сбросить флаг посещения инструкции. Каждая инструкция должна принадлежать только одному базовому блоку,
	// мы используем флаг для отслеживания этого ограничения.
	for (auto& instruction : *instructions) {
		instruction.SetFlag(FLAG_VISITED, false);
	}

	absl::flat_hash_set<Address> invalid_functions;
	// Начните с каждого известного адреса точки входа функции и следуйте по нему. 
	// Создайте новые функции и добавьте к ним базовые блоки и ребра.
	for (Address entry_point : call_graph->GetFunctions()) {
		if (GetInstruction(instructions, entry_point) == instructions->end()) {
			continue;  // Пропустить недопустимые/импортированные функции.
		}
		std::stack<Address> address_stack;
		address_stack.push(entry_point);

		const int initial_edge_number = new_edges.size();
		int current_bb_number = 0;
		int number_of_instructions = 0;
		// Вести учет базовых блоков, уже добавленных в данную функцию.
		absl::flat_hash_set<Address> function_basic_blocks;
		while (!address_stack.empty()) {
			Address address = address_stack.top();
			address_stack.pop();
			Instructions::iterator instruction =
				GetInstruction(instructions, address);
			if (instruction == instructions->end()) {
				continue;
			}
			CHECK(instruction->GetAddress() == address);
			if (!function_basic_blocks.insert(address).second) {
				// Мы уже имели дело с этим базовым блоком.
				continue;
			}
			BasicBlock* basic_block = BasicBlock::Find(address);
			if (basic_block == nullptr) {
				
				///\n
				/// Нам необходимо создать новый базовый блок.
				BasicBlockInstructions basic_block_instructions;
				int bb_instr_cnt = 0;
				bool bb_skip = false;
				do {
					if (++bb_instr_cnt > kMaxFunctionInstructions) {
						bb_skip = true;
						break;
					}
					CHECK(!instruction->HasFlag(FLAG_VISITED));
					instruction->SetFlag(FLAG_VISITED, true);
					basic_block_instructions.AddInstruction(instruction);
					instruction = GetNextInstruction(instructions, instruction);
				} while (instruction != instructions->end() &&
					!std::binary_search(basic_block_breaks.begin(),
						basic_block_breaks.end(),
						instruction->GetAddress()));
				basic_block = BasicBlock::Create(&basic_block_instructions);
				number_of_instructions += bb_instr_cnt;
				if (bb_skip) {
					LOG(WARNING) << absl::StrCat("Skipping enormous basic block: ",
						absl::Hex(address, absl::kZeroPad8));
					continue;
				}
			}
			else {
				number_of_instructions += basic_block->GetInstructionCount();
			}
			CHECK(basic_block != nullptr);
			++current_bb_number;
			// Стирает все new_edges для текущей точки входа (для экономии памяти)
			// и добавляет точку входа в список недопустимых функций,
			// которая обрабатывается позже (после всех точек входа). Этот шаг экономит память и процессор,
			// поскольку он пропускает генерацию результатов,
			// которые в противном случае были бы отброшены функцией FlowGraph::FinalizeFunctions
			if ((current_bb_number > kMaxFunctionEarlyBasicBlocks) ||
				(number_of_instructions > kMaxFunctionInstructions)) {
				if (initial_edge_number < new_edges.size()) {
					new_edges.erase(new_edges.begin() + initial_edge_number,
						new_edges.end());
				}
				invalid_functions.insert(entry_point);
				break;
			}

			// Три возможности:
			// - базовый блок заканчивается некодовой потоковой инструкцией
			// - базовый блок заканчивается инструкцией ветвления
			// - базовый блок заканчивается перед инструкцией basic_block_breaks
			CHECK(basic_block != nullptr);
			address = basic_block->GetLastAddress();
			instruction = GetInstruction(instructions, address);
			CHECK(instruction != instructions->end());
			auto edge =
				std::lower_bound(edges_.begin(), edges_.end(), address,
					[](const FlowGraphEdge& edge, Address address) {
				return edge.source < address;
			});
			if (edge != edges_.end() && edge->source == address) {
				// Инструкция ветвления.
				for (; edge != edges_.end() && edge->source == address; ++edge) {
					address_stack.push(edge->target);
				}
			}
			else if (instruction->IsFlow()) {
				
				///\n
				///  Мы должны были попасть на инструкцию basic_block_breaks.\n
				/// Добавляем синтетическое безусловное ребро ветвления к следующей инструкции.
				const Address next_address = instruction->GetNextInstruction();
				address_stack.push(next_address);
				new_edges.emplace_back(address, next_address,
					FlowGraphEdge::TYPE_UNCONDITIONAL);
			}
		}
	}

	if (!invalid_functions.empty()) {
		LOG(INFO) << "Early erase of " << invalid_functions.size()
			<< " invalid functions.";

		// Удаляем все входные базовые блоки для "недействительных" функций,
		// мы сохраняем точки входа в call_graph->functions_, чтобы позже FlowGraph::FinalizeFunctions
		// мог добавить записи "фиктивных" функций для целей вызова, которые могут быть неправильными,
		// но мы не можем определить это в данный момент.
		// Такие недействительные цели вызова будут помечены как импортированные функции в выходном binexport.
		for (const Address& addr : invalid_functions) {
			BasicBlock::blocks().erase(addr);
		}
		// Удаление всех ребер, идущих от/к недействительным_функциям. Этот шаг может быть не обязательным,
		// но он уменьшает объем данных, которые будут обрабатываться в дальнейшем.
		edges_.erase(
			std::remove_if(edges_.begin(), edges_.end(),
				[&invalid_functions](const FlowGraphEdge& edge) {
			return (invalid_functions.find(edge.source) !=
				invalid_functions.end()) ||
				(invalid_functions.find(edge.target) !=
					invalid_functions.end());
		}),
			edges_.end());
	}

	// Добавляем новые синтетические ребра.
	edges_.insert(edges_.end(), new_edges.begin(), new_edges.end());
	std::sort(edges_.begin(), edges_.end());
}

void FlowGraph::MergeBasicBlocks(const CallGraph& call_graph) {
	
	///\n
	/// На данном этапе мы создали базовые блоки, но еще не добавили ребра к функциям.\n
	/// Перед окончательным созданием функций мы сначала выполняем объединение базовых блоков.
	auto delete_edge = [this, &call_graph](const FlowGraphEdge& edge) {
		if (edge.type != FlowGraphEdge::TYPE_UNCONDITIONAL) {
			// Только безусловные ребра могут потенциально привести к слиянию.
			return false;
		}

		BasicBlock* target_basic_block = BasicBlock::Find(edge.target);
		if (!target_basic_block) {
			DLOG(INFO) << absl::StrCat("No target basic block for edge ",
				absl::Hex(edge.source, absl::kZeroPad8),
				" -> ",
				absl::Hex(edge.target, absl::kZeroPad8));
			return true;
		}

		if (target_basic_block->begin()->GetInDegree() != 1) {
			// У нас есть более чем одно ребро => не удалять.
			return false;
		}

		if (call_graph.GetFunctions().count(target_basic_block->GetEntryPoint())) {
			// Целевой target_basic_block базовый блок  является точкой входа в функцию => не удалять.
			return false;
		}

		BasicBlock* source_basic_block = BasicBlock::FindContaining(edge.source);
		if (!source_basic_block) {
			LOG(INFO) << absl::StrCat("No source basic block for edge ",
				absl::Hex(edge.source, absl::kZeroPad8),
				" -> ",
				absl::Hex(edge.target, absl::kZeroPad8));
			return true;
		}

		CHECK(source_basic_block->GetLastAddress() == edge.source);
		if (source_basic_block == target_basic_block) {
			// Это самозацикливающееся ребро => не удалять.
			return false;
		}

		auto edges = std::equal_range(
			edges_.begin(), edges_.end(), edge,
			[](const FlowGraphEdge& one, const FlowGraphEdge& two) {
			// Считать ребра эквивалентными только на основании их исходного адреса.
			return one.source < two.source;
		});
		if (std::distance(edges.first, edges.second) > 1) {
			// Существует более одного ребра, исходящего из исходного адреса. Не объединять.
			// Хотя для безусловных ребер это обычно не происходит, для синтетических ребер блока try/catch это произойдет.
			// Впервые введена для дизассемблера DEX в cl/100567062.
			CHECK(edge.source == edges.first->source);
			return false;
		}

		source_basic_block->AppendBlock(*target_basic_block);
		BasicBlock::blocks().erase(target_basic_block->GetEntryPoint());
		return true;
	};

	// Удалите все ребра, соединяющие объединенные базовые блоки.
	edges_.erase(std::remove_if(edges_.begin(), edges_.end(), delete_edge),
		edges_.end());
}

/**
 * \brief \n Теперь у нас есть глобальный "суп" из базовых блоков и ребер.\n
 * Далее нам необходимо проследить поток от каждой точки входа в функцию\n
 * и собрать список базовых блоков и ребер для каждой функции.\n
 *  При этом мы также связываем новую функцию с графом вызовов.\n
 * \param call_graph CallGraph* call_graph
 */
void FlowGraph::FinalizeFunctions(CallGraph* call_graph) {
	// Теперь у нас есть глобальный "суп" из базовых блоков и ребер.
	// Далее нам необходимо проследить поток от каждой точки входа в функцию
	// и собрать список базовых блоков и ребер для каждой функции.
	// При этом мы также связываем новую функцию с графом вызовов.
	for (Address entry_point : call_graph->GetFunctions()) {
		std::stack<Address> address_stack;
		address_stack.push(entry_point);
		std::unique_ptr<Function> function(new Function(entry_point));
		size_t num_instructions = 0;
		// Следите за базовыми блоками и ребрами, уже добавленными в эту функцию.
		absl::flat_hash_set<Address> function_basic_blocks;
		// TODO(cblichmann): Встреча одного и того же базового блока несколько раз в процессе обхода ожидаема и нормальна.
		// А вот встреча с одним и тем же ребром - нет. Это просто неэффективно - зачем мы вообще добавили это дважды?
		// В настоящее время только дизассемблер ARM выводит лишние ребра.
		absl::flat_hash_set<FlowGraphEdge, FlowGraphEdgeHash> done_edges;
		while (!address_stack.empty()) {
			Address address = address_stack.top();
			address_stack.pop();
			if (!function_basic_blocks.insert(address).second) {
				continue;  // Уже добавлено в функцию.
			}
			if (function_basic_blocks.size() >= kMaxFunctionBasicBlocks ||
				function->GetEdges().size() >= kMaxFunctionEdges ||
				num_instructions >= kMaxFunctionInstructions) {
				break;
			}
			BasicBlock* basic_block = BasicBlock::Find(address);
			if (!basic_block) {
				// Функция без тела (импортированная/недействительная)(imported/invalid).
				continue;
			}
			function->AddBasicBlock(basic_block);
			num_instructions += basic_block->GetInstructionCount();

			const auto source_address = basic_block->GetLastAddress();
			auto edge =
				std::lower_bound(edges_.begin(), edges_.end(), source_address,
					[](const FlowGraphEdge& edge, Address address) {
				return edge.source < address;
			});
			uint64_t dropped_edges = 0;
			for (; edge != edges_.end() && edge->source == source_address; ++edge) {
				if (!BasicBlock::Find(edge->target)) {
					DLOG(INFO) << absl::StrCat(
						"Dropping edge ", absl::Hex(edge->source, absl::kZeroPad8),
						" -> ", absl::Hex(edge->target, absl::kZeroPad8),
						" because the target address is invalid.");
					++dropped_edges;
					continue;
				}
				if (done_edges.insert(*edge).second) {
					function->AddEdge(*edge);
					address_stack.push(edge->target);
				}
			}
			LOG_IF(INFO, dropped_edges > 0) << absl::StrCat(
				"Dropped ", dropped_edges,
				" edges because the target address is invalid (current basic block ",
				absl::Hex(address, absl::kZeroPad8), ").");
		}
		if (function_basic_blocks.size() >= kMaxFunctionBasicBlocks ||
			function->GetEdges().size() >= kMaxFunctionEdges ||
			num_instructions >= kMaxFunctionInstructions) {
			DLOG(INFO) << absl::StrCat(
				"Discarding excessively large function ",
				absl::Hex(entry_point, absl::kZeroPad8), ": ",
				function_basic_blocks.size(), " basic blocks, ",
				function->GetEdges().size(), " edges, ", num_instructions,
				" instructions (Limit is ", kMaxFunctionBasicBlocks, ", ",
				kMaxFunctionEdges, ", ", kMaxFunctionInstructions, ")");
			function->Clear();
		}
		for (const auto* basic_block : function->GetBasicBlocks()) {
			// Итерация базового блока и добавление ребер в граф вызовов для каждой инструкции вызова.
			// Граф вызовов уже знает об адресах источника и цели, но еще не связан с функциями.
			const auto& call_edges = call_graph->GetEdges();
			for (const auto& instruction : *basic_block) {
				if (instruction.HasFlag(FLAG_CALL)) {
					auto edge = std::lower_bound(
						call_edges.begin(), call_edges.end(), instruction.GetAddress(),
						[](const EdgeInfo& edge, Address address) {
						return edge.source_ < address;
					});
					for (; edge != call_edges.end() &&
						edge->source_ == instruction.GetAddress();
						++edge) {
						call_graph->ScheduleEdgeAdd(function.get(), edge->source_,
							edge->target_);
					}
				}
			}
		}
		function->SortGraph();
		functions_.insert(std::make_pair(entry_point, function.release()));
	}

	// Они нам больше не нужны (функции хранят свою собственную копию).
	Edges().swap(edges_);
	call_graph->CommitEdges();  // Очистить временные ребра.
}

void FlowGraph::ReconstructFunctions(Instructions* instructions,
	CallGraph* call_graph,
	NoReturnHeuristic noreturn_heuristic) {
	CreateBasicBlocks(instructions, call_graph, noreturn_heuristic);
	MergeBasicBlocks(*call_graph);
	FinalizeFunctions(call_graph);
}

void FlowGraph::PruneFlowGraphEdges() {
	// Глупый шаг постобработки, но IDA иногда выдает ломаные ребра (направленные в никуда),
	// если она неправильно разобрала секцию данных.
	for (auto kv : functions_) {
		kv.second->FixEdges();
	}
}
