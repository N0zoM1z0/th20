#pragma once
#include "WindowState.hpp"
namespace th20 {
// Narrow borrowed WindowState view: no storage, vtable or synthetic wrapper.
// The original +0x2100 index selects one of four 12-byte RepeatCounters
// beginning at WindowState +0x2104.
struct NativeWindowFrameScheduleView {
    WindowState::RepeatCounter* active_repeat_41ca50();
    void schedule_frame_4193e0();
};
}
