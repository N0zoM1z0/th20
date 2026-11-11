// Complete original 437B device-frame accumulator at 0x004ABD50.
// The actual 32B Window/Frame clock callback calls this member if the
// real process device exists. The original 346B WindowState seconds
// clock provides elapsed time; the 14 original PE data fields include
// the true unsigned DWORD 0/2^32 double correction table.
// All source arithmetic fields are real used frame metrics, not filler.
#include "NativeCardClockViews.hpp"
#include "NativeWindowFrameClockView.hpp"
#include "GameController.hpp"
#include <cstdint>
#include <cstddef>
namespace th20 {
struct NativeFrameMetrics {
    double last_timestamp;
    std::uint32_t slow_frame_count;
    std::uint32_t sample_count;
    double presented_accumulator;
    double realtime_accumulator;
    float estimated_fps;
};
static_assert(offsetof(NativeFrameMetrics, estimated_fps)==0x20);
extern GameController* current_game_controller;
extern const double native_frame_min_window_56c468;
extern const double native_frame_count_step_56c470;
extern const float native_frame_maximum_fps_570618;
extern const float native_frame_minimum_fps_570614;
extern std::uint8_t native_frame_skip_count_5c4f84;

std::int32_t NativeFrameDeviceClockView::frame_seconds_4abd50() {
    const double time=native_card_window_time_5b6758.current_seconds_41cb10();
    if (time < reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->last_timestamp) reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->last_timestamp=time;
    if (time-reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->last_timestamp >= native_frame_min_window_56c468) {
        const double delta=time-reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->last_timestamp;
        reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->last_timestamp+=delta;
        const std::int32_t sample=static_cast<std::int32_t>(reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->sample_count);
        static const double correction_table[2]={0.0,4294967296.0};
        reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->estimated_fps=static_cast<float>(
            (static_cast<double>(sample)+correction_table[static_cast<std::uint32_t>(sample)>>31])/delta);
        if (reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->estimated_fps > native_frame_maximum_fps_570618)
            ++reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->slow_frame_count;
        else reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->slow_frame_count=0;
        if (current_game_controller &&
            ((current_game_controller->game_flags.bits>>4)&1u)==0 &&
            ((current_game_controller->game_flags.bits>>2)&1u)==0) {
            reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->realtime_accumulator+=native_frame_count_step_56c470;
            if (reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->estimated_fps > native_frame_minimum_fps_570614)
                reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->presented_accumulator+=native_frame_count_step_56c470;
            else reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->presented_accumulator+=static_cast<double>(reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->estimated_fps);
        }
        if (current_game_controller) current_game_controller->game_flags.bits&=~0x100u;
        reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->sample_count=0;
    }
    reinterpret_cast<NativeFrameMetrics*>(reinterpret_cast<std::uint8_t*>(this)+0x18)->sample_count+=static_cast<std::uint32_t>(native_frame_skip_count_5c4f84)+1u;
    this->frame_pipeline_4ac0e0();
    return 1;
}
}
