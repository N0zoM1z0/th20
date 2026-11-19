#include "Timer.hpp"

namespace th20 {

void Timer::add_unscaled(float delta) {
    previous = current;
    current_fraction += delta;
    current = static_cast<std::int32_t>(current_fraction);
}

} // namespace th20
