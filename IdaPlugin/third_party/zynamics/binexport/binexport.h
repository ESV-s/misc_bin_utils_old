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

// This file provide a set of commonly used utility functions to work with
// BinExport2 protos.

#ifndef BINEXPORT_H_
#define BINEXPORT_H_

#include <vector>

#include "third_party/zynamics/binexport/binexport2.pb.h"
#include "third_party/zynamics/binexport/types.h"

		///\n
/// В этом пространстве имен собраны функции, которые работают непосредственно\n
/// с буферами протокола BinExport2, подобно классу, в котором есть только статические методы.
namespace security::binexport {
	
		///\n
	/// Возвращает адрес инструкции. Заботится об инструкциях без адреса\n
	/// (например, являющихся частью непрерывного цикла инструкций).\n
	/// Прерывает процесс с фатальной ошибкой, если для инструкции не найден адрес.\n
	/// Заметим, что это должно происходить при хорошо сформированном proto BinExport2.\n
	/// Если указанный индекс выходит за границы, то поведение не определено.
Address GetInstructionAddress(const BinExport2& proto, int index);

		///\n
/// Как и GetInstructionAddress, но возвращает адреса всех инструкций в BinExport2 proto.\n
/// Эта функция более эффективна, чем многократный вызов GetInstructionAddress() в цикле.\n
/// Компромисс заключается в том, что возвращаемый вектор будет хранить все адреса,\n
/// в отличие от самого BinExport2 proto, который хранит только начало непрерывного выполнения инструкций.
std::vector<Address> GetAllInstructionAddresses(const BinExport2& proto);

}  // namespace security::binexport

#endif  // BINEXPORT_H_
