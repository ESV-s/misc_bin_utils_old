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

// Defines the structures corresponding to the database tables ex_?_base_types
// and ex_?_types, respectively, to represent types and members of compound
// types according to the C type system.

#ifndef BASE_TYPES_H_
#define BASE_TYPES_H_

#include <cstdint>
#include <string>
#include <vector>

#include "third_party/zynamics/binexport/types.h"

struct MemberType;

/**
 * \brief \n Представляет базовый тип (например, int, struct_A и т.д.).\n
 * Инстанцирование base_type не является потокобезопасным.
 */
class BaseType {
public: 
	/**
	 * \brief \n Примечание: при изменении этого перечисления необходимо\n
	 * обновить и метод GetCategoryString.\n
	 */
	enum TypeCategory {
		kAtomic,
		kPointer,
		kStruct,
		kArray,
		kUnion,
		kFunctionPrototype
	};

	BaseType()
		: id_(NextTypeId()),
		pointer_(nullptr),
		category_(kAtomic) {}

	using BaseTypes = std::vector<const BaseType*>;
	using MemberTypes = std::vector<MemberType*>;
	using MemberIds = std::vector<int>;

	/**
	 * \brief \n Возвращает идентификатор базы данных данного базового типа.\n
	 * \return id_
	 */
	uint32_t GetId() const;

	void SetName(const std::string& name);
	const std::string& GetName() const;

	void SetSize(size_t size);
	size_t GetSize() const;

	void SetSigned(bool is_signed);
	bool IsSigned() const;

	void SetPointer(const BaseType* pointer);
	const BaseType* GetPointer() const;

	void AddMember(MemberType* member);

	/**
	 * \brief \n Возвращает список членов, отсортированных по смещению в порядке возрастания.
	 * \return members_
	 */
	const MemberTypes& GetMembers() const;

	void SetCategory(TypeCategory category);
	std::string GetCategoryString() const;

	static const MemberType* ResolveMember(const BaseType* base_type, int offset);

private:
	static uint32_t NextTypeId();

	uint32_t id_;

	/**
	 * \brief \n Имя данного типа.
	 */
	std::string name_;

	/**
	 * \brief \n Размер данного типа в битах.
	 */
	size_t size_ = 0;

	/**
	 * \brief \n Может ли этот тип представлять знаковые значения?
	 */
	bool is_signed_ = false;

	/**
	 * \brief \n Если это тип указателя, то мы также имеем родительское отношение\n
	 * (например, int** -> int* -> int).
	 */
	const BaseType* pointer_;

	/**
	 * \brief \n Список членов, принадлежащих данному базовому типу.\n
	 * Базовый тип не является владельцем экземпляров MemberType.\n
	 * Вместо этого они принадлежат контейнеру типов.\n
	 */
	MemberTypes members_;
	TypeCategory category_;
};

/**
 * \brief \n Представляет элемент составного типа.\n
 * Экземпляры MemberType не являются потокобезопасными.
 */
struct MemberType {
	// Представляет собой нулевое значение в схеме базы данных.
	enum { DB_NULL_VALUE = -1 };

	MemberType() : id(NextTypeId()), type(nullptr), parent_type(nullptr) {}

	/**
	 * \brief \n Соответствующий id в базе данных.\n
	 */
	uint32_t id;

	/**
	 * \brief \n Имя участника.
	 */
	std::string name;

	/**
	 * \brief \n Тип данного члена.
	 */
	const BaseType* type;

	/**
	 * \brief \n Родительский id, в котором содержится данный тип.
	 */
	const BaseType* parent_type;

	/**
	 * \brief \n Смещение этого члена в типе структуры.\n
	 * DB_NULL_VALUE, если в базе данных этот член должен быть NULL (для массивов).
	 */
	int offset = DB_NULL_VALUE;

	/**
	 * \brief \n Младший аргумент, если это указатель функции.\n
	 * DB_NULL_VALUE, если в базе данных это должно быть NULL.\n
	 * (все, кроме указателей функций).
	 */
	int argument = DB_NULL_VALUE;

	/**
	 * \brief \n Количество элементов, если это массив.\n
	 * DB_NULL_VALUE, если в базе данных это должно быть NULL\n
	 * (все, кроме массивов).
	 */
	int num_elements = DB_NULL_VALUE;

private:
	static uint32_t NextTypeId();
};

#endif  // BASE_TYPES_H_
