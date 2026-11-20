#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragments for original Enemy ECL opcodes 553 and 554.
bool execute_enemy_controller_setter_opcode(EnemyState& state,
                                             std::int32_t opcode);
}
