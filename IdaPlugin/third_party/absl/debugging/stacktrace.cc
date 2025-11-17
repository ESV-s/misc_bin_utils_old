// Copyright 2017 The Abseil Authors.
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

// Произвести трассировку стека.
//
// Мы можем попытаться получить трассировку стека тремя различными способами:
//
// 1) Наш ручной распутыватель стеков.  Это зависит от определенной разметки стека,
//    которая используется gcc (и системами, использующими
//	  gcc-совместимый ABI) на системах x86, по крайней мере, начиная с gcc 2.95.
//    Для своей работы он использует указатель кадра.
//
// 2) Библиотека libunwind.  Она находится в стадии разработки и
//    как отдельная библиотека добавляет новую зависимость,
//    но не требует указателя кадра.  Она также не вызывает malloc.
//
// 3) Разматыватель gdb - также тот, который используется кодом исключения c++.
//    Очевидно, что он хорошо протестирован, но имеет фатальный недостаток:
//    он может вызывать malloc() из разматывателя.  Это проблема,
//    потому что мы пытаемся использовать разматыватель для инструмента malloc().
//
// Примечание: если вы добавите сюда новую реализацию, убедитесь, что она работает
// корректно при вызове absl::GetStackTrace() с max_depth == 0.
// В некоторых кодах это может происходить.

#include "third_party/absl/debugging/stacktrace.h"

#include <atomic>

#include "third_party/absl/base/attributes.h"
#include "third_party/absl/base/port.h"
#include "third_party/absl/debugging/internal/stacktrace_config.h"

#if defined(ABSL_STACKTRACE_INL_HEADER)
#include ABSL_STACKTRACE_INL_HEADER
#else
# error Cannot calculate stack trace: will need to write for your environment

# include "third_party/absl/debugging/internal/stacktrace_aarch64-inl.inc"
# include "third_party/absl/debugging/internal/stacktrace_arm-inl.inc"
# include "third_party/absl/debugging/internal/stacktrace_generic-inl.inc"
# include "third_party/absl/debugging/internal/stacktrace_powerpc-inl.inc"
# include "third_party/absl/debugging/internal/stacktrace_unimplemented-inl.inc"
# include "third_party/absl/debugging/internal/stacktrace_win32-inl.inc"
# include "third_party/absl/debugging/internal/stacktrace_x86-inl.inc"
#endif

namespace absl {
	ABSL_NAMESPACE_BEGIN
		namespace {

		typedef int(*Unwinder)(void**, int*, int, int, const void*, int*);
		std::atomic<Unwinder> custom;

		template <bool IS_STACK_FRAMES, bool IS_WITH_CONTEXT>
		ABSL_ATTRIBUTE_ALWAYS_INLINE inline int Unwind(void** result, int* sizes,
			int max_depth, int skip_count,
			const void* uc,
			int* min_dropped_frames) {
			Unwinder f = &UnwindImpl<IS_STACK_FRAMES, IS_WITH_CONTEXT>;
			Unwinder g = custom.load(std::memory_order_acquire);
			if (g != nullptr) f = g;

			// Add 1 - счетчик пропусков для самой функции размотки
			int size = (*f)(result, sizes, max_depth, skip_count + 1, uc,
				min_dropped_frames);
			// Для отключения вызова хвоста (*f)(...)
			ABSL_BLOCK_TAIL_CALL_OPTIMIZATION();
			return size;
		}

	}  // anonymous namespace

	ABSL_ATTRIBUTE_NOINLINE ABSL_ATTRIBUTE_NO_TAIL_CALL int GetStackFrames(
		void** result, int* sizes, int max_depth, int skip_count) {
		return Unwind<true, false>(result, sizes, max_depth, skip_count, nullptr,
			nullptr);
	}

	ABSL_ATTRIBUTE_NOINLINE ABSL_ATTRIBUTE_NO_TAIL_CALL int
		GetStackFramesWithContext(void** result, int* sizes, int max_depth,
			int skip_count, const void* uc,
			int* min_dropped_frames) {
		return Unwind<true, true>(result, sizes, max_depth, skip_count, uc,
			min_dropped_frames);
	}

	ABSL_ATTRIBUTE_NOINLINE ABSL_ATTRIBUTE_NO_TAIL_CALL int GetStackTrace(
		void** result, int max_depth, int skip_count) {
		return Unwind<false, false>(result, nullptr, max_depth, skip_count, nullptr,
			nullptr);
	}

	ABSL_ATTRIBUTE_NOINLINE ABSL_ATTRIBUTE_NO_TAIL_CALL int
		GetStackTraceWithContext(void** result, int max_depth, int skip_count,
			const void* uc, int* min_dropped_frames) {
		return Unwind<false, true>(result, nullptr, max_depth, skip_count, uc,
			min_dropped_frames);
	}

	void SetStackUnwinder(Unwinder w) {
		custom.store(w, std::memory_order_release);
	}

	int DefaultStackUnwinder(void** pcs, int* sizes, int depth, int skip,
		const void* uc, int* min_dropped_frames) {
		skip++;  // For this function
		Unwinder f = nullptr;
		if (sizes == nullptr) {
			if (uc == nullptr) {
				f = &UnwindImpl<false, false>;
			}
			else {
				f = &UnwindImpl<false, true>;
			}
		}
		else {
			if (uc == nullptr) {
				f = &UnwindImpl<true, false>;
			}
			else {
				f = &UnwindImpl<true, true>;
			}
		}
		volatile int x = 0;
		int n = (*f)(pcs, sizes, depth, skip, uc, min_dropped_frames);
		x = 1; (void)x;  // Для отключения вызова хвоста (*f)(...)
		return n;
	}

	ABSL_NAMESPACE_END
}  // namespace absl
