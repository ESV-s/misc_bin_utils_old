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

#ifndef UTIL_IDB_EXPORT_H_
#define UTIL_IDB_EXPORT_H_

#include <memory>
#include <vector>

#include "third_party/absl/status/status.h"
#include "third_party/absl/status/statusor.h"
#include "third_party/absl/strings/string_view.h"
#include "third_party/absl/synchronization/mutex.h"
#include "third_party/zynamics/binexport/types.h"

namespace security::binexport {

// File extensions for the files used by the IdbExporter.
constexpr const char kBinExportExtension[] = ".BinExport";
constexpr const char kIdbExtension[] = ".idb";
constexpr const char kIdbExtension64[] = ".i64";

		///\n
/// Экспорт баз данных IDA Pro в формат BinExport v2.\n
/// Если было добавлено несколько баз данных,\n
/// экспортируется до num_threads параллельно.
class IdbExporter {
 public:
  struct Options {
    Options& set_export_dir(std::string value) {
      export_dir = std::move(value);
      return *this;
    }

    Options& set_ida_dir(std::string value) {
      ida_dir = std::move(value);
      return *this;
    }

    Options& set_num_threads(int value) {
      num_threads = value;
      return *this;
    }

    Options& set_alsologtostderr(bool value) {
      alsologtostderr = value;
      return *this;
    }

    Options& set_log_filename(std::string value) {
      log_filename = std::move(value);
      return *this;
    }

    Options& set_x86_noreturn_heuristic(bool value) {
      x86_noreturn_heuristic = value;
      return *this;
    }

    std::string export_dir;  ///<\n Каталог для экспорта файлов
    std::string ida_dir;     ///<\n Каталог установки IDA Pro
    int num_threads = 1;
    bool alsologtostderr = false;
    std::string log_filename;
    bool x86_noreturn_heuristic = false;
  };

  explicit IdbExporter(Options options) : options_(std::move(options)) {}

  void AddDatabase(std::string path);

  ///\n
  /// Экспорт базы данных Ida ...\n
  /// Выполняет экспорт базы данных, вызывая progress после каждой базы данных с указанием\n 
  /// текущего статуса ошибки. Если progress возвращает false, то процесс экспорта\n
  /// останавливается.
  absl::Status Export(
      std::function<bool(const absl::Status& status,
                         const std::string& idb_path, double elapsed_sec)>
          progress = nullptr);

 private:
  Options options_;
  absl::Mutex queue_mutex_;
  std::vector<std::string> idb_paths_ ABSL_GUARDED_BY(queue_mutex_);
};

		///\n
/// Возвращает список баз данных IDA Pro, которые необходимо экспортировать по пути (нерекурсивный).\n
/// При наличии двух баз данных с одинаковым именем предпочтение будет отдано 64-битной (т.е. имеющей расширение .i64).\n
/// Если параметр existing_binexports не равен nullptr, то в него добавляются существующие файлы .BinExport.\n
/// Возвращаемые списки не имеют префикса path и гарантированно дизъюнктивны по базовым именам файлов.\n
/// Примечание: Эта функция обрабатывает расширения файлов без учета их регистра,\n
/// чтобы хорошо работать на файловых системах, где это может быть проблемой (обычно это Windows и macOS).
absl::StatusOr<std::vector<std::string>> CollectIdbsToExport(
    absl::string_view path, std::vector<std::string>* existing_binexports);

}  // namespace security::binexport

#endif  // UTIL_IDB_EXPORT_H_
