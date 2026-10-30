// Whole original 76B/27-native-x86 Polygon Motion TRIANGLEFAN wrapper.
// Real 455B fan child with count61 and original Motion/Vector3 sources;
// three original E8/one PE HIGHLOW physical roles, entire 76/76 strict.
#include "NativeMotionPolygonOwner.hpp"
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationRuntimeOwner.hpp"
#include <cstdint>
namespace th20 {
void NativeMotionPolygonOwner::draw_polygon_fan_45fb10(const Vector2* center) {
    Vector3* const vertex_data=reinterpret_cast<Vector3*>(
        reinterpret_cast<std::uint8_t*>(this)+0x1E8);
    float* const colors=&(*vertex_data)[0];
    const Vector2* const points=reinterpret_cast<const Vector2*>(&position_ref());
    reinterpret_cast<AnimationDrawDetailedOwner*>(current_animation_pool)->draw_vertex_fan_43cb70(
        61,center,points,reinterpret_cast<const std::uint32_t*>(colors));
}
}
