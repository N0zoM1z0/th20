#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "Context.hpp"
#include "DiagnosticAllocator.hpp"
#include "EnemyController.hpp"
#include "Graphics.hpp"
#include <array>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <new>
#include <vector>

namespace {
th20::Animation* old_animation;
th20::Animation* new_animation;
std::vector<int> events;
int expected_script;
th20::Vector3 expected_position;
}

namespace th20 {
// Owned host fixtures for unresolved production startup and lifetimes. The
// maintained movement, Motion, parent/list, ANM and graphics constructors run
// unchanged. These fixtures make no native ECL/resource/controller claim.
LockRegistry process_locks;
DiagnosticAllocator::DiagnosticAllocator() : state_word_(0), resource_() {}
DiagnosticAllocator allocator;
DiagnosticAllocator* process_allocator = &allocator;
void DiagnosticAllocator::release_animation_callback(AnimationCallback* value) {
    assert(!value);
}
const Matrix4 identity_matrix = [] {
    Matrix4 result;
    for (int i = 0; i != 4; ++i) result.elements[i][i] = 1.0f;
    return result;
}();
Graphics process_graphics;
Graphics::~Graphics() = default;
AnimationFile::~AnimationFile() = default;
int ScriptStack::pop(std::int32_t, void*, char) { std::abort(); }
EclScriptPosition::EclScriptPosition() noexcept : subroutine(0), offset(0) {}
EclRuntime::EclRuntime() noexcept : time(0), async_id(0), manager(nullptr), signal(0),
    rank(0), flags(0) {}
EclManager::EclManager() : field_04(0), field_08(0), current_runtime(nullptr),
    loader(nullptr) {}
EclManager::~EclManager() = default;
Enemy::~Enemy() = default;
std::int32_t EclManager::execute_opcode() { std::abort(); }
std::int32_t EclManager::read_integer(std::int32_t) { std::abort(); }
std::int32_t* EclManager::integer_destination(std::int32_t) { std::abort(); }
float EclManager::read_float(std::int32_t) { std::abort(); }
float* EclManager::float_destination(std::int32_t) { std::abort(); }
std::int32_t Enemy::execute_opcode() { std::abort(); }
std::int32_t Enemy::read_integer(std::int32_t) { std::abort(); }
std::int32_t* Enemy::integer_destination(std::int32_t) { std::abort(); }
float Enemy::read_float(std::int32_t) { std::abort(); }
float* Enemy::float_destination(std::int32_t) { std::abort(); }
TaskInfo::~TaskInfo() = default;
void TaskInfo::enable() { std::abort(); }
void TaskInfo::disable() { std::abort(); }
EnemyController::EnemyController() noexcept : field_c4(0), field_c8(0),
    field_cc(0), field_e0(0), animation_files{}, loader(nullptr), field_120(0),
    field_124(0), player_index(0), context(nullptr) {}
EnemyController::~EnemyController() = default;
EnemyController* expected_controller;
AnimationFile* expected_file;
AnimationFile* EnemyController::animation_file(std::int32_t index) {
    assert(this == expected_controller && index == 2);
    events.push_back(2);
    return expected_file;
}
// Bounded lookup/retirement/spawn fixtures observe the native call contract.
// Their still-unreconstructed renderer and file bodies are not executed.
Animation* AnimationHandle::resolve() {
    events.push_back(1);
    if (value == 11) return old_animation;
    if (value == 12) return new_animation;
    value = 0;
    return nullptr;
}
void AnimationHandle::retire() {
    assert(value == 11);
    events.push_back(3);
    value = 0;
}
AnimationHandle AnimationFile::spawn(const char* stem, std::int32_t script,
    const Vector3& position, float rotation, std::int32_t layer, std::uint32_t flags) {
    assert(this == expected_file && !stem && script == expected_script);
    assert(rotation == 0 && layer == 8 && flags == 0);
    assert(position.x == expected_position.x && position.y == expected_position.y &&
           position.z == expected_position.z);
    events.push_back(4);
    AnimationHandle result;
    result.value = 12;
    return result;
}
}

