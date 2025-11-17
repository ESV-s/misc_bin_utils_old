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

#include "third_party/zynamics/binexport/expression.h"

#include <sstream>

#include "base/logging.h"
#include "third_party/zynamics/binexport/hash.h"
#include "third_party/zynamics/binexport/instruction.h"

Expression::StringCache Expression::string_cache_;
Expression::ExpressionCache Expression::expression_cache_;
int Expression::global_id_ = 0;

Expression::Expression(const Expression* parent, const std::string& symbol,
	int64_t immediate, Type type, uint16_t position,
	bool relocatable)
	: symbol_(CacheString(symbol)),
	immediate_(immediate),
	parent_(parent),
	position_(position),
	type_(type),
	relocatable_(relocatable) {
	DCHECK(!symbol.empty() || IsImmediate());
}

Expression* Expression::Create(const Expression* parent,
	const std::string& symbol, int64_t immediate,
	Type type, uint16_t position, bool relocatable) {
	Expression expression(parent, symbol, immediate, type, position, relocatable);
	const std::string signature = expression.CreateSignature();
	ExpressionCache::iterator i = expression_cache_.find(signature);
	if (i != expression_cache_.end()) {
		return &i->second;
	}
	// Id должен быть просто подсчетом того, сколько объектов уже находитс€ в кэше.
	expression.id_ = ++global_id_;
	return &expression_cache_.insert(std::make_pair(signature, expression))
		.first->second;
}

void Expression::EmptyCache() {
	ExpressionCache().swap(expression_cache_);
	StringCache().swap(string_cache_);
	global_id_ = 0;
}

const std::string* Expression::CacheString(const std::string& value) {
	return &*string_cache_.insert(value).first;
}

const Expression::ExpressionCache& Expression::GetExpressions() {
	return expression_cache_;
}

bool Expression::IsSymbol() const { return type_ == TYPE_SYMBOL; }

bool Expression::IsRegister() const { return type_ == TYPE_REGISTER; }

bool Expression::IsImmediate() const {
	return type_ == TYPE_IMMEDIATE_INT || type_ == TYPE_IMMEDIATE_FLOAT ||
		type_ > TYPE_DEREFERENCE;
	// ƒополнительные типы используютс€ только дл€ подсветки синтаксиса
	// и различени€ различных типов непосредственных меток (location, function, local/global variable).
}

bool Expression::IsOperator() const { return type_ == TYPE_OPERATOR; }

bool Expression::IsDereferenceOperator() const {
	return type_ == TYPE_DEREFERENCE;
}

bool Expression::IsRelocation() const { return relocatable_; }

int Expression::GetId() const { return id_; }

Expression::Type Expression::GetType() const { return type_; }

const std::string& Expression::GetSymbol() const { return *symbol_; }

uint16_t Expression::GetPosition() const { return position_; }

int64_t Expression::GetImmediate() const { return immediate_; }

const Expression* Expression::GetParent() const { return parent_; }

std::string Expression::CreateSignature() {
	std::string signature(19 /* length of the signature */, '0');
	signature[0] = static_cast<char>(type_);
	*reinterpret_cast<uint16_t*>(&signature[1]) = position_;
	*reinterpret_cast<Address*>(&signature[3]) = immediate_;
	*reinterpret_cast<uint32_t*>(&signature[11]) = GetSdbmHash(*symbol_);
	*reinterpret_cast<uint32_t*>(&signature[15]) = parent_ ? parent_->GetId() : 0;
	return signature;
}

std::ostream& operator<<(std::ostream& stream, const Expression& expression) {
	if (expression.IsDereferenceOperator()) {
		stream << "[";
	}
	else if (!expression.GetSymbol().empty()) {
		stream << expression.GetSymbol();
	}
	else if (expression.GetImmediate() >= 0) {
		stream << std::hex << expression.GetImmediate();
	}
	else {
		stream << "-" << std::hex << -expression.GetImmediate();
	}

	// TODO(cblichmann): –еализаци€ с использованием RenderExpression в instruction.cc
	// for (auto it =
	//      expression.children.begin(); it != expression.children.end(); ++it)
	//   stream << "(" << **it << ")";

	if (expression.IsDereferenceOperator()) {
		stream << "]";
	}
	return stream;
}

/**
 * \brief \n ѕоскольку структура xref в IDA содержит только адрес, но не операнд и не выражение дл€ адресной ссылки,\n
 * мы должны разобратьс€ с этим самосто€тельно.\n
 * —начала: ѕопытатьс€ сопоставить непосредственный адрес с точным целевым адресом,\n
 * и если это не удаетс€, то использовать оператор разыменовани€ адреса,\n
 * единственный операнд или первый попавшийс€ непосредственный адрес - в таком случае.\n
 * \param instruction const Instruction& instruction
 * \param target Address target
 * \return std::pair<int, int>
 */
std::pair<int, int> GetSourceExpressionId(const Instruction& instruction,
	Address target) {
	///\n
	/// —начала попробуйте найти точное непосредственное совпадение в выражении любого операнда.\n
	/// ѕопробуйте во втором выражении любого операнда выполнить разыменование пам€ти.
	int operand_index = 0;
	for (const auto* operand : instruction) {
		// _RPT1(0, "Operand  = %d \n", operand);
		int expression_index = 0;
		for (const auto* expression : *operand) {
			if (expression->IsImmediate() &&
				(Address)expression->GetImmediate() == target) {
				return{ operand_index, expression_index };
			}
			++expression_index;
		}
		++operand_index;
	}

	// ѕопробуйте во втором выражении любого операнда выполнить разыменование пам€ти.
	operand_index = 0;
	for (const auto* operand : instruction) {
		int expression_index = 0;
		for (const auto* expression : *operand) {
			if (expression->GetParent() &&
				expression->GetParent()->IsDereferenceOperator()) {
				// »спользуйте индекс родительского выражени€, если выражение не €вл€етс€ непосредственным.
				return{ operand_index, expression->IsImmediate()
					? expression_index
					: expression_index - 1 };
			}
			++expression_index;
		}
		++operand_index;
	}

	// ≈сли мы возвращаем только один операнд, то.
	if (instruction.GetOperandCount() == 1) {
		return{ 0, 0 };
	}

	// ¬ерните любое найденное непосредственное выражение.
	operand_index = 0;
	for (const auto* operand : instruction) {
		int expression_index = 0;
		for (const auto* expression : *operand) {
			if (expression->IsImmediate()) {
				return{ operand_index, expression_index };
			}
			++expression_index;
		}
		++operand_index;
	}

	// —датьс€.
	return{ -1, -1 };
}
