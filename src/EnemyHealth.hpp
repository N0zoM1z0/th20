#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

// Bit zero selects scaled health; bit one requests forced defeat.
struct EnemyHealthFlags { std::uint32_t bits; };

// The real 28-byte value at EnemyState+18c. Integer storage preserves native
// modulo32 accounting; queries and division interpret the required signed bits.
struct EnemyHealth {
    std::uint32_t health, field_04, phase_health, scaled_health, threshold, damage;
    EnemyHealthFlags flags;

    EnemyHealth();
    void reset();
    std::int32_t apply(std::int32_t amount);
    void record(std::int32_t amount);
    int positive() const;
    std::uint32_t forced_end() const;
};

static_assert(sizeof(EnemyHealthFlags) == 4);
static_assert(sizeof(EnemyHealth) == 28);
static_assert(offsetof(EnemyHealth, phase_health) == 8);
static_assert(offsetof(EnemyHealth, scaled_health) == 12);
static_assert(offsetof(EnemyHealth, threshold) == 16);
static_assert(offsetof(EnemyHealth, damage) == 20);
static_assert(offsetof(EnemyHealth, flags) == 24);

} // namespace th20
