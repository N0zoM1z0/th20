// Original whole 104B Motion-owned polygon-outline caller. SOURCE-PRESENT
// NONEXACT: natural C++ emits 102B/34-x86, missing native ESI save/restore
// ordering; the original has 104B/36-x86. Do not add artificial padding.
// The source receiver's original C++ class identity and fields beyond the
// Motion base are provisional; this does not allocate a new runtime object.
#include "NativeMotionPolygonOwner.hpp"
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationRuntimeOwner.hpp"
#include <cstdint>
namespace th20 {
extern const float native_sixteen;

void NativeMotionPolygonOwner::draw_polygon_outline_45faa0(const Vector2* center) {
    Vector3* const vertex_data = reinterpret_cast<Vector3*>(
        reinterpret_cast<std::uint8_t*>(this)+0x1E8);
    float* const colors = &(*vertex_data)[1];
    const Vector2* const points = &reinterpret_cast<const Vector2*>(&position_ref())[1];
    reinterpret_cast<AnimationDrawDetailedOwner*>(current_animation_pool)->draw_polygon_outline_43d370(
        60,center,points,reinterpret_cast<const std::uint32_t*>(colors),native_sixteen,1);
}
} // namespace th20
