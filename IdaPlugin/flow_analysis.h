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

#ifndef IDA_FLOW_ANALYSIS_H_
#define IDA_FLOW_ANALYSIS_H_

#include "third_party/absl/container/btree_map.h"
#include "third_party/zynamics/binexport/call_graph.h"
#include "third_party/zynamics/binexport/entry_point.h"
#include "third_party/zynamics/binexport/expression.h"
#include "third_party/zynamics/binexport/flow_graph.h"
#include "names.h"
#include "third_party/zynamics/binexport/instruction.h"
#include "third_party/zynamics/binexport/writer.h"

#include "third_party/zynamics/binexport/dump_writer.h"

#include "exporter.h"

namespace security::binexport {

// TODO(cblichmann): Use CacheString
using ModuleMap = absl::btree_map<Address, std::string>;


/**
 * \brief \n Creates a map "function address" -> "module name"\n
 * \return ModuleMap modules;
 * \n\n
 */
ModuleMap InitModuleMap();

void AnalyzeFlowIda(EntryPoints* entry_points, const ModuleMap& modules,
                    Writer* writer, detego::Instructions* instructions,
                    FlowGraph* flow_graph, CallGraph* call_graph,
                    FlowGraph::NoReturnHeuristic noreturn_heuristic);
	
void AnalyzeFlowIdaAdditional(EntryPoints* entry_points, const ModuleMap& modules,
	DumpWriter* writer, detego::Instructions* instructions,
	FlowGraph* flow_graph, CallGraph* call_graph,
	FlowGraph::NoReturnHeuristic noreturn_heuristic,
	Exporter* exporter);  // »«Ã≈Õ≈ÕŒ ·˚ÎÓ Writer* writer ÒÚ‡ÎÓ DumpWriter* writer

}  // namespace security::binexport

#endif  // IDA_FLOW_ANALYSIS_H_
