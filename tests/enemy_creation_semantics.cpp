#include "EnemyController.hpp"
#include "Context.hpp"
#include "DiagnosticAllocator.hpp"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>

namespace {
th20::Context context;
std::vector<std::unique_ptr<th20::Enemy>> allocated;
std::vector<int> events;
const char* expected_name;
th20::EnemySpawn* expected_parameters;
}

namespace th20 {
// Deliberate fixtures supply VM construction/default slots, production startup,
// pool/context selection, subroutine lookup and the spawn-application boundary.
// Actual creation, initialization, state/reset, generation, lists and selection
// run unchanged; the real VM lifetime has its own owned test.
LockRegistry process_locks;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator = &allocator;
std::uint32_t current_enemy_generation = 1, previous_enemy_generation = 0;
EclScriptPosition::EclScriptPosition() : subroutine(0), offset(0) {}
EclRuntime::EclRuntime() : time(0), async_id(0), manager(nullptr), signal(0), rank(0), flags{} {}
EclManager::EclManager() : field_04(0), field_08(0), current_runtime(&main), loader(nullptr) {}
EclManager::~EclManager() = default;
Enemy::~Enemy() = default;
TaskInfo::~TaskInfo() = default;
void TaskInfo::enable() { std::abort(); }
void TaskInfo::disable() { std::abort(); }
EnemyController::EnemyController() noexcept : field_124(0), player_index(0), context(nullptr) {}
EnemyController::~EnemyController() = default;
EnemyData::EnemyData() = default;
EnemyAnimationHandles::EnemyAnimationHandles() noexcept = default;
int EclManager::execute_opcode() { std::abort(); }
int EclManager::read_integer(int) { std::abort(); }
int* EclManager::integer_destination(int) { std::abort(); }
float EclManager::read_float(int) { std::abort(); }
float* EclManager::float_destination(int) { std::abort(); }
int Enemy::read_integer(int) { std::abort(); }
int* Enemy::integer_destination(int) { std::abort(); }
float Enemy::read_float(int) { std::abort(); }
float* Enemy::float_destination(int) { std::abort(); }
int EnemyState::execute_opcode() { std::abort(); }
int Enemy::execute_opcode() { std::abort(); }
int ScriptStack::pop(int, void*, char) { std::abort(); }
void Enemy::select_context(int index) {
    events.push_back(1);
    assert(current_runtime == &main && main.time == 0 && main.position.subroutine == -1);
    assert(main.stack.words.empty() && main.stack.words.capacity() >= 256);
    assert(main.stack.pointer == 0 && main.stack.frame_base == 0);
    player_index = index; this->context = &::context;
    state.context = &::context; state.field_2e8 = static_cast<std::uint32_t>(index);
}
template<> Enemy* DiagnosticAllocator::allocate_object<Enemy>(const char* label) {
    assert(std::strcmp(label, "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\enemy.cpp:69 EnemyInf") == 0);
    events.push_back(0);
    allocated.push_back(std::make_unique<Enemy>());
    return allocated.back().get();
}
int Enemy::apply_spawn(const EnemySpawn& parameters) {
    events.push_back(3); assert(&parameters == expected_parameters);
    assert(state.entity == this && state.identifier.value == previous_enemy_generation);
    assert(state.movements.size() == 1 && state.animations.size() == 1);
    assert(children.node == this && parent_link.node == this && !callback);
    assert(loader == ::context.enemies->loader && main.position.subroutine == 1);
    assert(main.position.offset == 0 && main.time == 0);
    spawn_parameters = parameters; return 0;
}
}

int main() {
    using namespace th20;
    EnemyController controller;
    EclLoader loader;
    assert(loader.subroutine_index("entry") == -1);
    loader.records = {{"alpha", nullptr}, {"entry", nullptr}, {"zeta", nullptr}};
    loader.subroutine_count = 3;
    assert(loader.subroutine_index("alpha") == 0 && loader.subroutine_index("entry") == 1);
    assert(loader.subroutine_index("zeta") == 2 && loader.subroutine_index("before") == -1);
    assert(loader.subroutine_index("0") == -1 && loader.subroutine_index("zz") == -1);
    context.enemies = &controller;
    controller.loader = &loader;
    controller.player_index = 2;
    controller.data.field_88 = 32;
    assert(controller.capacity() == 32 && controller.count() == 0);
    controller.data.field_88 = 0xffffffffu; controller.field_124 = 0x80000000u;
    assert(controller.capacity() == -1 && controller.count() == (-2147483647-1));
    controller.data.field_88 = 32; controller.field_124 = 0;
    current_enemy_generation = 0x1ffff;
    assert(controller.generation() == 0x1ffff);
    assert(controller.advance_generation() == 0x1ffff);
    assert(previous_enemy_generation == 0x1ffff && current_enemy_generation == 0x20001);
    current_enemy_generation = 0xffffffff;
    controller.player_index = -1;
    controller.advance_generation(); assert(current_enemy_generation == 0xffff0001);
    controller.player_index = 2;
    current_enemy_generation = 0x20005;
    EnemySpawn parameters;
    parameters.health = 900;
    expected_parameters = &parameters;
    expected_name = "entry";
    events.clear();
    Enemy* first = controller.create(expected_name, parameters, nullptr);
    assert((events == std::vector<int>{0,1,3}));
    assert(controller.count() == 1 && first->state.identifier.value == 0x20005);
    assert(controller.enemies.next == &first->controller_link && controller.enemies.tail == &first->controller_link);
    assert(!first->parent_link.owner && first->spawn_parameters.health == 900);
    events.clear();
    Enemy* second = controller.create(expected_name, parameters, first);
    assert((events == std::vector<int>{0,1,3}));
    assert(controller.count() == 2 && second->state.identifier.value == 0x20006);
    assert(controller.enemies.next == &second->controller_link && second->controller_link.next == &first->controller_link);
    assert(controller.enemies.tail == &first->controller_link);
    assert(first->children.next == &second->parent_link && first->children.tail == &second->parent_link);
    assert(second->parent() == first);
    // Reset retains independent flags/rank while clearing active script storage.
    first->main.flags.bits = 0xa5; first->main.rank = 0x7e;
    first->main.stack.words.assign(300, 0x12345678);
    first->main.stack.pointer = 123; first->main.stack.frame_base = 44;
    first->main.interpolators.resize(2);
    first->main.signal = 19;
    first->reset();
    assert(first->main.flags.bits == 0xa4 && first->main.rank == 0x7e && first->main.signal == 0);
    assert(first->main.async_id == -1 && first->main.manager == first && first->main.interpolators.empty());
    assert(first->main.position.subroutine == -1 && first->main.position.offset == -1);
    assert(first->main.stack.words.empty() && first->main.stack.words.capacity() >= 300);
    assert(first->runtimes.node == &first->main && !first->runtimes.next);
    assert(loader.select(first, "missing") == 0 && first->main.position.subroutine == -1);
    assert(first->main.position.offset == 0 && first->main.time == 0);
    second->parent_link.detach(); second->controller_link.detach(); first->controller_link.detach();
    assert(controller.enemies.tail == &controller.enemies && !controller.enemies.next);
    assert(first->children.tail == &first->children && !first->children.next);
    allocated.clear();
}
