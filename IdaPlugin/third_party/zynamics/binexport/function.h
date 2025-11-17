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

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <cstdint>

#include "third_party/absl/container/btree_map.h"
#include "third_party/absl/container/node_hash_set.h"
#include "third_party/zynamics/binexport/basic_block.h"
#include "third_party/zynamics/binexport/edge.h"
#include "third_party/zynamics/binexport/types.h"

#include "exporter.h"

class CallGraph;
class Function;
class FlowGraph;

class Exporter;

using Functions = absl::btree_map<Address, Function*>;

class Function {
public:
	using Edges = std::vector<FlowGraphEdge>;

	enum FunctionType : uint8_t {
		TYPE_NONE = 123,
		TYPE_STANDARD = 0,
		TYPE_LIBRARY = 1,
		TYPE_IMPORTED = 2,
		TYPE_THUNK = 3,
		TYPE_INVALID = 4,
	};

	enum Name {
		MANGLED = 0,
		DEMANGLED = 1,
	};

	static const char* GetTypeName(FunctionType type);

	explicit Function(Address entry_point);

	Function(const Function&) = delete;
	Function& operator=(const Function&) = delete;

	~Function();
	///\n
	/// Удалить основные блоки и грани, но оставить точку входа и название.
	void Clear();

	void AddBasicBlock(BasicBlock* basic_block);
	void AddEdge(const FlowGraphEdge& edge);
	void SortGraph();
	void FixEdges();
	///\n
	/// Возвращает набор ребер цикла, определенный алгоритмом\n
	/// Dominator Tree от Lengauer и Tarjan.\n
	/// Ребра будут возвращены отсортированными по адресу источника,\n
	/// что соответствует порядку их хранения в самом графе.
	void GetBackEdges(std::vector<Edges::const_iterator>* back_edges) const;

	Address GetEntryPoint() const;

	void SetType(FunctionType type);

	///\n
	/// Получить тип функции ...\n
	/// Возвращает тип функции (если он назначен) как есть, если значение raw равно true.\n
	/// Если raw равен false или функции не был присвоен тип,\n
	/// применяется дополнительная эвристика;\n
	/// возврат TYPE_THUNK для функций с адресом точки входа 0,\n
	/// THUNK_IMPORTED, если она не имеет базовых блоков, и TYPE_STANDARD в противном случае.\n
	/// TODO(cblichmann): Разделить на две функции: GetType() и GetRawType().
	FunctionType GetType(bool raw) const;

	bool IsImported() const;

	std::string GetModuleName() const;
	void SetModuleName(const std::string& name);
	void SetName(const std::string& name, const std::string& demangled_name);
	std::string GetName(Name type) const;
	bool HasRealName() const;

	const Edges& GetEdges() const;
	const BasicBlocks& GetBasicBlocks() const;
	const BasicBlock* GetBasicBlockForAddress(Address address) const;

	void Render(std::ostream* stream, const CallGraph& call_graph,
		const FlowGraph& flow_graph) const;

	void RenderAdditional(std::ostream* stream, const CallGraph& call_graph,
		const FlowGraph& flow_graph, Exporter& exporter) const;
	
	int GetLibraryIndex() const { return library_index_; }

	void SetLibraryIndex(int library_index) { library_index_ = library_index; }

	double GetMdIndex() const { return md_index_; }
	void SetMdIndex(double md_index) { md_index_ = md_index; }

private:
	int GetBasicBlockIndexForAddress(Address address) const;
	BasicBlock* GetMutableBasicBlockForAddress(Address address);

	using StringCache = absl::node_hash_set<std::string>;
	static StringCache string_cache_;
	static int instance_count_;

	Address entry_point_;
	BasicBlocks basic_blocks_;
	Edges edges_;
	std::string name_;
	std::string demangled_name_;
	const std::string* module_name_;
	FunctionType type_;
	int library_index_;
	double md_index_;
};

#endif  // FUNCTION_H_
