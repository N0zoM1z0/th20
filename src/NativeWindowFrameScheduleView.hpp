#pragma once
#include "WindowState.hpp"
namespace th20 {
// Narrow borrowed WindowState view: no storage, vtable or synthetic wrapper.
// The original +0x2100 index selects one of four 12-byte RepeatCounters
// beginning at WindowState +0x2104.
struct NativeWindowFrameScheduleView {
    WindowState::RepeatCounter* active_repeat_41ca50();
    void schedule_frame_4193e0();
    void update_scene_419760();
    void present_no_wait_4199a0();
    void present_paced_419a50();
    std::int32_t frame_controller_step_419c20();
    std::int32_t frame_controller_no_wait_419de0();
    std::int32_t frame_controller_paced_41a030();
    std::int32_t frame_leave_412540();
};
}
