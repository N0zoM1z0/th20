#include "EnemyController.hpp"
#include "Context.hpp"
#include "SecureCrt.hpp"

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

void Enemy::configure_phase(std::uint32_t index, std::int32_t life,
                            std::int32_t time, const char* name) {
    if (state.phases.size() < index + 1) state.phases.resize(index + 1);
    state.phases[index].life = life;
    if (life >= 0) {
        state.phases[index].time = time;
        if (name) {
            strcpy_s(state.phases[index].script, 64, name);
            strcpy_s(state.phases[index].timeout_script, 64, name);
        } else {
            state.phases[index].script[0] = 0;
            state.phases[index].timeout_script[0] = 0;
        }
    }
}

void Enemy::configure_timeout(std::uint32_t index, const char* name) {
    if (state.phases.size() < index + 1) state.phases.resize(index + 1);
    if (name) strcpy_s(state.phases.at(index).timeout_script, 64, name);
    else state.phases[index].timeout_script[0] = 0;
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
