#include "ClockScalar.hpp"

namespace th20 {

ClockScalar default_timer_clock{1.0f};
ClockScalar* timer_clock_sources[1]{&default_timer_clock};

ClockScalar::operator float() const {
    return value;
}

float ClockScalar::operator*(float delta) const {
    return value * delta;
}

} // namespace th20
