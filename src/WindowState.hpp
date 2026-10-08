#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

struct HWND__;
struct HINSTANCE__;

namespace th20 {

union WindowFlags {
    std::uint32_t word;
    struct Bits {
        std::uint32_t started : 1 = 0;
        std::uint32_t device_reset : 1 = 0;
        std::uint32_t unlimited : 1 = 0;
        std::uint32_t field_3_4 : 2 = 0;
        std::uint32_t bit5 : 1 = 0;
        std::uint32_t bit6 : 1 = 0;
        std::uint32_t bit7 : 1 = 0;
        std::uint32_t retained : 24;
        Bits();
    } bits;
};

// Native global construction and frame/path consumers establish these fields.
// Unnamed fields retain their observed storage; natural alignment supplies the
// actual inter-member gaps. Original construction and global startup stay open.
struct WindowState {
    HWND__* window;
    HWND__* previous_window;
    std::int32_t quit_requested;
    HINSTANCE__* instance;
    std::int32_t nominal_width, nominal_height;
    std::int32_t playfield_width, playfield_height;
    std::int32_t offset_x, offset_y;
    struct Pair { std::int32_t first, second; };
    Pair retained_28, retained_30;
    std::int32_t mesh_offset_x[2], mesh_offset_y[2];
    Pair retained_48, retained_50;
    std::int32_t field_0058, field_005c, field_0060, field_0064;
    std::uint8_t active, cursor_latch;
    std::uint32_t startup_status;
    std::int8_t draw_counter;
    std::uint64_t performance_frequency, performance_origin;
    std::uint8_t field_0088;
    char user_data_directory[0x1000];
    char module_directory[0x1000];
    std::uint8_t saved_screen_saver, saved_low_power, saved_power_off;
    std::int32_t display_mode_value;
    WindowFlags flags;
    std::uint32_t reset_delay;
    double field_2098;
    std::int32_t scaled_width, scaled_height, client_width, client_height;
    std::int32_t display_width, display_height, viewport_width, viewport_height;
    float scale;
    double current_time, previous_time, next_update_time, clock_offset;
    double previous_draw_time, current_draw_time;
    std::int32_t field_20f8, sleep_budget;
    std::uint32_t input_latch;
    struct RepeatCounter {
        std::int32_t first, second, elapsed;
        void reset(std::int32_t value);
    };
    std::array<RepeatCounter, 4> repeat;

    std::int32_t display_mode() const;
    std::int32_t mesh_view_x(std::int32_t index) const;
    std::int32_t mesh_view_y(std::int32_t index) const;
    std::int32_t mesh_width() const;
    std::int32_t mesh_height() const;
    std::uint32_t needs_device_reset() const;
    void set_draw_counter(std::int8_t value);
    void set_device_reset(std::uint32_t value);
    void set_reset_delay(std::uint32_t value);
    void restore_system_settings();
};

static_assert(sizeof(WindowFlags) == 4);
static_assert(sizeof(WindowState::Pair) == 8);
static_assert(sizeof(WindowState::RepeatCounter) == 12);
// Portable tests exercise the same member bodies; only x86 claims this layout.
static_assert(sizeof(void*) != 4 || sizeof(WindowState) == 0x2138);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, draw_counter) == 0x70);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, performance_frequency) == 0x78);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, user_data_directory) == 0x89);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, display_mode_value) == 0x208c);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, flags) == 0x2090);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, field_2098) == 0x2098);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, current_time) == 0x20c8);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, mesh_offset_x) == 0x38);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, mesh_offset_y) == 0x40);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, scaled_width) == 0x20a0);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, scaled_height) == 0x20a4);
static_assert(sizeof(void*) != 4 || offsetof(WindowState, repeat) == 0x2104);

// Storage is deliberately undefined until original startup is reconstructed.
extern WindowState window_state;
void bring_window_to_foreground(HWND__* window);
int is_japanese_user_locale();

} // namespace th20
