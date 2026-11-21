#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragments for Enemy bounds, health, selection and state controls.
bool execute_enemy_control_opcode(EnemyState& state, std::int32_t opcode);
}
