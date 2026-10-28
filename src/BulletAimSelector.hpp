#pragma once

#include "Vector3.hpp"
#include <cstdint>

namespace th20 {
// Full game-owned angle selector shared by the native Bullet command engine.
// Selector bands distinguish fixed, player-aimed, random, and enemy-aimed shots.
float select_bullet_aim(std::int32_t view_index, float fixed_angle,
                        const Vector3& position, float direction_code,
                        float deviation);
} // namespace th20
