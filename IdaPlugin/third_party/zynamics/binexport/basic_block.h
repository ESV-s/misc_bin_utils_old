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

#ifndef BASIC_BLOCK_H_
#define BASIC_BLOCK_H_

#include <forward_list>
#include <iosfwd>
#include <memory>
#include <map>
#include <vector>
#undef max

#include "third_party/absl/container/btree_map.h"
#include "third_party/zynamics/binexport/instruction.h"
#include "third_party/zynamics/binexport/nested_iterator.h"
#include "third_party/zynamics/binexport/range.h"
#include "third_party/zynamics/binexport/types.h"

#include "exporter.h"

class CallGraph;
class FlowGraph;
class BasicBlock;

class Exporter;

/**
 * \brief \n Этот класс используется для инициализации BasicBlocks.\n
 * Для хранения диапазонов в нем используется вектор, а не связный список,\n
 * таким образом, диапазоны могут быть добавлены и контейнер\n
 * может быть очищен без особых накладных расходов.
 */
class BasicBlockInstructions {
public:
	friend class BasicBlock;

	/**
	 * \brief \n Добавляет инструкцию по итератору.\n
	 * Итератор может быть использован для хранения инструкции и последующего доступа к ней.\n
	 * Для экземпляра данного класса итератор должен ссылаться\n
	 * на один и тот же контейнер Instructions в каждом вызове.\n
	 * 
	 */
	void AddInstruction(Instructions::iterator instruction);
	void Clear() { ranges_.clear(); }

private:
	using InstructionRanges = std::vector<InstructionRange>;
	InstructionRanges ranges_;
};

using BasicBlocks = std::vector<BasicBlock*>;

#pragma pack(push, 1)
class BasicBlock {
private:

	/**
	 * \brief \n Важно: Это должен быть отсортированный контейнер.
	 */
	using Cache = absl::btree_map<Address, std::unique_ptr<BasicBlock>>;

	/**
	 * \brief \n В большинстве случаев на один базовый блок приходится только один InstructionRange.\n
	 * Исключение составляют перекрывающиеся инструкции и добавляемые базовые блоки.\n
	 * Связный список используется потому, что он имеет наименьшие затраты памяти при наличии только одного элемента.
	 */
	using InstructionRanges = std::forward_list<InstructionRange>;
	using RangeIterator = InstructionRanges::iterator;
	using RangeConstIterator = InstructionRanges::const_iterator;

public:
	using InstructionIterator = NestedIterator<RangeIterator>;
	using InstructionConstIterator = NestedIterator<RangeConstIterator>;

	/**
	 * \brief \n Копирование запрещено во избежание глубокого копирования контейнера ranges_.
	 */
	BasicBlock(const BasicBlock&) = delete;
	const BasicBlock& operator=(const BasicBlock&) = delete;

	///\n
	/// Возвращает базовый блок по адресу entry_point_address.
	static BasicBlock* Find(Address entry_point_address) {
		const auto pivot(cache_.find(entry_point_address));
		if (pivot != cache_.end() &&
			pivot->second->GetEntryPoint() == entry_point_address) {
			return pivot->second.get();
		}
		return nullptr;
	}

