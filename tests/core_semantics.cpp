#include "Random.hpp"
#include "Timer.hpp"
#include "ClockScalar.hpp"

#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <limits>

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
}
