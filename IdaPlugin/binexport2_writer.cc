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

// New BinExport protocol buffer based file format. Should be more complete and
// more compact than the original one.
//
// Example rates for item
// 000026157fb0ada54135ef1f182585fc3edbca4769b9ea3629d6cda9161dc566:
// 1.2M Nov 15 16:37 000026.BinExport
// 199K Nov 15 16:37 000026.BinExport.gz
// 500K Nov 15 16:37 000026.BinExport2
// 107K Nov 15 16:37 000026.BinExport2.gz
//
// So the new format is smaller than the original by about a factor ~2, despite
// the fact that the original completely omitted operands! Both formats compress
// equally well by another factor of ~5.

#include "third_party/zynamics/binexport/binexport2_writer.h"

#include <algorithm>
#include <cinttypes>
#include <string>
#include <fstream>

#include "base/logging.h"
#include "third_party/absl/container/flat_hash_map.h"
#include "third_party/absl/strings/str_cat.h"
#include "third_party/absl/strings/string_view.h"
#include "third_party/absl/time/clock.h"
#include "third_party/absl/time/time.h"
#include "third_party/zynamics/binexport/binexport2.pb.h"
#include "third_party/zynamics/binexport/call_graph.h"
#include "third_party/zynamics/binexport/flow_graph.h"
#include "third_party/zynamics/binexport/function.h"
#include "third_party/zynamics/binexport/util/status_macros.h"

namespace security::binexport {
	namespace {

		/**
		 * \brief \n Сортировка по убыванию количества вхождений, затем по мнемонической строке.\n
		 * Не путать с оператором > - эта функция вызывается как оператор меньше чем.\n
		 * \param one std::pair<std::string, int32_t>
		 * \param two std::pair<std::string, int32_t>
		 * \return
		 */
		bool SortMnemonicsByOccurrenceCount(
			const std::pair<std::string, int32_t>& one,
			const std::pair<std::string, int32_t>& two) {
			if (one.second != two.second) {
				return one.second > two.second;
			}
			return one.first < two.first;
		}

		/**
		 * \brief \n Сортировка по мнемонической строке.\n
		 * \param one std::pair<std::string, int32_t>
		 * \param two std::pair<std::string, int32_t>
		 * \return
		 */
		bool SortMnemonicsAlphabetically(const std::pair<std::string, int32_t>& one,
			const std::pair<std::string, int32_t>& two) {
			return one.first < two.first;
		}

		/**
		 * \brief \n Хранит уникальные мнемоники в result proto.\n
		 * Возвращает вектор мнемоник, отсортированных по лексикографическому принципу для быстрого поиска.\n
		 * Каждой мнемонике соответствует свой индекс в массиве result proto.
		 * \param instructions
		 * \param mnemonics
		 * \param proto
		 */
		void WriteMnemonics(const Instructions& instructions,
			std::vector<std::pair<std::string, int32_t>>* mnemonics,
			BinExport2* proto) {
			// Получить гистограмму мнемоник. Отсортировать гистограмму по убыванию количества вхождений.
			// Сохранить мнемоники в буфере proto результата. Запомните индексы, присвоенные массиву proto. 
			//Сортировать вектор индексов по строке мнемоники, чтобы обеспечить быстрый бинарный поиск по строке
			//и отображения из строки в индекс.
			absl::flat_hash_map<std::string, int32_t> mnemonic_histogram;
			for (const auto& instruction : instructions) {
				if (instruction.HasFlag(FLAG_INVALID)) {
					continue;
				}
				++mnemonic_histogram[instruction.GetMnemonic()];
			}
			mnemonics->reserve(mnemonic_histogram.size());
			for (auto& mnemonic : mnemonic_histogram) {
				mnemonics->push_back(std::move(mnemonic));
			}
			std::sort(mnemonics->begin(), mnemonics->end(),
				&SortMnemonicsByOccurrenceCount);
			proto->mutable_mnemonic()->Reserve(mnemonics->size());
			for (auto& mnemonic : *mnemonics) {
				mnemonic.second = proto->mnemonic_size();  // Remember current index.
				proto->add_mnemonic()->set_name(mnemonic.first);
			}
			std::sort(mnemonics->begin(), mnemonics->end(), &SortMnemonicsAlphabetically);
		}

