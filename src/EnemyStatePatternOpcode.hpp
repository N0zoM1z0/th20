#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragment for the native EnemyPattern ECL opcode family.
bool execute_enemy_pattern_opcode(EnemyState& state, std::int32_t opcode);
}
