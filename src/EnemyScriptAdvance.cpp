#include "Enemy.hpp"
namespace th20 {
std::int32_t* EnemyState::integer_argument_destination(std::int32_t index) {
    auto& owner = *entity;
    return owner.integer_argument_destination(index);
}

float* EnemyState::float_argument_destination(std::int32_t index) {
    auto& owner = *entity;
    return owner.float_argument_destination(index);
}

std::int32_t* Enemy::integer_argument_destination(std::int32_t index) {
    auto& runtime = *current_runtime;
    return runtime.integer_destination(index);
}

float* Enemy::float_argument_destination(std::int32_t index) {
    auto& runtime = *current_runtime;
    return runtime.float_destination(index);
}

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
