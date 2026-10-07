#include "Enemy.hpp"

namespace th20 {

Enemy::Enemy() noexcept : EclManager(), flags{}, controller_link(this), state(),
    spawn_parameters(), children(), parent_link(), callback(nullptr),
    player_index(0), context(nullptr) {}

Enemy* Enemy::parent() { return parent_link.owner_value()->node_value(); }
Vector3& Enemy::position_ref() { return state.motion_110.position_ref(); }
} // namespace th20
