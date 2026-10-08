#include "EnemyController.hpp"
#include "Context.hpp"
#include "DiagnosticAllocator.hpp"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <array>
#include <limits>
#include <stdexcept>
#include <vector>

namespace {
th20::Context context;
std::vector<std::unique_ptr<th20::Enemy>> allocated;
std::vector<int> events;
const char* expected_name;
th20::EnemySpawn* expected_parameters;
th20::EnemyController* lookup_controller = nullptr;
th20::Enemy* resolved_enemy = nullptr;
unsigned lookup_calls = 0, find_calls = 0;
}

namespace th20 {
// Deliberate fixtures supply VM construction/default slots, production startup,
// pool/context selection, subroutine lookup and the spawn-application boundary.
// Actual Controller/Task construction, creation, initialization, state/reset,
// generation, lists and selection run unchanged; the VM lifetime has its own test.
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
EnemyController::~EnemyController() = default;
int EclManager::execute_opcode() { std::abort(); }
int EclManager::read_integer(int) { std::abort(); }
int* EclManager::integer_destination(int) { std::abort(); }
float EclManager::read_float(int) { std::abort(); }
float* EclManager::float_destination(int) { std::abort(); }
int Enemy::read_integer(int) { std::abort(); }
float Enemy::read_float(int) { std::abort(); }
// Explicit Session and whole-list-find observation boundaries. Destination,
// checked-slot and handle-resolution bodies are the real production source.
std::int32_t enemy_script_globals[4] = {};
EnemyController* enemy_controller(std::int32_t index) {
    assert(index == 0); ++lookup_calls; return lookup_controller;
}
Enemy* EnemyController::find(std::uint32_t identifier) {
    ++find_calls;
    return resolved_enemy && resolved_enemy->state.identifier.value == identifier
        ? resolved_enemy : nullptr;
}
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
    assert(controller.flags == 2 && !controller.update_node && !controller.draw_node);
    assert(controller.loaded_names.empty() && controller.loaded_names.capacity() == 0);
    assert(controller.field_c4 == 0 && controller.field_c8 == 0 && controller.field_cc == 0);
    assert(controller.field_e0 == 0 && controller.field_120 == 0 && controller.field_124 == 0);
    assert(controller.identifier_128.value == 0 && controller.player_index == 0 && !controller.context);
    assert(!controller.loader && controller.enemies.tail == &controller.enemies);
    assert(!controller.enemies.node && !controller.enemies.next && !controller.enemies.previous);
    assert(!controller.enemies.owner && !controller.enemies.iterator);
    for (auto* file : controller.animation_files) assert(file == nullptr);
    assert(previous_enemy_generation == 1 && current_enemy_generation == 2);
    // Dirty placement construction verifies that actual constructors clear
    // retained flag bits/pointers and cannot depend on pre-zeroed host storage.
    constexpr std::size_t guard = 16;
    alignas(TaskInfo) std::array<unsigned char, sizeof(TaskInfo)+2*guard> task_storage;
    task_storage.fill(0xa5);
    auto* dirty_task = std::construct_at(reinterpret_cast<TaskInfo*>(task_storage.data()+guard));
    assert(dirty_task->flags == 2 && !dirty_task->update_node && !dirty_task->draw_node);
    std::destroy_at(dirty_task);
    alignas(EnemyController) std::array<unsigned char, sizeof(EnemyController)+2*guard> controller_storage;
    controller_storage.fill(0xa5);
    current_enemy_generation = 0xffffffffu;
    auto* dirty_controller = std::construct_at(reinterpret_cast<EnemyController*>(controller_storage.data()+guard));
    assert(dirty_controller->flags == 2 && !dirty_controller->update_node && !dirty_controller->draw_node);
    assert(dirty_controller->loaded_names.empty() && dirty_controller->loaded_names.capacity() == 0);
    assert(dirty_controller->field_c4 == 0 && dirty_controller->field_c8 == 0 && dirty_controller->field_cc == 0);
    assert(dirty_controller->field_e0 == 0 && dirty_controller->field_120 == 0 && dirty_controller->field_124 == 0);
    assert(dirty_controller->player_index == 0 && !dirty_controller->context && !dirty_controller->loader);
    assert(dirty_controller->enemies.tail == &dirty_controller->enemies);
    for (auto* file : dirty_controller->animation_files) assert(file == nullptr);
    for (const auto& handle : dirty_controller->data.handles) assert(handle.value == 0);
    assert(previous_enemy_generation == 0xffffffffu && current_enemy_generation == 1);
    std::destroy_at(dirty_controller); // Controller disposal is still a fixture.
    for (std::size_t i=0;i<guard;++i) {
        assert(task_storage[i] == 0xa5 && task_storage[sizeof(TaskInfo)+guard+i] == 0xa5);
        assert(controller_storage[i] == 0xa5 && controller_storage[sizeof(EnemyController)+guard+i] == 0xa5);
    }
    // Real Data and handle constructors initialize every owned scalar/slot.
    assert(controller.data.field_30 == 0 && controller.data.field_34 == 0);
    assert(controller.data.field_38 == 0 && controller.data.field_3c == 0);
    assert(controller.data.field_40 == 0 && controller.data.field_84.value == 0);
    assert(controller.data.field_88 == 0 && controller.data.field_9c == 0 && controller.data.field_a0 == 0);
    assert(controller.data.counters.field_00 == 0 && controller.data.counters.field_2c == 0.0f);
    for (const auto& handle : controller.data.handles) assert(handle.value == 0);
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
    // Original pointers alias storage; writes preserve signed word bits and
    // unrelated counters. This uses real Enemy/State/Data/Movement lifetimes.
    lookup_controller = &controller;
    controller.data.handles[0].value = second->state.identifier.value;
    resolved_enemy = second;
    lookup_calls = find_calls = 0;
    auto* selected_int = first->integer_destination(-9943);
    assert(selected_int == reinterpret_cast<std::int32_t*>(&second->state.counters.field_00));
    assert(lookup_calls == 4 && find_calls == 2); // both resolutions are retained
    *selected_int = std::numeric_limits<std::int32_t>::min();
    assert(second->state.counters.field_00 == 0x80000000u && first->state.counters.field_00 == 0);
    assert(first->integer_destination(-9949) == reinterpret_cast<std::int32_t*>(&controller.data.field_38));
    assert(first->integer_destination(-9926) == reinterpret_cast<std::int32_t*>(&controller.data.counters.field_00));
    for (int i = 0; i != 4; ++i) {
        auto* word = first->integer_destination(-9895 + i);
        assert(word == &enemy_script_globals[i]); *word = -100 - i;
    }
    auto* selected_float = first->float_destination(-9939);
    assert(selected_float == &second->state.counters.field_10);
    *selected_float = -17.25f;
    assert(second->state.counters.field_10 == -17.25f && first->state.counters.field_10 == 0.0f);
    assert(first->float_destination(-9935) == &first->state.counters.field_20);
    assert(first->float_destination(-9922) == &controller.data.counters.field_10);
    first->state.movements.emplace_back();
    const std::array<float*,4> coordinates{
        &first->state.movements[0].motion.position.x, &first->state.movements[0].motion.position.y,
        &first->state.movements[1].motion.position.x, &first->state.movements[1].motion.position.y};
    for (int i = 0; i != 4; ++i) {
        auto* coordinate = first->float_destination(-9995 + i);
        assert(coordinate == coordinates[i]); *coordinate = 37.0f + i;
    }
    // Stale and absent selections fall back to self; a stale handle is retained.
    resolved_enemy = nullptr;
    assert(first->integer_destination(-9943) == reinterpret_cast<std::int32_t*>(&first->state.counters.field_00));
    assert(first->float_destination(-9939) == &first->state.counters.field_10);
    assert(controller.data.handles[0].value == second->state.identifier.value);
    lookup_controller = nullptr; lookup_calls = find_calls = 0;
    assert(controller.selected(0) == nullptr && lookup_calls == 1 && find_calls == 0);
    for (std::uint32_t index : {16u, std::numeric_limits<std::uint32_t>::max()}) {
        lookup_calls = 0; bool threw = false;
        try { controller.selected(index); } catch (const std::out_of_range&) { threw = true; }
        assert(threw && lookup_calls == 0);
    }
    controller.data.handles[15].value = second->state.identifier.value;
    lookup_controller = &controller; resolved_enemy = second;
    assert(controller.selected(15) == second); // actual maximum valid slot
    unsigned integer_count = 0, float_count = 0;
    for (int index = -10000; index <= -9800; ++index) {
        integer_count += first->integer_destination(index) != nullptr;
        float_count += first->float_destination(index) != nullptr;
    }
    assert(integer_count == 19 && float_count == 24);
    for (int index : {0, 1, -1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}) {
        assert(first->integer_destination(index) == nullptr && first->float_destination(index) == nullptr);
    }
    lookup_controller = nullptr; resolved_enemy = nullptr;
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
