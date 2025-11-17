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
// File: status.h
// -----------------------------------------------------------------------------
//
// Этот заголовочный файл определяет библиотеку Abseil `status`, состоящую из:
//
//   * Класс `absl::Status` для хранения информации об обработке ошибок
//   * Набор канонических кодов ошибок `absl::StatusCode`, а также связанные с ними
//     утилиты для генерации и распространения кодов состояния.
//   * Набор вспомогательных функций для создания кодов состояния и проверки их значений
//
// В Google `absl::Status` является основным механизмом для изящной
// обработки ошибок на границах API (и, в частности, на границах RPC).
// Некоторые из этих ошибок могут быть восстановимы, а другие - нет.
// Большинство функций, которые могут выдать восстанавливаемую ошибку, должны быть спроектированы так, чтобы
// возвращать значение `absl::Status` (или `absl::StatusOr`).
//
// Example:
//
// absl::Status myFunction(absl::string_view fname, ...) {
//   ...
//   // encounter error
//   if (error condition) {
//     return absl::InvalidArgumentError("bad mode");
//   }
//   // else, return OK
//   return absl::OkStatus();
// }
//
// Функция `absl::Status` предназначена для возврата либо "OK", либо одного из множества
// различных кодов ошибок, соответствующих типичным состояниям ошибки.
// Практически во всех случаях при использовании `absl::Status` следует использовать канонические
// коды ошибок (типа `absl::StatusCode`), перечисляемые в этом заголовочном файле.
// Эти канонические коды понятны всей кодовой базе и будут приниматься на всех границах API и RPC.
#ifndef ABSL_STATUS_STATUS_H_
#define ABSL_STATUS_STATUS_H_

#include <iostream>
#include <string>

#include "third_party/absl/container/inlined_vector.h"
#include "third_party/absl/status/internal/status_internal.h"
#include "third_party/absl/strings/cord.h"
#include "third_party/absl/strings/string_view.h"
#include "third_party/absl/types/optional.h"

namespace absl {
ABSL_NAMESPACE_BEGIN

// absl::StatusCode
//
// Код `absl::StatusCode` - это перечисляемый тип, указывающий либо на отсутствие ошибки ("OK")
// либо состояние ошибки. В большинстве случаев `absl::Status` указывает на устранимую ошибку,
// и цель сигнализации об ошибке - указать, какое действие следует предпринять в ответ на эту ошибку. 
// Эти коды ошибок соответствуют кодам ошибок proto RPC,
// указанным в https://cloud.google.com/apis/design/errors.
//
// Перечисленные ниже ошибки являются каноническими ошибками, связанными с ``absl::Status``.
// и используются во всей кодовой базе. В результате эти коды ошибок являются несколько общими.
//
// В общем случае старайтесь возвращать наиболее конкретную ошибку, если их может быть несколько.
// Например, предпочтите `kOutOfRange`, а не `kFailedPrecondition`, если применяются оба кода. 
// Аналогично предпочтите `kNotFound` или `kAlreadyExists`, а не `kFailedPrecondition`.
//
// Поскольку эти ошибки могут пересекать границы RPC, эти коды привязаны к определениям `google.rpc.Code` в пределах
// https://github.com/googleapis/googleapis/blob/master/google/rpc/code.proto
// Строковое значение этих RPC-кодов обозначено в каждом перечислении ниже.
//
// Если ваш код обработки ошибок требует большего контекста,
// вы можете присоединить полезную нагрузку к своему статусу.
//  Смотрите `absl::Status::SetPayload()` и `absl::Status::GetPayload()` ниже.
enum class StatusCode : int {
  // StatusCode::kOk
  //
  // kOK (код gRPC "OK") не указывает на ошибку; это значение возвращается при успехе.
  // Обычно это значение проверяется перед тем, как продолжить вызов через границу API или RPC. 
  // Для проверки этого значения следует использовать функцию-член `absl::Status::ok()`, а не осматривать исходный код.
  kOk = 0,

  // StatusCode::kCancelled
  //
  // kCancelled (код gRPC "CANCELLED") указывает на то, что операция была отменена, как правило, вызывающей стороной.
  kCancelled = 1,