		/**
		 * \brief \n Перевод из внутреннего (internal) типа выражения в тип выражение,\n
		 * используемое форматом BinExport2 proto.\n
		 * \param type
		 * \return BinExport2::Expression::Type
		 */
		BinExport2::Expression::Type ExpressionTypeToProtoType(Expression::Type type) {
			switch (type) {
			case Expression::TYPE_SYMBOL:
				return BinExport2::Expression::SYMBOL;
			case Expression::TYPE_IMMEDIATE_INT:
				return BinExport2::Expression::IMMEDIATE_INT;
			case Expression::TYPE_IMMEDIATE_FLOAT:
				return BinExport2::Expression::IMMEDIATE_FLOAT;
			case Expression::TYPE_OPERATOR:
				return BinExport2::Expression::OPERATOR;
			case Expression::TYPE_REGISTER:
				return BinExport2::Expression::REGISTER;
			case Expression::TYPE_SIZEPREFIX:
				return BinExport2::Expression::SIZE_PREFIX;
			case Expression::TYPE_DEREFERENCE:
				return BinExport2::Expression::DEREFERENCE;

				// Используется только в IDA, мы отображаем их на простые SYMBOL.
			case Expression::TYPE_GLOBALVARIABLE:
			case Expression::TYPE_JUMPLABEL:
			case Expression::TYPE_STACKVARIABLE:
			case Expression::TYPE_FUNCTION:
				return BinExport2::Expression::SYMBOL;

			default:
				LOG(QFATAL) << "Invalid expression type: " << type;
				return BinExport2::Expression::IMMEDIATE_INT;  // Не достигнуто
			}
		}

		bool SortExpressionsById(const Expression* one, const Expression* two) {
			return one->GetId() < two->GetId();
		}

		/**
		 * \brief \n Сохраняет деревья выражений.
		 * \param proto BinExport2* proto
		 */
		void WriteExpressions(BinExport2* proto) {
			std::vector<const Expression*> expressions;
			expressions.reserve(Expression::GetExpressions().size());
			for (const auto& expression_cache_entry : Expression::GetExpressions()) {
				expressions.push_back(&expression_cache_entry.second);
			}
			std::sort(expressions.begin(), expressions.end(), &SortExpressionsById);

			proto->mutable_expression()->Reserve(expressions.size());
			for (const Expression* expression : expressions) {
				// В выражениях Proto используется индекс, основанный на нулях, а в выражениях C++ - на единицах.
				DCHECK_EQ(expression->GetId() - 1, proto->expression_size());
				const auto& symbol = expression->GetSymbol();
				DCHECK(!symbol.empty() || expression->IsImmediate());
				BinExport2::Expression* proto_expression(proto->add_expression());
				if (!symbol.empty()) {
					proto_expression->set_symbol(symbol);
				}
				if (expression->GetParent() != nullptr) {
					proto_expression->set_parent_index(expression->GetParent()->GetId() - 1);
				}
				if (expression->IsImmediate()) {
					proto_expression->set_immediate(expression->GetImmediate());
				}
				if (expression->IsRelocation()) {
					proto_expression->set_is_relocation(true);
				}
				const auto type = ExpressionTypeToProtoType(expression->GetType());
				if (type != BinExport2::Expression::IMMEDIATE_INT) {
					// Сохраняется только в том случае, если отличается от значения по умолчанию.
					proto_expression->set_type(type);
				}
			}
		}

		bool SortOperandsById(const Operand* one, const Operand* two) {
			return one->GetId() < two->GetId();
		}

		/**
		 * \brief \n Хранит деревья выражений (expression trees) для каждого операнда.
		 * \param proto BinExport2* proto
		 */
		void WriteOperands(BinExport2* proto) {
			std::vector<const Operand*> operands;
			operands.reserve(Operand::GetOperands().size());
			for (const auto& operand_cache_entry : Operand::GetOperands()) {
				operands.push_back(&operand_cache_entry.second);
			}
			std::sort(operands.begin(), operands.end(), &SortOperandsById);

			proto->mutable_operand()->Reserve(operands.size());
			for (const Operand* operand : operands) {
				// В выражениях Proto используется индекс, основанный на нулях, а в выражениях C++ - на единицах.
				QCHECK_EQ(operand->GetId() - 1, proto->operand_size());
				BinExport2::Operand* proto_operand(proto->add_operand());
				proto_operand->mutable_expression_index()->Reserve(
					operand->GetExpressionCount());
				const auto* previous_expression = *(operand->begin());
				for (const auto* expression : *operand) {
					QCHECK(expression->GetParent() != previous_expression->GetParent() ||
						expression->GetPosition() >= previous_expression->GetPosition());
					proto_operand->add_expression_index(expression->GetId() - 1);
					previous_expression = expression;
				}
			}
		}

