#pragma once
#include <cstdint>
namespace th20 {
// Immutable native lookup table entries are exactly six 32-bit words /0x18.
// The signed code ends at -1; bit depth and the original four packed channel
// masks are read by the whole original 681B GDI bitmap creation function.
struct NativeGlyphPixelFormat {
    std::int32_t code;
    std::uint32_t bits_per_pixel, alpha_mask, red_mask, green_mask, blue_mask;
};
static_assert(sizeof(NativeGlyphPixelFormat)==0x18);
}
