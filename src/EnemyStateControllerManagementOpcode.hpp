#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Returns true when the opcode is handled; result preserves native ECL return values.
bool execute_enemy_controller_management_opcode(
    EnemyState& state, std::int32_t opcode, std::int32_t& result);
}
