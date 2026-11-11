// Original 433B/110-i386 Window frame controller Boss 0x00419C20.
// Real WindowState frame interval, FunctionChain callbacks, D3D9 scene
// transition, 15 E8, 18 genuine data relocations and 301 ordinary bytes.
// The nested frame-end scope naturally generates native original NOP.
#include "NativeWindowFrameScheduleView.hpp"
#include "NativeCardClockViews.hpp"
#include "Graphics.hpp"
#include "FunctionChainController.hpp"
#include "AnimationRuntimeOwner.hpp"
#include <d3d9.h>
#include <cstdint>
namespace th20 {
struct NativeAnimationPoolStagingView:AnimationPoolOwner {
    void reset_staging_buffers_445a40();
};
struct NativeTickGraphicsView {
    void setup_view_41dce0(int view);
    void bail_out_4d9e30();
};
extern std::uint32_t native_window_options_5b87e8;
extern const double native_sched_one_56c468;
extern const double native_sched_sixty_56c470;
extern std::uint8_t native_frame_skip_5c4f84;
extern std::uint32_t native_render_alpha_5c5af8;
extern double native_frame_elapsed_5c5b18;
std::int32_t __fastcall graphics_disable_fog(Graphics* graphics);
#define WIN() (*reinterpret_cast<WindowState*>(this))
#define VIEW() (*reinterpret_cast<NativeTickGraphicsView*>(&process_graphics))
#define NOW() (reinterpret_cast<NativeCardWindowTimeView*>(this)->current_seconds_41cb10())
std::int32_t NativeWindowFrameScheduleView::frame_controller_step_419c20() {
    if ((native_window_options_5b87e8 >> 2) & 1) {
        while (WIN().current_time > WIN().next_update_time) {
            WIN().next_update_time = native_sched_one_56c468/native_sched_sixty_56c470+WIN().next_update_time;
        }
    }
    current_animation_pool->flush_draws();
    VIEW().setup_view_41dce0(2);
    int status=process_chain->update();
    if (status==0) {
        VIEW().bail_out_4d9e30();
        return 1;
    } else {
        if (status==-1) {
            VIEW().bail_out_4d9e30();
            return 2;
        }
    }
    ++WIN().draw_counter;
    if (static_cast<int>(native_frame_skip_5c4f84)+1 <= WIN().draw_counter) {
        process_graphics.get_device()->BeginScene();
        reinterpret_cast<NativeAnimationPoolStagingView*>(current_animation_pool)->reset_staging_buffers_445a40();
        native_render_alpha_5c5af8=0xff;
        graphics_disable_fog(&process_graphics);
        process_chain->draw();
        current_animation_pool->flush_draws();
        process_graphics.get_device()->SetTexture(0,nullptr);
        process_graphics.get_device()->EndScene();
        WIN().draw_counter=0;
        schedule_frame_4193e0();
    }
    native_frame_elapsed_5c5b18=NOW()-WIN().current_time;
    {
        frame_leave_412540();
    }
    return 0;
}
#undef WIN
#undef VIEW
#undef NOW
}
