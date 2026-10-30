// Original entire 827B polygon segment dynamic update: source-present
// NONEXACT semantic candidate. The original uses two C++ counted ranges
// and specific iterator/utility library calls; this source preserves the
// source-inferred 61*8B point region, actual +0x2DC float lanes,
// real 59.0f angular denominator but UNVERIFIED original range bounds,
// random deviation clamp and closure without claiming original x86 bytes.
// Do NOT add to the strict unit manifest before exact replay succeeds.
#include "NativePolygonSegmentSlot.hpp"
#include "Vector2.hpp"
#include "Angle.hpp"
#include "GameRandom.hpp"
#include "MotionMath.hpp"
#include <cstddef>
#include <cstdint>
namespace th20 {
extern GameRandom native_polygon_random_5ba4c4;
extern const float native_two;
extern const float native_four;
extern const float native_pi;
extern const float native_fifty_nine;

// This view represents the field groups independently exposed by the
// original fixed-slot owner. No second competing segment class is defined.
struct NativePolygonGeometryView {
    Vector2 perimeter[61];
    std::uint8_t retained_1e8_to_2dc[0xF4];
    float radius[60];
    std::uint8_t retained_3cc_to_3d4[8];
};
static_assert(sizeof(NativePolygonGeometryView)==sizeof(NativePolygonSegmentSlot));
static_assert(offsetof(NativePolygonGeometryView,radius)==0x2DC);

void NativePolygonSegmentSlot::update_polygon_dynamics_45f670(float limit) {
    auto& perimeter=*reinterpret_cast<Vector2 (*)[61]>(
        reinterpret_cast<std::uint8_t*>(this));
    auto& radius=*reinterpret_cast<float (*)[60]>(
        reinterpret_cast<std::uint8_t*>(this)+0x2DC);
    // Source radius[0] is intentionally set to zero before using the
    // first position; the original stores both the old/new float lanes.
    radius[0] = 0.0f;
    const float first_radius=radius[0];
    polar(*reinterpret_cast<Vector3*>(&perimeter[0]),0.0f,first_radius);

    // The exact native first/second counted-range bounds are still open.
    // This straightforward 1..59 loop is a semantic hypothesis, not native
    // instruction/control-flow parity with the original 827B parent.
    // The original GameRandom::signed_unit result has the x87 float ABI.
    for (std::int32_t i=1;i<60;++i) {
        float& current_radius=radius[i];
        current_radius+=native_polygon_random_5ba4c4.signed_unit()*native_two;
        if (current_radius>limit+native_four) {
            current_radius=limit+native_four;
        } else if (current_radius<limit-native_four) {
            current_radius=limit-native_four;
        }
    }

    Angle angle(0.0f);
    std::int32_t index=1;
    for (;index<60;++index) {
        polar(*reinterpret_cast<Vector3*>(&perimeter[index]),
              static_cast<float>(angle),radius[index]);
        angle+=(native_pi*native_two)/native_fifty_nine;
    }
    perimeter[60]=perimeter[1];
}
} // namespace th20
