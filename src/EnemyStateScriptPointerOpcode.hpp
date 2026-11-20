#pragma once
#include "EclRuntime.hpp"
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragment for the original Enemy ECL opcode 632.
// The instruction reference is the parent's live packet, including trailing data.
bool execute_enemy_script_pointer_opcode(EnemyState& state,
                                          const EclInstruction& instruction,
                                          std::int32_t opcode);
}
