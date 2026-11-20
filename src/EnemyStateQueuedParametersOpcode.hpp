#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragments for original Enemy ECL opcodes 700 and 701.
// Both branches mutate the selected writable queued shot/metadata pair.
bool execute_enemy_queued_parameters_opcode(EnemyState& state, std::int32_t opcode);
}
