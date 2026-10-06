#include "Random.hpp"
#include "Timer.hpp"

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
}
