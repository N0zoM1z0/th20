#pragma once
#include <cstdarg>

namespace th20 {
// The native wrapper forwards a 0x500-byte buffer to narrow vsprintf_s.
void __cdecl format_text_447940(char* output, const char* pattern, std::va_list arguments);
}
