#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragment for original Enemy ECL opcodes 702 and 703.
// This is a source-organizing helper, not a separate original native function.
// The 41,967-byte EnemyState::execute_opcode parent remains source-absent.
bool execute_enemy_laser_opcode(EnemyState& state, std::int32_t opcode);
}
