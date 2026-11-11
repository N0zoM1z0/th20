// Whole original 385B Window paced D3D9 Present/Reset Boss, native
// 0x00419A50. Uses true WindowState clock fields, actual 1/60 timing,
// Win32 Sleep, screenshot scene and genuine Direct3D9 COM methods.
// Original 0x00419A50 Window per-frame D3D9 present with pacing branch.
#include "NativeWindowFrameScheduleView.hpp"
#include "NativeCardClockViews.hpp"
#include <windows.h>
#include <cstdint>
#include <d3d9.h>
namespace th20 {
struct NativeWindowPresentGraphics {
    IDirect3DDevice9* device_412730();
    void frame_recover_4dd840();
    void frame_complete_4dbd70();
};
extern NativeWindowPresentGraphics native_window_present_graphics_5c4d40;
struct NativeWindowPresentRenderer {
    void frame_lost_41dbe0();
    void frame_restored_41d9f0();
};
extern NativeWindowPresentRenderer* native_window_present_renderer_5c0028;
extern D3DPRESENT_PARAMETERS native_window_d3d_parameters_5c4e24;
extern std::int32_t native_window_present_status_5c586c;
extern std::uint8_t native_window_frame_pacing_enabled_5c4f89;
extern const double native_scheduler_one_56c468;
extern const double native_scheduler_sixty_56c470;
extern const double native_scheduler_thousand_56cd88;
extern const double native_window_pacing_minimum_56cd50;
extern const double native_window_pacing_bias_56cd80;
void __cdecl window_frame_initialize_41a2c0();
void __cdecl window_frame_clock_dispatch_4193c0();
#define WIN() (*reinterpret_cast<WindowState*>(this))
#define NOW() (reinterpret_cast<NativeCardWindowTimeView*>(this)->current_seconds_41cb10())
void NativeWindowFrameScheduleView::present_paced_419a50() {
    WIN().current_time=NOW();
    if (native_window_frame_pacing_enabled_5c4f89==1
        && WIN().current_time-WIN().previous_draw_time <
            native_scheduler_one_56c468/native_scheduler_sixty_56c470
        && WIN().current_time-WIN().previous_draw_time > native_window_pacing_minimum_56cd50) {
        std::int32_t wait_milliseconds=static_cast<std::int32_t>(
            (native_scheduler_one_56c468/native_scheduler_sixty_56c470+
                WIN().previous_draw_time-WIN().current_time)*
                native_scheduler_thousand_56cd88-native_window_pacing_bias_56cd80);
        if (wait_milliseconds>0) Sleep(wait_milliseconds);
    }
    WIN().current_draw_time=NOW();
    update_scene_419760();
    {
        IDirect3DDevice9* device=native_window_present_graphics_5c4d40.device_412730();
        if (device->Present(nullptr,nullptr,nullptr,nullptr)<0) {
            native_window_present_graphics_5c4d40.frame_recover_4dd840();
            native_window_present_renderer_5c0028->frame_lost_41dbe0();
            IDirect3DDevice9* reset_device=native_window_present_graphics_5c4d40.device_412730();
            reset_device->Reset(&native_window_d3d_parameters_5c4e24);
            native_window_present_renderer_5c0028->frame_restored_41d9f0();
            native_window_present_graphics_5c4d40.frame_complete_4dbd70();
            window_frame_initialize_41a2c0();
            native_window_present_status_5c586c=2;
        }
    }
    WIN().previous_draw_time=NOW();
    window_frame_clock_dispatch_4193c0();
}
#undef WIN
#undef NOW
}
