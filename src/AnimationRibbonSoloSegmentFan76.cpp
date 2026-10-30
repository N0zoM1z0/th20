// Original complete 76B single-segment ribbon TRIANGLEFAN wrapper.
// Native 60-vertex fan, packed color cells +0x1E0 and Motion base +0x00.
#include "NativeRibbonSoloGroup.hpp"
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Motion.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include <cstdint>
namespace th20 {
void NativeRibbonSoloSegmentDrawView::draw_45dae0(const Vector3* position) {
    Vector3* const color_data = reinterpret_cast<Vector3*>(
        reinterpret_cast<std::uint8_t*>(this) + 0x1E0);
    float* const colors = &(*color_data)[0];
    const Vector2* const points = reinterpret_cast<const Vector2*>(
        &reinterpret_cast<Motion*>(this)->position_ref());
    reinterpret_cast<AnimationDrawDetailedOwner*>(current_animation_pool)->draw_vertex_fan_43cb70(
        60, reinterpret_cast<const Vector2*>(position), points,
        reinterpret_cast<const std::uint32_t*>(colors));
}
} // namespace th20
