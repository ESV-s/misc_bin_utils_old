#pragma once
/**
* \file function_utils.h
* \brief Вспомогательные функции для безопасной работы с функциями IDA:
*        классификация адреса (Head / TailChunk / Thunk), сбор tail-чанков,
*        разворачивание thunk-функций в целевую точку.
*
* \details Файл предназначен для IDA 7.6 (Windows, VS2015, C++14).
*          Все публичные сущности снабжены Doxygen-комментариями.
*/

#include <ida.hpp>      ///< Базовые типы/константы IDA (ea_t, BADADDR, и т.п.).
#include <funcs.hpp>    ///< Описание func_t и работы с функциями (get_func, флаги, итераторы).
#include <ua.hpp>       ///< Декодер инструкций (decode_insn), тип insn_t, UA_MAXOP.
//#include <allins.hpp>   ///< Описания мнемоник (is_jmp_insn можно реализовать вручную при необходимости).
#include <vector>       ///< STL контейнер std::vector.

/**
* \enum FuncKind
* \brief Тип классификации адреса/функции.
*
* \var FuncKind::None
*      Адрес не принадлежит никакой функции (get_func вернул nullptr).
* \var FuncKind::Head
*      Обычная функция (головной чанк), не tail и не thunk.
* \var FuncKind::TailChunk
*      Хвостовой чанк функции (FUNC_TAIL). У него нет собственного фрейма/аргументов.
* \var FuncKind::Thunk
*      Функция-обёртка/переадресатор (FUNC_THUNK), чаще всего делает jmp на цель.
*/
enum class FuncKind { None, Head, TailChunk, Thunk };

/**
* \struct FuncClassify
* \brief Результат классификации функции по адресу.
*
* \var FuncClassify::kind
*      Определённый вид (None / Head / TailChunk / Thunk).
* \var FuncClassify::this_chunk
*      То, что вернул get_func(ea). Может быть head либо tail-чанк.
* \var FuncClassify::head
*      Владелец: если это tail — тут будет указатель на голову; если head/thunk — совпадает с this_chunk.
*/
struct FuncClassify {
	FuncKind kind = FuncKind::None;
	func_t*  this_chunk = nullptr;
	func_t*  head = nullptr;
};

/**
* \brief Классифицирует адрес: определяет, является ли он частью head, tail-chunk или thunk.
* \param ea Адрес внутри предполагаемой функции.
* \return Структура FuncClassify с заполненными полями kind/this_chunk/head.
*
* \par Условия
* - \b if: get_func(ea) == nullptr → вернём kind=None (адрес вне функций).
* - \b else-if: у функции стоит флаг FUNC_TAIL → kind=TailChunk и head будет владельцем.
* - \b else-if: стоит флаг FUNC_THUNK → kind=Thunk и head=this_chunk.
* - \b else: обычная голова → kind=Head и head=this_chunk.
*/
FuncClassify ClassifyFunction(ea_t ea);

/**
* \brief Возвращает все диапазоны кода (head + tails) конкретной функции.
* \param head Указатель на головную функцию (НЕ tail).
* \return Вектор диапазонов range_t (включая голову как первый элемент).
*
* \par Примечание
* Итератор func_tail_iterator_t проходит сначала head-чанк, затем все tail-чанки.
* Это удобно для суммирования «полезного» размера функции без двойного учёта.
*/
std::vector<range_t> CollectAllChunks(const func_t* head);

/**
* \brief Резолвит цель thunk-функции (куда она переадресует вызов).
* \param f Указатель на \b НЕконстантную func_t (важно для IDA 7.6 API).
* \return Адрес целевой функции (ea_t) или BADADDR, если определить не удалось.
*
* \details В IDA 7.6 сигнатура штатной функции такая:
*          \code
*          ea_t calc_thunk_func_target(func_t *pfn, ea_t *pthunk_target);
*          \endcode
*          Поэтому сюда передаётся \b func_t* (НЕ const), и первый аргумент — это pfn.
*
* \par Алгоритм
* - \b if: f == nullptr \b или у функции нет флага FUNC_THUNK → вернуть BADADDR.
* - Иначе сначала пробуем штатную calc_thunk_func_target(f, &target).
*   - \b if: она вернула адрес != BADADDR → сразу вернуть его.
* - \b else: фолбэк — декодируем первую инструкцию и пытаемся вытащить прямой jmp near/far.
*/
ea_t ResolveThunkTarget(func_t* f);