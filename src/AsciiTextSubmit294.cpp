// Original 294B text submit Boss, full two-path game source, NONEXACT.
// The core's genuine EDX:EAX uint64 result is published directly into the
// native hidden eight-byte result object, separately in each real path.
// Pinned MSVC i386 emits 292B/104 instructions versus 294B/106 original:
// only two original compiler-generated post-destructor NOPs are absent.
// The exact original full 294B extent is NOT claimed or truncated.
#include "NativeAsciiTextDrawView.hpp"
#include "NativeGlyphTextCore.hpp"
#include <cstdint>
#include <functional>
namespace th20 {
// The separately original 2227-byte text renderer core at 0x00415830.
// Its complete implementation and original C++ spelling remain unresolved.

// This is an explicitly MSVC-i386-specific representation operation:
// the same eight valid return bytes are written as a packed integer and
// read as the original pair of 32-bit result words. It does not allocate
// an extra buffer, invent a helper call or change native pixel semantics.
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
            texture, font, align, 1, mode, callback);
        return out;
    } else {
        NativeTextDrawResult8 out;
        *reinterpret_cast<std::uint64_t*>(&out)=native_text_core_415830(
            transform, horizontal_offset, layer, 0, formatted,
            texture, font, align, 0, mode, callback);
        return out;
    }
}

} // namespace th20
