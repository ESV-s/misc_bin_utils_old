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

#ifndef UTIL_PROCESS_H_
#define UTIL_PROCESS_H_

#include <string>
#include <vector>

#include "third_party/absl/status/status.h"
#include "third_party/absl/status/statusor.h"
#include "third_party/absl/strings/string_view.h"
#include "third_party/zynamics/binexport/types.h"

namespace security::binexport {

	///\n
/// Возвращает последнюю ошибку OS в виде строки.
	std::string GetLastOsError();

	///\n
/// Устанавливает содержимое переменной окружения для текущего процесса.\n
/// Если значение пустое, то переменная не будет установлена. В случае успеха возвращает true.
	bool SetEnvironmentVariable(const std::string& name, const std::string& value);

	///\n
/// Порождает процесс и ожидает его завершения.\n
/// argv: Вектор с аргументами командной строки, первым элементом которого должно быть имя файла образа процесса.\n
/// При успехе эта функция возвращает код выхода процесса, если wait был true.\n
/// Если wait был ложным, то при успехе возвращается ноль.
	absl::StatusOr<int> SpawnProcessAndWait(const std::vector<std::string>& argv);

	///\n
/// Подобно SpawnProcessAndWait, но не дожидается завершения дочернего процесса.
	absl::Status SpawnProcess(const std::vector<std::string>& argv);

	///\n
/// Возвращает каталог данных приложения для конкретной платформы,\n
/// который представляет собой путь, доступный для записи каждому пользователю.\n
/// Если каталог не существует, функция пытается его создать.\n
/// При вызове с командой "BinDiff" возвращается один из этих путей:\n
///   OS       Typical value\n
///   ------------------------------------------------------\n
///   Windows  C:\Users\<User>\AppData\Roaming\BinDiff\n
///            %AppData%\BinDiff\n
///   Linux    /home/<User>/.bindiff\n
///   macOS    /Users/<User>/Library/Application Support/BinDiff
	absl::StatusOr<std::string> GetOrCreateAppDataDirectory(
		absl::string_view product_name);

	///\n
	/// Возвращает каталог данных приложения для конкретной платформы.\n
	/// Обычно это не записываемый путь.\n
	/// Возвращает один из этих путей при вызове с командой "BinDiff":\n
///   OS       Typical value\n
///   ------------------------------------------------------\n
///   Windows  C:\ProgramData\BinDiff\n
///            %ProgramData%\BinDiff\n
///   Linux    /etc/opt/bindiff\n
///   macOS    /Library/Application Support/BinDiff
	absl::StatusOr<std::string> GetCommonAppDataDirectory(
		absl::string_view product_name);

}  // namespace security::binexport

#endif  // UTIL_PROCESS_H_
