#include "Enemy.hpp"

namespace th20 {

// Native 35-byte 0x00497240 leaf: set EnemyState::flags.word_04 bit 9.
void __fastcall set_enemy_state_flag_04_bit_9(Enemy* enemy) {
    enemy->state.flags.word_04 |= 0x200u;
}

} // namespace th20
