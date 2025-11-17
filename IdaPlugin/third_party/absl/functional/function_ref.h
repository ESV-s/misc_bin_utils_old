// Copyright 2019 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// -----------------------------------------------------------------------------
// File: function_ref.h
// -----------------------------------------------------------------------------
//
// Ётот заголовочный файл определ€ет тип `absl::FunctionRef` дл€
// хранени€ несобственной ссылки на объект любого вызываемого типа.
// “ака€ ссылка на функцию обычно наиболее полезна в качестве аргумента
// с ограничением типа дл€ принимающих типов функций,
// которые не принимают права собственности и не копируют тип;
// использование ссылочного типа в этом случае позвол€ет избежать копировани€ и выделени€.
// «десь применимы лучшие практики использовани€ других
// несобственных ссылочно-подобных объектов (например, `absl::string_view`).
//
// ѕо своему использованию `absl::FunctionRef` аналогичен `std::function`, но имеет следующие отличи€:
//
// * ќн не владеет базовым объектом.
// * ” него нет нулевого или пустого состо€ни€.
// * ќн никогда не выполн€ет глубокого копировани€ или выделени€.
// * ќн гораздо быстрее и дешевле в построении.
// * ќн тривиально копируемый и разрушаемый.
//
// ¬ общем случае `absl::FunctionRef` не следует использовать в качестве возвращаемого значени€, члена данных или дл€ инициализации `std::function`.
// “акое использование часто приводит к проблемам с временем жизни.
// ѕреобразовав что-либо в `absl::FunctionRef`, вы не сможете впоследствии сделать глубокую копию.
//
// Ётот класс подходит дл€ использовани€ везде, где можно использовать "const std::function<>&" без создани€ копии.
// ‘ункции ForEach и другие версии шаблона visitor €вл€ютс€ хорошим примером использовани€ этого класса.
//
// Ётот класс тривиально копируетс€ и должен передаватьс€ по значению.
#ifndef ABSL_FUNCTIONAL_FUNCTION_REF_H_
#define ABSL_FUNCTIONAL_FUNCTION_REF_H_

#include <cassert>
#include <functional>
#include <type_traits>

#include "third_party/absl/functional/internal/function_ref.h"
#include "third_party/absl/meta/type_traits.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// FunctionRef
//
// Dummy class declaration to allow the partial specialization based on function
// types below.
template <typename T>
class FunctionRef;

// FunctionRef
//
// An `absl::FunctionRef` is a lightweight wrapper to any invokable object with
// a compatible signature. Generally, an `absl::FunctionRef` should only be used
// as an argument type and should be preferred as an argument over a const
// reference to a `std::function`.
//
// Example:
//
//   // The following function takes a function callback by const reference
//   bool Visitor(const std::function<void(my_proto&,
//                                         absl::string_view)>& callback);
//
//   // Assuming that the function is not stored or otherwise copied, it can be
//   // replaced by an `absl::FunctionRef`:
//   bool Visitor(absl::FunctionRef<void(my_proto&, absl::string_view)>
//                  callback);
//
// Note: the assignment operator within an `absl::FunctionRef` is intentionally
// deleted to prevent misuse; because the `absl::FunctionRef` does not own the
// underlying type, assignment likely indicates misuse.
template <typename R, typename... Args>
class FunctionRef<R(Args...)> {
 private:
  // Used to disable constructors for objects that are not compatible with the
  // signature of this FunctionRef.
  template <typename F,
            typename FR = absl::base_internal::invoke_result_t<F, Args&&...>>
  using EnableIfCompatible =
      typename std::enable_if<std::is_void<R>::value ||
                              std::is_convertible<FR, R>::value>::type;

 public:
  // Constructs a FunctionRef from any invokable type.
  template <typename F, typename = EnableIfCompatible<const F&>>
  FunctionRef(const F& f)  // NOLINT(runtime/explicit)
      : invoker_(&absl::functional_internal::InvokeObject<F, R, Args...>) {
    absl::functional_internal::AssertNonNull(f);
    ptr_.obj = &f;
  }

  // Overload for function pointers. This eliminates a level of indirection that
  // would happen if the above overload was used (it lets us store the pointer
  // instead of a pointer to a pointer).
  //
  // This overload is also used for references to functions, since references to
  // functions can decay to function pointers implicitly.
  template <
      typename F, typename = EnableIfCompatible<F*>,
      absl::functional_internal::EnableIf<absl::is_function<F>::value> = 0>
  FunctionRef(F* f)  // NOLINT(runtime/explicit)
      : invoker_(&absl::functional_internal::InvokeFunction<F*, R, Args...>) {
    assert(f != nullptr);
    ptr_.fun = reinterpret_cast<decltype(ptr_.fun)>(f);
  }

  // To help prevent subtle lifetime bugs, FunctionRef is not assignable.
  // Typically, it should only be used as an argument type.
  FunctionRef& operator=(const FunctionRef& rhs) = delete;

  // Call the underlying object.
  R operator()(Args... args) const {
    return invoker_(ptr_, std::forward<Args>(args)...);
  }

 private:
  absl::functional_internal::VoidPtr ptr_;
  absl::functional_internal::Invoker<R, Args...> invoker_;
};

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_FUNCTIONAL_FUNCTION_REF_H_
