// Original 0x004199A0 entire 164B Window Present/Reset Boss.
// Genuine scoped IDirect3DDevice9::Present and separately acquired
// Reset device lifetime naturally reproduce native MSVC compiler NOP.
// Borrowed original Graphics/Renderer process globals, not new objects.
#include "NativeWindowFrameScheduleView.hpp"
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
void __cdecl window_frame_initialize_41a2c0();
void __cdecl window_frame_clock_dispatch_4193c0();
void NativeWindowFrameScheduleView::present_no_wait_4199a0() {
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
    window_frame_clock_dispatch_4193c0();
}
}
