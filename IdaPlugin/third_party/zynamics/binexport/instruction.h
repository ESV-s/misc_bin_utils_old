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

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <ostream>
#include <string>
#include <vector>

#include "third_party/absl/container/node_hash_set.h"
#include "third_party/zynamics/binexport/operand.h"
#include "third_party/zynamics/binexport/range.h"

#include "exporter.h"

class FlowGraph;
class AddressSpace;
class Exporter;

enum {
	FLAG_NONE = 0,

	///\n
/// »спользуетс€ в основном цикле разборки: адрес инструкции уже посещен.
FLAG_VISITED = 1 << 0,

///\n
/// Ёто инструкци€ потока, и она продолжает выполнение следующей (в отличие от jmps или call).\n
/// TODO(soerenme)  ак заметил olonho@, этот флаг используетс€ несколько непоследовательно во всей кодовой базе.\n
/// Ќам следует использовать следующее определение: если флаг установлен,\n
/// то выполнение гарантированно переходит к следующей инструкции.\n
/// “.е. ветвлени€ и переключени€ не имеют его установки. ¬ызовы могут быть, а могут и не быть,\n
/// в зависимости от того, возвращаютс€ ли они.
FLAG_FLOW = 1 << 1,

///\n
/// Ёта инструкци€ уже экспортирована (используетс€ в программе написани€ базы данных).
FLAG_EXPORTED = 1 << 2,

		///\n
/// Ёта инструкци€ €вл€етс€ ветвью, условной или безусловной.\n
/// ¬ насто€щее врем€ устанавливаетс€ только Bea.\n
/// Ќамеренно имеет то же значение, что и FLAG_EXPORTED, поскольку оба они используютс€ в изолированных\n
/// и независимых контекстах и могут быть сброшены/забыты после использовани€.\n
FLAG_BRANCH = 1 << 2,

		///\n
/// »нструкци€ соответствовала подпис€м в библиотеке.
FLAG_LIB = 1 << 3,

		///\n
/// Ёта инструкци€ недействительна.
FLAG_INVALID = 1 << 4,

		///\n
/// Ёта инструкци€ €вл€етс€ вызовом.
FLAG_CALL = 1 << 5,

		///\n
/// ѕо этому адресу начинаетс€ или switch таблица или vtable.
FLAG_TABLE_START = 1 << 6,

		///\n
/// Ёта инструкци€ €вл€етс€ инструкцией NOP.
FLAG_NOP = 1 << 7,

		///\n
/// Ёта инструкци€ €вл€етс€ точкой входа.
FLAG_ENTRY_POINT = 1 << 8,
};

#pragma pack(push, 1)
class Instruction {
public:
	using GetBytesCallback = std::function<std::string(const Instruction&)>;
	using StringCache = absl::node_hash_set<std::string>;

	explicit Instruction(Address address, Address next_instruction = 0,
		uint16_t size = 0, const std::string& mnemonic = "",
		const Operands& operands = Operands());
	Instruction& operator=(const Instruction&);
	Instruction(const Instruction&);
	~Instruction();

	static const std::string* CacheString(const std::string& value);
	static void SetBitness(int bitness);
	static int GetBitness();
	static void SetGetBytesCallback(GetBytesCallback callback);
	static void SetMemoryFlags(AddressSpace* flags);
	static void SetVirtualMemory(AddressSpace* virtual_memory);
	static bool IsNegativeValue(int64_t value);

	uint8_t GetOperandCount() const;
	Operands::iterator begin() const;
	Operands::iterator end() const;
	Operands::const_iterator cbegin() const;
	Operands::const_iterator cend() const;
	const Operand& GetOperand(int index) const;
	// TODO(cblichmann): Remove these again as part of improving the overall API
	//                   of this class.
	const Operand& GetFirstOperand() const;
	const Operand& GetSecondOperand() const;
	const Operand& GetThirdOperand() const;

	Address GetAddress() const;
	int GetSize() const;
	Address GetNextInstruction() const;
	void SetNextInstruction(Address address);
	const std::string& GetMnemonic() const;
	std::string GetBytes() const;
	uint16_t GetInDegree() const;
	void AddInEdge();
	void Render(std::ostream* stream, const FlowGraph& flow_graph) const;
	void RenderAdditional(std::ostream* stream, const FlowGraph& flow_graph, Exporter& exporter) const;
	
	bool IsFlow() const;
	bool IsExported() const;
	static bool IsExported(Address address);
	void SetExported(bool exported);
	void SetFlag(uint8_t flag, bool value);
	bool HasFlag(uint8_t flag) const;

private:
	static int instance_count_;
	static StringCache string_cache_;
	static Operands operands_;
	static int bitness_;
	static GetBytesCallback get_bytes_callback_;
	static AddressSpace* flags_;
	static AddressSpace* virtual_memory_;

	const std::string* mnemonic_;  ///<\n 4|8 + overhead in stringcache
	Address address_;              ///<\n 8
	uint32_t operand_index_;       ///<\n 4 + overhead in operand pointer vector
	uint8_t operand_count_;        ///<\n 1
	uint16_t in_degree_;  ///<\n 2 TODO(cblichmann): in-degree count in edges.
	uint8_t size_;        ///<\n 1
};
#pragma pack(pop)

		///\n
/// TODO(cblichmann): ”далите этот хак. ќн находитс€ здесь потому, что IDA определ€ет одноименную глобальную переменную.
namespace detego {
	using Instructions = std::vector<Instruction>;
}  // namespace detego
using namespace detego;  // NOLINT

using InstructionRange = Range<detego::Instructions>;

void SortInstructions(detego::Instructions* instructions);
Instructions::const_iterator GetInstructionFromRange(
	const InstructionRange& range, Address address);
Instructions::iterator GetInstructionFromRange(InstructionRange* range,
	Address address);
Instructions::iterator GetInstruction(detego::Instructions* instructions,
	Address address);
Instructions::iterator GetNextInstruction(detego::Instructions* instructions,
	Instructions::iterator instruction);
std::string RenderOperands(const Instruction& instruction,
	const FlowGraph& flow_graph);
std::string RenderOperandsAdditional(const Instruction& instruction,
	const FlowGraph& flow_graph, Exporter& exporter);


#endif  // INSTRUCTION_H_
