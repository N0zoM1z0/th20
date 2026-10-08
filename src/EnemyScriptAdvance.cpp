#include "Enemy.hpp"
namespace th20 {
int EnemyState::advance_scripts() {
    if ((flags.word_04 >> 26) & 1u) return 0;
    flags.word_04 |= 0x04000000u;
    if (update_movements()) return -1;
    auto* owner = entity;
    float step = timer_a8.step();
    if (owner->EclManager::tick(step)) return -1;
    if (update_callback && (this->*update_callback)()) return -1;
    return 0;
}
}
