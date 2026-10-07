#include "Enemy.hpp"

namespace th20 {

EclInstruction* Enemy::current_instruction() { return current_runtime->current(); }

int Enemy::execute_opcode() { return state.execute_opcode(); }

std::int32_t Enemy::integer_argument(std::int32_t index) {
    auto& runtime = *current_runtime;
    return runtime.integer_argument(index);
}

float Enemy::float_argument(std::int32_t index) {
    auto& runtime = *current_runtime;
    return runtime.float_argument(index);
}

std::int32_t EnemyState::integer_argument(std::int32_t index) {
    auto& enemy = *entity;
    return enemy.integer_argument(index);
}

float EnemyState::float_argument(std::int32_t index) {
    auto& enemy = *entity;
    return enemy.float_argument(index);
}

} // namespace th20
