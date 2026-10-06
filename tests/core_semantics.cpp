#include "Random.hpp"
#include "Timer.hpp"
#include "ClockScalar.hpp"
#include "FunctionChain.hpp"
#include "LockRegistry.hpp"
#include "TaskInfo.hpp"

#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <limits>

namespace {
unsigned callback_calls;
std::int32_t callback_a(void*) { ++callback_calls; return 1; }
std::int32_t callback_b(void*) { ++callback_calls; return 2; }
std::int32_t callback_c(void*) { ++callback_calls; return 3; }
}

int main() {
    // Independent division-based oracle, including states outside normal seeds.
    std::uint32_t sample = 0x81a7b393u;
    for (unsigned i = 0; i != 100000; ++i) {
        sample = sample * 1664525u + 1013904223u;
        const auto expected = static_cast<std::uint32_t>(
            (static_cast<std::uint64_t>(sample) * 48271u) % 2147483647u);
        assert(th20::random_step(sample) == expected);
    }
    assert(th20::random_step(0) == 0);
    assert(th20::random_step(2147483647u) == 0);
    assert(th20::random_step(0xffffffffu) == 48271u);
    th20::RandomState random{1};
    for (const auto value : {48271u, 182605794u, 1291394886u, 1914720637u}) {
        assert(random.next() == value);
        assert(random.state == value);
    }

    constexpr std::array<std::int32_t, 7> values = {
        std::numeric_limits<std::int32_t>::min(), -999999, -1, 0, 1,
        16777217, std::numeric_limits<std::int32_t>::max()};
    for (std::uint32_t flags = 0; flags != 256; ++flags) {
        th20::Timer timer{12, 34, 56.0f, flags};
        timer.reset();
        assert(timer.previous == -999999 && timer.current == 0);
        assert(std::bit_cast<std::uint32_t>(timer.current_fraction) == 0);
        assert(timer.flags == flags);
        for (const auto mode : {0u, 1u, 2u, 3u, 4u, 0xffffffffu}) {
            timer.flags = flags;
            timer.set_mode(mode);
            assert((timer.flags & ~6u) == (flags & ~6u));
            assert(((timer.flags >> 1) & 3u) == (mode % 4u));
        }
        for (const auto value : values) {
            timer.flags = flags;
            timer.set(value);
            assert(timer.current == value);
            assert(static_cast<std::uint32_t>(timer.previous)
                   == static_cast<std::uint32_t>(value) - 1u);
            assert(timer.current_fraction == static_cast<float>(value));
            assert(timer.flags == ((flags & 1u) ? flags : ((flags & ~6u) | 1u)));
        }
    }

    assert(th20::timer_clock_sources[0] == &th20::default_timer_clock);
    assert(th20::default_timer_clock.value == 1.0f);
    th20::ClockScalar half{0.5f};
    th20::timer_clock_sources[0] = &half;
    th20::Timer fractional{99, 17, 0.25f, 0xfffffff7u};
    assert(fractional.tick() == 0);
    assert(fractional.previous == 17 && fractional.current_fraction == 0.75f);
    assert(fractional.flags == 0xfffffff1u);
    assert(fractional.tick() == 1 && fractional.current_fraction == 1.25f);
    fractional.add(-0.5f);
    assert(fractional.previous == 1 && fractional.current == 1);
    assert(fractional.current_fraction == 1.0f);

    // Near-one paths advance the integer independently of the float value.
    th20::ClockScalar near_one{0.995f};
    th20::timer_clock_sources[0] = &near_one;
    th20::Timer independent{0, 100, 2.25f, 1u};
    assert(independent.tick() == 101 && independent.current_fraction == 3.25f);
    independent.add(2.0f);
    assert(independent.current == 5 && independent.current_fraction == 5.25f);

    // Strict interval endpoints use scaling; null uses an unscaled step.
    for (float rate : {0.99f, 1.01f}) {
        th20::ClockScalar endpoint{rate};
        th20::timer_clock_sources[0] = &endpoint;
        th20::Timer timer{0, 0, 0.0f, 1u};
        timer.add(100.0f);
        assert(timer.current_fraction == rate * 100.0f);
        assert(timer.current == (rate < 1.0f ? 99 : 101));
    }
    th20::timer_clock_sources[0] = nullptr;
    th20::Timer null_clock{0, std::numeric_limits<std::int32_t>::max(), 4.25f, 1u};
    assert(null_clock.tick() == std::numeric_limits<std::int32_t>::min());
    assert(null_clock.current_fraction == 5.25f);
    th20::Timer uninitialized{91, 71, 44.0f, 0xfffffffeu};
    assert(uninitialized.tick() == 1 && uninitialized.current_fraction == 1.0f);
    assert(uninitialized.previous == 0 && uninitialized.flags == 0xfffffff9u);
    th20::timer_clock_sources[0] = &th20::default_timer_clock;

    int context = 22;
    for (std::uint32_t flags = 0; flags != 256; ++flags) {
        th20::FunctionChainNode node{0, 0, nullptr, nullptr, nullptr,
                                    th20::FunctionChainLink{}, nullptr};
        th20::FunctionChainLink link{&node};
        assert(link.node == &node && link.next == nullptr && link.previous == nullptr);
        assert(link.owner == nullptr && link.iterator == nullptr);
        node.priority = -31;
        node.flags = flags;
        node.link.node = &node;
        node.link.next = &node.link;
        node.link.previous = &node.link;
        node.set_userdata(&context);
        node.set_before_insert(callback_b);
        node.set_shutdown_callback(callback_c);
        assert(node.before_insert == callback_b && node.on_shutdown == callback_c);
        node.set_callback(callback_a);
        assert(node.callback == callback_a && node.before_insert == nullptr && node.on_shutdown == nullptr);
        node.set_before_insert(callback_b);
        node.set_shutdown_callback(callback_c);
        node.clear_callbacks();
        assert(node.callback == nullptr && node.before_insert == nullptr && node.on_shutdown == nullptr);
        node.set_owned();
        assert(node.flags == (flags | 1u));
        node.enable();
        assert(node.flags == (flags | 3u));
        node.disable();
        assert(node.flags == ((flags | 1u) & ~2u));
        assert(node.priority == -31 && node.userdata == &context);
        assert(node.link.node == &node && node.link.next == &node.link && node.link.previous == &node.link);
    }
    assert(callback_calls == 0); // Setters never invoke or dispatch a callback.

    th20::FunctionChainLink first, middle, last;
    first.insert_after(&last);
    assert(first.next == &last && last.previous == &first && last.next == nullptr);
    last.insert_before(&middle);
    assert(first.next == &middle && middle.previous == &first);
    assert(middle.next == &last && last.previous == &middle);
    assert(first.previous == nullptr && last.next == nullptr);
    assert(middle.owner == nullptr && last.owner == nullptr);
    th20::FunctionChainLink before_first;
    first.insert_before(&before_first);
    assert(before_first.next == &first && first.previous == &before_first);
    assert(before_first.previous == nullptr);

    th20::LockRegistry registry;
    assert(!registry.enabled());
    std::array<unsigned char, sizeof(registry)> registry_before{}, registry_after{};
    std::memcpy(registry_before.data(), &registry, sizeof(registry));
    registry.enable();
    assert(registry.enabled());
    std::memcpy(registry_after.data(), &registry, sizeof(registry));
    unsigned changed = 0;
    for (std::size_t index = 0; index != registry_before.size(); ++index) {
        if (registry_before[index] != registry_after[index]) {
            ++changed;
            assert(registry_before[index] == 0 && registry_after[index] == 1);
        }
    }
    assert(changed == 1); // Locks, tracked depths and adjacent storage survive.
    registry.disable();
    assert(!registry.enabled());
    std::memcpy(registry_after.data(), &registry, sizeof(registry));
    assert(registry_before == registry_after);

    th20::TaskInfo task;
    assert(task.flags == 2 && task.update_node == nullptr && task.draw_node == nullptr);
    th20::TaskInfo* virtual_task = &task;
    virtual_task->enable();
    virtual_task->disable();
    th20::FunctionChainNode update{0, 0xffffffffu, callback_a, callback_b, callback_c,
                                  th20::FunctionChainLink{}, &context};
    th20::FunctionChainNode draw{0, 0x12345678u, callback_a, callback_b, callback_c,
                                th20::FunctionChainLink{}, &context};
    task.update_node = &update;
    virtual_task->disable();
    assert(update.flags == 0xfffffffdu && draw.flags == 0x12345678u);
    task.draw_node = &draw;
    virtual_task->enable();
    assert(update.flags == 0xffffffffu && draw.flags == 0x1234567au);
    task.update_node = nullptr;
    virtual_task->disable();
    assert(update.flags == 0xffffffffu && draw.flags == 0x12345678u);
    assert(task.flags == 2 && callback_calls == 0);
    assert(update.callback == callback_a && draw.userdata == &context);
}
