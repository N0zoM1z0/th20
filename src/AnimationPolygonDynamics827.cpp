// Original full 827B polygon dynamics Boss. Authentic two C++20 dropped
// arrays, first vertex pointer, ordered index/Angle lifetimes and native ABI.
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
    reinterpret_cast<NativePolygonGeometryView*>(this)->radius[0] = 0.0f;
    const float first_radius = reinterpret_cast<NativePolygonGeometryView*>(this)->radius[0];
    Vector3* const initial_point = reinterpret_cast<Vector3*>(&reinterpret_cast<NativePolygonGeometryView*>(this)->perimeter[0]);
    polar(*initial_point, 0.0f, first_radius);

    // Native std::views::drop(1) visits radii 1..61, with COMISS bounds.
    for (float& current_radius : reinterpret_cast<NativePolygonGeometryView*>(this)->radius | std::views::drop(1)) {
        current_radius += native_polygon_random_5ba4c4.signed_unit() * native_two;
        if (current_radius > limit + native_four) {
            current_radius = limit + native_four;
        } else if (current_radius < limit - native_four) {
            current_radius = limit - native_four;
        }
    }

    std::int32_t index = 1;
    Angle angle(0.0f);
    // This second native drop view visits vertices 1..60.
    for (Vector2& vertex : reinterpret_cast<NativePolygonGeometryView*>(this)->perimeter | std::views::drop(1)) {
        polar(*reinterpret_cast<Vector3*>(&vertex),
              static_cast<float>(angle), reinterpret_cast<NativePolygonGeometryView*>(this)->radius[index]);
        angle += (native_pi * native_two) / native_fifty_nine;
        ++index;
    }
    // The original explicitly duplicates point 1 into the closure point 60.
    reinterpret_cast<NativePolygonGeometryView*>(this)->perimeter[60] = reinterpret_cast<NativePolygonGeometryView*>(this)->perimeter[1];
}
} // namespace th20
