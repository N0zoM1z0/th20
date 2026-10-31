#pragma once
#include <array>
#include <cstdint>
#include <memory_resource>
#include <vector>
namespace th20 {
// The original 2,245B Boss has FOUR genuine E8 to the folded 22B
// std::array<int32_t,2>::operator[] / native 0x00414580: once each for
// the live x and y coordinates in both BGRA32 and RGBA4444 paths.
// A custom struct with two fields is byte-compatible but hides four
// physical original callable operations from this large game method.
using GlyphMaskOffset = std::array<std::int32_t, 2>;
using GlyphMaskOffsets = std::pmr::vector<GlyphMaskOffset>;
static_assert(sizeof(GlyphMaskOffset)==8);
#if defined(_M_IX86)
static_assert(sizeof(GlyphMaskOffsets)==16);
#endif
}
