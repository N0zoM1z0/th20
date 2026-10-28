#include "Bullet.hpp"
#include "AnimationRuntimeOwner.hpp"

namespace th20 {
// Complete original six-group draw orchestrator. The currently open 273-byte
// per-group draw routine and Renderer class are external native dependencies.
std::int32_t BulletController::draw_groups() {
    current_animation_pool->select_draw_layer(12, view_index);
    for (std::int32_t group = 0; group < 6; ++group) draw_group(group);
    return 1;
}
} // namespace th20
