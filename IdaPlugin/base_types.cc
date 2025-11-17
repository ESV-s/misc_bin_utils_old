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

#include "third_party/zynamics/binexport/base_types.h"

#include <algorithm>
#include <cassert>
#include <cstddef>

namespace {

	/**
	 * \brief \n ≈сли это аргументы прототипа функции, то мы сортируем по позиции аргумента,\n
	 * в противном случае сортировка производитс€ по смещению члена (member offset).
	 * \param lhs 
	 * \param rhs 
	 * \return 
	 */
	bool SortMemberTypes(const MemberType* lhs, const MemberType* rhs) {
		if (lhs->offset == MemberType::DB_NULL_VALUE &&
			rhs->offset == MemberType::DB_NULL_VALUE) {
			return lhs->argument < rhs->argument;
		}
		return lhs->offset < rhs->offset;
	}

}  // namespace

  /**
  * \brief \n ѕоследовательности базы данных должны начинатьс€ с единицы.\n
  * »наче инициализаци€ в BinNavi может закончитьс€ неудачей.
  */
uint32_t BaseType::NextTypeId() {
	static uint32_t type_id = 1;
	return type_id++;
}

uint32_t BaseType::GetId() const { return id_; }

void BaseType::SetName(const std::string& name) { name_ = name; }

const std::string& BaseType::GetName() const { return name_; }

void BaseType::SetSize(size_t size) {
	size_ = size;
}

size_t BaseType::GetSize() const {
	return size_;
}

void BaseType::SetSigned(bool is_signed) {
	is_signed_ = is_signed;
}

bool BaseType::IsSigned() const {
	return is_signed_;
}

void BaseType::SetPointer(const BaseType* pointer) {
	pointer_ = pointer;
}

const BaseType* BaseType::GetPointer() const {
	return pointer_;
}

void BaseType::AddMember(MemberType* member) {
	members_.insert(std::lower_bound(members_.begin(),
		members_.end(), member, &SortMemberTypes), member);
}

const BaseType::MemberTypes& BaseType::GetMembers() const {
	return members_;
}

void BaseType::SetCategory(TypeCategory category) {
	category_ = category;
}

std::string BaseType::GetCategoryString() const {
	switch (category_) {
	case kAtomic:
		return "atomic";
	case kPointer:
		return "pointer";
	case kStruct:
		return "struct";
	case kArray:
		return "array";
	case kUnion:
		return "union";
	case kFunctionPrototype:
		return "function_pointer";
	default:
		assert(false && "Unknown category value.");
		return "UNKNOWN";
	}
}

bool IsWithinMember(const MemberType* member, int offset) {
	return offset >= member->offset
		&& offset < member->offset + member->type->GetSize();
}

/**
 * \brief \n Ќаходит в структуре член x, занимающий место в диапазоне [offset, offset + sizeof(x)).\n
 * ¬озвращает NULL, если такого члена не существует.\n
 * —мещение должно быть задано в битах.\n
 * \param base_type const BaseType* base_type
 * \param offset offset
 * \return MemberTypes::const_iterator cit : nullptr  as ? *cit : nullptr
 */
const MemberType* BaseType::ResolveMember(const BaseType* base_type,
	int offset) {
	if (base_type->GetMembers().empty()) {
		return nullptr;
	}

	MemberType search_member;
	search_member.offset = offset;
	MemberTypes::const_iterator cit =
		std::lower_bound(base_type->GetMembers().begin(),
			base_type->GetMembers().end(),
			&search_member,
			&SortMemberTypes);
	// ћы могли бы найти последующий член (так как нижн€€ граница дает нам первый член,
	// который больше или равен относительно нашего поискового смещени€).
	if (cit == base_type->GetMembers().end() || !IsWithinMember(*cit, offset)) {
		if (cit == base_type->GetMembers().begin()) {
			return nullptr;
		}
		--cit;
	}

	return IsWithinMember(*cit, offset) ? *cit : nullptr;
}

uint32_t MemberType::NextTypeId() {
	static uint32_t member_id = 1;
	return member_id++;
}
