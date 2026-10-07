#include "EnemyState.hpp"
#include <array>
#include <cassert>
#include <memory_resource>
#include <new>

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
    state->~EnemyState();
    assert(metadata.use_count() == 1);
    assert(resource.live == 0);
    std::pmr::set_default_resource(previous);
}
