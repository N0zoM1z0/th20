// Whole original 274B/71-i386 game GDI glyph text extent Boss at 0x004156E0.
// The source deliberately preserves native CP932 conversion, the actual
// 22-font array, direct GetDC(window getter) call (no extra HWND local),
// original GDI SelectObject lifetime and packed SIZE EDX:EAX return.
#include "NativeGlyphFontResources.hpp"
#include "NativeGlyphWindowHostView.hpp"
#include <windows.h>
#include <cstdint>
#include <cstring>
#include <cwchar>
namespace th20 {
std::uint64_t __cdecl measure_glyph_text_4156e0(const char* encoded,
                                                  std::int32_t font) {
    HFONT selected_font=native_glyph_fonts_5b66f0[font];
    wchar_t unicode[257];
    std::memset(unicode,0,0x202);
    MultiByteToWideChar(932,0,encoded,-1,unicode,0x100);
    HDC dc=GetDC(native_window_host_5b6758.current_window_40c300());
    HGDIOBJ previous=SelectObject(dc,selected_font);
    std::uint32_t length=static_cast<std::uint32_t>(std::wcslen(unicode));
    SIZE extent;
    GetTextExtentPoint32W(dc,unicode,length,&extent);
    extent.cx+=4;
    extent.cy+=4;
    SelectObject(dc,previous);
    // Original Windows i386 ABI returns two 32-bit SIZE fields in EDX:EAX.
    // This intentionally preserves the native packed representation rather
    // than adding a synthesized 64-bit shift or an extra return-copy local.
    return *reinterpret_cast<const std::uint64_t*>(&extent);
}
}