		/**
		 * \brief \n Бинарный поиск заданной мнемоники. Поиск мнемоники,\n
		 *  которая на самом деле не содержится в наборе, является фатальной ошибкой.\n
		 * \param mnemonics const std::vector<std::pair<std::string, int32_t>>& mnemonics
		 * \param mnemonic  const std::string& mnemonic
		 * \return
		 */
		int32_t GetMnemonicIndex(
			const std::vector<std::pair<std::string, int32_t>>& mnemonics,
			const std::string& mnemonic) {
			const auto it = lower_bound(mnemonics.begin(), mnemonics.end(),
				std::make_pair(mnemonic, 0));
			QCHECK(it != mnemonics.end()) << "Unknown mnemonic: " << mnemonic;
			QCHECK_EQ(mnemonic, it->first);
			return it->second;
		}

		/**
		 * \brief \n Найти цели вызова для данной инструкции и сохранить их в буфере протокола.
		 * \param instruction_address instruction_address
		 * \param address_references  const AddressReferences& address_references
		 * \param proto_instruction   BinExport2::Instruction* proto_instruction
		 */
		void WriteCallTargets(Address instruction_address,
			const AddressReferences& address_references,
			BinExport2::Instruction* proto_instruction) {
			const AddressReferences::const_iterator reference =
				lower_bound(address_references.begin(), address_references.end(),
					AddressReference(instruction_address, std::make_pair(-1, -1),
						0, TYPE_CALL_DIRECT));
			for (AddressReferences::const_iterator i = reference;
				i != address_references.end() && i->source_ == instruction_address;
				++i) {
				if (!i->IsCall()) {
					continue;
				}
				proto_instruction->add_call_target(i->target_);
			}
		}

		/**
		 * \brief \n Записать инструкцию
		 * \param flow_graph const FlowGraph& flow_graph
		 * \param instructions const Instructions& instructions
		 * \param mnemonics	const std::vector<std::pair<std::string, int32_t>>& mnemonics
		 * \param address_references const AddressReferences& address_references
		 * \param instruction_indices std::vector<std::pair<Address, int32_t>>* instruction_indices
		 * \param proto	BinExport2* proto
		 */
		void WriteInstructions(
			const FlowGraph& flow_graph, const Instructions& instructions,
			const std::vector<std::pair<std::string, int32_t>>& mnemonics,
			const AddressReferences& address_references,
			std::vector<std::pair<Address, int32_t>>* instruction_indices,
			BinExport2* proto) {
			QCHECK(std::is_sorted(address_references.begin(), address_references.end()));
			proto->mutable_instruction()->Reserve(instructions.size());
			const Instruction* previous_instruction(nullptr);
			for (const Instruction& instruction : instructions) {
				if (instruction.HasFlag(FLAG_INVALID)) {
					previous_instruction = nullptr;
					continue;
				}
				instruction_indices->push_back(
					std::make_pair(instruction.GetAddress(), proto->instruction_size()));
				BinExport2::Instruction* proto_instruction(proto->add_instruction());
				QCHECK_EQ(instruction.GetSize(), instruction.GetBytes().size());
				// Записать полный адрес инструкции, если:
				// - нет предыдущей инструкции
				// - предыдущая инструкция не имеет кодового потока в текущую инструкцию
				// - предыдущая инструкция перекрывает текущую
				// - текущая инструкция является точкой входа в функцию
				if (previous_instruction == nullptr || !previous_instruction->IsFlow() ||
					previous_instruction->GetAddress() + previous_instruction->GetSize() !=
					instruction.GetAddress() ||
					flow_graph.GetFunction(instruction.GetAddress())) {
					proto_instruction->set_address(instruction.GetAddress());
				}
				proto_instruction->set_raw_bytes(instruction.GetBytes());
				if (const auto index =
					GetMnemonicIndex(mnemonics, instruction.GetMnemonic())) {
					// Сохраняется только в том случае, если отличается от значения по умолчанию.
					proto_instruction->set_mnemonic_index(index);
				}
				proto_instruction->mutable_operand_index()->Reserve(
					instruction.GetOperandCount());
				for (const auto* operand : instruction) {
					QCHECK_GT(operand->GetId(), 0);
					proto_instruction->add_operand_index(operand->GetId() - 1);
				}
				WriteCallTargets(instruction.GetAddress(), address_references,
					proto_instruction);
				previous_instruction = &instruction;
			}
			std::sort(instruction_indices->begin(), instruction_indices->end());
		}

