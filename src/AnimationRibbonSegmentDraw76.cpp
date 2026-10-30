// Complete 76B original ribbon segment LINESTRIP caller at 0x0045EAC0.
// Real Vector3 packed-color stream +0x1E0 and offset-zero Motion base.
#include "NativeRibbonPolygonGroup.hpp"
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Motion.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include <cstdint>
namespace th20 {
void NativeRibbonSegment::draw_ribbon_45eac0(const Vector3* position) {
    Vector3* const vertex_data = reinterpret_cast<Vector3*>(
        reinterpret_cast<std::uint8_t*>(this) + 0x1E0);
    float* const colors = &(*vertex_data)[0];
    const Vector2* const points = reinterpret_cast<const Vector2*>(
        &reinterpret_cast<Motion*>(this)->position_ref());
    reinterpret_cast<AnimationDrawDetailedOwner*>(current_animation_pool)->draw_vertex_line_43d1a0(
        60, reinterpret_cast<const Vector2*>(position), points,
        reinterpret_cast<const std::uint32_t*>(colors));
}
} // namespace th20
