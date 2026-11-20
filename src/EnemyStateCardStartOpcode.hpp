#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;
struct EclInstruction;

// Natural-C++ source fragment for the shared Enemy ECL card-start opcodes.
bool execute_enemy_card_start_opcode(EnemyState& state,
                                     const EclInstruction& instruction,
                                     std::int32_t opcode);
}
