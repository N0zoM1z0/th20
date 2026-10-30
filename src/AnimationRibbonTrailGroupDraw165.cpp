#include "NativeRibbonTrailGroup.hpp"
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "AnimationDrawDetailedOwner.hpp"
#include "Motion.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include <cstdint>
namespace th20 {
std::int32_t NativeRibbonTrailGroup::draw() {
    reinterpret_cast<AnimationQuadSubmitOwner*>(current_animation_pool)->bind_native_texture_state(animation);
    Vector3 position;
    animation->position(position);
    float* const first_color = &reinterpret_cast<Vector3*>(&colors_208)->operator[](0);
    const Vector2* const points = reinterpret_cast<const Vector2*>(
        &reinterpret_cast<Motion*>(&vertices_08)->position_ref());
    std::int32_t count = static_cast<std::int32_t>(timer_30c);
    reinterpret_cast<AnimationDrawDetailedOwner*>(current_animation_pool)->draw_vertex_line_43d1a0(
        count, reinterpret_cast<const Vector2*>(&position), points,
        reinterpret_cast<const std::uint32_t*>(first_color));
    return 0;
}
}
