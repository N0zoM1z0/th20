// Native two-path text submission with a by-value callback and hidden 8B result.
// The complete source body is 292B; the original 294B additionally retains
// two NOPs after parameter destruction on the returning paths.
#include "NativeAsciiTextDrawView.hpp"
#include "NativeGlyphTextCore.hpp"
#include <cstdint>
#include <functional>
namespace th20 {
// On the locked MSVC x86 ABI, write the core's packed EDX:EAX result into
// the returned two-word object without an additional intermediate object.
#if defined(_M_IX86)
static_assert(sizeof(NativeTextDrawResult8) == sizeof(std::uint64_t));
#endif
NativeTextDrawResult8 NativeTextSubmitOwner::submit_text_44fff0(
    IDirect3DBaseTexture9* texture, SpriteData* sprite,
    std::int32_t horizontal_offset, std::int32_t layer,
    std::uint32_t color, const char* formatted,
    std::int32_t bit10, std::int32_t font,
    std::int32_t align, const NativeTextTransform4* transform,
    std::int32_t mode, std::function<void()> callback)
{
    if (bit10 == 0) {
        NativeTextDrawResult8 out;
        *reinterpret_cast<std::uint64_t*>(&out)=native_text_core_415830(
            transform, horizontal_offset, layer, color, formatted,
            texture, font, align, 1, reinterpret_cast<std::uint8_t*>(mode), callback);
        return out;
    } else {
        NativeTextDrawResult8 out;
        *reinterpret_cast<std::uint64_t*>(&out)=native_text_core_415830(
            transform, horizontal_offset, layer, 0, formatted,
            texture, font, align, 0, reinterpret_cast<std::uint8_t*>(mode), callback);
        return out;
    }
}

} // namespace th20
