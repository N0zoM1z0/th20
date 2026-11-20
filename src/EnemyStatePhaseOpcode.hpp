#pragma once
#include "EclRuntime.hpp"
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragments for original Enemy ECL opcodes 514 and 521.
bool execute_enemy_phase_opcode(EnemyState& state,
                                 const EclInstruction& instruction,
                                 std::int32_t opcode);
}
