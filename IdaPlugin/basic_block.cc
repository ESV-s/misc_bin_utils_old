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

#include "third_party/zynamics/binexport/basic_block.h"

#include <iomanip>
#include <ostream>

#include "third_party/zynamics/binexport/call_graph.h"

BasicBlock::Cache BasicBlock::cache_;

void BasicBlockInstructions::AddInstruction(
	Instructions::iterator instruction) {
	auto last_range = ranges_.end();
	if (last_range != ranges_.begin() && instruction == (--last_range)->end()) {
		*last_range = InstructionRange(last_range->begin(), last_range->end() + 1);
	}
	else {
		ranges_.emplace_back(instruction, instruction + 1);
	}
}

BasicBlock* BasicBlock::Create(BasicBlockInstructions* instructions) {
	using Iterator = NestedIterator<
		typename BasicBlockInstructions::InstructionRanges::const_iterator>;

	auto ranges_end = instructions->ranges_.end();
	Iterator instruction_first(instructions->ranges_.begin(), ranges_end);
	if (instruction_first == Iterator(ranges_end)) {
		return nullptr;
	}

	// Создайте BasicBlock позже, если он здесь еще не существует.
	//auto [entry, found] = cache_.emplace(instruction_first->GetAddress(),nullptr /* no BasicBlock */);
	//if (!found) {
	//  return nullptr;
	//}



	auto val = cache_.emplace(instruction_first->GetAddress(), nullptr /* no BasicBlock */);
	auto found = std::get<1>(val);
	auto entry = std::get<0>(val);


	if (!found) {
		return nullptr;
	}

	auto& ptr = entry->second;
	ptr.reset(new BasicBlock(instructions));
	instructions->Clear();
	return ptr.get();
}

void BasicBlock::Render(std::ostream* stream, const CallGraph& call_graph,
	const FlowGraph& flow_graph) const {
	for (const auto& instruction : *this) {
		*stream << std::hex << std::setfill('0') << std::uppercase << std::setw(8)
			<< instruction.GetAddress() << " ";
		_RPT0(0, "BasicBlock::Render::1\n");
		instruction.Render(stream, flow_graph);
		std::pair<Comments::const_iterator, Comments::const_iterator> comments =
			call_graph.GetComments(instruction.GetAddress());

		if (comments.first != comments.second) {
			for (; comments.first != comments.second; ++comments.first) {
				*stream << "  // " << *comments.first->comment_ << "\n";
			}
		}
		else {
			*stream << std::endl;
		}
	}
}


void BasicBlock::RenderAdditional(std::ostream* stream,
	const CallGraph& call_graph,
	const FlowGraph& flow_graph,
	Exporter& exporter) const {
#ifdef _DEBUG
	*stream << "		Start render basic block BasicBlock::RenderAdditional";
#endif
	// начинаем рендерить базовые блоки функции ...
	// получим количество инструкций в базовом блоке 
	const auto ins_count = this->GetInstructionCount();
	*stream << "    has " << ins_count << "  instructions \n";

	for (const auto& instruction : *this) {

#ifdef _DEBUG
		*stream << "IA = ";
#endif
		// получаем адрес инструкции
		*stream << std::hex << std::setfill('0') << std::uppercase << std::setw(8)
			<< instruction.GetAddress() << " ";

		// рендерим инструкцию дальше 
		instruction.RenderAdditional(stream, flow_graph, exporter);

		std::pair<Comments::const_iterator, Comments::const_iterator> comments =
			call_graph.GetComments(instruction.GetAddress());

		if (comments.first != comments.second) {
			for (; comments.first != comments.second; ++comments.first) {
				*stream << "  // " << *comments.first->comment_ << "\n";
			}
		}
		else {
			*stream << std::endl;

		}

	}

#ifdef _DEBUG
	// закончили рендерить базовый блок функции ...
	*stream << "		Finish render basic block BasicBlock::RenderAdditional\n";
#endif	

}

int BasicBlock::GetInstructionCount() const {
	int count = 0;
	for (const auto& r : ranges_) {
		count += r.size();
	}
	return count;
}

BasicBlock::InstructionConstIterator BasicBlock::GetInstruction(
	Address address) const {
	// Это O(n) на диапазонах, однако обычно диапазон должен быть только один.
	for (auto range = ranges_.begin(), ranges_end = ranges_.end();
		range != ranges_end; ++range) {
		if (address >= range->begin()->GetAddress() &&
			address <= (range->end() - 1)->GetAddress()) {
			auto it(::GetInstructionFromRange(*range, address));
			if (it != range->end()) {
				assert(address == it->GetAddress());
				return InstructionConstIterator(range, ranges_end, it);
			}
		}
	}
	return end();
}

BasicBlock::RangeConstIterator BasicBlock::BeforeEndRange() const {
	auto last = ranges_.before_begin();
	// Это O(n) на диапазонах, однако обычно диапазон должен быть только один.
	for (auto range(ranges_.begin()), ranges_end(ranges_.end());
		range != ranges_end; ++range) {
		++last;
	}
	return last;
}