  // StatusCode::kUnknown
  //
  // kUnknown (код gRPC "UNKNOWN") указывает на возникновение неизвестной ошибки.
  // В общем случае, если это возможно, следует выдавать более конкретные ошибки.
  // Ошибки, вызванные API, которые не возвращают достаточно информации об ошибке,
  // могут быть преобразованы в эту ошибку.
  kUnknown = 2,

  // StatusCode::kInvalidArgument
  //
  // kInvalidArgument (gRPC-код "INVALID_ARGUMENT") указывает на то,
  // что вызывающая сторона указала некорректный аргумент,
  // например некорректно сформированное имя файла.
  // Отметим, что подобные ошибки должны быть узко ограничены
  // и указывать на некорректный характер самих аргументов.
  // Ошибки с корректно сформированными аргументами, которые могут привести
  // к ошибкам с состоянием принимающей системы, следует обозначать `kFailedPrecondition`.
  kInvalidArgument = 3,

  // StatusCode::kDeadlineExceeded
  //
  // kDeadlineExceeded (gRPC-код "DEADLINE_EXCEEDED") указывает на то,
  // что срок выполнения операции истек до ее завершения.
  // Для операций, которые могут изменять состояние системы,
  // эта ошибка может быть возвращена даже при успешном завершении операции.
  // Например, успешный ответ от сервера мог задержаться достаточно долго, чтобы срок истек.
  kDeadlineExceeded = 4,

  // StatusCode::kNotFound
  //
  // kNotFound (код gRPC "NOT_FOUND") указывает на то, что некоторая запрошенная сущность (например, файл или каталог) не была найдена.
  //
  // `kNotFound` полезен, если запрос должен быть отклонен для целого класса пользователей,
  // например, при постепенном развертывании функций или недокументированного списка разрешений.
  // Если же запрос должен быть отклонен для определенного круга пользователей,
  // например, при управлении доступом на основе пользователей, используйте вместо этого `kPermissionDenied`.
  kNotFound = 5,

  // StatusCode::kAlreadyExists
  //
  // kAlreadyExists (код gRPC "ALREADY_EXISTS") указывает на то, что сущность,
  // которую пыталась создать вызывающая сторона (например, файл или каталог), уже существует.
  kAlreadyExists = 6,

  // StatusCode::kPermissionDenied
  //
  // kPermissionDenied (gRPC-код "PERMISSION_DENIED") указывает на то,
  // что вызывающая сторона не имеет разрешения на выполнение указанной операции.
  // Обратите внимание, что эта ошибка отличается от ошибки, связанной с *не*аутентифицированным пользователем.
  // Данный код ошибки не означает, что запрос корректен,
  // запрашиваемая сущность существует или удовлетворяет каким-либо другим предварительным условиям.
  //
  // `kPermissionDenied` не должен использоваться для отказов, вызванных исчерпанием какого-либо ресурса.
  // Вместо этого для таких ошибок следует использовать `kResourceExhausted`.
  // `kPermissionDenied` не должен использоваться, если вызывающий абонент не может быть идентифицирован.
  // Вместо этого для таких ошибок используйте `kUnauthenticated`.
  kPermissionDenied = 7,

  // StatusCode::kResourceExhausted
  //
  // kResourceExhausted (gRPC code "RESOURCE_EXHAUSTED") indicates some resource
  // has been exhausted, perhaps a per-user quota, or perhaps the entire file
  // system is out of space.
  kResourceExhausted = 8,

  // StatusCode::kFailedPrecondition
  //
  // kFailedPrecondition (gRPC code "FAILED_PRECONDITION") indicates that the
  // operation was rejected because the system is not in a state required for
  // the operation's execution. For example, a directory to be deleted may be
  // non-empty, an "rmdir" operation is applied to a non-directory, etc.
  //
  // Some guidelines that may help a service implementer in deciding between
  // `kFailedPrecondition`, `kAborted`, and `kUnavailable`:
  //
  //  (a) Use `kUnavailable` if the client can retry just the failing call.
  //  (b) Use `kAborted` if the client should retry at a higher transaction
  //      level (such as when a client-specified test-and-set fails, indicating
  //      the client should restart a read-modify-write sequence).
  //  (c) Use `kFailedPrecondition` if the client should not retry until
  //      the system state has been explicitly fixed. For example, if an "rmdir"
  //      fails because the directory is non-empty, `kFailedPrecondition`
  //      should be returned since the client should not retry unless
  //      the files are deleted from the directory.
  kFailedPrecondition = 9,

