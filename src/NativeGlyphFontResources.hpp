#pragma once
#include <windows.h>
#include <array>
namespace th20 {
// The original font table spans [0x005B66F0,0x005B6748), exactly 0x58
// bytes: 22 native i386 HFONT words, not the old speculative 32 entries.
// Actual original std::array<_Unchecked_begin/_Unchecked_end> methods
// establish this native fixed extent independently of the GDI text owner.
extern std::array<HFONT,22> native_glyph_fonts_5b66f0;
void release_glyph_fonts_4155b0();
}
