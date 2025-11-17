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

#ifndef LIBRARY_MANAGER_H_
#define LIBRARY_MANAGER_H_

#include <set>
#include <string>
#include <vector>

#include "third_party/absl/container/flat_hash_map.h"
#include "third_party/zynamics/binexport/types.h"

		///\n
/// Теория работы: данный класс хранит список известных на данный момент библиотек,\n
/// идентифицированных по имени и ссылке, а также функций и ссылок,\n
/// и поддерживает структуры, достаточные для работы со следующими API:
/// - добавление библиотеки, получение уникального целочисленного идентификатора библиотеки (если библиотека уже добавлена, то повторное использование)
/// - вспомнить, что с идентификатором библиотеки связан адрес (используется)
/// - помнить, что библиотека используется
/// - получить вектор всех библиотек, для которых существует такая ассоциация
/// - привязать адрес к функции без явного ее использования
/// - записывать ссылку между двумя адресами и извлекать цель по источнику
///\n Менеджер библиотек различает известные и используемые функции и библиотеки.
///\n  Известная библиотека/функция просто регистрируется в менеджере, но мы не утверждаем, что она используется текущим анализируемым элементом.\n
/// Используемая библиотека/функция явно ссылается на анализируемый элемент.
class LibraryManager {
public:
	enum class Linkage { kDynamic, kStatic };
	enum class UpdateKind { kNoUpdate, kUpdateUsedLibraries };

	struct LibraryRecord {
		LibraryRecord(const std::string& name, Linkage linkage, int library_index)
			: name(name), linkage(linkage), library_index(library_index) {}

		bool IsStatic() const { return linkage == Linkage::kStatic; }

		bool Equals(const LibraryRecord& other) const {
			// We compare name and linkage to check equality, library index is not
			// relevant.
			return (name == other.name) && (linkage == other.linkage);
		}

		std::string name;
		Linkage linkage;
		int library_index;
	};

	struct FunctionInfo {
		FunctionInfo() = default;

		FunctionInfo(const std::string& module_name,
			const std::string& function_name, int library_index)
			: module_name(module_name),
			function_name(function_name),
			library_index(library_index) {}
		
		///\n
		/// Это не то же самое, что библиотека, поскольку модули могут иметь более мелкую детализацию,\n
		/// например, DEX использует имя класса как имя_модуля, а библиотека - это DEX\n
		/// или JAR-файл, содержащий несколько классов.
		std::string module_name;
		std::string function_name;
		int library_index = -1;
	};

	LibraryManager() = default;
	
		///\n
	/// Присваивает заданному имени библиотеки целочисленный индекс. Если он уже присутствует - 
	/// повторно использует существующий индекс. Возвращает индекс библиотеки.
	int AddKnownLibrary(const std::string& library_name, Linkage linkage);
	
		///\n
	/// Присваивает имя функции адресу.
	void AddKnownFunction(const std::string& function_name, Address address) {
		AddKnownFunction("", function_name, -1, address);
	}

	void AddKnownFunction(const std::string& module_name,
		const std::string& function_name, int library_index,
		Address address);
	
		///\n
	/// Добавляет функцию, импортированную из библиотеки\n
	/// (-1, если она неизвестна), адрес составляется.
	Address AddImportedFunction(const std::string& module_name,
		const std::string& function_name,
		int library_index);
	
		///\n
	/// Возвращает библиотеку по индексу библиотеки.
	const LibraryRecord& GetKnownLibrary(int library_index) const {
		return library_list_[library_index];
	}
	
		///\n
	/// Возвращает известную функцию по адресу.
	const FunctionInfo* GetKnownFunction(Address address) const;

	
		///\n
	/// Перечисляет все используемые библиотеки.
	void GetUsedLibraries(std::vector<const LibraryRecord*>* used) const;
	
		///\n
	/// Обновления используемых библиотек
	void UpdateUsedLibraries();
	
		///\n
	/// Находит индекс библиотеки для заданного адреса, -1, если его нет.
	int GetLibraryIndex(Address address) const;
	
		///\n
	/// Сообщает менеджеру,\n
	/// что 'address' связан с библиотекой с указанным индексом библиотеки.
	void UseFunction(Address address, int library_index,
		UpdateKind update_kind = UpdateKind::kUpdateUsedLibraries);
	
		///\n
	/// Маркировка библиотеки как использованной.
	int UseLibrary(const std::string& library, Linkage linkage);
	
		///\n
	/// Возвращает true, если адрес был ранее помечен с помощью UseFunction().
	bool IsKnownFunction(Address address) const {
		return used_functions_.count(address) > 0;
	}
	
		///\n
	/// Возвращает количество обнаруженных на данный момент библиотечных функций.
	int CountUsedFunctions() const { return used_functions_.size(); }
	
		///\n
	/// Возвращает количество известных функций.
	int CountKnownFunctions() const { return known_functions_.size(); }
	
		///\n
	/// Запись ссылки между двумя адресами.
	void AddReference(Address source, Address target) {
		references_.emplace(source, target);
	}
	
		///\n
	/// Получение ссылки по адресу источника.
	bool GetReference(Address source, Address* target) const;
	
		///\n
	/// Инициализировать значение, используемое для формирования адреса импортируемой функции,
	/// в соответствии с предоставленной разрядностью.
	void InitializeImportsBase(int bitness);

private:
		///\n
	/// Первый адрес для импортируемой функции. Последующие получаются путем уменьшения этого значения.\n
	/// Значения выбраны таким образом, чтобы минимизировать возможность конфликтов с адресами реальных функций.\n
	/// Неканонический x86-64-битный диапазон адресов, начинающийся с FFFF800000000000 - 1.\n
	/// See https://en.wikipedia.org/wiki/X86-64#Canonical_form_addresses.\n
	/// Встретить такой адрес в реальном x86-64 невозможно.
	static const Address kFirstImportedAddress64 = 0xFFFF800000000000ULL - 1;
	
		///\n
	/// Для 32-битного случая сложнее придумать неиспользуемый диапазон адресов,\n
	/// поэтому мы просто используем конец адресного пространства.
	static const Address kFirstImportedAddress32 = 0xFFFFFFFF;
	
		///\n
	/// Используемые библиотеки.
	std::set<int> used_libraries_;
	
		///\n
	/// Сопоставляет адрес известной функции с ее целочисленным библиотечным индексом.
	absl::flat_hash_map<Address, int> used_functions_;
	
		///\n
	/// Список всех известных библиотек, индексированных по индексу библиотеки.
	std::vector<LibraryRecord> library_list_;
	
		///\n
	/// Map всех известных функций, индексированных по адресу.\n
	/// Отличается от used_functions_, так как известные и используемые функции - это не одно и то же.
	absl::flat_hash_map<Address, FunctionInfo> known_functions_;
	
		///\n
	/// Ссылки между адресами.
	absl::flat_hash_map<Address, Address> references_;
	
		///\n
	/// Текущий придуманный адрес импортируемой функции.
	Address current_imported_address_ = kFirstImportedAddress32;
	
		///\n
	/// Текущая битность.
	int bitness_ = 32;
};

#endif  // LIBRARY_MANAGER_H_
