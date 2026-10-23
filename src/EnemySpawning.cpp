#include "EnemyController.hpp"
#include "Context.hpp"
#include "DiagnosticAllocator.hpp"

namespace th20 {

std::int32_t EnemyController::count() const { return static_cast<std::int32_t>(field_124); }
std::int32_t EnemyController::capacity() const { return static_cast<std::int32_t>(data.field_88); }

Enemy* EnemyController::create(const char* name, const EnemySpawn& parameters, Enemy* parent) {
    Enemy* enemy = process_allocator->allocate_object<Enemy>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\enemy.cpp:69 EnemyInf");
    enemy->initialize(player_index, name);
    if (parent) {
        auto& children = parent->children;
        children.append(&enemy->parent_link);
    }
    enemy->apply_spawn(parameters);
    auto& list = enemies;
    list.prepend(&enemy->controller_link);
    ++field_124;
    return enemy;
}

void EnemyController::clear() {
    auto& list = enemies;
    for (auto it = list.begin(), *finish = list.end(); it.differs(finish); it.advance()) {
        auto* link = it.get();
        auto* enemy = link->node_value();
        if (!(((enemy->state.flags.word_00 >> 5) & 1u)
            || ((enemy->state.flags.word_00 >> 7) & 1u)
            || ((enemy->state.flags.word_04 >> 6) & 1u)
            || ((enemy->state.flags.word_04 >> 7) & 1u)
            || ((enemy->state.flags.word_00 >> 10) & 1u))
            || ((enemy->state.flags.word_00 >> 8) & 1u)) {
            enemy->state.pattern.reset();
            enemy->state.vector_6c.x = 0;
            enemy->state.vector_6c.y = 192.0f;
            enemy->state.field_284 = 0;
            enemy->defeat();
            for (auto& animation : enemy->state.animations) animation.handle.retire();
            enemy->state.animations.clear();
            enemy->state.flags.word_04 |= 0x200u;
        }
    }
    data.timer_8c++;
}
void EnemyController::clear_matching(std::int32_t field_30) {
    auto& list = enemies;
    for (auto it = list.begin(), *finish = list.end(); it.differs(finish); it.advance()) {
        auto* link = it.get();
        auto* enemy = link->node_value();
        if (!(((enemy->state.flags.word_00 >> 5) & 1u)
            || ((enemy->state.flags.word_00 >> 7) & 1u)
            || ((enemy->state.flags.word_04 >> 6) & 1u)
            || ((enemy->state.flags.word_04 >> 7) & 1u)
            || ((enemy->state.flags.word_00 >> 10) & 1u))
            || ((enemy->state.flags.word_00 >> 8) & 1u)) {
            if (enemy->state.field_30 == field_30) {
                enemy->state.pattern.reset();
                enemy->state.vector_6c.x = 0;
                enemy->state.vector_6c.y = 192.0f;
                enemy->state.field_284 = 0;
                enemy->defeat();
                for (auto& animation : enemy->state.animations) animation.handle.retire();
                enemy->state.animations.clear();
                enemy->state.flags.word_04 |= 0x200u;
            }
        }
    }
    data.timer_8c++;
}
void EnemyController::clear_variant_565() {
    auto& list = enemies;
    for (auto it = list.begin(), *finish = list.end(); it.differs(finish); it.advance()) {
        auto* link = it.get();
        auto* enemy = link->node_value();
        if (!(((enemy->state.flags.word_00 >> 5) & 1u)
            || ((enemy->state.flags.word_00 >> 7) & 1u)
            || ((enemy->state.flags.word_04 >> 6) & 1u)
            || ((enemy->state.flags.word_04 >> 7) & 1u)
            || ((enemy->state.flags.word_00 >> 10) & 1u))
            || ((enemy->state.flags.word_00 >> 8) & 1u)) {
            enemy->state.pattern.reset();
            enemy->state.vector_6c.x = 0;
            enemy->state.vector_6c.y = 192.0f;
            enemy->state.field_284 = 0;
            enemy->state.field_27c = -1;
            enemy->defeat();
            for (auto& animation : enemy->state.animations) animation.handle.retire();
            enemy->state.animations.clear();
            enemy->state.flags.word_04 |= 0x200u;
        }
    }
    data.timer_8c++;
}
void EnemyController::clear_variant_573() {
    auto& list = enemies;
    for (auto it = list.begin(), *finish = list.end(); it.differs(finish); it.advance()) {
        auto* link = it.get();
        auto* enemy = link->node_value();
        if (!(((enemy->state.flags.word_00 >> 5) & 1u)
            || ((enemy->state.flags.word_00 >> 7) & 1u)
            || ((enemy->state.flags.word_04 >> 6) & 1u)
            || ((enemy->state.flags.word_04 >> 7) & 1u)
            || ((enemy->state.flags.word_00 >> 10) & 1u))
            || ((enemy->state.flags.word_00 >> 8) & 1u)) {
            if (!enemy->state.flag_04_bit_30()) {
                enemy->state.pattern.reset();
                enemy->state.vector_6c.x = 0;
                enemy->state.vector_6c.y = 192.0f;
                enemy->state.field_284 = 0;
                enemy->defeat();
                for (auto& animation : enemy->state.animations) animation.handle.retire();
                enemy->state.animations.clear();
                enemy->state.flags.word_04 |= 0x200u;
            }
        }
    }
    data.timer_8c++;
}

void EnemyController::set_angle_128(float angle) { angle_128 = angle; }

} // namespace th20