namespace {
void reset(th20::EnemyState& state, std::size_t count = 1) {
    state.flags = {};
    state.initialize();
    state.movements.resize(count);
    state.vector_170 = {};
    events.clear();
    th20::process_graphics.viewports[0].final_vector = {};
}
void check_construction() {
    alignas(th20::Graphics) std::array<unsigned char, sizeof(th20::Graphics)> bytes;
    bytes.fill(0xa5);
    auto* graphics = ::new (bytes.data()) th20::Graphics;
    auto retained = [](const auto& member) {
        const auto* first = reinterpret_cast<const unsigned char*>(&member);
        for (std::size_t i = 0; i < sizeof(member); ++i) assert(first[i] == 0xa5);
    };
    retained(graphics->view);
    retained(graphics->projection);
    retained(graphics->device_caps);
    retained(graphics->field_db0);
    retained(graphics->version_data_size);
    assert(!graphics->direct3d && !graphics->device && !graphics->current_viewport);
    assert(graphics->field_b08 == -2 && graphics->field_b0c == -2);
    assert(graphics->field_b10 == -2 && graphics->update_duration == 0);
    assert(graphics->flags.bit7 && graphics->flags.bit11);
    assert(graphics->flags.retained == (0xa5a5a5a5u >> 14));
    for (auto byte : graphics->snapshot_path) assert(byte == 0);
    for (const auto& viewport : graphics->viewports) {
        retained(viewport.view);
        retained(viewport.projection);
        assert(viewport.bounds_11c.x == 0 && viewport.bounds_124.y == 0);
        assert(viewport.points[2].x == 0 && viewport.final_vector.z == 0);
    }
    const auto& config = graphics->configuration;
    assert(config.version == 0x200002 && config.size == 176);
    assert(config.bindings[1].keyboard.slot7 == 0x27);
    assert(config.value_70 == 600 && config.value_72 == 600);
    assert(config.saved_window_x == std::numeric_limits<std::int32_t>::min());
    assert(config.flags.bit7 && config.flags.retained == (0xa5a5a5a5u >> 9));
    const auto* config_bytes = reinterpret_cast<const unsigned char*>(&config);
    for (std::size_t i : {0x77u, 0xa5u, 0xa6u, 0xa7u}) assert(config_bytes[i] == 0xa5);
    graphics->~Graphics();
}
void check_movement(th20::Enemy& enemy, th20::Enemy& parent) {
    auto& state = enemy.state;
    state.entity = &enemy;
    parent.children.reset(&parent);
    parent.children.append(&enemy.parent_link);
    assert(enemy.parent() == &parent);
    reset(state);
    state.motion_110.position = {1, 2, 3};
    state.movements[0].motion.vector_38 = {2, 3, 4};
    // Explicit interpolation targets override velocity; the old combined value
    // is captured before following, per-record advancement or composition.
    auto& interpolation = state.movements[0].position;
    interpolation.duration = 1;
    interpolation.timer = 0;
    interpolation.end = {9, 10, 11};
    state.update_movements();
    assert(state.motion_c8.position.x == 1 && state.motion_c8.position.z == 3);
    assert(state.motion_110.position.x == 9 && state.motion_110.position.z == 11);
    assert(interpolation.duration == 0);

    reset(state, 2);
    parent.state.motion_110.position = {4, 5, 6};
    state.flags.word_08 = 8;
    state.flags.word_04 = 1u << 10;
    state.movements[0].motion.flags.bits = 32; // Frozen motion still receives offset.
    state.movements[1].motion.flags.bits = 32;
    state.movements[1].motion.position = {1, 2, 3};
    state.movements[0].motion.value_20 = 73;
    th20::process_graphics.viewports[0].final_vector = {10, 20, 30};
    state.update_movements();
    assert(state.movements[0].motion.position.x == 14);
    assert(state.movements[0].motion.value_20 == 73);
    assert(state.movements[1].motion.position.y == 22);
    assert(state.motion_110.position.z == 69);

    reset(state);
    auto& movement = state.movements[0];
    movement.motion.select_orbit();
    movement.scalar_ac.duration = 5;
    movement.scalar_ac.timer = 7;
    movement.scalar_d8.begin(1, 0, 1.0f, 2.0f);
    movement.vector_104.begin(1, 0, th20::Vector2(3, 4), th20::Vector2(5, 6));
    state.update_movements();
    assert(movement.scalar_ac.timer.current == 7 && movement.scalar_ac.duration == 5);
    // Orbit velocity advances the newly sampled radius by its sampled rate.
    assert(movement.motion.value_20 == 11 && movement.motion.value_24 == 6);
    assert(movement.motion.value_18 == 2);
    assert(movement.scalar_d8.duration == 0 && movement.vector_104.duration == 0);
    movement.motion.select_elliptic();
    state.update_movements();
    assert(movement.scalar_ac.timer.current == 7);
    reset(state);
    state.movements[0].scalar_ac.begin(1, 0, 0.0f, 0.5f);
    state.update_movements();
    assert(state.movements[0].motion.angle_1c.value == 0.5f);
    parent.children.remove(&enemy.parent_link);
}
void check_bounds(th20::EnemyState& state) {
    for (int axis = 0; axis < 2; ++axis) {
        reset(state);
        state.movements[0].motion.position = axis == 0 ? th20::Vector3(300, 500, 0)
                                                    : th20::Vector3(0, 500, 0);
        assert(state.update_movements() == 0); // Has never entered.
        assert(!(state.flags.word_08 & 64));
        state.flags.word_04 |= 1;
        assert(state.update_movements() == -1);
        state.flags.word_00 |= 1u << (axis + 2);
        assert(state.update_movements() == 0);
    }
    reset(state);
    state.movements[0].motion.position = {-192, 448, 0};
    assert(state.update_movements() == 0 && (state.flags.word_08 & 64));
    assert(state.flags.word_04 & 1);
    state.movements[0].motion.position.x = std::numeric_limits<float>::quiet_NaN();
    assert(state.update_movements() == 0 && (state.flags.word_08 & 64));
}
void check_animation(th20::EnemyState& state, th20::Context& context) {
    th20::AnimationFile file;
    th20::EnemyController controller;
    th20::expected_file = &file;
    th20::expected_controller = &controller;
    context.enemies = &controller;
    state.context = &context;
    th20::Animation old, replacement;
    old_animation = &old;
    new_animation = &replacement;
    old.position_ref() = {7, 8, 9};
    replacement.base.vector_70 = {-40, -30};
    replacement.base.vector_50 = {2, 3};
    for (int before : {-1, 0, 1, 9}) {
        for (int after : {-1, 0, 1}) {
            reset(state);
            state.field_20 = 2;
            state.field_28 = 100;
            state.field_2c = before;
            state.flags.word_04 = 16;
            state.movements[0].motion.position.x = static_cast<float>(after);
            state.movements[0].motion.position.y = 100;
            state.animations[0].handle.value = 11;
            expected_position = old.position_ref();
            int transition = 0;
            if (before == -1) transition = after == 0 ? 3 : 2;
            if (before == 0) transition = after == -1 ? 1 : 2;
            if (before == 1) transition = after == 0 ? 4 : 1;
            expected_script = 100 + transition;
            state.update_movements();
            if (before == after) assert(events == std::vector<int>{1});
            else {
                assert(events == (std::vector<int>{1, 2, 3, 4, 1}));
                assert(state.field_2c == after && state.animations[0].handle.value == 12);
                assert(state.vector_170.x == 90 && state.vector_170.y == 80);
            }
        }
    }
    reset(state);
    state.context = &context;
    state.field_20 = 2;
    state.field_28 = 100;
    state.field_2c = -1;
    state.flags.word_04 = 16;
    state.animations[0].handle.value = 99; // Failed lookup clears before spawn.
    expected_script = 103;
    expected_position = {};
    state.update_movements();
    assert(events == (std::vector<int>{1, 2, 4, 1}));
    reset(state);
    state.vector_170 = {37, 41};
    state.animations[0].handle.value = 99;
    state.update_movements();
    assert(state.animations[0].handle.value == 0);
    assert(state.vector_170.x == 37 && state.vector_170.y == 41);
    reset(state);
    old.base.vector_50 = {1, 1};
    old.base.vector_70 = {-std::numeric_limits<float>::quiet_NaN(), -0.0f};
    state.animations[0].handle.value = 11;
    state.update_movements();
    assert(state.vector_170.x == 0 && !std::signbit(state.vector_170.x));
    assert(std::isnan(state.vector_170.y) && !std::signbit(state.vector_170.y));
}
}

int main() {
    check_construction();
    th20::Context context;
    assert(!context.enemies && !context.primary_owner && !context.overlay_owner);
    th20::Enemy enemy, parent;
    check_movement(enemy, parent);
    check_bounds(enemy.state);
    check_animation(enemy.state, context);
}
