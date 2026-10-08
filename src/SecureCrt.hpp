#pragma once
#include <cstdarg>
#include <cstdio>
#include <cstring>

// Windows uses its actual secure CRT declarations and fixed-array overload.
// Portable CPU fixtures implement only the valid-input CRT boundary.
#if !defined(_WIN32)
extern "C" int vsprintf_s(char*, std::size_t, const char*, std::va_list);
extern "C" int strcpy_s(char*, std::size_t, const char*);
template<std::size_t Size>
int vsprintf_s(char (&buffer)[Size], const char* format, std::va_list arguments) {
    return vsprintf_s(buffer, Size, format, arguments);
}
#endif
