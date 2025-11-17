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

#include "third_party/zynamics/binexport/call_graph.h"

#include <algorithm>
#include <iomanip>
#include <iterator>
#include <ostream>


#include "debug_log.h"
#include "third_party/zynamics/binexport/hash.h"
#include "third_party/zynamics/binexport/flow_graph.h"


namespace {

	bool EdgeFunctionIsNull(const EdgeInfo& edge) { return edge.function_ == 0; }

	bool AreDuplicateRegularComments(const Comment& lhs, const Comment& rhs) {
		return lhs.address_ == rhs.address_ && lhs.type_ == Comment::REGULAR &&
			rhs.type_ == Comment::REGULAR;
	}

}  // namespace

CallGraph::StringCache CallGraph::string_cache_;
int CallGraph::instance_count_ = 0;

// Attention: do _not_ use source_basic_block_id for sorting!
// We change that after putting EdgeInfos in a set!
bool operator<(const EdgeInfo& one, const EdgeInfo& two) {
	if (one.source_ != two.source_) {
		return one.source_ < two.source_;
	}

	if (one.function_ != two.function_) {
		return one.function_->GetEntryPoint() < two.function_->GetEntryPoint();
	}

	return one.target_ < two.target_;
}

bool operator==(const EdgeInfo& one, const EdgeInfo& two) {
	return one.function_ == two.function_ && one.source_ == two.source_ &&
		one.target_ == two.target_;
}

int i = 0;

void CallGraph::Render(std::ostream* stream,
	const FlowGraph& flow_graph) const {
	TRACE_FN();
	_RPT0(0, "Function list from CallGraph::Render::1 function \n");
	i = 0;
	for (const auto& function_address : functions_) {
		const Function* function = flow_graph.GetFunction(function_address);

		*stream << std::hex << std::setfill('0') << std::uppercase << std::setw(8)
			<< function_address << " " << std::setfill(' ') << std::setw(8)
			<< (function->GetType(false) != Function::TYPE_STANDARD
				? Function::GetTypeName(function->GetType(false))
				: "")
			<< " " << function->GetModuleName()
			<< (function->GetModuleName().empty() ? "" : ".")
			<< function->GetName(Function::DEMANGLED);
		i++;
		_RPT5(0, " %x %s %s %s %s \n",
			function_address,
			(function->GetType(false) != Function::TYPE_STANDARD ? Function::GetTypeName(function->GetType(false)) : ""),
			function->GetModuleName().c_str(),
			function->GetName(Function::DEMANGLED).c_str(),
			(function->GetModuleName().empty() ? "" : "."));

		int library_index = function->GetLibraryIndex();
		if (library_index != -1) {
			const auto& library = library_manager_.GetKnownLibrary(library_index);
			*stream << " from "
				<< (library.IsStatic() ? "static" : "dynamic")
				<< " library " << library.name;

			_RPT1(0, "CallGraph::Render::2 function  \n library = %s \n", library.name.c_str());
		}
		// Предпочтите "\n" вместо endl при вызове в цикле, так как std::endl каждый раз сбрасывает поток.
		*stream << "\n";

	}

	_RPT1(0, "CallGraph::Render - Function list finish with %d functions\n", i);
	i = 0;
	_RPT0(0, "CallGraph::Render::3 Function edges start\n");
	for (const auto& edge : edges_) {
		i++;
		const Function* function = flow_graph.GetFunction(edge.target_);
		*stream << std::hex << std::setfill('0') << std::uppercase << std::setw(8)
			<< edge.function_->GetEntryPoint() << ":" << std::hex
			<< std::setfill('0') << std::uppercase << std::setw(8)
			<< edge.source_ << " -> " << std::hex << std::setfill('0')
			<< std::uppercase << std::setw(8) << edge.target_ << "    "
			<< edge.function_->GetName(Function::DEMANGLED) << " -> "
			<< (function ? function->GetName(Function::DEMANGLED) : "") << "\n";

		_RPT5(0, " %x : %x  ->  %x  %s  -> %s \n",
			edge.function_->GetEntryPoint(),
			edge.source_,
			edge.target_,
			edge.function_->GetName(Function::DEMANGLED).c_str(),
			(function ? function->GetName(Function::DEMANGLED) : "").c_str());

	}
	_RPT1(0, "CallGraph::Render::3 Function edges finish with %d \n", i);
	i = 0;
}

