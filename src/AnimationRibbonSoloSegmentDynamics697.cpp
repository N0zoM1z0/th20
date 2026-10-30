// Native complete original 697B/190-i386 solo-ribbon dynamics Boss.
// Color byte +2, two 60-cell loops, limit +/-limit/4 and polar 2*pi/58.
#include "NativeRibbonSoloGroup.hpp"
#include "Motion.hpp"
#include "Vector3.hpp"
#include "Angle.hpp"
#include "GameRandom.hpp"
#include "MotionMath.hpp"
#include <cstddef>
#include <cstdint>
namespace th20 {
extern GameRandom native_polygon_random_5ba4c4;
extern const float native_two, native_four, native_pi, native_fifty_eight;
extern const float native_sixteen, native_ribbon_color_bias224;
void NativeRibbonSoloSegmentUpdateView::update_45d780(float limit) {
    NativeRibbonScalarSpan* const colors = reinterpret_cast<NativeRibbonScalarSpan*>(&color_cells_1e0);
    auto* color = reinterpret_cast<float*>(&reinterpret_cast<Motion*>(colors)->position_ref());
    auto* color_end = colors->end_45dca0();
    for (; color != color_end; ++color) {
        float* const active = color;
        *(reinterpret_cast<std::uint8_t*>(active) + 2) = static_cast<std::uint8_t>(
            native_polygon_random_5ba4c4.signed_unit() * native_sixteen + native_ribbon_color_bias224);
    }
    NativeRibbonScalarSpan* const radius = &radius_2d0;
    auto* current = reinterpret_cast<float*>(&reinterpret_cast<Motion*>(radius)->position_ref());
    auto* finish = radius->end_45dca0();
    for (; current != finish; ++current) {
        float* const active = current;
        *active += native_polygon_random_5ba4c4.signed_unit() * native_two;
        if (*active > limit / native_four + limit) {
            *active = limit / native_four + limit;
        } else if (*active < limit - limit / native_four) {
            *active = limit - limit / native_four;
        }
    }
    std::int32_t index = 0;
    Angle direction(0.0f);
    reinterpret_cast<Vector3*>(&radius_2d0)->operator[](0) = 0.0f;
    NativeRibbonPointSpan* const points = &perimeter_00;
    auto* point = reinterpret_cast<Vector2*>(&reinterpret_cast<Motion*>(points)->position_ref());
    auto* point_finish = points->end_45dcc0();
    for (; point != point_finish; ++point) {
        Vector2* const active = point;
        polar(*reinterpret_cast<Vector3*>(active), static_cast<float>(direction), radius_2d0.values[index]);
        direction += (native_pi * native_two) / native_fifty_eight;
        ++index;
    }
    perimeter_00.values[59] = perimeter_00.values[1];
}
} // namespace th20
