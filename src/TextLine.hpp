#pragma once

#include "Vector3.hpp"

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace th20 {

// REF-022: native ASCII queue records have a 0x140-byte stride.
struct TextLine {
    char text[256];
    Vector3 position;
    std::uint32_t color;
    std::uint32_t blend;
    float scale_x;
    float scale_y;
    float rotation;
    std::uint32_t field_120;
    std::uint32_t field_124;
    std::int32_t font;
    std::uint32_t shadow;
    std::int32_t layer;
    std::int32_t frames;
    std::uint32_t align_x;
    std::uint32_t align_y;

    TextLine();
};

static_assert(sizeof(TextLine) == 0x140);
static_assert(offsetof(TextLine, position) == 0x100);
static_assert(offsetof(TextLine, color) == 0x10C);
static_assert(offsetof(TextLine, blend) == 0x110);
static_assert(offsetof(TextLine, scale_x) == 0x114);
static_assert(offsetof(TextLine, scale_y) == 0x118);
static_assert(offsetof(TextLine, rotation) == 0x11C);
static_assert(offsetof(TextLine, field_120) == 0x120);
static_assert(offsetof(TextLine, field_124) == 0x124);
static_assert(offsetof(TextLine, font) == 0x128);
static_assert(offsetof(TextLine, shadow) == 0x12C);
static_assert(offsetof(TextLine, layer) == 0x130);
static_assert(offsetof(TextLine, frames) == 0x134);
static_assert(offsetof(TextLine, align_x) == 0x138);
static_assert(offsetof(TextLine, align_y) == 0x13C);
static_assert(std::is_trivially_copyable_v<TextLine>);

} // namespace th20
