#include "WindowState.hpp"

namespace th20 {

WindowFlags::Bits::Bits() = default;

// The original native window/instance HWND/HINSTANCE getters fold to
// already exact physically shared tiny game getters at 0x0040C300
// and 0x0041CAB0; do not count their bytes again.
HWND__* WindowState::window_handle() const { return window; }
HINSTANCE__* WindowState::instance_handle() const { return instance; }

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
