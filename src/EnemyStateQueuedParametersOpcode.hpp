#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragments for original Enemy ECL opcodes 619, 633, 700 and 701.
// These branches mutate the selected writable queued shot/metadata pair.
bool execute_enemy_queued_parameters_opcode(EnemyState& state, std::int32_t opcode);
}
