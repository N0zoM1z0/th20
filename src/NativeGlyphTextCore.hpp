#pragma once
#include "NativeAsciiTextDrawView.hpp"
#include <cstdint>
#include <functional>
namespace th20 {
// The native text-core has no receiver and returns the text extent packed
// into EDX:EAX. The native +0x10 word is GDI text color and the native
// +0x14 word is the separate glyph-mask outline color. Native +0x2C
// holds a completion-byte pointer borrowed by the captured render job.
// The trailing by-value
// std::function owns the queued job.
std::uint64_t __cdecl native_text_core_415830(
    const NativeTextTransform4* transform, std::int32_t horizontal_offset,
    std::int32_t text_color_word, std::uint32_t outline_color, const char* formatted,
    IDirect3DBaseTexture9* texture, std::int32_t font, std::int32_t align,
    std::int32_t is_special, std::uint8_t* completion_flag,
    std::function<void()> callback);
}
