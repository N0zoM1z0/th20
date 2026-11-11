// Real game WindowState per-frame scheduler, original 0x004193E0
// 884B / 239 i386 / 32 native E8 / 21 PE HIGHLOW.
// This complete executable C++20 research candidate restores the genuine
// 346B clock, all 14 exact 31B active-repeat getter calls, real Win32 timer,
// Graphics/D3D vtable poll and loss/reset path, and 32 ordered callee roles.
// The entire 884B parent is NONEXACT: do NOT credit any parent game bytes.
// Frame/swapchain owner layouts are deliberately borrowed, never allocated.
#include "NativeWindowFrameScheduleView.hpp"
#include "NativeCardClockViews.hpp"
#include "NativeGlyphCanvasView.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <cstdint>
namespace th20 {
struct NativeFrameDevice {
    void** vtable;
};
struct NativeFrameGraphicsView {
    NativeFrameDevice* device_412730();
    void frame_recover_4dd840();
    void frame_complete_4dbd70();
};
extern NativeFrameGraphicsView native_frame_graphics_5c4d40;
struct NativeFrameAnimationPoolView {
    void frame_lost_41dbe0();
    void frame_restored_41d9f0();
};
extern NativeFrameAnimationPoolView* native_frame_renderer_5c0028;
extern unsigned char native_frame_present_5c4e24;
extern std::int32_t native_frame_status_5c586c;
extern const double native_scheduler_one_56c468;
extern const double native_scheduler_sixty_56c470;
extern const double native_scheduler_thousand_56cd88;
extern const double native_scheduler_bias_56cd78;
extern const double native_scheduler_refresh_56cd60;
extern const double native_scheduler_poll_56cd58;
void __cdecl window_frame_clock_dispatch_4193c0();
void __cdecl window_frame_initialize_41a2c0();

struct NativeFrameGraphicsStateView {
    void update_scene_419760();
};
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

    std::int32_t quit=0;
    std::int32_t received=0;
    const double now=NOW();
    if (now < WINDOW().current_draw_time)
        WINDOW().current_draw_time=now;
    if (now-WINDOW().current_draw_time < native_scheduler_refresh_56cd60) {
        if (reinterpret_cast<NativeGlyphCanvasView*>(&GFX())->canvas_width_415800()==0) {
            while (NOW()-WINDOW().current_draw_time < native_scheduler_poll_56cd58)
                Sleep(1);
            received=0;
            while (1) {
                NativeFrameDevice* device=GFX().device_412730();
                auto fn=reinterpret_cast<long (__stdcall*)(NativeFrameDevice*,std::int32_t,std::int32_t*)>(
                    (*reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(device->vtable)+0x4C)));
                quit=fn(device,0,&received);
                if (quit!=0 || received!=0) break;
            }
        }
    } else {
        if (REPEAT().second>0) --REPEAT().second;
    }

    WINDOW().current_draw_time=NOW();
    reinterpret_cast<NativeFrameGraphicsStateView*>(this)->update_scene_419760();
    {
        NativeFrameDevice* device=GFX().device_412730();
        auto fn=reinterpret_cast<long (__stdcall*)(NativeFrameDevice*,void*,void*,void*,void*)>((*reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(device->vtable)+0x44)));
        if (fn(device,nullptr,nullptr,nullptr,nullptr)<0) {
            GFX().frame_recover_4dd840();
            native_frame_renderer_5c0028->frame_lost_41dbe0();
            device=GFX().device_412730();
            auto reset=reinterpret_cast<long (__stdcall*)(NativeFrameDevice*,void*)>((*reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(device->vtable)+0x40)));
            if (reset(device,&native_frame_present_5c4e24)==0) {
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