  // StatusCode::kAborted
  //
  // kAborted (gRPC code "ABORTED") indicates the operation was aborted,
  // typically due to a concurrency issue such as a sequencer check failure or a
  // failed transaction.
  //
  // See the guidelines above for deciding between `kFailedPrecondition`,
  // `kAborted`, and `kUnavailable`.
  kAborted = 10,

  // StatusCode::kOutOfRange
  //
  // kOutOfRange (gRPC code "OUT_OF_RANGE") indicates the operation was
  // attempted past the valid range, such as seeking or reading past an
  // end-of-file.
  //
  // Unlike `kInvalidArgument`, this error indicates a problem that may
  // be fixed if the system state changes. For example, a 32-bit file
  // system will generate `kInvalidArgument` if asked to read at an
  // offset that is not in the range [0,2^32-1], but it will generate
  // `kOutOfRange` if asked to read from an offset past the current
  // file size.
  //
  // There is a fair bit of overlap between `kFailedPrecondition` and
  // `kOutOfRange`.  We recommend using `kOutOfRange` (the more specific
  // error) when it applies so that callers who are iterating through
  // a space can easily look for an `kOutOfRange` error to detect when
  // they are done.
  kOutOfRange = 11,

  // StatusCode::kUnimplemented
  //
  // kUnimplemented (gRPC code "UNIMPLEMENTED") indicates the operation is not
  // implemented or supported in this service. In this case, the operation
  // should not be re-attempted.
  kUnimplemented = 12,

  // StatusCode::kInternal
  //
  // kInternal (gRPC code "INTERNAL") indicates an internal error has occurred
  // and some invariants expected by the underlying system have not been
  // satisfied. This error code is reserved for serious errors.
  kInternal = 13,

  // StatusCode::kUnavailable
  //
  // kUnavailable (gRPC code "UNAVAILABLE") indicates the service is currently
  // unavailable and that this is most likely a transient condition. An error
  // such as this can be corrected by retrying with a backoff scheme. Note that
  // it is not always safe to retry non-idempotent operations.
  //
  // See the guidelines above for deciding between `kFailedPrecondition`,
  // `kAborted`, and `kUnavailable`.
  kUnavailable = 14,

  // StatusCode::kDataLoss
  //
  // kDataLoss (gRPC code "DATA_LOSS") indicates that unrecoverable data loss or
  // corruption has occurred. As this error is serious, proper alerting should
  // be attached to errors such as this.
  kDataLoss = 15,

  // StatusCode::kUnauthenticated
  //
  // kUnauthenticated (gRPC code "UNAUTHENTICATED") indicates that the request
  // does not have valid authentication credentials for the operation. Correct
  // the authentication and try again.
  kUnauthenticated = 16,