		void WriteBasicBlocks(
			const Instructions& instructions,
			const std::vector<std::pair<Address, int32_t>>& instruction_indices,
			BinExport2* proto) {
			CHECK((instruction_indices.empty() && BasicBlock::blocks().empty()) ||
				(!instruction_indices.empty() && !BasicBlock::blocks().empty()));
			proto->mutable_basic_block()->Reserve(BasicBlock::blocks().size());
			auto instruction_index_it = instruction_indices.begin();
			int id = 0;
			for (auto& basic_block : BasicBlock::blocks()) {
				// Обычно элементы кэша не должны модифицироваться, так как изменение объектов может привести к изменению их порядка.
				// Однако здесь мы изменяем только id, что не влияет на порядок.
				BinExport2::BasicBlock proto_basic_block;
				bool basic_block_is_invalid = false;
				int begin_index = -1, end_index = -1;
				for (const auto& instruction : *basic_block.second) {
					// Весь базовый блок является недействительным, если он содержит хоть одну недействительную инструкцию.
					if (instruction.HasFlag(FLAG_INVALID)) {
						basic_block_is_invalid = true;
						break;
					}
					if (instruction_index_it == instruction_indices.end() ||
						instruction.GetAddress() != instruction_index_it->first) {
						instruction_index_it =
							lower_bound(instruction_indices.begin(), instruction_indices.end(),
								std::make_pair(instruction.GetAddress(), 0));
					}
					QCHECK(instruction_index_it != instruction_indices.end());
					QCHECK_EQ(instruction_index_it->first, instruction.GetAddress());
					const int instruction_index = instruction_index_it->second;
					++instruction_index_it;

					if (begin_index < 0) {
						begin_index = instruction_index;
						end_index = begin_index + 1;
					}
					else if (instruction_index != end_index) {
						// Последовательность нарушена, сохраните интервал.
						BinExport2::BasicBlock::IndexRange* index_range(
							proto_basic_block.add_instruction_index());
						index_range->set_begin_index(begin_index);
						if (end_index != begin_index + 1) {
							// Мы опускаем индекс конца в случае интервала в одну инструкцию.
							index_range->set_end_index(end_index);
						}
						begin_index = instruction_index;
						end_index = begin_index + 1;
					}
					else {
						// Последовательность не прерывается, запомните end_index.
						end_index = instruction_index + 1;
					}
				}
				BinExport2::BasicBlock::IndexRange* index_range(
					proto_basic_block.add_instruction_index());
				index_range->set_begin_index(begin_index);
				if (end_index != begin_index + 1) {
					// Мы опускаем конечный индекс в случае интервала в одну инструкцию.
					index_range->set_end_index(end_index);
				}
				if (!basic_block_is_invalid) {
					basic_block.second->set_id(id++);
					*proto->add_basic_block() = proto_basic_block;
				}
			}
		}

		// 
		/**
		 * \brief \n Трансляция из внутреннего типа графа потока в тип графа, используемый буфером протокола.\n
		 * \param type FlowGraphEdge::Type type
		 * \return BinExport2::FlowGraph::Edge::Type
		 */
		BinExport2::FlowGraph::Edge::Type FlowGraphEdgeTypeToProtoType(
			FlowGraphEdge::Type type) {
			switch (type) {
			case FlowGraphEdge::TYPE_TRUE:
				return BinExport2::FlowGraph::Edge::CONDITION_TRUE;
			case FlowGraphEdge::TYPE_FALSE:
				return BinExport2::FlowGraph::Edge::CONDITION_FALSE;
			case FlowGraphEdge::TYPE_UNCONDITIONAL:
				return BinExport2::FlowGraph::Edge::UNCONDITIONAL;
			case FlowGraphEdge::TYPE_SWITCH:
				return BinExport2::FlowGraph::Edge::SWITCH;
			default:
				LOG(QFATAL) << "Invalid flow graph edge type: " << type;
				return BinExport2::FlowGraph::Edge::UNCONDITIONAL;  // Не достигнуто
			}
		}

