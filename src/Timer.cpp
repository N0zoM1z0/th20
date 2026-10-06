#include "Timer.hpp"

namespace th20 {

void Timer::reset() {
    current = 0;
    previous = -999999;
    current_fraction = 0.0f;
}

void Timer::set_mode(std::uint32_t mode) {
    flags = ((mode & 3u) << 1) | (flags & ~6u);
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

} // namespace th20
