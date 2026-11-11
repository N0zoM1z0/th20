#pragma once
#include <cstdint>
namespace th20 {
// These views borrow actual game process receivers without adding storage or
// synthesizing owner layouts. The global 0x005B6758 also owns the real
// WindowState; 0x005C60FC is the Card/play record archive owner.
struct NativeCardClockView { void process_clock_4872d0(); };
struct NativeCardWindowTimeView { double current_seconds_41cb10(); };
extern NativeCardWindowTimeView native_card_window_time_5b6758;
extern const double native_card_tick_seconds_56fe60;
extern const double native_card_double_two_56fe68;
extern const double native_card_double_hundred_56fe70;
struct NativeCardTimeSaveArchiveView {
    std::uint8_t* primary_record_488740(std::int32_t index);
    std::uint8_t* alternate_record_488770(std::int32_t index);
};
extern NativeCardTimeSaveArchiveView* native_card_play_5c60fc;
void __cdecl card_clock_update_487560();
}
