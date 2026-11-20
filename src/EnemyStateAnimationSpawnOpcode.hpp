#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragment for original Enemy ECL opcode 555.
bool execute_enemy_animation_spawn_opcode(EnemyState& state, std::int32_t opcode);
}
