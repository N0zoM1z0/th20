#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragments for the original Enemy ECL opcodes 600 and 601.
bool execute_enemy_shot_fire_opcode(EnemyState& state, std::int32_t opcode);
}
