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

#ifndef X86_NOP_H_
#define X86_NOP_H_

#include <cstddef>

#include "third_party/absl/strings/string_view.h"

		///\n
/// Возвращает true, если инструкция, начинающаяся с первого байта в "bytes", является инструкцией NOP.
/// NOP были взяты из ассемблера GNU i386_align_code() (в файле tc-i386.c).
/// Подробнее см. b/24084521#comment7
bool IsNopX86(absl::string_view bytes);

#endif  // X86_NOP_H_
