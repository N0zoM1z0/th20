#pragma once
#include "NativeAsciiTextDrawView.hpp"

namespace th20 {
// Borrowed Renderer view. The variadic member passes this and the hidden
// eight-byte result address on the stack, as in the original i386 caller.
struct NativeRendererFormattedTextView : NativeTextSubmitOwner {
    NativeTextDrawResult8 __cdecl draw_formatted_text_44ac20(
        Animation* animation, std::int32_t layer, std::uint32_t color,
        std::int32_t font, std::int32_t horizontal, std::int32_t align,
        std::int32_t mode, std::function<void()> callback,
        const wchar_t* format, ...);
    NativeTextDrawResult8 __cdecl draw_centered_text_44add0(
        Animation* animation, std::int32_t layer, std::uint32_t color,
        std::int32_t font, std::int32_t align, std::int32_t mode,
        std::function<void()> callback, const wchar_t* format, ...);
};
}
