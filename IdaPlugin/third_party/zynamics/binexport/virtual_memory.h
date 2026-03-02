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

#ifndef VIRTUAL_MEMORY_H_
#define VIRTUAL_MEMORY_H_

#include <atomic>
#include <map>
#include <vector>

#include "third_party/absl/container/btree_map.h"
#include "third_party/absl/container/flat_hash_map.h"
#include "third_party/zynamics/binexport/types.h"

class AddressSpace {
public:
	enum {
		kRead = 1 << 0,    ///<\n адресное пространство доступно для чтения.
		kWrite = 1 << 1,   ///<\n адресное пространство доступно для записи.
		kExecute = 1 << 2  ///<\n адресное пространство является executable.
	};

	using MemoryBlock = std::vector<Byte>;
	using Data = absl::btree_map<Address, MemoryBlock>;
	using Flags = absl::flat_hash_map<Address, int>;

	///\n
/// копирует блок. возвращает true, если блок был успешно добавлен,\n
/// false, если блок перекрывает существующую память.\n
	bool AddMemoryBlock(Address address, const MemoryBlock& block, int flags);

	///\n
/// возвращает блок памяти, содержащий адрес.
	Data::const_iterator GetMemoryBlock(Address address) const;

	Data::iterator GetMemoryBlock(Address address);
	
		///\n
	/// возвращает true, если адрес отображен в данное адресное пространство,\n
	/// т.е. попадает в один из блоков памяти, принадлежащих данному классу.
	bool IsValidAddress(Address address) const;
	
		///\n
	/// возвращает true, если блок памяти по этому адресу доступен для чтения.
	bool IsReadable(Address address) const;
	
		///\n
	/// возвращает true, если блок памяти по этому адресу доступен для записи.
	bool IsWritable(Address address) const;
	
		///\n
	/// возвращает true, если блок памяти по этому адресу является executable.
	bool IsExecutable(Address address) const;
	
		///\n
	/// получение флагов для конкретного адреса:
	int GetFlags(Address address) const;
	
		///\n
	/// размер всего адресного пространства в байтах.\n
	/// время выполнения - O(количество блоков памяти).
	size_t size() const;
	
		///\n
	/// адрес карты блоков памяти, доступный только для чтения.\n
	/// сортировка по возрастанию адреса.
	const Data& data() const { return data_; }
	
		///\n
	/// получить доступ к байту по адресу. Неопределенное поведение,\n
	/// если адрес не отображен в данное адресное пространство.
	const Byte& operator[](Address address) const;
	Byte& operator[](Address address);
	
		///\n
		/// интерпретирует байты по адресу как little endian и сохраняет результат.\n
		/// возвращает true, если чтение прошло успешно.
	template <typename T>
	bool ReadLittleEndian(Address address, T* data) const;
	template <typename T>
	bool ReadLittleEndian(const MemoryBlock& memory_block,
		MemoryBlock::size_type index, T* data) const;

private:
	Data data_;
	Flags flags_;
};

template <typename T>
bool AddressSpace::ReadLittleEndian(Address address, T* data) const {
	const auto memory_block = GetMemoryBlock(address);
	if (memory_block == data_.end()) {
		return false;
	}
	return ReadLittleEndian(memory_block->second, address - memory_block->first,
		data);
}

template <typename T>
bool AddressSpace::ReadLittleEndian(const MemoryBlock& memory_block,
	MemoryBlock::size_type index,
	T* data) const {
	if (!data || index + sizeof(T) > memory_block.size()) {
		return false;
	}
	*data = 0;
	for (T i = 0; i < sizeof(T); ++i) {
		*data |= static_cast<T>(memory_block[index + i]) << (i * 8);
	}
	return true;
}

#endif  // VIRTUAL_MEMORY_H_
