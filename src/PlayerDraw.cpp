#include "Player.hpp"
#include "AnimationRuntimeOwner.hpp"

namespace th20 {
std::int32_t Player::draw() {
    if (state_value() == 2) return 1;
    current_animation_pool->select_draw_layer(12, view_index);
    animation.vector_5bc = position_ref();
    animation.base.flags.layer_mode = 1;
    current_animation_pool->draw(&animation);
    current_animation_pool->flush_draws();
    return 1;
}
} // namespace th20