void CallGraph::RenderAdditional(std::ostream* stream,
	const FlowGraph& flow_graph,
	Exporter& exporter) const {

	TRACE_FN();
	
	// создадим строковые переменные , и они будут пустые для релиза
	// а для дебага назначим им значения
	// в релизе вместо них будет пусто а в дебаге будет текст
	// по которому мы определим какая переменная и что обозначает !!

	std::string fa{}; // функции адрес
	std::string ft{}; // функции тип
	std::string fmn{}; // функции модуля неим
	std::string fmnne{}; // функции модуля неим не пустой
	std::string fnd{}; // функции имя DEMANGLED
	std::string kl{}; // едж KnownLibrary
	std::string ln{}; // либрари неим



	std::string eep = {}; // entry point
	std::string esrc = {}; // edge source
	std::string etgt = {}; //  edge.target_ 
	std::string efn = {}; // edge.function_->GetName
	std::string ffn = {}; // function ? function->GetName


#ifdef _DEBUG
	*stream << "\n		Start output CallGraph::RenderAdditional for functions_ " << "\n";

	fa = "FA ";
	ft = "FT ";
	fmn = "FMN ";
	fnd = " FND ";
	fmnne = " FMNNE ";
	kl = " KL ";
	ln = " LN ";

	eep = "EEP ";
	esrc = " ESRC ";
	etgt = "ETRT ";
	efn = "EFN ";
	ffn = " FFN ";

#endif


	for (const auto& function_address : functions_) {
		const Function* function = flow_graph.GetFunction(function_address);

		auto func_type = (function->GetType(false) != Function::TYPE_STANDARD ? Function::GetTypeName(function->GetType(false)) : "");
		auto func_module_name = function->GetModuleName();
		auto func_name = function->GetName(Function::DEMANGLED);

		*stream << fa << std::hex << std::setfill('0') << std::uppercase << std::setw(8)
			<< function_address << " " << ft << std::setfill(' ') << std::setw(8)
			<< func_type
			<< " " << fmn << func_module_name
			<< (function->GetModuleName().empty() ? "" : fmnne + ".") // " FMNNE ." изменено  - ранее было просто    '"."'
			<< fnd << func_name;


		int library_index = function->GetLibraryIndex();
		if (library_index != -1) {
			const auto& library = library_manager_.GetKnownLibrary(library_index);
			*stream << kl << " from "
				<< (library.IsStatic() ? "static" : "dynamic")
				<< " library " << ln << library.name;
		}
		// Предпочтите "\n" вместо endl при вызове в цикле, так как std::endl каждый раз сбрасывает поток.
		*stream << "\n";
		// далее добавляем полученные данные в наши мапы ... №№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№
		auto &m = exporter.local_func_address;
		if (m.find(function_address) != m.end()) {
			// found
		}
		else
		{
			exporter.import_func_address[function_address] = func_name;
		}

		// конец добавляем полученные данные в наши мапы ... №№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№№
	}
#ifdef _DEBUG

	*stream << "\n		Finish output CallGraph::RenderAdditional for functions_ " << "\n";
	*stream << "\n		Start output CallGraph::RenderAdditional for edges_ " << "\n";

#endif



	for (const auto& edge : edges_) {
		const Function* function = flow_graph.GetFunction(edge.target_);

		*stream << eep << std::hex << std::setfill('0') << std::uppercase << std::setw(8)
			<< edge.function_->GetEntryPoint() << ":" << esrc << std::hex
			<< std::setfill('0') << std::uppercase << std::setw(8)
			<< edge.source_ << " -> " << etgt << std::hex << std::setfill('0')
			<< std::uppercase << std::setw(8) << edge.target_ << "    "
			<< efn << edge.function_->GetName(Function::DEMANGLED) << " -> "
			<< (function ? ffn + function->GetName(Function::DEMANGLED) : "") << "\n";

	}
#ifdef _DEBUG
	*stream << "\n		Finish output CallGraph::RenderAdditional for edges_ " << "\n";
#endif	

	}


CallGraph::CallGraph() { ++instance_count_; }

CallGraph::~CallGraph() {
	--instance_count_;
	if (instance_count_ == 0) {
		StringCache{}.swap(string_cache_);
	}
}

const std::string* CallGraph::CacheString(const std::string& text) {
	return &*string_cache_.insert(text).first;
}

void CallGraph::AddFunction(Address address) { functions_.insert(address); }

void CallGraph::AddEdge(Address source, Address target) {
	edges_.push_back(EdgeInfo(0, source, target));
}

void CallGraph::ScheduleEdgeAdd(Function* function, Address source,
	Address target) {
	temp_edges_.push_back(EdgeInfo(function, source, target));
}

void CallGraph::SortEdges() { std::sort(edges_.begin(), edges_.end()); }

void CallGraph::CommitEdges() {
	std::copy(temp_edges_.begin(), temp_edges_.end(),
		std::back_inserter<Edges>(edges_));
	Edges().swap(temp_edges_);

	edges_.erase(std::remove_if(edges_.begin(), edges_.end(), EdgeFunctionIsNull),
		edges_.end());  // Удалить ребра (edges) без исходных функций. (Remove edges without source functions.)
	SortEdges();

	// Удаление дубликатов.
	edges_.erase(std::unique(edges_.begin(), edges_.end()), edges_.end());
}

