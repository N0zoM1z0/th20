#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragment for original Enemy ECL opcode 549.
bool execute_enemy_membership_opcode(EnemyState& state, std::int32_t opcode);
}
