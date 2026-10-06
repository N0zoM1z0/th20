#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

// Native remap selects one of five words for each of sixteen color records.
struct BulletColorStyle {
    std::uint32_t words[5];
};

struct BulletStyle {
    std::uint32_t script;
    BulletColorStyle colors[16];
    float radius;
    std::uint32_t draw_group;
    std::uint32_t cancel_type;
    std::uint32_t word_150;
    std::uint32_t child_script;
};

static_assert(sizeof(BulletColorStyle) == 20);
static_assert(sizeof(BulletStyle) == 0x158);
static_assert(offsetof(BulletStyle, colors) == 4);
static_assert(offsetof(BulletStyle, radius) == 0x144);
static_assert(offsetof(BulletStyle, child_script) == 0x154);

// Actual writable BSS array, populated by native startup401280. Its storage and
// original initializer remain undefined in maintained production source.
extern BulletStyle bullet_styles[50];
// Valid type indices are0..49, matching the original unchecked array access.
float bullet_radius(std::int32_t type);

} // namespace th20
