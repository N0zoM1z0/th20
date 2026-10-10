#pragma once

#include <cstddef>
#include <cstdint>
#include <random>

namespace th20 {

// The explicit uint32_t engine also preserves the observed x86 storage on hosts
// whose uint_fast32_t is wider. On locked MSVC this is std::minstd_rand.
using GameRandomEngine = std::linear_congruential_engine<std::uint32_t, 48271, 0, 0x7fffffff>;

struct GameRandom {
    std::uint32_t field_00 = 0;
    GameRandomEngine engine;
    std::uint32_t minimum = 0;
    std::uint32_t upper = 0x00ffff00;
    std::uint32_t modulus = 0;
    std::uint32_t last = 0;
    std::uint32_t id;

    explicit GameRandom(std::uint32_t stream_id);
    // Both state-changing operations unconditionally own shared mutex slot 10.
    // Sampling requires a nonzero modulus; the native DIV failure is not replaced.
    void seed(std::uint32_t value);
    std::uint32_t next();
    std::uint32_t bounded(std::uint32_t count);
    float unit();
    float range(float limit);
    float signed_unit();
    float radians();
    float signed_range(float limit);
};

static_assert(sizeof(GameRandomEngine) == 4);
static_assert(sizeof(GameRandom) == 28);
static_assert(offsetof(GameRandom, engine) == 4);
static_assert(offsetof(GameRandom, modulus) == 16);
static_assert(offsetof(GameRandom, last) == 20);
static_assert(offsetof(GameRandom, id) == 24);

} // namespace th20
