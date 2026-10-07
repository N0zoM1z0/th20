#include "EnemyState.hpp"
#include "Enemy.hpp"
#include <array>
#include <cassert>
#include <memory_resource>
#include <new>
#include <cmath>
#include <limits>
#include <type_traits>

// An owned test payload verifies shared lifetime without claiming the native
// shot-metadata object's still unresolved layout or factory implementation.
namespace th20 { struct ShotMetadata {}; }

namespace {
struct CountingResource : std::pmr::memory_resource {
    unsigned live = 0;
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        void* result = std::pmr::new_delete_resource()->allocate(bytes, alignment);
        ++live;
        return result;
    }
    void do_deallocate(void* value, std::size_t bytes, std::size_t alignment) override {
        assert(live);
        --live;
        std::pmr::new_delete_resource()->deallocate(value, bytes, alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};
}

void check_enemy_state() {
    static_assert(std::is_nothrow_constructible_v<th20::Enemy>);
    static_assert(noexcept(std::declval<th20::Motion&>().set_angle(0.0f)));
    CountingResource resource;
    auto* previous = std::pmr::set_default_resource(&resource);
    alignas(th20::EnemyState) std::array<unsigned char,
        sizeof(th20::EnemyState) + 2 * alignof(th20::EnemyState)> storage;
    storage.fill(0xa5);
    auto* state = ::new (storage.data() + alignof(th20::EnemyState)) th20::EnemyState;
    assert(!state->entity && !state->context && !state->mesh);
    assert(state->animations.empty() && state->movements.empty());
    assert(state->queued.empty() && state->phases.empty());
    assert(state->field_278 == 10 && state->field_27c == -1);
    assert(state->flags.word_00 == 0 && state->flags.word_04 == 0 &&
           state->flags.word_08 == 0);
    for (unsigned i = 0; i != alignof(th20::EnemyState); ++i) {
        assert(storage[i] == 0xa5);
        assert(storage[alignof(th20::EnemyState) + sizeof(th20::EnemyState) + i] == 0xa5);
    }

    assert(state->initialize() == 0);
    assert(state->movements.size() == 1 && state->animations.size() == 1);
    assert(state->animations.front().handle.value == 0);
    assert(state->animations.front().parent == -1);
    state->movements.resize(3);
    state->movements.front().motion.position.x = 17.0f;
    state->animations.resize(3);
    state->animations.front().handle.value = 73;
    state->animations.front().offset.x = 19.0f;
    state->animations.front().parent = 4;
    state->phases.resize(4);
    const auto phase_capacity = state->phases.capacity();
    state->health.health = 91;
    state->health.scaled_health = 637;
    state->health.threshold = 12;
    state->health.flags.bits = 0xffffffffu;
    state->pattern.counts.fill(5);
    state->pattern.extra_counts.fill(8);
    state->field_1c = 71;
    state->field_278 = 92;
    state->timer_2a8 = 17;
    state->motion_110.position = th20::Vector3(2.0f, 3.0f, 4.0f);
    state->flags = {0x11223344u, 0x55667788u, 0xaabbccddu};
    auto metadata = std::make_shared<th20::ShotMetadata>();
    state->queued.emplace_front();
    state->queued.front().owner = metadata;
    state->queued.front().field_30 = 23;
    assert(metadata.use_count() == 2);

    assert(state->initialize() == 0);
    assert(state->movements.size() == 1);
    assert(state->movements.front().motion.position.x == 0.0f);
    assert(state->animations.size() == 1);
    assert(state->animations.front().handle.value == 73);
    assert(state->animations.front().offset.x == 19.0f);
    assert(state->animations.front().parent == 4);
    assert(state->phases.empty() && state->phases.capacity() == phase_capacity);
    assert(state->queued.front().field_30 == 23 && metadata.use_count() == 2);
    assert(state->health.health == 0 && state->health.scaled_health == 637);
    assert(state->health.threshold == 12 && state->health.flags.bits == 0xfffffffdu);
    for (auto count : state->pattern.counts) assert(count == 0);
    for (auto count : state->pattern.extra_counts) assert(count == 0);
    assert(state->pattern.radius_x == 32.0f && state->pattern.radius_y == 32.0f);
    assert(state->bounds_5c.x == 24.0f && state->bounds_5c.y == 24.0f);
    assert(state->bounds_64.x == 24.0f && state->bounds_64.y == 24.0f);
    assert(state->motion_110.position.x == 0.0f && state->motion_110.flags.bits == 0);
    assert(state->field_268 == 20 && state->field_26c == 3 && state->field_264 == -1);
    assert(state->field_270 == -1 && state->field_27c == -1);
    assert(state->field_34 == 1 && state->field_4c == 1.0f && state->field_284 == 0);
    assert(state->field_1c == 71 && state->field_278 == 92);
    assert(state->timer_2a8.current == 17);
    assert(state->timer_a8.current == 0 && state->timer_b8.current == 0 &&
           state->timer_288.current == 0 && state->timer_298.current == 0);
    assert(state->flags.word_00 == 0x11223344u && state->flags.word_04 == 0x55667788u &&
           state->flags.word_08 == 0xaabbccddu);

    // Compose actual movement records without advancing their interpolation
    // timers or velocities. Bounds operate on the resulting combined position.
    state->flags.word_04 = 0;
    state->movements.resize(3);
    state->movements[0].motion.position = th20::Vector3(10.0f, 20.0f, 3.0f);
    state->movements[1].motion.position = th20::Vector3(4.0f, -3.0f, 2.0f);
    state->movements[2].motion.position = th20::Vector3(-1.0f, 5.0f, -4.0f);
    state->motion_110.position = th20::Vector3(2.0f, 7.0f, 8.0f);
    const auto timer_before = state->movements[0].position.timer.current;
    state->combine_movements();
    assert(state->motion_110.position.x == 13.0f && state->motion_110.position.y == 22.0f &&
           state->motion_110.position.z == 1.0f);
    assert(state->motion_110.vector_38.x == 11.0f && state->motion_110.vector_38.y == 15.0f &&
           state->motion_110.vector_38.z == -7.0f);
    assert(state->movements[0].motion.position.x == 10.0f);
    assert(state->movements[0].position.timer.current == timer_before);

    state->flags.word_04 = 2;
    state->bounds_178.x = state->bounds_178.y = 0.0f;
    state->bounds_178.width = state->bounds_178.height = 20.0f;
    state->combine_movements();
    assert(state->motion_110.position.x == 10.0f && state->motion_110.position.y == 10.0f);
    assert(state->movements[0].motion.position.x == 7.0f &&
           state->movements[0].motion.position.y == 8.0f &&
           state->movements[0].motion.position.z == 3.0f);
    assert(state->movements[1].motion.position.x == 4.0f &&
           state->movements[2].motion.position.y == 5.0f);
    state->combine_movements();
    assert(state->motion_110.position.x == 10.0f && state->motion_110.position.y == 10.0f);

    state->movements[0].motion.position = th20::Vector3(-100.0f, -100.0f, 3.0f);
    state->combine_movements();
    assert(state->motion_110.position.x == -10.0f && state->motion_110.position.y == -10.0f);
    assert(state->movements[0].motion.position.x == -13.0f &&
           state->movements[0].motion.position.y == -12.0f);

    // Frozen combined motion still records displacement, then bounds and
    // redistributes its retained position into record zero.
    state->motion_110.flags.fields.frozen = 1;
    state->motion_110.position = th20::Vector3(100.0f, -100.0f, 11.0f);
    state->combine_movements();
    assert(state->motion_110.position.x == 10.0f && state->motion_110.position.y == -10.0f &&
           state->motion_110.position.z == 11.0f);
    assert(state->movements[0].motion.position.z == 13.0f);
    state->motion_110.position.x = std::numeric_limits<float>::quiet_NaN();
    state->combine_movements();
    assert(std::isnan(state->motion_110.position.x));
    assert(std::isnan(state->movements[0].motion.position.x));
    assert(state->motion_110.position.y == -10.0f);

    auto& configured = state->movements[1].motion;
    configured.flags.bits = 0xa5a5a5a5u;
    configured.select_orbit();
    assert(configured.flags.bits == 0xa5a5a5a2u);
    configured.select_elliptic();
    assert(configured.flags.bits == 0xa5a5a5a3u);
    configured.select_linear();
    assert(configured.flags.bits == 0xa5a5a5a0u);
    configured.set_position_x(-0.0f);
    configured.set_position_y(19.0f);
    configured.set_speed(-7.0f);
    configured.set_angle(7.0f);
    assert(std::signbit(configured.position_x()) && configured.position_y() == 19.0f);
    assert(configured.position.z == 2.0f && configured.value_18 == -7.0f);
    assert(configured.angle_1c.value == th20::normalize_angle(7.0f));

    state->~EnemyState();
    assert(metadata.use_count() == 1);
    assert(resource.live == 0);
    std::pmr::set_default_resource(previous);
}