		void WriteFlowGraphs(const FlowGraph& flow_graph, BinExport2* proto) {
			proto->mutable_flow_graph()->Reserve(flow_graph.GetFunctions().size());
			for (const auto& address_to_function : flow_graph.GetFunctions()) {
				const Function& function = *address_to_function.second;
				if (function.GetBasicBlocks().empty() ||
					function.GetType(true /* raw type */) == Function::TYPE_INVALID) {
					continue;  // Пропустите пустые графы потоков, они существуют только как узлы графа вызовов.
				}

				BinExport2::FlowGraph* proto_flow_graph = proto->add_flow_graph();
				proto_flow_graph->mutable_basic_block_index()->Reserve(
					function.GetBasicBlocks().size());
				for (const BasicBlock* basic_block : function.GetBasicBlocks()) {
					if (basic_block->GetEntryPoint() == function.GetEntryPoint()) {
						proto_flow_graph->set_entry_basic_block_index(basic_block->id());
					}
					proto_flow_graph->add_basic_block_index(basic_block->id());
				}
				QCHECK_GE(proto_flow_graph->entry_basic_block_index(), 0);
				QCHECK_EQ(proto_flow_graph->basic_block_index_size(),
					function.GetBasicBlocks().size());

				std::vector<Function::Edges::const_iterator> back_edges;
				function.GetBackEdges(&back_edges);
				auto back_edge = back_edges.begin();
				proto_flow_graph->mutable_edge()->Reserve(function.GetEdges().size());
				for (const FlowGraphEdge& edge : function.GetEdges()) {
					BinExport2::FlowGraph::Edge* proto_edge = proto_flow_graph->add_edge();
					const BasicBlock* source = function.GetBasicBlockForAddress(edge.source);
					CHECK(source != nullptr);
					const BasicBlock* target = function.GetBasicBlockForAddress(edge.target);
					CHECK(target != nullptr);
					proto_edge->set_source_basic_block_index(source->id());
					proto_edge->set_target_basic_block_index(target->id());

					const auto type = FlowGraphEdgeTypeToProtoType(edge.type);
					if (type != BinExport2::FlowGraph::Edge::UNCONDITIONAL) {
						// Сохраняется только в том случае, если отличается от значения по умолчанию.
						proto_edge->set_type(type);
					}

					// Продвигаем  back edge iterator. Обратите внимание, что back edges и regular edges сортируются одинаково,
					// поэтому мы можем выполнять итерации по векторам с шагом блокировки.
					for (; back_edge != back_edges.end() &&
						(*back_edge)->source < edge.source &&
						(*back_edge)->target < edge.target;
						++back_edge) {
					}
					if (back_edge != back_edges.end() &&
						(*back_edge)->source == edge.source &&
						(*back_edge)->target == edge.target) {
						proto_edge->set_is_back_edge(true);
						++back_edge;
					}
				}
			}
		}

		/**
		 * \brief \n Переводит из внутреннего типа функции графа вызовов BinDetego \n
		 * в тип функции, используемый буфером протокола.\n
		 * \param type Function::FunctionType type
		 * \return BinExport2::CallGraph::Vertex::Type
		 */
		BinExport2::CallGraph::Vertex::Type CallGraphVertexTypeToProtoType(
			Function::FunctionType type) {
			switch (type) {
			case Function::TYPE_STANDARD:
				return BinExport2::CallGraph::Vertex::NORMAL;
			case Function::TYPE_LIBRARY:
				return BinExport2::CallGraph::Vertex::LIBRARY;
			case Function::TYPE_IMPORTED:
				return BinExport2::CallGraph::Vertex::IMPORTED;
			case Function::TYPE_THUNK:
				return BinExport2::CallGraph::Vertex::THUNK;
			case Function::TYPE_INVALID:
				return BinExport2::CallGraph::Vertex::INVALID;
			default:
				LOG(QFATAL) << "Invalid call graph vertex type: " << type;
				return BinExport2::CallGraph::Vertex::NORMAL;  // Не достигнуто
			}
		}

		/**
		 * \brief \n Сортировка по адресу\n
		 * Используется для бинарного поиска массива вершин графа вызовов для конкретной функции.\n
		 * \param one const BinExport2::CallGraph::Vertex&
		 * \param two const BinExport2::CallGraph::Vertex&
		 * \return
		 */
		bool SortByAddress(const BinExport2::CallGraph::Vertex& one,
			const BinExport2::CallGraph::Vertex& two) {
			return one.address() < two.address();
		}

		/**
		 * \brief \n Функции в исходном графе call_graph сортируются по адресу \n
		 * и последовательно добавляются в буфер протокола.\n
		 * Следовательно, мы можем осуществлять двоичный поиск по определенному адресу.\n
		 * Поиск адреса, который в действительности не содержится в графе, является фатальной ошибкой!!!
		 * \param call_graph BinExport2::CallGraph& call_graph
		 * \param address uint64_t address
		 * \return int32_t
		 */
		int32_t GetVertexIndex(const BinExport2::CallGraph& call_graph,
			uint64_t address) {
			BinExport2::CallGraph::Vertex vertex;
			vertex.set_address(address);
			const auto& it =
				std::lower_bound(call_graph.vertex().begin(), call_graph.vertex().end(),
					vertex, &SortByAddress);
			QCHECK(it != call_graph.vertex().end())
				<< "Can't find a call graph node for: "
				<< absl::StrCat(absl::Hex(address, absl::kZeroPad8));
			QCHECK_EQ(address, it->address())
				<< "Can't find a call graph node for: "
				<< absl::StrCat(absl::Hex(address, absl::kZeroPad8));
			return it - call_graph.vertex().begin();
		}

