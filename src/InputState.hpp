#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
struct IDirectInputDevice8W;
namespace th20 {

// REF-006: retained words are live input history copied by the frame owner.
// Construction, polling and the enclosing controller are not reconstructed.
struct InputButtonState {
    std::uint32_t current, previous, repeat8, repeat12, pressed, released;
    std::array<std::uint32_t, 32> repeat8_count, repeat12_count;
    std::array<std::uint32_t, 32> retained_118, held_frames, retained_218;
    std::array<std::uint32_t, 6> retained_298;
    std::uint32_t held8, retained_2b4, last_input_kind, suppress_previous;
    void update();
    std::uint32_t current_bits(std::uint32_t mask) const;
    // Physical button index must be in 0..31; the receiver must be valid.
    std::uint32_t held_frame_count(std::uint32_t index) const;
    std::uint32_t pressed_bits(std::uint32_t mask) const;
    int repeated_or_pressed(std::uint32_t mask) const;
};
static_assert(sizeof(InputButtonState) == 0x2c0);
static_assert(offsetof(InputButtonState, held_frames) == 0x198);
static_assert(offsetof(InputButtonState, held8) == 0x2b0);

struct InputDevice {
    std::int32_t kind, logical_index;
    IDirectInputDevice8W* direct_input;
    std::int32_t xinput_index;
    InputButtonState buttons;
    std::array<std::uint8_t, 256> raw;
    std::uint32_t retained_3d0;
    void reset_header();
    void initialize_keyboard(std::int32_t index);
    void initialize_xinput(std::int32_t physical, std::int32_t logical);
};
static_assert(sizeof(void*) != 4 || sizeof(InputDevice) == 0x3d4);
static_assert(sizeof(void*) != 4 || offsetof(InputDevice, buttons) == 0x10);
static_assert(sizeof(void*) != 4 || offsetof(InputDevice, raw) == 0x2d0);

// A negative binding is disabled. Nonnegative bindings require readable storage.
// The return re-reads the byte after the OR, including when raw aliases output.
std::uint32_t map_input_byte(std::uint32_t* output, std::int16_t index,
                           std::uint32_t bit, const std::uint8_t* raw);
} // namespace th20
