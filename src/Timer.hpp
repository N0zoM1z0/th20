#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

// REF-001: field accesses checked at 0x00423F50, 0x00423FE0, 0x00423F80.
// Reset preserves flags. Setting a value initializes only when bit 0 is clear.
struct TimerFlagBits {
    std::uint32_t initialized : 1;
    std::uint32_t mode : 2;
    std::uint32_t other : 29;
};
static_assert(sizeof(TimerFlagBits) == 4);

struct Timer {
    std::int32_t previous;
    std::int32_t current;
    float current_fraction;
    // Raw-word and bit-field views follow the MSVC x86 flag representation.
    union {
        std::uint32_t flags;
        TimerFlagBits flag_bits;
    };

    void reset();
    void set_mode(std::uint32_t mode);
    void set(std::int32_t value);
    void add(float delta);
    std::int32_t tick();
};

static_assert(sizeof(Timer) == 16);
static_assert(offsetof(Timer, previous) == 0);
static_assert(offsetof(Timer, current) == 4);
static_assert(offsetof(Timer, current_fraction) == 8);
static_assert(offsetof(Timer, flags) == 12);

} // namespace th20
