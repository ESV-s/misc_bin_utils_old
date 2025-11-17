/**
* \file function_utils.cpp
* \brief Реализация утилит для работы с функциями IDA (классификация, чанки, thunk-цели).
*/

#include "function_utils.h"
#include <name.hpp>     ///< Чтобы получить имя по адресу (get_ea_name), если нужно.

/**
* \brief Внутренняя функция: получить владельца (head) для tail-чанка.
* \param f Указатель на func_t (может быть head или tail).
* \return Если f - tail, вернётся владелец (head). Если f - head, вернётся f. Если nullptr - nullptr.
*
* \par Условия
* - \b if: f == nullptr → возвращаем nullptr.
* - \b else-if: !(f->flags & FUNC_TAIL) → это не хвост, возвращаем f как голову.
* - \b else: перебираем все head-функции и их хвосты; если диапазон tail совпал — это и есть владелец.
*/
static func_t* ResolveHead(func_t* f)
{
	if (!f) {                          ///< [if] Нет входной функции — вернуть nullptr.
		return nullptr;
	}

	if ((f->flags & FUNC_TAIL) == 0) { ///< [else-if] Это не хвост — значит уже head.
		return f;                        ///< Возвращаем её как голову.
	}

	// [else] Это tail: ищем его владельца (head) перебором всех функций в базе.
	for (func_t* hf = get_next_func(inf.min_ea);  ///< Начинаем с минимального адреса базы.
		hf != nullptr;                            ///< Пока есть функции...
		hf = get_next_func(hf->end_ea))           ///< Переходим к следующей.
	{
		func_tail_iterator_t it(hf);                 ///< Итератор по чанкам конкретной head-функции.
		for (bool ok = it.first(); ok; ok = it.next()) {
			const range_t& r = it.chunk();             ///< Текущий чанк (диапазон адресов).
													   // Сравниваем диапазон tail-чанка с текущим диапазоном итератора.
			if (f->start_ea == r.start_ea && f->end_ea == r.end_ea) {
				return hf;                               ///< Нашли совпадение — hf и есть владелец (head).
			}
		}
	}
	return nullptr;                                ///< Владелец не найден (маловероятно) — вернуть nullptr.
}

/**
* \copydoc ClassifyFunction
*/
FuncClassify ClassifyFunction(ea_t ea)
{
	FuncClassify out{};                            ///< Результат по умолчанию: kind=None, указатели = nullptr.

	out.this_chunk = get_func(ea);                 ///< Запрашиваем у IDA функцию, в которой лежит адрес.
	if (!out.this_chunk) {                         ///< [if] Если адрес вне функций — оставляем kind=None.
		return out;                                  ///< Возвращаем пустую классификацию.
	}

	out.head = ResolveHead(out.this_chunk);        ///< Определяем владельца (для tail) или саму голову.

	if (out.this_chunk->flags & FUNC_TAIL) {       ///< [if] Хвостовой чанк?
		out.kind = FuncKind::TailChunk;              ///< Да — помечаем как TailChunk.
	}
	else if (out.this_chunk->flags & FUNC_THUNK) { ///< [else-if] Thunk?
		out.kind = FuncKind::Thunk;                  ///< Да — помечаем как Thunk.
	}
	else {                                         ///< [else] Обычная голова.
		out.kind = FuncKind::Head;                   ///< Помечаем как Head.
	}

	return out;                                    ///< Возвращаем заполненный результат.
}

/**
* \copydoc CollectAllChunks
*/
std::vector<range_t> CollectAllChunks(const func_t* head)
{
	std::vector<range_t> chunks;                   ///< Контейнер STL для хранения диапазонов (head + tails).
	if (!head) {                                   ///< [if] Нет головы — возвращаем пустой вектор.
		return chunks;
	}

	func_tail_iterator_t it(const_cast<func_t*>(head)); ///< Итератор IDA требует неконстантный указатель.
	for (bool ok = it.first(); ok; ok = it.next()) {    ///< Проходим все чанки: сначала head, потом хвосты.
		chunks.push_back(it.chunk());                     ///< Кладём текущий диапазон в вектор (по значению).
	}
	return chunks;                                      ///< Возвращаем собранные диапазоны.
}

/**
* \copydoc ResolveThunkTarget
*/
ea_t ResolveThunkTarget(func_t* f)
{
	if (!f || (f->flags & FUNC_THUNK) == 0) {      ///< [if] Нет функции ИЛИ это не thunk — вернуть BADADDR.
		return BADADDR;
	}

	ea_t target = BADADDR;                          ///< Переменная для целевого адреса (инициализируем BADADDR).

													// 1) Штатный способ IDA 7.6:
													//    сигнатура: ea_t calc_thunk_func_target(func_t *pfn, ea_t *pthunk_target);
													//    Первый аргумент — сама функция, второй — указатель, куда можно записать адрес.
	ea_t ret = calc_thunk_func_target(f, &target);  ///< Вызываем API: вернёт адрес цели ИЛИ BADADDR.

	if (ret != BADADDR) {                           ///< [if] Если вернулся валидный адрес...
		return ret;                                   ///< ...то это и есть целевая точка thunk.
	}
	// [else] ret == BADADDR: штатная функция не помогла; возможно редкий формат thunk,
	// поэтому попробуем фолбэк-детекцию по первой инструкции.

	insn_t insn;                                    ///< Объект для хранения декодированной инструкции.
	if (decode_insn(&insn, f->start_ea) > 0) {      ///< [if] Если удалось декодировать первую инструкцию...
													// Простейший случай: прямой jmp (relative/absolute). В разных процессорах
													// вид jmр может отличаться; здесь мы не проверяем мнемонику напрямую, а
													// пытаемся вытащить целевой операнд подходящего типа.
		for (int i = 0; i < UA_MAXOP; ++i) {          ///< Перебираем все операнды инструкции.
			auto &op = insn.ops[i];                     ///< Удобная ссылка на текущий операнд.
			if (op.type == o_near || op.type == o_far) {///< [if] Операнд — адрес перехода (near/far)?
				return to_ea(insn.cs, op.addr);           ///< Конвертируем адрес с учётом сегмента и возвращаем.
			}
			else {                                    ///< [else] Операнд не является адресом — продолжаем поиск.
				/* ничего не делаем, идём к следующему операнду */;
			}
		}
	}
	else {                                        ///< [else] decode_insn не смог декодировать инструкцию.
		/* ничего не делаем — просто упадём в BADADDR ниже */;
	}

	return BADADDR;                                  ///< Ничего не нашли — вернуть BADADDR.
}