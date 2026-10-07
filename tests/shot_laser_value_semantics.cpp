#include "ShotMetadata.hpp"
#include "LaserParameters.hpp"
#include <array>
#include <cassert>
#include <cstdlib>
#include <exception>
#include <memory_resource>
#include <new>
#include <type_traits>
#include <utility>

namespace {
struct Resource : std::pmr::memory_resource {
    unsigned live = 0;
    bool reject = false;
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        if (reject) throw std::bad_alloc();
        auto* result = std::pmr::new_delete_resource()->allocate(bytes, alignment);
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

void zero_command(const th20::BulletCommand& value) {
    assert(value.operand_00 == 0 && value.operand_04 == 0);
    assert(value.operand_08 == 0 && value.operand_0c == 0);
    assert(value.operand_10 == 0 && value.operand_14 == 0);
    assert(value.operand_18 == 0 && value.operand_1c == 0);
    assert(value.opcode == 0 && value.flags == 0 && !value.script);
}

void metadata_construction(Resource& resource) {
    static_assert(std::is_nothrow_default_constructible_v<th20::ShotMetadata>);
    static_assert(!std::is_nothrow_move_assignable_v<th20::ShotMetadata>);
    alignas(th20::ShotMetadata) std::array<unsigned char,
        sizeof(th20::ShotMetadata) + 2 * alignof(th20::ShotMetadata)> storage;
    storage.fill(0xa5);
    auto* memory = storage.data() + alignof(th20::ShotMetadata);
    auto* value = ::new (memory) th20::ShotMetadata;
    assert(value->field_00 == 0 && value->field_14 == 0 && value->field_18 == 0);
    assert(value->field_1c == 0 && value->field_20 == 0);
    assert(value->field_24 == 0 && value->field_28 == 0 && value->field_2c == 0);
    assert(value->field_30 == 0 && value->field_34 == 0);
    assert(value->field_38 == 0 && value->field_3a == 0 && value->field_44 == 0);
    assert(value->field_48 == 0 && !value->field_49);
    assert(value->sound == 21 && value->alternate_sound == 38);
    assert(value->commands.get_allocator().resource() == &resource);
    assert(value->commands.size() == 2 && resource.live == 1);
    for (const auto& command : value->commands) zero_command(command);
    // Construction preserves implicit trailing ABI padding and adjacent storage.
    const auto tail = reinterpret_cast<unsigned char*>(&value->field_49) - memory +
                      sizeof(value->field_49);
    for (auto i = tail; i != sizeof(th20::ShotMetadata); ++i) assert(memory[i] == 0xa5);
    for (unsigned i = 0; i != alignof(th20::ShotMetadata); ++i) {
        assert(storage[i] == 0xa5);
        assert(storage[sizeof(th20::ShotMetadata) + alignof(th20::ShotMetadata) + i] == 0xa5);
    }
    value->~ShotMetadata();
    assert(resource.live == 0);
}

void metadata_transfer(Resource& first, Resource& second) {
    {
        th20::ShotMetadata source, destination;
        source.commands.resize(5);
        source.commands[3].opcode = 24;
        source.commands[3].script = "owned test script";
        source.sound = -7;
        source.field_49 = true;
        auto* source_buffer = source.commands.data();
        destination = std::move(source);
        assert(destination.commands.data() == source_buffer && source.commands.empty());
        assert(destination.commands[3].opcode == 24 && destination.sound == -7);
        assert(destination.field_49 && first.live == 1);
        destination = th20::ShotMetadata();
        assert(destination.commands.size() == 2 && destination.sound == 21);
        assert(destination.alternate_sound == 38 && !destination.field_49);
        for (const auto& command : destination.commands) zero_command(command);
    }
    assert(first.live == 0);
    {
        th20::ShotMetadata source;
        source.commands.resize(5);
        source.commands[4].operand_18 = -123;
        source.field_20 = 17.5f;
        auto* source_buffer = source.commands.data();
        std::pmr::set_default_resource(&second);
        th20::ShotMetadata copied(source), destination;
        assert(copied.commands.get_allocator().resource() == &second);
        assert(copied.commands.data() != source_buffer && copied.field_20 == 17.5f);
        copied.commands[4].operand_18 = 42;
        assert(source.commands[4].operand_18 == -123);
        destination = std::move(source);
        assert(destination.commands.get_allocator().resource() == &second);
        assert(destination.commands.data() != source_buffer);
        assert(destination.commands.size() == 5 && destination.commands[4].operand_18 == -123);
        assert(destination.field_20 == 17.5f);
        std::pmr::set_default_resource(&first);
    }
    assert(first.live == 0 && second.live == 0);
}

void laser_lifetimes(Resource& resource) {
    {
        th20::LaserType0Parameters zero;
        th20::LaserType1Parameters one;
        th20::LaserType2Parameters two;
        th20::LaserType3Parameters three;
        assert(zero.position.x == 0 && zero.position.y == 0 && zero.position.z == 0);
        assert(one.velocity.x == 0 && one.velocity.y == 0 && one.velocity.z == 0);
        assert(three.vector_0c.x == 0 && three.vector_0c.y == 0 && three.vector_0c.z == 0);
        assert(one.growth_speed == 8 && one.delay == 0 && one.grow_time == 0);
        assert(one.sustain_time == 0 && one.shrink_time == 0 && one.sound == 0);
        assert(zero.flags == 0 && one.flags == 0 && two.flags.word == 0 && three.flags == 0);
        assert(!two.path && two.sound == 0 && two.motion_sound == 0 && two.time == 0);
        assert(three.field_30 == 0.0f);
        assert(zero.commands.empty() && one.commands.empty());
        assert(two.commands.empty() && three.commands.empty() && resource.live == 0);
        assert(zero.view_index == 0 && one.view_index == 0 && two.view_index == 0 && three.view_index == 0);
        zero.commands.resize(1);
        one.commands.resize(2);
        two.commands.resize(3);
        three.commands.resize(4);
        assert(resource.live == 4);
        for (const auto& command : two.commands) zero_command(command);
    }
    assert(resource.live == 0);
}
}

int main(int argc, char**) {
    Resource first, second;
    auto* previous = std::pmr::set_default_resource(&first);
    if (argc != 1) {
        first.reject = true;
        std::set_terminate([] { std::_Exit(77); });
        th20::ShotMetadata value;
        return 1;
    }
    metadata_construction(first);
    metadata_transfer(first, second);
    laser_lifetimes(first);
    std::pmr::set_default_resource(previous);
    assert(first.live == 0 && second.live == 0);
}
