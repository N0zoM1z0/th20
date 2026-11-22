#pragma once
#include <cstdint>
namespace th20 {
struct EnemyState;
bool execute_enemy_player_angle_opcode(EnemyState& state, std::int32_t opcode);
}
