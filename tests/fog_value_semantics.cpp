#include "FogValue.hpp"
#include "Interpolation.hpp"

#include <array>
#include <bit>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <new>

namespace {
std::uint32_t packed_reference(const float* channels) {
    std::uint32_t result = 0;
    for (unsigned i = 0; i != 4; ++i) {
        const auto integer = static_cast<std::int64_t>(std::trunc(double(channels[i])));
        result |= (static_cast<std::uint64_t>(integer) & 255u) << (i * 8);
    }
    return result;
}
template<class T> void dirty_construction() {
    alignas(T) std::array<unsigned char, sizeof(T) + 2 * alignof(T)> storage;
    for (unsigned pattern = 0; pattern != 256; ++pattern) {
        storage.fill(static_cast<unsigned char>(pattern));
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
void check_value(const th20::FogValue& value, const std::array<float, 6>& expected) {
    std::array<std::uint32_t, 7> words;
    std::memcpy(words.data(), &value, sizeof(value));
    for (unsigned i = 0; i != 6; ++i)
        assert(words[i] == std::bit_cast<std::uint32_t>(expected[i]));
    assert(words[6] == packed_reference(expected.data() + 2));
}
}

void check_fog_values() {
    dirty_construction<th20::FogValue>();
    dirty_construction<th20::FogInterpolation>();
    for (int integer = -1024; integer <= 1024; ++integer) {
        for (float fraction : {-0.75f, -0.0f, 0.25f, 0.75f}) {
            const float channel = integer + fraction;
            const std::array<float, 6> expected{-0.0f, 8000.f, channel,
                                               channel + 1, channel - 1, channel + 255};
            th20::FogValue value(expected[0], expected[1], expected[2], expected[3],
                                 expected[4], expected[5]);
            check_value(value, expected);
            value.packed = 0xa55aa55a;
            value.pack();
            check_value(value, expected);
        }
    }
    for (float edge : {-2147483648.f, 2147483520.f, -0.0f}) {
        th20::FogValue value(0, 1, edge, edge, edge, edge);
        const std::array<float, 6> expected{0, 1, edge, edge, edge, edge};
        check_value(value, expected);
    }
    const auto nan = std::bit_cast<float>(0x7fc12345u);
    th20::FogValue raw(nan, -0.0f, 0, 0, 0, 0);
    assert(std::bit_cast<std::uint32_t>(raw.near_distance) == 0x7fc12345u);
    assert(std::bit_cast<std::uint32_t>(raw.far_distance) == 0x80000000u);

    std::uint32_t seed = 0x4718d0u;
    const auto next = [&] { seed = seed * 1664525u + 1013904223u; return seed; };
    for (unsigned n = 0; n != 10000; ++n) {
        std::array<float, 6> x, y;
        for (auto& item : x) item = float(int(next() % 8192) - 4096) / 8.f;
        for (auto& item : y) item = float(int(next() % 8192) - 4096) / 8.f;
        th20::FogValue a(x[0], x[1], x[2], x[3], x[4], x[5]);
        th20::FogValue b(y[0], y[1], y[2], y[3], y[4], y[5]);
        a.packed = 0x12345678; b.packed = 0xabcdef01;
        const auto before_a = a, before_b = b;
        std::array<float, 6> add, subtract, scale;
        const float factor = float(int(next() % 17) - 8) / 4.f;
        for (unsigned i = 0; i != 6; ++i) {
            add[i] = float(double(x[i]) + double(y[i]));
            subtract[i] = float(double(x[i]) - double(y[i]));
            scale[i] = float(double(x[i]) * double(factor));
        }
        check_value(a + b, add); check_value(a - b, subtract);
        check_value(a * factor, scale);
        assert(std::memcmp(&a, &before_a, sizeof(a)) == 0);
        assert(std::memcmp(&b, &before_b, sizeof(b)) == 0);
        a = a + b; check_value(a, add);
        a = before_a; a = a - b; check_value(a, subtract);
        a = before_a; a = a * factor; check_value(a, scale);
    }
}
