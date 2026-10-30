#pragma once
// Original 0x3D4-byte polygon segment, as recovered from three distinct
// native constructors and the whole-exact 827-byte dynamic-update parent.
#include "Vector2.hpp"
#include "AnimationHandle.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
namespace th20 {
struct NativePolygonSegmentSlot {
    std::array<Vector2,61> perimeter;
    // These 4B packed-color cells use a physically folded zero constructor
    // accepted under AnimationHandle; original source type remains unknown.
    std::array<AnimationHandle,61> color_handles;
    std::array<float,62> radius;

    NativePolygonSegmentSlot();
    void initialize_palette_45fc90(std::uint32_t diffuse_color);
    // Original complete 827B/237-x86 dynamic update: whole native strict exact.
    void update_polygon_dynamics_45f670(float limit);
};
static_assert(sizeof(NativePolygonSegmentSlot)==0x3D4);
static_assert(offsetof(NativePolygonSegmentSlot,perimeter)==0);
static_assert(offsetof(NativePolygonSegmentSlot,color_handles)==0x1E8);
static_assert(offsetof(NativePolygonSegmentSlot,radius)==0x2DC);
}
