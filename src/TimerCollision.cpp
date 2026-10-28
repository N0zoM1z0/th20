#include "Timer.hpp"

namespace th20 {
// The original multiplication consumes signed current at native Timer+4;
// no fractional clock conversion or hidden frame-time scaling is involved.
std::int32_t Timer::operator*(std::int32_t factor) const {
    return current * factor;
}

// Native nonzero protocol is a full thiscall member with a byte-bool result.
bool Timer::operator!=(std::int32_t value) const {
    return current != value;
}
} // namespace th20
