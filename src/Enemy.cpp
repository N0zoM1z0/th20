#include "Enemy.hpp"
#include "EnemyController.hpp"
#include "Context.hpp"

namespace th20 {

Enemy::Enemy() noexcept : EclManager(), flags{}, controller_link(this), state(),
    spawn_parameters(), children(), parent_link(), callback(nullptr),
    player_index(0), context(nullptr) {}

Enemy* Enemy::parent() { return parent_link.owner_value()->node_value(); }
Vector3& Enemy::position_ref() { return state.motion_110.position_ref(); }
bool Enemy::bomb_drop_disabled() { return (state.flags.word_08 >> 5) & 1u; }
AnimationFile* Enemy::animation_file(std::int32_t index) {
    auto* controller = context->enemy_controller();
    return controller->animation_file(index);
}
bool Enemy::damage_marked() { return (state.flags.word_08 >> 4) & 1u; }
} // namespace th20