	///\n
	/// Возвращает базовый блок, содержащий адрес, если таковой имеется.
	static BasicBlock* FindContaining(Address address) {
		auto pivot(cache_.lower_bound(address));
		if (pivot != cache_.end() && pivot->second->GetEntryPoint() == address) {
			return pivot->second.get();
		}

		///\n
		/// Мы не нашли базового блока по адресу. Далее мы ищем базовый блок, содержащий адрес.\n
		/// Мы стараемся делать это эффективно. Базовые блоки не обязательно имеют\n
		/// строго возрастающие адреса (из-за слияния или перекрытия базовых блоков),\n
		/// поэтому нам необходимо выполнить исчерпывающий поиск. Однако мы знаем,\n
		/// что наиболее вероятное местоположение совпадения будет находиться где-то\n
		/// в непосредственной близости от адреса, поэтому мы выполняем поиск от точки поворота наружу.\n
		/// Перед итерацией всех инструкций базового блока мы также проверяем сначала последний адрес.\n
		/// Это объясняется тем, что большинство вызовов будут искать либо адрес точки входа,\n
		/// либо адрес точки выхода базового блока.
		Cache::reverse_iterator left(pivot);
		Cache::iterator right(pivot);
		for (; left != cache_.rend() || right != cache_.end();) {
			if (left != cache_.rend()) {
				const auto* basic_block = left->second.get();
				if (basic_block->GetLastAddress() == address ||
					basic_block->GetInstruction(address) != basic_block->end()) {
					return left->second.get();
				}
				++left;
			}
			if (right != cache_.end()) {
				const auto* basic_block = right->second.get();
				if (basic_block->GetLastAddress() == address ||
					basic_block->GetInstruction(address) != basic_block->end()) {
					return right->second.get();
				}
				++right;
			}
		}
		return nullptr;
	}

	///\n
	/// Возвращает nullptr, если инструкция пуста\n или если в той же точке входа уже существует блок.\n
	static BasicBlock* Create(BasicBlockInstructions* instructions);

	static void DestroyCache() { Cache().swap(cache_); }

	static Cache& blocks() { return cache_; }

	void set_id(int id) { id_ = id; }
	int id() const { return id_; }

	///\n
	/// Реализованы begin() и end() для поддержки циклов, основанных на диапазоне.\n
	/// Флаги инструкций могут быть изменены, для этого также необходим неконстантный доступ.
	InstructionIterator begin() {
		return InstructionIterator(ranges_.begin(), ranges_.end());
	}
	///\n
	/// Реализованы begin() и end() для поддержки циклов, основанных на диапазоне.\n
	/// Флаги инструкций могут быть изменены, для этого также необходим неконстантный доступ.
	InstructionIterator end() { return InstructionIterator(ranges_.end()); }
	///\n
	/// Реализованы begin() и end() для поддержки циклов, основанных на диапазоне.\n
	/// Флаги инструкций могут быть изменены, для этого также необходим неконстантный доступ.
	InstructionConstIterator begin() const {
		return InstructionConstIterator(ranges_.begin(), ranges_.end());
	}
	///\n
	/// Реализованы begin() и end() для поддержки циклов, основанных на диапазоне.\n
	/// Флаги инструкций могут быть изменены, для этого также необходим неконстантный доступ.
	InstructionConstIterator end() const {
		return InstructionConstIterator(ranges_.end());
	}

	InstructionConstIterator GetInstruction(Address address) const;
	Address GetLastAddress() const {
		auto last(BeforeEndRange());
		return ((last->end() - 1)->GetAddress());
	}
	Address GetEntryPoint() const {
		auto entry_point(begin());
		return entry_point->GetAddress();
	}

	void AppendBlock(const BasicBlock& other) { Append(&other.ranges_); }

	int GetInstructionCount() const;
	void Render(std::ostream* stream, const CallGraph& call_graph,
		const FlowGraph& flow_graph) const;

	void RenderAdditional(std::ostream* stream, const CallGraph& call_graph,
		const FlowGraph& flow_graph, Exporter& exporter ) const;

private:
	explicit BasicBlock(BasicBlockInstructions* instructions) : id_(-1) {
		Append(&instructions->ranges_);
	}

	template <typename Container>
	void Append(Container* other_ranges) {
		auto last(BeforeEndRange());

		for (auto& other_range : *other_ranges) {
			if (!other_range.empty()) {
				last = ranges_.insert_after(last, other_range);
			}
		}
	}

	RangeConstIterator BeforeEndRange() const;

	static Cache cache_;

	/**
	* \brief \n Осторожно: это может оказаться непостоянным для общих базовых блоков.\n
	*/
	int id_;
	InstructionRanges ranges_;
};
#pragma pack(pop)

#endif  // BASIC_BLOCK_H_
