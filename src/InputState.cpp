#include "InputState.hpp"
namespace th20 {
std::uint32_t InputButtonState::current_bits(std::uint32_t mask) const {
    return current & mask;
}

std::uint32_t InputButtonState::held_frame_count(std::uint32_t index) const {
    return current_bits(1u << index) ? held_frames[index] : 0;
}

void InputDevice::reset_header() {
    kind = 0;
    logical_index = 0;
    direct_input = nullptr;
    xinput_index = 0;
}
void InputDevice::initialize_keyboard(std::int32_t index) {
    kind = 0;
    logical_index = index;
}
void InputDevice::initialize_xinput(std::int32_t physical, std::int32_t logical) {
    kind = 2;
    xinput_index = physical;
    logical_index = logical;
}
std::uint32_t map_input_byte(std::uint32_t* output, std::int16_t index,
                           std::uint32_t bit, const std::uint8_t* raw) {
    if (index < 0) return 0;
    *output |= (raw[index] & 0x80) ? bit : 0;
    return (raw[index] & 0x80) ? bit : 0;
}
void InputButtonState::update() {
    std::uint32_t bit = 1;
    std::uint32_t remaining = current;
    repeat8 = 0;
    repeat12 = 0;
    held8 = 0;
    for (unsigned i = 0; i < 32; ++i, remaining >>= 1, bit <<= 1) {
        if (remaining & 1) {
            ++repeat8_count[i];
            ++repeat12_count[i];
            ++held_frames[i];
            if (repeat8_count[i] >= 8) held8 |= bit;
            if (repeat8_count[i] >= 26) {
                repeat8 |= bit;
                repeat8_count[i] -= 8;
            }
            if (repeat12_count[i] >= 26) {
                repeat12 |= bit;
                repeat12_count[i] -= 12;
            }
        } else {
            repeat8_count[i] = 0;
            repeat12_count[i] = 0;
            held_frames[i] = 0;
        }
    }
    pressed = (current ^ previous) & current;
    released = (current ^ previous) & ~current;
}
std::uint32_t InputButtonState::pressed_bits(std::uint32_t mask) const {
    return pressed & mask;
}
void InputButtonState::reset_replay() {
    retained_118.fill(0);
    retained_218.fill(0);
    field_298 = 0;
    replay_current = 0;
    replay_previous = 0;
    replay_repeat = 0;
    replay_pressed = 0;
    replay_released = 0;
    retained_2b4 = 0;
}
void InputButtonState::update_replay() {
    std::uint32_t bit = 1;
    std::uint32_t remaining = replay_current;
    replay_repeat = 0;
    retained_2b4 = 0;
    for (unsigned i = 0; i < 32; ++i, remaining >>= 1, bit <<= 1) {
        if (remaining & 1) {
            ++retained_118[i];
            ++retained_218[i];
            if (retained_118[i] >= 8) retained_2b4 |= bit;
            if (retained_118[i] >= 26) {
                replay_repeat |= bit;
                retained_118[i] -= 8;
            }
        } else {
            retained_118[i] = 0;
            retained_218[i] = 0;
        }
    }
    replay_pressed = (replay_current ^ replay_previous) & replay_current;
    replay_released = (replay_current ^ replay_previous) & ~replay_current;
}

int InputButtonState::repeated_or_pressed(std::uint32_t mask) const {
    return (pressed_bits(mask) != 0 || (repeat8 & mask) != 0) ? 1 : 0;
}
} // namespace th20