  // StatusCode::DoNotUseReservedForFutureExpansionUseDefaultInSwitchInstead_
  //
  // NOTE: this error code entry should not be used and you should not rely on
  // its value, which may change.
  //
  // The purpose of this enumerated value is to force people who handle status
  // codes with `switch()` statements to *not* simply enumerate all possible
  // values, but instead provide a "default:" case. Providing such a default
  // case ensures that code will compile when new codes are added.
  kDoNotUseReservedForFutureExpansionUseDefaultInSwitchInstead_ = 20
};

// StatusCodeToString()
//
// Возвращает имя кода состояния или "", если это неизвестное значение.
std::string StatusCodeToString(StatusCode code);

// operator<<
//
// Передает StatusCodeToString(code) в `os`.
std::ostream& operator<<(std::ostream& os, StatusCode code);

// absl::Status
//
// Класс `absl::Status` обычно используется для изящной обработки ошибок,
// возникающих на границах API (и, в частности, на границах RPC).
// Некоторые из этих ошибок могут быть восстановимы, а другие - нет.
// Большинство функций, которые могут выдать восстанавливаемую ошибку,
// должны возвращать либо `absl::Status` (или аналогичный `absl::StatusOr<T>`,
// который содержит либо объект типа `T`, либо ошибку).
//
// Разработчики API должны строить свои функции таким образом,
// чтобы они возвращали `absl::OkStatus()` при успехе,
// или `absl::StatusCode` при ошибке другого типа (например, ошибка `absl::StatusCode::kInvalidArgument`).
// API предоставляет удобные функции для определения каждого кода состояния.
//
// Example:
//
// absl::Status myFunction(absl::string_view fname, ...) {
//   ...
//   // encounter error
//   if (error condition) {
//     // Construct an absl::StatusCode::kInvalidArgument error
//     return absl::InvalidArgumentError("bad mode");
//   }
//   // else, return OK
//   return absl::OkStatus();
// }
//
// Пользователям, работающим с кодами ошибок статуса, лучше проверять статус OK с помощью функции-члена `ok()`.
// Работа с несколькими кодами ошибок может оправдать использование оператора switch,
// но проверяйте только те коды ошибок, которые вы умеете обрабатывать;
// не пытайтесь исчерпывающе сопоставить все канонические коды ошибок.
// Ошибки, которые не могут быть обработаны, должны регистрироваться и/или передаваться на более высокие уровни. 
// Если вы используете оператор switch, убедитесь, что вы также обеспечили `default:` switch case,
// чтобы код не сломался при добавлении в API других канонических кодов.
//
// Example:
//
//   absl::Status result = DoSomething();
//   if (!result.ok()) {
//     LOG(ERROR) << result;
//   }
//
//   // Provide a default if switching on multiple error codes
//   switch (result.code()) {
//     // The user hasn't authenticated. Ask them to reauth
//     case absl::StatusCode::kUnauthenticated:
//       DoReAuth();
//       break;
//     // The user does not have permission. Log an error.
//     case absl::StatusCode::kPermissionDenied:
//       LOG(ERROR) << result;
//       break;
//     // Propagate the error otherwise.
//     default:
//       return true;
//   }
//
// Сообщение `absl::Status` может опционально включать полезную нагрузку, содержащую дополнительную информацию об ошибке.
// Как правило, эта полезная нагрузка служит для одной из нескольких целей:
//
//    * Она может предоставлять более тонкую семантическую информацию об ошибке для облегчения ее устранения.
//    * Она может предоставлять человекочитаемую контекстную информацию, которую целесообразно отображать конечному пользователю.
//
// Example:
//
//   absl::Status result = DoSomething();
//   // Сообщите пользователю о необходимости повторить попытку через 30 секунд
//   // See more error details in googleapis/google/rpc/error_details.proto
//   if (absl::IsResourceExhausted(result)) {
//     google::rpc::RetryInfo info;
//     info.retry_delay().seconds() = 30;
//      // Полезная нагрузка требует уникального ключа (URL, чтобы не было коллизий с другими полезными нагрузками),
//     // и `absl::Cord` для хранения закодированных данных.
//     absl::string_view url = "type.googleapis.com/google.rpc.RetryInfo";
//     result.SetPayload(url, info.SerializeAsCord());
//     return result;
//   }
//
class ABSL_MUST_USE_RESULT Status final {
 public:
  // Constructors

  // Этот конструктор по умолчанию создает статус OK без сообщения или полезной нагрузки.
  // Избегайте этого конструктора и предпочитайте явное построение статуса OK с помощью `absl::OkStatus()`.
  Status();

  // Создает статус в каноническом пространстве ошибок
  // с указанным `absl::StatusCode` и сообщением об ошибке.
  // Если `code == absl::StatusCode::kOk`,
  // `msg` игнорируется и строится объект, идентичный статусу OK.
  //
  // Строка `msg` должна быть в формате UTF-8.
  // В противном случае реализация может сообщить об этом (например, вывести предупреждение).
  Status(absl::StatusCode code, absl::string_view msg);

