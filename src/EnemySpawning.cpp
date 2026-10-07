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

} // namespace th20
