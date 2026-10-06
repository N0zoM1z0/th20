#include "Timer.hpp"
#include "ClockScalar.hpp"

namespace th20 {

Timer::Timer() : previous(0), current(0), current_fraction(0.0f), flags(0) {}

Timer::operator std::int32_t() const {
    return current;
}

std::int32_t Timer::operator%(std::int32_t divisor) const {
    return current % divisor;
}

void Timer::operator+=(std::int32_t amount) {
    add(static_cast<float>(amount));
}

void Timer::operator-=(std::int32_t amount) {
    *this += static_cast<std::int32_t>(-static_cast<std::uint32_t>(amount));
}

void Timer::operator++(int) {
    tick();
}

void Timer::operator--(int) {
    *this -= 1;
}

bool Timer::at_least(std::int32_t value) const {
    return current >= value;
}

bool Timer::equals(std::int32_t value) const {
    return current == value;
}

bool Timer::less_than(std::int32_t value) const {
    return current < value;
}

void Timer::reset() {
    current = 0;
    previous = -999999;
    current_fraction = 0.0f;
}

void Timer::set_mode(std::uint32_t mode) {
    flag_bits.mode = mode;
}

void Timer::set(std::int32_t value) {
    if (!(flags & 1u)) {
        reset();
        set_mode(0);
        flags |= 1u;
    }
    current = value;
    current_fraction = static_cast<float>(value);
    // C++20 integer conversion defines the target's modulo-2^32 subtraction.
    previous = static_cast<std::int32_t>(static_cast<std::uint32_t>(value) - 1u);
}

void Timer::add(float delta) {
    if (!(flags & 1u)) {
        reset();
        set_mode(0);
        flags |= 1u;
    }
    if (((flags >> 1) & 3u) >= 1u) {
        flags &= ~6u;
    }
    ClockScalar* clock = timer_clock_sources[(flags >> 1) & 3u];
    previous = current;
    if (clock) {
        if (*clock > 0.99f && *clock < 1.01f) {
            current_fraction += delta;
        } else {
            current_fraction += *clock * delta;
        }
    } else {
        current_fraction += delta;
    }
    current = static_cast<std::int32_t>(current_fraction);
}

std::int32_t Timer::tick() {
    if (!(flags & 1u)) {
        reset();
        set_mode(0);
        flags |= 1u;
    }
    if (((flags >> 1) & 3u) >= 1u) {
        flags &= ~6u;
    }
    ClockScalar* clock = timer_clock_sources[(flags >> 1) & 3u];
    previous = current;
    if (clock) {
        if (*clock > 0.99f && *clock < 1.01f) {
            current = static_cast<std::int32_t>(static_cast<std::uint32_t>(current) + 1u);
            current_fraction += 1.0f;
        } else {
            current_fraction += *clock;
            current = static_cast<std::int32_t>(current_fraction);
        }
    } else {
        current = static_cast<std::int32_t>(static_cast<std::uint32_t>(current) + 1u);
        current_fraction += 1.0f;
    }
    return current;
}

} // namespace th20
