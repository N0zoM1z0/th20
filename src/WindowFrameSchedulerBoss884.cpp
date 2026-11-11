// Original game WindowState 884B frame scheduler (0x004193E0).
// Complete gameplay/control-flow source, still NONEXACT.
// Real D3D9 GetRasterStatus(UINT,D3DRASTER_STATUS*) at vtable +0x4C
// supplies the original two-DWORD InVBlank/ScanLine output (not fake
// result locals). Native Present and Reset at +0x44/+0x40 use
// separately acquired D3D9 device pointers. The actual clock,
// RepeatCounter, Renderer, WinMM imports and Graphics owner are borrowed.
// The typed 866B candidate has all 32/32 native E8 target roles and
// 21/21 native data destination roles; parent bytes remain uncredited.
#include "NativeWindowFrameScheduleView.hpp"
#include "NativeCardClockViews.hpp"
#include "NativeGlyphCanvasView.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <cstdint>
namespace th20 {
struct NativeFrameGraphicsView {
    IDirect3DDevice9* device_412730();
    void frame_recover_4dd840();
    void frame_complete_4dbd70();
};
extern NativeFrameGraphicsView native_frame_graphics_5c4d40;
struct NativeFrameAnimationPoolView {
    void frame_lost_41dbe0();
    void frame_restored_41d9f0();
};
extern NativeFrameAnimationPoolView* native_frame_renderer_5c0028;
extern D3DPRESENT_PARAMETERS native_frame_present_5c4e24;
extern std::int32_t native_frame_status_5c586c;
extern const double native_scheduler_one_56c468;
extern const double native_scheduler_sixty_56c470;
extern const double native_scheduler_thousand_56cd88;
extern const double native_scheduler_bias_56cd78;
extern const double native_scheduler_refresh_56cd60;
extern const double native_scheduler_poll_56cd58;
void __cdecl window_frame_clock_dispatch_4193c0();
void __cdecl window_frame_initialize_41a2c0();

#define WINDOW() (*reinterpret_cast<WindowState*>(this))
#define NOW() (reinterpret_cast<NativeCardWindowTimeView*>(this)->current_seconds_41cb10())
#define GFX() native_frame_graphics_5c4d40
#define REPEAT() (*active_repeat_41ca50())
void NativeWindowFrameScheduleView::schedule_frame_4193e0() {
    WINDOW().current_time=NOW();
    WINDOW().sleep_budget=static_cast<std::int32_t>(
        ((native_scheduler_one_56c468/native_scheduler_sixty_56c470+
          WINDOW().previous_draw_time-WINDOW().current_time)*native_scheduler_thousand_56cd88)-
        native_scheduler_bias_56cd78);

    if (REPEAT().second >= WINDOW().sleep_budget) {
        if (WINDOW().sleep_budget >= 0)
            REPEAT().second=WINDOW().sleep_budget;
        else REPEAT().second=0;
        REPEAT().elapsed=0;
    } else {
        ++REPEAT().elapsed;
        if (REPEAT().elapsed >= 15) {
            if (REPEAT().second < REPEAT().first)
                ++REPEAT().second;
            REPEAT().elapsed=0;
        }
    }
    if (WINDOW().sleep_budget < 0) WINDOW().sleep_budget=0;

    // The original local is the native D3DRASTER_STATUS pair:
    // raster.InVBlank at [ebp-0xC] and raster.ScanLine at [ebp-0x8].
    D3DRASTER_STATUS raster{};
    raster.ScanLine=0;
    const double now=NOW();
    if (now < WINDOW().current_draw_time)
        WINDOW().current_draw_time=now;
    if (now-WINDOW().current_draw_time < native_scheduler_refresh_56cd60) {
        if (reinterpret_cast<NativeGlyphCanvasView*>(&GFX())->canvas_width_415800()==0) {
            while (NOW()-WINDOW().current_draw_time < native_scheduler_poll_56cd58)
                Sleep(1);
            raster.InVBlank=FALSE;
            while (1) {
                IDirect3DDevice9* device=GFX().device_412730();
                if (device->GetRasterStatus(0,&raster)!=D3D_OK) break;
                if (raster.InVBlank!=FALSE) break;
            }
        }
    } else {
        if (REPEAT().second>0) --REPEAT().second;
    }

    WINDOW().current_draw_time=NOW();
    update_scene_419760();
    {
        IDirect3DDevice9* device=GFX().device_412730();
        if (device->Present(nullptr,nullptr,nullptr,nullptr)<0) {
            GFX().frame_recover_4dd840();
            native_frame_renderer_5c0028->frame_lost_41dbe0();
            IDirect3DDevice9* reset_device=GFX().device_412730();
            if (reset_device->Reset(&native_frame_present_5c4e24)==D3D_OK) {
                native_frame_renderer_5c0028->frame_restored_41d9f0();
                GFX().frame_complete_4dbd70();
                window_frame_initialize_41a2c0();
                native_frame_status_5c586c=2;
            }
        }
    }
    window_frame_clock_dispatch_4193c0();
    NOW();
    if (REPEAT().second>0) {
        timeBeginPeriod(1);
        Sleep(REPEAT().second);
        timeEndPeriod(1);
    }
    WINDOW().previous_draw_time=NOW();
}
#undef WINDOW
#undef NOW
#undef GFX
#undef REPEAT
}
