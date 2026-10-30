#pragma once
// Original native polygon renderer segment exposes a Motion base at offset 0.
// Its original class name/full ~0x3D4 record fields are still provisional.
#include "Motion.hpp"
#include "Vector2.hpp"
namespace th20 {
struct NativeMotionPolygonOwner : Motion {
    // Original 104B method source is NONEXACT (candidate 102B/34 x86).
    void draw_polygon_outline_45faa0(const Vector2* center);
    // Whole original 76B/27 x86 method strictly exact, native RET 4.
    void draw_polygon_fan_45fb10(const Vector2* center);
};
}
