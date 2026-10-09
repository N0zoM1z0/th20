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

    Timer() noexcept;
    std::int32_t changed() const;
    std::int32_t every(std::int32_t divisor) const;
    operator std::int32_t() const;
    float fraction() const;
    // Unchecked native clock lookup; the established source slot is mode 0.
    float step() const;
    void operator=(std::int32_t value);
    // The divisor must be nonzero; INT32_MIN / -1 is outside the C++ domain.
    std::int32_t operator%(std::int32_t divisor) const;
    void operator+=(std::int32_t amount);
    void operator-=(std::int32_t amount);
    void operator++(int);
    void operator++();
    void operator--(int);
    void reset();
    void set_mode(std::uint32_t mode);
    void set(std::int32_t value);
    void add(float delta);
    std::int32_t tick();
    bool at_least(std::int32_t value) const;
    bool at_most(std::int32_t value) const;
    bool equals(std::int32_t value) const;
    bool less_than(std::int32_t value) const;
    bool greater_than(std::int32_t value) const;
};

static_assert(sizeof(Timer) == 16);
static_assert(offsetof(Timer, previous) == 0);
static_assert(offsetof(Timer, current) == 4);
static_assert(offsetof(Timer, current_fraction) == 8);
static_assert(offsetof(Timer, flags) == 12);

} // namespace th20
