#include "WindowState.hpp"

namespace th20 {

WindowFlags::Bits::Bits() = default;

std::int32_t WindowState::display_mode() const {
    return display_mode_value;
}

std::uint32_t WindowState::needs_device_reset() const {
    return flags.bits.device_reset;
}

void WindowState::set_draw_counter(std::int8_t value) {
    draw_counter = value;
}

void WindowState::set_device_reset(std::uint32_t value) {
    flags.bits.device_reset = value;
}

void WindowState::set_reset_delay(std::uint32_t value) {
    reset_delay = value;
}

void WindowState::RepeatCounter::reset(std::int32_t value) {
    first = value;
    second = value;
    elapsed = 0;
}

} // namespace th20
