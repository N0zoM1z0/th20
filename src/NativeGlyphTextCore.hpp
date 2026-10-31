#pragma once
#include "NativeAsciiTextDrawView.hpp"
#include <cstdint>
#include <functional>
namespace th20 {
// The native text-core has no receiver and returns the text extent packed
// into EDX:EAX. The trailing by-value std::function owns the queued job.
std::uint64_t __cdecl native_text_core_415830(
    const NativeTextTransform4* transform, std::int32_t horizontal_offset,
    std::int32_t layer, std::uint32_t color, const char* formatted,
    IDirect3DBaseTexture9* texture, std::int32_t font, std::int32_t align,
    std::int32_t is_special, std::int32_t mode,
    std::function<void()> callback);
}
