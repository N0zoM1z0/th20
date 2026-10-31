#pragma once
#include <cstdint>
#include <memory_resource>
#include <vector>
namespace th20 {
// The original 2,245B glyph compositor creates two 16B PMR vectors of
// signed two-word displacements, once for each supported pixel format.
struct GlyphMaskOffset {
    std::int32_t x, y;
};
using GlyphMaskOffsets = std::pmr::vector<GlyphMaskOffset>;
static_assert(sizeof(GlyphMaskOffset)==8);
#if defined(_M_IX86)
static_assert(sizeof(GlyphMaskOffsets)==16);
#endif
}
