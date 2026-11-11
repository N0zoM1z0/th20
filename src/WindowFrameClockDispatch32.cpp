// Original 32B Window/frame dispatch leaf at 0x004193C0.
// Calls the real process frame update when present, then the Card clock.
#include "NativeCardClockViews.hpp"
namespace th20 {
struct NativeFrameDeviceClockView { void frame_seconds_4abd50(); };
extern NativeFrameDeviceClockView* native_frame_device_5c4a00;
void __cdecl window_frame_clock_dispatch_4193c0() {
    if (native_frame_device_5c4a00)
        native_frame_device_5c4a00->frame_seconds_4abd50();
    card_clock_update_487560();
}
}
