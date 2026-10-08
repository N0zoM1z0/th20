#pragma once
#include <cwchar>
// Native Windows uses the actual pinned CRT. Portable fixtures cover only
// valid-input secure wchar calls; their invalid-parameter policy remains open.
#if !defined(_WIN32)
extern "C" int wcscpy_s(wchar_t*, std::size_t, const wchar_t*);
extern "C" int wcscat_s(wchar_t*, std::size_t, const wchar_t*);
#endif