		void WriteCallGraph(const CallGraph& call_graph, const FlowGraph& flow_graph,
			BinExport2* proto) {
			BinExport2::CallGraph* proto_call_graph(proto->mutable_call_graph());
			proto_call_graph->mutable_vertex()->Reserve(flow_graph.GetFunctions().size());
			// Создать список используемых библиотек.
			std::vector<const LibraryManager::LibraryRecord*> used_libraries;
			call_graph.GetLibraryManager().GetUsedLibraries(&used_libraries);
			absl::flat_hash_map<int, int> use_index;
			for (int i = 0; i < used_libraries.size(); ++i) {
				use_index[used_libraries[i]->library_index] = i;
			}

			///\n Используется для проверки того, что функции отсортированы по адресу.\n
			uint64_t previous_entry_point_address = 0;
			absl::flat_hash_map<std::string, int32_t> module_index;
			for (const auto& function_it : flow_graph.GetFunctions()) {
				const Function& function(*function_it.second);
				QCHECK_GE(function.GetEntryPoint(), previous_entry_point_address);
				previous_entry_point_address = function.GetEntryPoint();
				QCHECK(call_graph.GetFunctions().find(function.GetEntryPoint()) !=
					call_graph.GetFunctions().end());
				BinExport2::CallGraph::Vertex* proto_function(
					proto_call_graph->add_vertex());
				proto_function->set_address(function.GetEntryPoint());
				const auto vertex_type =
					CallGraphVertexTypeToProtoType(function.GetType(false));
				if (vertex_type != BinExport2::CallGraph::Vertex::NORMAL) {
					// Сохраняется только в том случае, если отличается от значения по умолчанию.
					proto_function->set_type(vertex_type);
				}
				if (function.HasRealName()) {
					proto_function->set_mangled_name(function.GetName(Function::MANGLED));
					if (function.GetName(Function::DEMANGLED) !=
						function.GetName(Function::MANGLED)) {
						proto_function->set_demangled_name(
							function.GetName(Function::DEMANGLED));
					}
				}
				int library_index = function.GetLibraryIndex();
				if (library_index != -1) {
					// Мы сериализуем индекс использования, а не индекс библиотеки
					// (так как последний относится к массиву всех известных библиотек).
					proto_function->set_library_index(use_index[library_index]);
				}
				const std::string& module = function.GetModuleName();
				if (!module.empty()) {
					auto it = module_index.emplace(module, module_index.size());
					proto_function->set_module_index(it.first->second);
				}
			}

			if (!module_index.empty()) {
				proto->mutable_module()->Reserve(module_index.size());
				// Здесь мы имеем O(N^2) по количеству классов, что не должно быть большой проблемой.
				for (int i = 0; i < module_index.size(); ++i) {
					auto* module = proto->add_module();
					module->set_name(
						std::find_if(module_index.begin(), module_index.end(),
							[i](const std::pair<std::string, int32_t>& kv) -> bool {
								return kv.second == i;
							})
						->first);
				}
			}

			proto_call_graph->mutable_edge()->Reserve(call_graph.GetEdges().size());
			for (const EdgeInfo& edge : call_graph.GetEdges()) {
				BinExport2::CallGraph::Edge* proto_edge(proto_call_graph->add_edge());
				CHECK(edge.function_ != nullptr);
				const uint64_t source_address(edge.function_->GetEntryPoint());
				const uint64_t target_address(edge.target_);
				proto_edge->set_source_vertex_index(
					GetVertexIndex(*proto_call_graph, source_address));
				proto_edge->set_target_vertex_index(
					GetVertexIndex(*proto_call_graph, target_address));
			}

			proto->mutable_library()->Reserve(used_libraries.size());
			for (const auto* used : used_libraries) {
				auto* library = proto->add_library();
				library->set_name(used->name);
				library->set_is_static(used->IsStatic());
			}
		}

		void WriteStrings(
			const AddressReferences& address_references,
			const AddressSpace& address_space,
			const std::vector<std::pair<Address, int32_t>>& instruction_indices,
			BinExport2* proto) {
			absl::flat_hash_map<std::string, int> string_to_string_index;
			for (const auto& reference : address_references) {
				if (reference.kind_ != TYPE_DATA_STRING &&
					reference.kind_ != TYPE_DATA_WIDE_STRING) {
					continue;
				}
				// Длина строки должна быть > 0.
				if (reference.size_ == 0) {
					continue;
				}
				const auto instruction =
					lower_bound(instruction_indices.begin(), instruction_indices.end(),
						std::make_pair(reference.source_, 0));
				// Добавляем строки и ссылки на строки только в том случае,
				// если существует инструкция, фактически ссылающаяся на эту строку.
				if (instruction == instruction_indices.end() ||
					instruction->first != reference.source_) {
					continue;
				}

				std::string content;

			 /**
			  * \brief \n В случае block_size_left > reference.size_ мы, вероятно, должны проверить,\n
			  * может ли следующий блок памяти быть объединен с текущим,\n
			  * и предоставить какое-либо решение для чтения межблочных строк.
			  */
				const auto block = address_space.GetMemoryBlock(reference.target_);
				if (block == address_space.data().end()) {
					continue;
				}
				const Address block_address = reference.target_ - block->first;
				const int block_size_left = block->second.size() - block_address;
				if (reference.kind_ != TYPE_DATA_STRING) {
					continue;
				}
				content = std::string(
					reinterpret_cast<const char*>(&address_space[reference.target_]),
					std::min(reference.size_, block_size_left));

				auto it =
					string_to_string_index.try_emplace(content, proto->string_table_size());
				// Дублирование строк.
				if (it.second != false) {
					proto->add_string_table(it.first->first);
				}
				auto* proto_string_reference = proto->add_string_reference();
				proto_string_reference->set_instruction_index(instruction->second);
				proto_string_reference->set_instruction_operand_index(
					reference.source_operand_);
				proto_string_reference->set_operand_expression_index(
					reference.source_expression_);
				proto_string_reference->set_string_table_index(it.first->second);
			}
		}