  Status(const Status&);
  Status& operator=(const Status& x);

  // Move operators

  // Состояние "moved-from" является действительным, но не определенным.
  Status(Status&&) noexcept;
  Status& operator=(Status&&);

  ~Status();

  // Status::Update()
  //
  // Обновление существующего статуса на `new_status` при условии, что `this->ok()`.
  // Если существующий статус уже содержит не-ок ошибку,
  // то обновление не имеет эффекта и сохраняет текущие данные.
  // Заметим, что в будущем это поведение может измениться,
  // чтобы дополнить текущий не-ок статус дополнительной информацией о `new_status`.
  //
  // `Update()` обеспечивает удобный способ отслеживания первой возникшей ошибки.
  //
  // Example:
  //   // Instead of "if (overall_status.ok()) overall_status = new_status"
  //   overall_status.Update(new_status);
  //
  void Update(const Status& new_status);
  void Update(Status&& new_status);

  // Status::ok()
  //
  // Возвращает `true`, если `this->ok()`. Предпочтительнее проверять статус OK с помощью этой функции-члена.
  ABSL_MUST_USE_RESULT bool ok() const;

  // Status::code()
  //
  // Возвращает канонический код ошибки типа `absl::StatusCode` данного статуса.
  absl::StatusCode code() const;

  // Status::raw_code()
  //
  // Возвращает необработанный (канонический) код ошибки, соответствующий значению
  // перечисления определений `google.rpc.Code` в пределах.
  // https://github.com/googleapis/googleapis/blob/master/google/rpc/code.proto.
  // Эти значения могут выходить за пределы диапазона канонических значений перечисления `absl::StatusCode`.
  //
  // ПРИМЕЧАНИЕ: Эта функция должна вызываться только при конвертации в ассоциированный wire format.
  // Для обработки ошибок используйте `Status::code()`.
  int raw_code() const;

  // Status::message()
  //
  // Возвращается сообщение об ошибке, связанное с данным кодом ошибки, если оно доступно.
  // Обратите внимание, что это сообщение редко описывает код ошибки. 
  // Нередко сообщение об ошибке представляет собой пустую строку.
  // В результате для отладочного протоколирования лучше использовать `Status::ToString()`.
  absl::string_view message() const;

  friend bool operator==(const Status&, const Status&);
  friend bool operator!=(const Status&, const Status&);

  // Status::ToString()
  //
  // Возвращается комбинация из названия кода ошибки, сообщения и любых связанных с ним сообщений полезной нагрузки.
  // Эта строка предназначена просто для того, чтобы быть читаемой человеком,
  // и ее точный формат не должен быть нагрузочным.
  // Не полагайтесь на точный формат результата `ToString()`, который может измениться.
  //
  // Выводимые на печать кодовое имя и сообщение обычно являются подстроками результата,
  // а для печати полезной нагрузки используется механизм
  // принтера статусной полезной нагрузки (который является внутренним).
  std::string ToString() const;

  // Status::IgnoreError()
  //
  // Игнорирует любые ошибки. Этот метод ничего не делает,
  // кроме потенциального подавления жалоб от любых инструментов, проверяющих, не падают ли ошибки на дно.
  void IgnoreError() const;

  // swap()
  //
  // Поменять содержимое одного состояния на другое.
  friend void swap(Status& a, Status& b);

  //----------------------------------------------------------------------------
  // Payload Management APIs
  //----------------------------------------------------------------------------

