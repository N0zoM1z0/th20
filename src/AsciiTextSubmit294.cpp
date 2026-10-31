// Original 294B text submit member: complete two-path native gameplay source.
// Original strict matching remains open: the 2227B core returns packed 64-bit
// integer output, while this member returns the eight-byte result aggregate.
// At pinned /Od the natural two-path C++ owner still generates 319B, not the
// original 294B, though all seven genuine call identities are preserved.
#include "NativeAsciiTextDrawView.hpp"
#include "NativeGlyphTextCore.hpp"
#include <cstdint>
#include <functional>
namespace th20 {
// The separately original 2227-byte text renderer core at 0x00415830.
// Its complete implementation and original C++ spelling remain unresolved.

// MSVC's native 8-byte return has the two 32-bit fields as one packed word;
// the observed 2227B core returns the same data directly in EDX:EAX.
union NativePackedTextResult {
    std::uint64_t packed;
    NativeTextDrawResult8 fields;
};
#if defined(_M_IX86)
static_assert(sizeof(NativePackedTextResult) == 8);
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
        NativePackedTextResult result;
        result.packed = native_text_core_415830(
            transform, horizontal_offset, layer, color, formatted,
            texture, font, align, 1, mode, callback);
        return result.fields;
    } else {
        NativePackedTextResult result;
        result.packed = native_text_core_415830(
            transform, horizontal_offset, layer, 0, formatted,
            texture, font, align, 0, mode, callback);
        return result.fields;
    }
}
} // namespace th20
