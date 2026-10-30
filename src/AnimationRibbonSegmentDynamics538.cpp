// Original complete 538B ribbon segment dynamics Boss at 0x0045E800.
// Two real 60-element C++ arrays: random/clamped radii, angle-driven
// polar position recomputation and one physical closure copy at vertex 59.
// Scope after Angle construction naturally reproduces the original NOP.
#include "NativeRibbonPolygonGroup.hpp"
#include "Motion.hpp"
#include "Vector3.hpp"
#include "Angle.hpp"
#include "GameRandom.hpp"
#include "MotionMath.hpp"
#include <cstdint>
namespace th20 {
extern GameRandom native_polygon_random_5ba4c4;
extern const float native_two, native_four, native_pi, native_fifty_nine;
void NativeRibbonSegment::update_ribbon_45e800(float limit) {
    NativeRibbonScalarSpan* const radius = &radius_2d0;
    auto* current = reinterpret_cast<float*>(
        &reinterpret_cast<Motion*>(radius)->position_ref());
    auto* finish = radius->end_45dca0();
    for (; current != finish; ++current) {
        float* const active = current;
        *active += native_polygon_random_5ba4c4.signed_unit() * native_two;
        if (*active > limit + native_four) {
            *active = limit + native_four;
        } else if (*active < limit - native_four) {
            *active = limit - native_four;
        }
    }
    std::int32_t index = 0;
    Angle direction(0.0f);
    {
        NativeRibbonPointSpan* const points = &perimeter_00;
        auto* point = reinterpret_cast<Vector2*>(
            &reinterpret_cast<Motion*>(points)->position_ref());
        auto* point_finish = points->end_45dcc0();
        for (; point != point_finish; ++point) {
            Vector2* const active = point;
            polar(*reinterpret_cast<Vector3*>(active), static_cast<float>(direction), radius_2d0.values[index]);
            direction += (native_pi * native_two) / native_fifty_nine;
            ++index;
        }
    }
    perimeter_00.values[59] = perimeter_00.values[0];
}
} // namespace th20