		void WriteDataReferences(
			const AddressReferences& address_references,
			const AddressSpace& address_space,
			const std::vector<std::pair<Address, int32_t>>& instruction_indices,
			BinExport2* proto) {
			// Сопоставление адрес кэша -> отображение инструкции.
			absl::flat_hash_map<Address, int32_t> address_to_index;
			for (const auto& index : instruction_indices) {
				address_to_index[index.first] = index.second;
			}
			for (const auto& reference : address_references) {
				if (reference.kind_ != TYPE_DATA) {
					continue;
				}
				// Invalid reference.
				if (reference.target_ == 0) {
					continue;
				}
				const auto instruction = address_to_index.find(reference.source_);
				// Добавляйте ссылки на данные только при наличии ссылающейся инструкции.
				if (instruction == address_to_index.end()) {
					continue;
				}
				if (address_space.IsValidAddress(reference.target_)) {
					auto* proto_data_reference = proto->add_data_reference();
					proto_data_reference->set_instruction_index(instruction->second);
					proto_data_reference->set_address(reference.target_);
				}
			}
		}

		/**
		 * \brief \n Переводит из внутреннего типа комментария в тип, используемый proto BinExport2.
		 * \param type 
		 * \return 
		 */
		BinExport2::Comment::Type CommentTypeToProtoType(Comment::Type type) {
			switch (type) {
			case Comment::REGULAR:
				return BinExport2::Comment::DEFAULT;
			case Comment::ENUM:
				return BinExport2::Comment::ENUM;
			case Comment::LOCATION:
				return BinExport2::Comment::LOCATION;
			case Comment::GLOBAL_REFERENCE:
				return BinExport2::Comment::GLOBAL_REFERENCE;
			case Comment::LOCAL_REFERENCE:
				return BinExport2::Comment::LOCAL_REFERENCE;
			case Comment::STRUCTURE:
				// Not currently exported
				return BinExport2::Comment::DEFAULT;
			case Comment::ANTERIOR:
				return BinExport2::Comment::ANTERIOR;
			case Comment::POSTERIOR:
				return BinExport2::Comment::POSTERIOR;
			case Comment::FUNCTION:
				return BinExport2::Comment::FUNCTION;
			default:
				LOG(QFATAL) << "Invalid comment type: " << type;
				return BinExport2::Comment::DEFAULT;  // Not reached
			}
		}

