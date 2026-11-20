#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragment for the original Enemy ECL opcode 614.
bool execute_enemy_queue_copy_opcode(EnemyState& state, std::int32_t opcode);
}
