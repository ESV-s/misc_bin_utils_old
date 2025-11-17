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

#ifndef FLOWGRAPH_H_
#define FLOWGRAPH_H_

#include <cstdint>
#include <map>
#include <tuple>

#include "third_party/absl/container/btree_map.h"
#include "third_party/absl/container/node_hash_set.h"
#include "third_party/zynamics/binexport/edge.h"
#include "third_party/zynamics/binexport/function.h"
#include "third_party/zynamics/binexport/instruction.h"

class Exporter;
class CallGraph;

class FlowGraph {
 public:
	 // Максимальное количество базовых блоков/ребер/инструкций, которое мы хотим разрешить для одной функции.
	 // Если функция имеет больше этого числа, мы просто отбрасываем ее как недействительную.
	 // Ограничение kMaxFunctionEarlyBasicBlocks оценивается перед объединением bb,
	 // поэтому его значение устанавливается относительно kMaxFunctionBasicBlocks
	 enum {
    kMaxFunctionBasicBlocks = 5000,
    kMaxFunctionEarlyBasicBlocks = kMaxFunctionBasicBlocks + 1000,
    kMaxFunctionEdges = 5000,
    kMaxFunctionInstructions = 20000
  };

  enum class NoReturnHeuristic { kNopsAfterCall, kNone };
  ///\n
  /// Адрес инструкции, номер операнда, идентификатор выражения
  using Ref = std::tuple<Address, uint8_t, int>;
  using Substitutions = absl::btree_map<Ref, const std::string*>;  // Заказано
  using Edges = std::vector<FlowGraphEdge>;

  FlowGraph() = default;

  FlowGraph(const FlowGraph&) = delete;
  FlowGraph& operator=(const FlowGraph&) = delete;

  ~FlowGraph();

  void AddEdge(const FlowGraphEdge& edge);
  const Edges& GetEdges() const { return edges_; }
  const Function* GetFunction(Address address) const;
  Function* GetFunction(Address address);
  Functions& GetFunctions() { return functions_; }
  const Functions& GetFunctions() const { return functions_; }
  ///\n
  /// Прослеживает поток кода от каждой точки входа в функцию и создает базовые блоки и функции.\n
  /// Если хоть одна инструкция в базовом блоке будет выполнена, то будут выполнены все.\n
  /// Это означает, что базовые блоки заканчиваются, если:
  /// - инструкция является ветвлением
  /// - инструкция является целью ветвления
  /// - инструкция является целью вызова (точкой входа в функцию)
  /// - инструкция следует за вызовом и является недействительной (предполагается, что вызов невозвратный)
  /// - инструкция является точкой ресинхронизации, т.е. последовательность
  /// пересекающихся инструкций вновь сливается в текущей.\n
  /// Примечание: Сохраняйте пространство имен detego, обычные "Instructions" конфликтуют с IDA.
  void ReconstructFunctions(
      detego::Instructions* instructions, CallGraph* call_graph,
      NoReturnHeuristic noreturn_heuristic = NoReturnHeuristic::kNopsAfterCall);

  void PruneFlowGraphEdges();
  void AddExpressionSubstitution(Address address, uint8_t operator_num,
                                 int expression_id,
                                 const std::string& substitution);
  const Substitutions& GetSubstitutions() const { return substitutions_; }

  ///\n
  /// Первое: Пометьте все инструкции как недействительные.\n
  /// Во-вторых: пометьте инструкции, на которые все еще ссылаются, как действительные.\n
  /// \n
  /// Устанавливает FLAG_INVALID для всех инструкций, на которые больше не ссылается ни один базовый блок.\n
  /// Заметим, что мы не можем легко удалить инструкции из вектора.\n
  /// так как они хранятся по значению и на них ссылаются другие.\n
  /// Примечание: Сохраняйте пространство имен detego, простое "Instructions" конфликтует с IDA.
  void MarkOrphanInstructions(detego::Instructions* instructions) const;

  void Render(std::ostream* stream, const CallGraph& call_graph) const;
  void RenderAdditional(std::ostream* stream, const CallGraph& call_graph,
	  Exporter& exporter) const;
	
 private:
	 ///\n
	 /// Поиск невозвратных вызовов. Мы просто считаем, что любой вызов,\n за которым следует недопустимая инструкция\n
	 /// или инструкцией многобайтовой подстановки (nop), является невозвратным.\n
	 ///\n
	 /// Возвращает вектор адресов инструкций, начинающих новые базовые блоки.\n 
	 /// Это касается случаев, когда конец базового блока вызывается извне базового блока,\n
	 ///т.е. ветвлениями или вызовами в последовательности инструкций.
  std::vector<Address> FindBasicBlockBreaks(
      detego::Instructions* instructions, CallGraph* call_graph,
      NoReturnHeuristic noreturn_heuristic);
  ///\n
  /// Следит за потоком от каждой точки входа в функцию\n
  /// и собирает глобальный "суп" из базовых блоков.\n
  /// Пока не привязан ни к одной функции.
  void CreateBasicBlocks(detego::Instructions* instructions,
                         CallGraph* call_graph,
                         NoReturnHeuristic noreturn_heuristic);

  /// Объединяет базовые блоки, если:\n
  /// 1) исходный базовый блок имеет ровно 1 выходной край\n
  /// 2) целевой базовый блок имеет ровно 1 внутренний край\n
  /// 3) исходный базовый блок != целевой базовый блок\n
  /// 4) целевой базовый блок != точка входа функции (мы хотим оставить это нетронутым)\n
  void MergeBasicBlocks(const CallGraph& call_graph);
  void FinalizeFunctions(CallGraph* call_graph);

  Edges edges_;
  Functions functions_;
  Substitutions substitutions_;
  absl::node_hash_set<std::string> string_cache_;
};

#endif  // FLOWGRAPH_H_
