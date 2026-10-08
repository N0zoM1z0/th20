#pragma once

#include "Timer.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace th20 {

// Fifteen item kinds are emitted, but each native count array has sixteen slots.
struct EnemyPattern {
    std::int32_t player, base_kind, bomb_kind;
    std::array<std::uint32_t, 16> counts, extra_counts;
    std::uint32_t duration;
    Timer timer;
    float radius_x, radius_y;

    EnemyPattern();
    void reset();
    void set_base_kind(std::int32_t value);
    std::int32_t base_kind_value() const;
    void clear_counts();
};

static_assert(std::is_trivially_copyable_v<EnemyPattern>);
static_assert(sizeof(EnemyPattern) == 168);
static_assert(offsetof(EnemyPattern, counts) == 0x0c);
static_assert(offsetof(EnemyPattern, extra_counts) == 0x4c);
static_assert(offsetof(EnemyPattern, duration) == 0x8c);
static_assert(offsetof(EnemyPattern, timer) == 0x90);
static_assert(offsetof(EnemyPattern, radius_x) == 0xa0);
static_assert(offsetof(EnemyPattern, radius_y) == 0xa4);

} // namespace th20
