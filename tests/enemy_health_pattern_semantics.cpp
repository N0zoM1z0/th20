#include "EnemyHealth.hpp"
#include "EnemyPattern.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <new>

namespace {
std::int64_t signed_word(std::uint32_t value) {
    return value < 0x80000000u ? value : std::int64_t(value) - 0x100000000LL;
}
std::uint32_t wrapped(std::int64_t value) {
    return static_cast<std::uint32_t>(static_cast<std::uint64_t>(value) & 0xffffffffu);
}
template<class T> void dirty_construction() {
    alignas(T) std::array<unsigned char, sizeof(T) + 2 * alignof(T)> storage;
    for (unsigned char pattern : {0x5a, 0xa5, 0xff}) {
        storage.fill(pattern);
        auto* value = ::new (storage.data() + alignof(T)) T;
        for (unsigned i = 0; i != alignof(T); ++i) {
            assert(storage[i] == pattern);
            assert(storage[alignof(T) + sizeof(T) + i] == pattern);
        }
        for (unsigned i = 0; i != sizeof(T); ++i)
            assert(storage[alignof(T) + i] == 0);
        value->~T();
    }
}
}

void check_enemy_health_pattern() {
    dirty_construction<th20::EnemyHealth>();
    dirty_construction<th20::EnemyPattern>();

    std::uint32_t seed = 0x71f30a95u;
    const auto next = [&] { seed = seed * 1664525u + 1013904223u; return seed; };
    for (unsigned n = 0; n != 10000; ++n) {
        th20::EnemyHealth value;
        std::array<std::uint32_t, 7> before;
        for (auto& word : before) word = next();
        if (n < 4) before[0] = std::array<std::uint32_t, 4>{0, 1, 0x80000000u, 0x7fffffffu}[n];
        std::memcpy(reinterpret_cast<unsigned char*>(&value), before.data(), sizeof(value));
        assert(value.positive() == (signed_word(before[0]) > 0 ? 1 : 0));
        assert(value.forced_end() == (before[6] & 2u ? 1u : 0u));
        const std::int32_t amount = static_cast<std::int32_t>(next());
        const auto signed_amount = std::int64_t(amount);
        const auto scaled = wrapped(signed_word(before[3]) - signed_amount);
        const auto numerator = wrapped(std::int64_t(scaled) - std::int64_t(before[4]) * 7);
        const auto result = before[6] & 1u
            ? wrapped(signed_word(numerator) / 7 + std::int64_t(before[4]))
            : wrapped(signed_word(before[0]) - signed_amount);
        auto expected = before;
        expected[0] = result;
        expected[5] = wrapped(std::int64_t(before[5]) + signed_amount);
        if (before[6] & 1u) expected[3] = scaled;
        assert(std::int64_t(value.apply(amount)) == signed_word(result));
        std::array<std::uint32_t, 7> actual;
        std::memcpy(actual.data(), &value, sizeof(value));
        assert(actual == expected);
        assert(value.positive() == (signed_word(result) > 0 ? 1 : 0));
        assert(value.forced_end() == (before[6] & 2u ? 1u : 0u));
        value.record(amount);
        expected[5] = wrapped(std::int64_t(expected[5]) + signed_amount);
        std::memcpy(actual.data(), &value, sizeof(value));
        assert(actual == expected);
        value.reset();
        expected[0] = expected[1] = expected[2] = expected[5] = 0;
        expected[6] &= ~2u;
        std::memcpy(actual.data(), &value, sizeof(value));
        assert(actual == expected);
    }

    for (std::uint32_t flags : {0u, 0xfffffffeu, 1u, 0xffffffffu}) {
        th20::EnemyPattern pattern;
        pattern.player = -7;
        pattern.base_kind = 13;
        pattern.bomb_kind = 15;
        for (unsigned i = 0; i != 16; ++i) {
            pattern.counts[i] = 0xa5000000u + i;
            pattern.extra_counts[i] = 0x80000000u + i;
        }
        pattern.duration = 170;
        pattern.timer.previous = -17;
        pattern.timer.current = 42;
        pattern.timer.current_fraction = 42.5f;
        pattern.timer.flags = flags;
        pattern.radius_x = -32.0f;
        pattern.radius_y = 71.0f;
        const auto extras = pattern.extra_counts;
        pattern.clear_counts();
        for (auto count : pattern.counts) assert(count == 0);
        assert(pattern.extra_counts == extras);
        assert(pattern.player == -7 && pattern.base_kind == 13 && pattern.bomb_kind == 15);
        assert(pattern.radius_x == -32.0f && pattern.radius_y == 71.0f);
        assert(pattern.duration == 0 && pattern.timer.previous == -1);
        assert(pattern.timer.current == 0 && pattern.timer.current_fraction == 0.0f);
        assert(pattern.timer.flags == (flags & 1u ? flags : (flags & ~6u) | 1u));
        pattern.reset();
        assert(pattern.player == 0 && pattern.base_kind == 0 && pattern.bomb_kind == 0);
        for (auto count : pattern.counts) assert(count == 0);
        for (auto count : pattern.extra_counts) assert(count == 0);
        assert(pattern.duration == 0 && pattern.timer.previous == -1);
        assert(pattern.timer.current == 0 && pattern.timer.current_fraction == 0.0f);
        assert(pattern.timer.flags == 1);
        assert(pattern.radius_x == 32.0f && pattern.radius_y == 32.0f);
    }
}
