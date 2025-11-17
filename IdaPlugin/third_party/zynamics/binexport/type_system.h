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

// ’ранит все элементы, составл€ющие систему типов.   ним относ€тс€:
// а) контейнер типов, в котором хран€тс€ все экземпл€ры базовых типов и членов.
// б) множество экземпл€ров типов, т.е. хран€щихс€ в пам€ти объектов определенного типа.
// в) все сегменты исполн€емого файла, т.е. смежные блоки пам€ти, которые могут содержать экземпл€ры типов.

#ifndef TYPE_SYSTEM_H_
#define TYPE_SYSTEM_H_

#include <set>
#include <vector>


#include "third_party/zynamics/binexport/types_container.h"
#include "third_party/zynamics/binexport/virtual_memory.h"

class BaseType;

		///\n
/// Ётот класс €вл€етс€ потокоопасным, так как использует статическое состо€ние.
class TypeSystem {
 public:
  TypeSystem(const TypesContainer& types_container,
             const AddressSpace& address_space)
      : types_container_(types_container), address_space_(address_space) {}
  TypeSystem(const TypeSystem&) = delete;
  TypeSystem& operator=(const TypeSystem&) = delete;

  using GetNameForInstance = std::string (*)(Address address);
	
		///\n
  /// —оздает подстановку типа в указанном месте (если это возможно).\n\n
  /// ¬озможно создание новой подстановки типа, если (в зависимости от платформы)\n
  /// контейнер способен определить ссылку на тип дл€ данного места.
  void AddTypeSubstitution(Address address, int operand_num, int expression_id);
	
		///\n
	/// —оздает подстановку типа в заданном месте, но при этом учитывает\n
	/// дополнительное непосредственное смещение, €вл€ющеес€ частью операнда.
  void AddDisplacedTypeSubstitution(Address address, Address displacement,
                                    int operand_num, int expression_id);
	
		///\n
  /// —оздает экземпл€р типа дл€ заданного адреса\n\n
  /// ¬озможно создание нового экземпл€ра типа,\n
  /// а также перекрестной ссылки данных на этот экземпл€р типа,\n
  /// если контейнер способен определить ссылку типа по адресу from_address,\n
  /// ссылающуюс€ на экземпл€р типа по адресу to_address.
  void CreateTypeInstance(Address from_address, int operand_num,
                          int expression_id, Address to_address,
                          GetNameForInstance get_name);
  void CreateMemoryTypeInstance(Address from_addres, int operand_num,
                                int expression_id, Address to_address,
                                GetNameForInstance get_name);

		///\n
  /// Ёкземпл€р типа св€зывает базовый тип с заданным адресом\n
  /// (т.е. некоторой точкой отсчета в секции данных).
  struct TypeInstance {
    TypeInstance(Address section_offset, const BaseType* base_type,
                 Address segment_address, const std::string& name)
        : section_offset(section_offset),
          base_type(base_type),
          segment_address(segment_address),
          database_id(NextId()),
          name(name) {}

    Address section_offset;
    const BaseType* base_type;
    int segment_address;
  	
		///\n
	/// Ќам априори нужна €вна€ база данных, поскольку таблица подстановок выражений\n
  	/// имеет внешний ключ к таблице экземпл€ров типов.
    int database_id;
    std::string name;

   private:
    static int NextId() {
      static int id = 0;
      return id++;
    }
  };
  using TypeInstances = std::set<TypeInstance>;
  
		///\n
  /// ѕредставл€ет собой ассоциацию выражени€-операнда со ссылкой на тип.
  struct TypeSubstitution {
    TypeSubstitution(Address address, int operand_num, int expression_id,
                     int offset, int base_type_id,
                     const BaseType::MemberIds& member_path)
        : address(address),
          operand_num(operand_num),
          expression_id(expression_id),
          offset(offset),
          base_type_id(base_type_id),
          member_path(member_path) {}

    Address address;
    int operand_num;
    int expression_id;
    int offset;
    int base_type_id;
    BaseType::MemberIds member_path;
  };
  using TypeSubstitutions = std::vector<TypeSubstitution>;
  
		///\n
  /// ѕредставл€ет собой перекрестную ссылку на данные (на экземпл€р типа).
  struct DataXRef {
    DataXRef(Address address, int operand_num, int expression_id,
             const TypeInstance* type_instance)
        : address(address),
          operand_num(operand_num),
          expression_id(expression_id),
          type_instance(type_instance) {}

    Address address;
    int operand_num;
    int expression_id;
    const TypeInstance* type_instance;
  };
  using DataXRefs = std::set<DataXRef>;

  const TypeSubstitutions& GetTypeSubstitutions() const {
    return type_substitutions_;
  }

  const TypeInstances& GetTypeInstances() const { return type_instances_; }

  const TypesContainer& GetTypes() const { return types_container_; }

  const DataXRefs& GetDataXRefs() const { return data_xrefs_; }

  const BaseType* GetStackFrame(const Function& function) const {
    return types_container_.GetStackFrame(function);
  }

  const BaseType* GetFunctionPrototype(const Function& function) const {
    return types_container_.GetFunctionPrototype(function);
  }

 private:
  void CreateInstance(const TypesContainer::TypeReference& reference,
                      Address from_address, int operand_num, int expression_id,
                      Address to_address, GetNameForInstance get_name);

  const TypesContainer& types_container_;
  const AddressSpace& address_space_;
  TypeInstances type_instances_;
  TypeSubstitutions type_substitutions_;
  DataXRefs data_xrefs_;
};

bool operator<(const TypeSystem::DataXRef& lhs,
               const TypeSystem::DataXRef& rhs);

bool operator<(const TypeSystem::TypeInstance& lhs,
               const TypeSystem::TypeInstance& rhs);

#endif  // TYPE_SYSTEM_H_
