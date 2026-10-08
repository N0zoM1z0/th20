#include "Enemy.hpp"

namespace th20 {

Identifier32 Enemy::identifier_value() { return state.identifier; }

std::int32_t Enemy::integer_argument_value(std::int32_t index, std::int32_t value) {
    auto& runtime = *current_runtime;
    return runtime.integer_argument_value(index, value);
}

float Enemy::float_argument_value(std::int32_t index, float value) {
    auto& runtime = *current_runtime;
    return runtime.float_argument_value(index, value);
}

std::int32_t EnemyState::integer_argument_value(std::int32_t index, std::int32_t value) {
    auto& enemy = *entity;
    return enemy.integer_argument_value(index, value);
}

float EnemyState::float_argument_value(std::int32_t index, float value) {
    auto& enemy = *entity;
    return enemy.float_argument_value(index, value);
}

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
