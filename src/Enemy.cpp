#include "Enemy.hpp"

namespace th20 {

Enemy::Enemy() noexcept : EclManager(), flags{}, controller_link(this), state(),
    spawn_parameters(), children(), parent_link(), callback(nullptr),
    player_index(0), context(nullptr) {}

} // namespace th20
