#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source for the 4-way and 8-way indexed ECL parameter copies.
bool execute_enemy_dynamic_parameter_opcode(EnemyState& state, std::int32_t opcode);
}
