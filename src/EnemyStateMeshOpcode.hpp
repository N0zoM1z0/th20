#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragment for original Enemy ECL opcode 621.
bool execute_enemy_mesh_opcode(EnemyState& state, std::int32_t opcode);
}
