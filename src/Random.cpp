#include "Random.hpp"

namespace th20 {

std::uint32_t random_step(std::uint32_t state) {
    std::uint64_t value = static_cast<std::uint64_t>(state) * 48271u;
    value = (value >> 31) + (value & 0x7fffffffu);
    value = value < 0x7fffffffu ? value : value - 0x7fffffffu;
    return static_cast<std::uint32_t>(value);
}

std::uint32_t RandomState::next() {
    state = random_step(state);
    return state;
}

} // namespace th20
