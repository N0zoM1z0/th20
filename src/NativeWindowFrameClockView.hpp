#pragma once
#include <cstdint>
namespace th20 {
// The native time pair is exactly two 32-bit words. The 113B parent
// copies these fields directly; leaf builders use a distinct 8-byte
// view for the separately emitted copy-constructor/assignment calls.
struct NativeFrameTimePair {std::uint32_t low, high;};
static_assert(sizeof(NativeFrameTimePair)==8);
// Borrowed actual process device frame-clock receiver; no new storage or
// vtable. The frame method returns 1 in the original game; its 32B caller
// ignores that value. A separate 113B frame-pipeline method remains open.
struct NativeFrameDeviceClockView {
    std::int32_t frame_seconds_4abd50();
    NativeFrameTimePair* frame_pipeline_4ac0e0();
};
extern NativeFrameDeviceClockView* native_frame_device_5c4a00;
}
