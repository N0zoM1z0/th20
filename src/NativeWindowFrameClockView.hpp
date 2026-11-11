#pragma once
#include <cstdint>
namespace th20 {
struct NativeFrameTimePair;
// Borrowed actual process device frame-clock receiver; no new storage or
// vtable. The frame method returns 1 in the original game; its 32B caller
// ignores that value. A separate 113B frame-pipeline method remains open.
struct NativeFrameDeviceClockView {
    std::int32_t frame_seconds_4abd50();
    NativeFrameTimePair* frame_pipeline_4ac0e0();
};
extern NativeFrameDeviceClockView* native_frame_device_5c4a00;
}
