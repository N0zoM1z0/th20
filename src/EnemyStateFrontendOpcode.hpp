#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

bool execute_enemy_frontend_opcode(
    EnemyState& state, std::int32_t opcode, std::int32_t& result);
}
