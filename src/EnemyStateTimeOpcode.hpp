#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

bool execute_enemy_time_opcode(EnemyState& state, std::int32_t opcode);
}
