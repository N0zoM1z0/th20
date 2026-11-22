#include "Enemy.hpp"

namespace th20 {

// This typed Enemy view emits the same relocation-free +0x88 getter as the
// existing Session::player_table head at 0x004989F0. It is a shared physical
// alias used by opcode 802, not a second original function or byte credit.
EnemyState& Enemy::state_value() { return state; }

} // namespace th20
