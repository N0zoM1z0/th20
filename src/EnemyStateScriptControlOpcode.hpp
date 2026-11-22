#pragma once

#include <cstdint>

namespace th20 {
struct EnemyState;
struct EclInstruction;

bool execute_enemy_script_control_opcode(EnemyState& state,
                                         const EclInstruction& instruction,
                                         std::int32_t opcode);
}
