#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragment for the shared original ECL opcodes 609-612.
// All four original opcode values dispatch to one inline native case body.
bool execute_enemy_shot_command_opcode(EnemyState& state, std::int32_t opcode);
}
