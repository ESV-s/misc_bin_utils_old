// ===== debug_log.h — лёгкий логгер для Visual Studio / IDA =====
#pragma once
#include <windows.h>
#include <cstdio>
#include <cstdarg>


/**
			как использовать


	#include "debug_log.h"

	void SomeInit()
	{
	TRACE_SCOPE();                 // зафиксирует вход/выход + время
	TRACE("init started");         // простая строка
	TRACEF("value=%d, ptr=%p", 42, this);  // форматированная строка
	}

	bool RunPass(int n)
	{
	TRACE_SCOPE();
	if (n == 0) TRACE("first pass");
	// ...
	return true;
	}

			что куда выводится

	Всегда: окно Output → Debug в Visual Studio (OutputDebugStringA).
	Если запустишь IDA под отладчиком и загрузишь плагин — логи видны сразу.
	Если хочешь лог в Release без отладчика, включи DYNLOG_TO_FILE=1 — будет писаться в %TEMP%\IdaPlugin.log.


			включение для Debug/Release

	самый удобный способ — добавить в Project → C/C++ → Preprocessor:
	для обоих конфигов: DYNLOG_ENABLE=1
	(или по вкусу: только для Debug, а в Release включать локально в нужных местах)

			быстрый «только имя функции» без RAII

	если хочешь максимально коротко и дёшево:
	#define TRACE_FN()  do{ ::dbg_gpt::printf("%s\r\n", __FUNCTION__); }while(0)
	Ставь TRACE_FN(); первой строкой каждой функции — и получишь линейный список вызовов в окне Output.

	чат  - обсуждение стека и кучи часть 2 ...

 */

namespace dbg_gpt {

	// ВЫКЛ/ВКЛ (определи DYNLOG_ENABLE в Project → C/C++ → Preprocessor → Preprocessor Definitions)
	// чтобы лог работал и в Debug, и в Release. Если не хочешь менять проект — просто оставь #if ниже.
#if !defined(DYNLOG_ENABLE)
#  if defined(_DEBUG)
#    define DYNLOG_ENABLE 1
#  else
#    define DYNLOG_ENABLE 1   // ← поставь 0, если в Release по умолчанию не нужно
#  endif
#endif

	// Опционально: лог в файл (temp\IdaPlugin.log). Поставь 1, если нужно.
#ifndef DYNLOG_TO_FILE
#define DYNLOG_TO_FILE 0
#endif

	// Опционально: дублировать в окно IDA (msg). По умолчанию выкл.
#ifndef DYNLOG_TO_IDA
#define DYNLOG_TO_IDA 0
#endif

	// ——— низкоуровневая отправка строки
	inline void out_rawA(const char* s) {
		::OutputDebugStringA(s);                  // окно Output в Visual Studio
#if DYNLOG_TO_FILE
		char tp[MAX_PATH]; DWORD n = GetTempPathA(MAX_PATH, tp);
		char fp[MAX_PATH]; _snprintf_s(fp, _TRUNCATE, "%sIdaPlugin.log", tp);
		FILE* f = nullptr; fopen_s(&f, fp, "ab");
		if (f) { fputs(s, f); fclose(f); }
#endif
#if DYNLOG_TO_IDA
		extern "C" void msg(const char *format, ...); // из SDK IDA
		msg("%s", s);
#endif
	}

	// printf-подобный форматтер
	inline void printfv(const char* fmt, va_list ap) {
		char buf[2048];
		_vsnprintf_s(buf, _TRUNCATE, fmt, ap);
		out_rawA(buf);
	}

	inline void printf(const char* fmt, ...) {
		va_list ap; va_start(ap, fmt);
		printfv(fmt, ap);
		va_end(ap);
	}

	// RAII-трейсер входа/выхода из функции
	struct ScopeTrace {
		const char* func;
		DWORD tid;
		LARGE_INTEGER t0;
		ScopeTrace(const char* f) : func(f), tid(GetCurrentThreadId()) {
			QueryPerformanceCounter(&t0);
			char line[256];
			_snprintf_s(line, _TRUNCATE, "--> %s (tid=%lu)\r\n", func, (unsigned long)tid);
			out_rawA(line);
		}
		~ScopeTrace() {
			LARGE_INTEGER t1, freq; QueryPerformanceCounter(&t1); QueryPerformanceFrequency(&freq);
			double ms = (t1.QuadPart - t0.QuadPart) * 1000.0 / (double)freq.QuadPart;
			char line[256];
			_snprintf_s(line, _TRUNCATE, "<-- %s (%.3f ms)\r\n", func, ms);
			out_rawA(line);
		}
	};

} // namespace dbg

  // ——— Макросы верхнего уровня — используешь их в коде ———
#if DYNLOG_ENABLE
#define TRACE_SCOPE()      ::dbg_gpt::ScopeTrace __trace_scope__(__FUNCTION__)
#define TRACEF(fmt, ...)   do{ ::dbg_gpt::printf("[%s] " fmt "\r\n", __FUNCTION__, __VA_ARGS__); }while(0)
#define TRACE(msg)         do{ ::dbg_gpt::printf("[%s] %s\r\n", __FUNCTION__, msg); }while(0)
#else
#define TRACE_SCOPE()      ((void)0)
#define TRACEF(...)        ((void)0)
#define TRACE(msg)         ((void)0)
#endif

#define TRACE_FN()  do{ ::dbg_gpt::printf("%s\r\n", __FUNCTION__); }while(0)

  // ===== end debug_log.h =====