  // A payload may be attached to a status to provide additional context to an
  // error that may not be satisifed by an existing `absl::StatusCode`.
  // Typically, this payload serves one of several purposes:
  //
  //   * It may provide more fine-grained semantic information about the error
  //     to facilitate actionable remedies.
  //   * It may provide human-readable contexual information that is more
  //     appropriate to display to an end user.
  //
  // A payload consists of a [key,value] pair, where the key is a string
  // referring to a unique "type URL" and the value is an object of type
  // `absl::Cord` to hold the contextual data.
  //
  // The "type URL" should be unique and follow the format of a URL
  // (https://en.wikipedia.org/wiki/URL) and, ideally, provide some
  // documentation or schema on how to interpret its associated data. For
  // example, the default type URL for a protobuf message type is
  // "type.googleapis.com/packagename.messagename". Other custom wire formats
  // should define the format of type URL in a similar practice so as to
  // minimize the chance of conflict between type URLs.
  // Users should ensure that the type URL can be mapped to a concrete
  // C++ type if they want to deserialize the payload and read it effectively.
  //
  // To attach a payload to a status object, call `Status::SetPayload()`,
  // passing it the type URL and an `absl::Cord` of associated data. Similarly,
  // to extract the payload from a status, call `Status::GetPayload()`. You
  // may attach multiple payloads (with differing type URLs) to any given
  // status object, provided that the status is currently exhibiting an error
  // code (i.e. is not OK).

  // Status::GetPayload()
  //
  // Gets the payload of a status given its unique `type_url` key, if present.
  absl::optional<absl::Cord> GetPayload(absl::string_view type_url) const;

  // Status::SetPayload()
  //
  // Sets the payload for a non-ok status using a `type_url` key, overwriting
  // any existing payload for that `type_url`.
  //
  // NOTE: This function does nothing if the Status is ok.
  void SetPayload(absl::string_view type_url, absl::Cord payload);

  // Status::ErasePayload()
  //
  // Erases the payload corresponding to the `type_url` key.  Returns `true` if
  // the payload was present.
  bool ErasePayload(absl::string_view type_url);

  // Status::ForEachPayload()
  //
  // Iterates over the stored payloads and calls the
  // `visitor(type_key, payload)` callable for each one.
  //
  // NOTE: The order of calls to `visitor()` is not specified and may change at
  // any time.
  //
  // NOTE: Any mutation on the same 'absl::Status' object during visitation is
  // forbidden and could result in undefined behavior.
  void ForEachPayload(
      const std::function<void(absl::string_view, const absl::Cord&)>& visitor)
      const;

 private:
  friend Status CancelledError();

  // Creates a status in the canonical error space with the specified
  // code, and an empty error message.
  explicit Status(absl::StatusCode code);

  static void UnrefNonInlined(uintptr_t rep);
  static void Ref(uintptr_t rep);
  static void Unref(uintptr_t rep);

  // REQUIRES: !ok()
  // Ensures rep_ is not shared with any other Status.
  void PrepareToModify();

  const status_internal::Payloads* GetPayloads() const;
  status_internal::Payloads* GetPayloads();

  // Takes ownership of payload.
  static uintptr_t NewRep(absl::StatusCode code, absl::string_view msg,
                          std::unique_ptr<status_internal::Payloads> payload);
  static bool EqualsSlow(const absl::Status& a, const absl::Status& b);

  // MSVC 14.0 limitation requires the const.
  static constexpr const char kMovedFromString[] =
      "Status accessed after move.";

  static const std::string* EmptyString();
  static const std::string* MovedFromString();

  // Returns whether rep contains an inlined representation.
  // See rep_ for details.
  static bool IsInlined(uintptr_t rep);

  // Indicates whether this Status was the rhs of a move operation. See rep_
  // for details.
  static bool IsMovedFrom(uintptr_t rep);
  static uintptr_t MovedFromRep();

  // Convert between error::Code and the inlined uintptr_t representation used
  // by rep_. See rep_ for details.
  static uintptr_t CodeToInlinedRep(absl::StatusCode code);
  static absl::StatusCode InlinedRepToCode(uintptr_t rep);

  // Converts between StatusRep* and the external uintptr_t representation used
  // by rep_. See rep_ for details.
  static uintptr_t PointerToRep(status_internal::StatusRep* r);
  static status_internal::StatusRep* RepToPointer(uintptr_t r);

  // Returns string for non-ok Status.
  std::string ToStringSlow() const;

