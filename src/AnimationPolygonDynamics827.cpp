// Original 827B polygon segment dynamics: native range and storage semantics
// reconstructed, but the complete parent remains NONEXACT pending COFF replay.
// Original array sizes are independently exposed by the native 0x45FFE0
// (62 floats) and 0x45FFF0 (61 Vector2) array-size accessors. The original
// two C++20 drop(1) ranges use their library iterator/cursor call chains.
#include "NativePolygonSegmentSlot.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Angle.hpp"
#include "GameRandom.hpp"
#include "MotionMath.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <ranges>
namespace th20 {
extern GameRandom native_polygon_random_5ba4c4;
extern const float native_two, native_four, native_pi, native_fifty_nine;

struct NativePolygonGeometryView {
    std::array<Vector2, 61> perimeter;
    std::array<std::uint32_t, 61> colors;
    std::array<float, 62> radius;
};
static_assert(sizeof(NativePolygonGeometryView) == sizeof(NativePolygonSegmentSlot));
static_assert(offsetof(NativePolygonGeometryView, colors) == 0x1E8);
static_assert(offsetof(NativePolygonGeometryView, radius) == 0x2DC);

void NativePolygonSegmentSlot::update_polygon_dynamics_45f670(float limit) {
    auto& geometry = *reinterpret_cast<NativePolygonGeometryView*>(this);
    auto& radius = geometry.radius;
    auto& perimeter = geometry.perimeter;
    radius[0] = 0.0f;
    const float first_radius = radius[0];
    polar(*reinterpret_cast<Vector3*>(&perimeter[0]), 0.0f, first_radius);

    // The original uses a dropped array range, not a handwritten 1..59 loop.
    // It updates indices 1..61, preserving the original COMISS NaN behavior.
    for (float& current_radius : radius | std::views::drop(1)) {
        current_radius += native_polygon_random_5ba4c4.signed_unit() * native_two;
        if (current_radius > limit + native_four) {
            current_radius = limit + native_four;
        } else if (current_radius < limit - native_four) {
            current_radius = limit - native_four;
        }
    }

    Angle angle(0.0f);
    std::int32_t index = 1;
    // 61 vertices, so the native drop view visits points 1..60.
    for (Vector2& vertex : perimeter | std::views::drop(1)) {
        polar(*reinterpret_cast<Vector3*>(&vertex),
              static_cast<float>(angle), radius[index]);
        angle += (native_pi * native_two) / native_fifty_nine;
        ++index;
    }
    // The original explicitly duplicates point 1 into the closure point 60.
    perimeter[60] = perimeter[1];
}
} // namespace th20
