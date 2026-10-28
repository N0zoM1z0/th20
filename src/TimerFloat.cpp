#include "Timer.hpp"

namespace th20 {
// Original game clock initialization uses a native float, preserving its
// fractional value and truncating only the whole current/previous fields.
extern const float native_one;

void Timer::set(float value) {
    if (!(flags & 1u)) {
        reset();
        set_mode(0);
        flags |= 1u;
    }
    current = static_cast<std::int32_t>(value);
    current_fraction = value;
    previous = static_cast<std::int32_t>(value - native_one);
}

void Timer::operator=(float value) { set(value); }
} // namespace th20
