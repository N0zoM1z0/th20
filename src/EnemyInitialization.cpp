#include "EnemyController.hpp"
#include "Context.hpp"

namespace th20 {

void Enemy::initialize(std::int32_t index, const char* name) {
    reset();
    select_context(index);
    state.entity = this;
    state.initialize();
    auto& list = children;
    list.reset(this);
    auto& link = parent_link;
    link.initialize(this);
    callback = nullptr;
    state.identifier = context->enemy_controller()->generation();
    context->enemy_controller()->advance_generation();
    auto& loader = *context->enemy_controller()->script_loader();
    loader.select(this, name);
}

EclLoader* EnemyController::script_loader() const { return loader; }
std::uint32_t EnemyController::generation() const { return current_enemy_generation; }
std::uint32_t EnemyController::advance_generation() {
    previous_enemy_generation = current_enemy_generation;
    ++current_enemy_generation;
    current_enemy_generation &= 0xffff;
    if (!current_enemy_generation) ++current_enemy_generation;
    current_enemy_generation |= static_cast<std::uint32_t>(player_index) << 16;
    return previous_enemy_generation;
}

} // namespace th20
