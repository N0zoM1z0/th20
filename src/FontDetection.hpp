#pragma once
#include <Windows.h>
#include <cstdint>

namespace th20 {

// Native font enumeration selects one of three availability bytes through
// this global pointer. Original font initialization/storage remain undefined.
extern std::uint8_t* current_font_probe;
int CALLBACK mark_font_available(const LOGFONTW*, const TEXTMETRICW*, DWORD, LPARAM);

} // namespace th20
