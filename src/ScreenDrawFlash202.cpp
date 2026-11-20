// Original 202B ScreenInf flash draw callback at 0x00424FA0.
#include "NativeScreenEffect.hpp"
#include "NativeWindowStateDrawView.hpp"
#include "WindowState.hpp"
#include <cstdint>
namespace th20 {
extern void __cdecl screen_draw_rect_423650(const float* rectangle,std::uint32_t color);
std::int32_t __cdecl screen_draw_flash_424fa0(void* task) {
    float rectangle[4]={
        static_cast<float>(reinterpret_cast<NativeWindowStateDrawView*>(&window_state)->offset_x_41cad0()),
        static_cast<float>(reinterpret_cast<NativeWindowStateDrawView*>(&window_state)->playfield_height_41caf0()),
        static_cast<float>(reinterpret_cast<NativeWindowStateDrawView*>(&window_state)->offset_x_41cad0())+
            static_cast<float>(reinterpret_cast<NativeWindowStateDrawView*>(&window_state)->playfield_width_424010()),
        static_cast<float>(reinterpret_cast<NativeWindowStateDrawView*>(&window_state)->playfield_height_41caf0())+
            static_cast<float>(reinterpret_cast<NativeWindowStateDrawView*>(&window_state)->offset_y_421810())
    };
    screen_draw_rect_423650(rectangle,
        (static_cast<NativeScreenInf*>(task)->alpha_18<<24)|
        (static_cast<NativeScreenInf*>(task)->field_24&0x00ffffffu));
    return 1;
}
}