  // Status supports two different representations.
  //  - When the low bit is off it is an inlined representation.
  //    It uses the canonical error space, no message or payload.
  //    The error code is (rep_ >> 2).
  //    The (rep_ & 2) bit is the "moved from" indicator, used in IsMovedFrom().
  //  - When the low bit is on it is an external representation.
  //    In this case all the data comes from a heap allocated Rep object.
  //    (rep_ - 1) is a status_internal::StatusRep* pointer to that structure.
  uintptr_t rep_;
};

// OkStatus()
//
// Returns an OK status, equivalent to a default constructed instance. Prefer
// usage of `absl::OkStatus()` when constructing such an OK status.
Status OkStatus();

// operator<<()
//
// Prints a human-readable representation of `x` to `os`.
std::ostream& operator<<(std::ostream& os, const Status& x);

// IsAborted()
// IsAlreadyExists()
// IsCancelled()
// IsDataLoss()
// IsDeadlineExceeded()
// IsFailedPrecondition()
// IsInternal()
// IsInvalidArgument()
// IsNotFound()
// IsOutOfRange()
// IsPermissionDenied()
// IsResourceExhausted()
// IsUnauthenticated()
// IsUnavailable()
// IsUnimplemented()
// IsUnknown()
//
// These convenience functions return `true` if a given status matches the
// `absl::StatusCode` error code of its associated function.
ABSL_MUST_USE_RESULT bool IsAborted(const Status& status);
ABSL_MUST_USE_RESULT bool IsAlreadyExists(const Status& status);
ABSL_MUST_USE_RESULT bool IsCancelled(const Status& status);
ABSL_MUST_USE_RESULT bool IsDataLoss(const Status& status);
ABSL_MUST_USE_RESULT bool IsDeadlineExceeded(const Status& status);
ABSL_MUST_USE_RESULT bool IsFailedPrecondition(const Status& status);
ABSL_MUST_USE_RESULT bool IsInternal(const Status& status);
ABSL_MUST_USE_RESULT bool IsInvalidArgument(const Status& status);
ABSL_MUST_USE_RESULT bool IsNotFound(const Status& status);
ABSL_MUST_USE_RESULT bool IsOutOfRange(const Status& status);
ABSL_MUST_USE_RESULT bool IsPermissionDenied(const Status& status);
ABSL_MUST_USE_RESULT bool IsResourceExhausted(const Status& status);
ABSL_MUST_USE_RESULT bool IsUnauthenticated(const Status& status);
ABSL_MUST_USE_RESULT bool IsUnavailable(const Status& status);
ABSL_MUST_USE_RESULT bool IsUnimplemented(const Status& status);
ABSL_MUST_USE_RESULT bool IsUnknown(const Status& status);

// AbortedError()
// AlreadyExistsError()
// CancelledError()
// DataLossError()
// DeadlineExceededError()
// FailedPreconditionError()
// InternalError()
// InvalidArgumentError()
// NotFoundError()
// OutOfRangeError()
// PermissionDeniedError()
// ResourceExhaustedError()
// UnauthenticatedError()
// UnavailableError()
// UnimplementedError()
// UnknownError()
//
// These convenience functions create an `absl::Status` object with an error
// code as indicated by the associated function name, using the error message
// passed in `message`.
Status AbortedError(absl::string_view message);
Status AlreadyExistsError(absl::string_view message);
Status CancelledError(absl::string_view message);
Status DataLossError(absl::string_view message);
Status DeadlineExceededError(absl::string_view message);
Status FailedPreconditionError(absl::string_view message);
Status InternalError(absl::string_view message);
Status InvalidArgumentError(absl::string_view message);
Status NotFoundError(absl::string_view message);
Status OutOfRangeError(absl::string_view message);
Status PermissionDeniedError(absl::string_view message);
Status ResourceExhaustedError(absl::string_view message);
Status UnauthenticatedError(absl::string_view message);
Status UnavailableError(absl::string_view message);
Status UnimplementedError(absl::string_view message);
Status UnknownError(absl::string_view message);

//------------------------------------------------------------------------------
// Implementation details follow
//------------------------------------------------------------------------------

inline Status::Status() : rep_(CodeToInlinedRep(absl::StatusCode::kOk)) {}

inline Status::Status(absl::StatusCode code) : rep_(CodeToInlinedRep(code)) {}

inline Status::Status(const Status& x) : rep_(x.rep_) { Ref(rep_); }

inline Status& Status::operator=(const Status& x) {
  uintptr_t old_rep = rep_;
  if (x.rep_ != old_rep) {
    Ref(x.rep_);
    rep_ = x.rep_;
    Unref(old_rep);
  }
  return *this;
}

inline Status::Status(Status&& x) noexcept : rep_(x.rep_) {
  x.rep_ = MovedFromRep();
}

inline Status& Status::operator=(Status&& x) {
  uintptr_t old_rep = rep_;
  rep_ = x.rep_;
  x.rep_ = MovedFromRep();
  Unref(old_rep);
  return *this;
}

inline void Status::Update(const Status& new_status) {
  if (ok()) {
    *this = new_status;
  }
}

inline void Status::Update(Status&& new_status) {
  if (ok()) {
    *this = std::move(new_status);
  }
}

inline Status::~Status() { Unref(rep_); }

inline bool Status::ok() const {
  return rep_ == CodeToInlinedRep(absl::StatusCode::kOk);
}

inline absl::string_view Status::message() const {
  return !IsInlined(rep_)
             ? RepToPointer(rep_)->message
             : (IsMovedFrom(rep_) ? absl::string_view(kMovedFromString)
                                  : absl::string_view());
}

inline bool operator==(const Status& lhs, const Status& rhs) {
  return lhs.rep_ == rhs.rep_ || Status::EqualsSlow(lhs, rhs);
}

inline bool operator!=(const Status& lhs, const Status& rhs) {
  return !(lhs == rhs);
}

inline std::string Status::ToString() const {
  return ok() ? "OK" : ToStringSlow();
}

inline void Status::IgnoreError() const {
  // no-op
}

inline void swap(absl::Status& a, absl::Status& b) {
  using std::swap;
  swap(a.rep_, b.rep_);
}

inline const status_internal::Payloads* Status::GetPayloads() const {
  return IsInlined(rep_) ? nullptr : RepToPointer(rep_)->payloads.get();
}

inline status_internal::Payloads* Status::GetPayloads() {
  return IsInlined(rep_) ? nullptr : RepToPointer(rep_)->payloads.get();
}

inline bool Status::IsInlined(uintptr_t rep) { return (rep & 1) == 0; }

inline bool Status::IsMovedFrom(uintptr_t rep) {
  return IsInlined(rep) && (rep & 2) != 0;
}

inline uintptr_t Status::MovedFromRep() {
  return CodeToInlinedRep(absl::StatusCode::kInternal) | 2;
}

inline uintptr_t Status::CodeToInlinedRep(absl::StatusCode code) {
  return static_cast<uintptr_t>(code) << 2;
}

inline absl::StatusCode Status::InlinedRepToCode(uintptr_t rep) {
  assert(IsInlined(rep));
  return static_cast<absl::StatusCode>(rep >> 2);
}

inline status_internal::StatusRep* Status::RepToPointer(uintptr_t rep) {
  assert(!IsInlined(rep));
  return reinterpret_cast<status_internal::StatusRep*>(rep - 1);
}

inline uintptr_t Status::PointerToRep(status_internal::StatusRep* rep) {
  return reinterpret_cast<uintptr_t>(rep) + 1;
}

inline void Status::Ref(uintptr_t rep) {
  if (!IsInlined(rep)) {
    RepToPointer(rep)->ref.fetch_add(1, std::memory_order_relaxed);
  }
}

inline void Status::Unref(uintptr_t rep) {
  if (!IsInlined(rep)) {
    UnrefNonInlined(rep);
  }
}

inline Status OkStatus() { return Status(); }

// Создается объект `Status` с кодом ошибки `absl::StatusCode::kCancelled`
// и пустым сообщением. Это сделано только для эффективности, учитывая, что
// в инфраструктуре часто встречаются ошибки kCancelled без сообщений.
inline Status CancelledError() { return Status(absl::StatusCode::kCancelled); }

ABSL_NAMESPACE_END
}  // namespace absl

#endif  // ABSL_STATUS_STATUS_H_
