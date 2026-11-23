#pragma once

#include <cstdint>

namespace th20 {
struct EnemyState;
bool execute_enemy_queued_shot_property_opcode(EnemyState& state, std::int32_t opcode);
}