int CallGraph::DeleteInvalidFunctions(FlowGraph* flow_graph) {
	// Delete all edges with invalid source or target functions.
	// Удалить все ребра (edges) с недопустимыми исходными или целевыми функциями.
	edges_.erase(
		std::remove_if(
			edges_.begin(), edges_.end(),
			[&flow_graph](const EdgeInfo& edge) {
		// The source function must exist and be valid.
		// Исходная функция должна существовать и быть действительной.
		const Function* source = edge.function_;
		if (!source || source->GetType(false) == Function::TYPE_INVALID) {
			return true;
		}

		// The target function must not exist or be valid. The "target not
		// exist" case covers calls into imported functions such as
		// operating system dlls.
		// Целевая функция не должна существовать или быть действительной.
		// Случай "целевая функция не существует" относится к вызовам импортированных функций,
		// таких как dll-библиотеки операционной системы.
		const Function* target = flow_graph->GetFunction(edge.target_);
		return target && target->GetType(false) == Function::TYPE_INVALID;
	}),
		edges_.end());

	int num_invalid_functions = 0;
	for (auto function = flow_graph->GetFunctions().begin();
		function != flow_graph->GetFunctions().end();) {
		if (function->second->GetType(false) == Function::TYPE_INVALID) {
			functions_.erase(function->first);
			delete function->second;
			// Note: btree_map<>::erase() invalidates iterators
			// Note: btree_map<>::erase() аннулирует итераторы
			function = flow_graph->GetFunctions().erase(function);
			++num_invalid_functions;
		}
		else {
			function++;
		}
	}

	return num_invalid_functions;
}

CallGraph::Edges::const_iterator CallGraph::GetEdges(Address source) const {
	EdgeInfo edge(0, source, 0);
	Edges::const_iterator i =
		std::lower_bound(edges_.begin(), edges_.end(), edge);
	return i != edges_.end() && i->source_ == source ? i : edges_.end();
}

CallGraph::FunctionEntryPoints& CallGraph::GetFunctions() { return functions_; }

const CallGraph::FunctionEntryPoints& CallGraph::GetFunctions() const {
	return functions_;
}

const CallGraph::Edges& CallGraph::GetEdges() const { return edges_; }

CallGraph::Edges& CallGraph::GetEdges() { return edges_; }
const Comments& CallGraph::GetComments() const { return comments_; }

Comments& CallGraph::GetComments() { return comments_; }

std::pair<Comments::const_iterator, Comments::const_iterator>
CallGraph::GetComments(Address address) const {
	return std::equal_range(comments_.begin(), comments_.end(),
		Comment(address, 0, nullptr, Comment::REGULAR),
		&SortComments);
}

void CallGraph::AddComment(Address address, size_t operand,
	const std::string& comment, Comment::Type type,
	bool repeatable) {
	comments_.push_back(
		Comment(address, operand, CacheString(comment), type, repeatable));
}

size_t CallGraph::GetStringReference(Address address) const {
	auto it = string_references_.find(address);
	if (it != string_references_.end()) {
		return it->second;
	}
	return 0;
}

void CallGraph::AddStringReference(Address address, const std::string& ref) {
	if (ref.empty()) {
		return;
	}

	// TODO(jduart): Concat multiple hashes.
	string_references_[address] = GetSdbmHash(ref);
}

// Fold the strings of all comments that are of type regular and share the same
// address, since the database schema doesn't allow more than one comment per
// address.
/**
 * \brief \n Сложите строки всех комментариев типа regular, имеющих один и тот же адрес,\n
 * поскольку схема базы данных не допускает более одного комментария на один адрес.
 */
void CallGraph::PostProcessComments() {
	std::stable_sort(comments_.begin(), comments_.end(), &SortComments);
	FoldComments();
}

// Removes comments with identical addresses and combines their strings but
// only if both are regular comments, since this is the only comment type that
// is actually written to the database.
// This method assumes that the comments are sorted by address.
/**
 * \brief \n Удаляет комментарии с одинаковыми адресами и объединяет их строки,\n
 * но только если оба являются обычными комментариями,\n
 * так как это единственный тип комментариев, который действительно записывается в базу данных.\n
 * В данном методе предполагается, что комментарии отсортированы по адресам.
 */
void CallGraph::FoldComments() {
	if (comments_.empty()) {
		return;
	}

	Comments::iterator first = comments_.begin();
	const Comments::iterator last = comments_.end();
	Comments::iterator result = first;
	while (++first != last) {
		if (!AreDuplicateRegularComments(*result, *first)) {
			*(++result) = *first;
		}
		else {
			std::string accumulated_comment(*result->comment_);
			while (first != last && AreDuplicateRegularComments(*result, *first)) {
				accumulated_comment.append("\n");
				accumulated_comment.append(*first->comment_);
				++first;
			}
			--first;
			result->comment_ = CacheString(accumulated_comment);
		}
	}
	comments_.erase(++result, comments_.end());
}
