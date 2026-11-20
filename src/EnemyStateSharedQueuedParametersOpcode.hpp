#pragma once
#include <cstdint>

namespace th20 {
struct EnemyState;

// Natural-C++ source fragments for original Enemy ECL opcodes 602, 603 and 604.
// These use the ensure-only shared_shot selector, never writable COW.
bool execute_enemy_shared_queued_parameters_opcode(EnemyState& state,
                                                    std::int32_t opcode);
}