		void WriteComments(
			const CallGraph& call_graph,
			const std::vector<std::pair<Address, int32_t>>& instruction_indices,
			BinExport2* proto) {
			absl::flat_hash_map<const std::string*, int> comment_to_index;
			for (const Comment& comment : call_graph.GetComments()) {



				auto val = comment_to_index.emplace(comment.comment_, proto->string_table_size());
				const auto new_comment_it = val.first;
				const auto inserted = val.second;

				//const auto[new_comment_it, inserted] = comment_to_index.emplace(comment.comment_, proto->string_table_size());
				if (inserted) {
					proto->add_string_table(*comment.comment_);
				}
				const auto instruction_it =
					lower_bound(instruction_indices.begin(), instruction_indices.end(),
						std::make_pair(comment.address_, 0));
				QCHECK(instruction_it != instruction_indices.end());

				const Address instruction_index = instruction_it->second;
				const int string_table_index = new_comment_it->second;

				///\n
				/// Напишите богатую структуру комментариев для BinDiff.
				const int comment_index = proto->comment_size();
				auto* proto_comment = proto->add_comment();
				proto_comment->set_instruction_index(instruction_index);
				proto_comment->set_string_table_index(string_table_index);
				proto_comment->set_type(CommentTypeToProtoType(comment.type_));
				proto_comment->set_repeatable(comment.repeatable_);

				// Код, специфичный для IDA, кодирует тип комментария в номере операнда.
				// Это связано с тем, что BinDiff внутренне добавляет все комментарии в глобальный кэш,
				// ключом которого является кортеж ((address, operand_id)-tuple).
				// Поэтому все комментарии для адреса должны иметь уникальный operand_id.
				// Не допускайте утечки этой детали реализации в записанный протобуф.
				constexpr int kMaxOp = 8;  // Same as IDA's UA_MAXOP
				int operand_num = comment.operand_num_;
				if (operand_num >= kMaxOp) {
					if (comment.type_ == Comment::GLOBAL_REFERENCE) {
						operand_num -= 1024;  // See ida/names.cc GetGlobalReferences()
					}
					else if (comment.type_ == Comment::LOCAL_REFERENCE) {
						operand_num -= 2048;  // See ida/names.cc GetLocalReferences()
					}
				}
				// Номера операндов нужно писать только в том случае, если комментарий относится к реальному операнду.
				if (operand_num >= 0 && operand_num < kMaxOp) {
					proto_comment->set_instruction_operand_index(operand_num);
				}

				// Добавить обратную ссылку на комментарий к инструкции
				proto->mutable_instruction(instruction_index)
					->add_comment_index(comment_index);
			}
		}

		void WriteSections(const AddressSpace& address_space, BinExport2* proto) {
			for (const auto& data : address_space.data()) {
				auto* section = proto->add_section();
				section->set_address(data.first);
				section->set_size(data.second.size());
				section->set_flag_r(address_space.IsReadable(data.first));
				section->set_flag_w(address_space.IsWritable(data.first));
				section->set_flag_x(address_space.IsExecutable(data.first));
			}
		}

		/**
		 * \brief \n Записывает буфер двоичного протокола в указанный файл.
		 * \param filename const std::string& filename
		 * \param proto BinExport2* proto
		 * \return 
		 */
		absl::Status WriteProtoToFile(const std::string& filename, BinExport2* proto) {
			std::ofstream stream(filename, std::ios::binary | std::ios::out);
			if (!proto->SerializeToOstream(&stream)) {
				return absl::UnknownError(
					absl::StrCat("error serializing data to: '", filename, ""));
			}
			return absl::OkStatus();
		}
	}  // namespace

	BinExport2Writer::BinExport2Writer(const std::string& result_filename,
		const std::string& executable_filename,
		const std::string& executable_hash,
		const std::string& architecture)
		: filename_(result_filename),
		executable_filename_(executable_filename),
		executable_hash_(executable_hash),
		architecture_(architecture) {}

	absl::Status BinExport2Writer::WriteToProto(
		const CallGraph& call_graph, const FlowGraph& flow_graph,
		const Instructions& instructions,
		const AddressReferences& address_references,
		const AddressSpace& address_space, BinExport2* proto) const {
		auto* meta_information = proto->mutable_meta_information();
		meta_information->set_executable_name(executable_filename_);
		meta_information->set_executable_id(executable_hash_);
		meta_information->set_architecture_name(architecture_);
		meta_information->set_timestamp(absl::ToUnixSeconds(absl::Now()));

		WriteExpressions(proto);
		WriteOperands(proto);
		{
			std::vector<std::pair<std::string, int32_t>> mnemonics;
			WriteMnemonics(instructions, &mnemonics, proto);
			std::vector<std::pair<Address, int32_t>> instruction_indices;
			WriteInstructions(flow_graph, instructions, mnemonics, address_references,
				&instruction_indices, proto);
			WriteBasicBlocks(instructions, instruction_indices, proto);
			WriteComments(call_graph, instruction_indices, proto);
			WriteStrings(address_references, address_space, instruction_indices, proto);
			// TODO(cblichmann): Write expression_substitution.
			WriteDataReferences(address_references, address_space, instruction_indices,
				proto);
		}
		WriteFlowGraphs(flow_graph, proto);
		WriteCallGraph(call_graph, flow_graph, proto);
		WriteSections(address_space, proto);

		return absl::OkStatus();
	}

	absl::Status BinExport2Writer::Write(
		const CallGraph& call_graph, const FlowGraph& flow_graph,
		const Instructions& instructions,
		const AddressReferences& address_references, const TypeSystem*,
		const AddressSpace& address_space) {
		LOG(INFO) << "Writing to: \"" << filename_ << "\".";

		BinExport2 proto;
		NA_RETURN_IF_ERROR(WriteToProto(call_graph, flow_graph, instructions,
			address_references, address_space, &proto));
		return WriteProtoToFile(filename_, &proto);
	}

}  // namespace security::binexport
