// Original 172B ScreenInf hold draw callback at 0x00424E80.
#include "NativeScreenEffect.hpp"
#include <cstdint>
namespace th20 {
extern const float native_screen_rect_width_640_56cdac;
extern const float native_screen_rect_inner_width_384_56cda4;
extern const float native_screen_half_2_56c8d0;
extern const float native_screen_top_16_56cd90;
extern const float native_screen_height_448_56d7c0;
extern void __cdecl screen_draw_rect_423650(const float* rectangle,std::uint32_t color);
std::int32_t __cdecl screen_draw_hold_424e80(void* task) {
    struct ScreenHoldDrawLocals {
        std::uint32_t view_slot;
        float left;
        float top;
        float right;
        float bottom;
    } locals;
    locals.view_slot=static_cast<NativeScreenInf*>(task)->view_40;
    locals.left=(native_screen_rect_width_640_56cdac-
                 native_screen_rect_inner_width_384_56cda4)/native_screen_half_2_56c8d0;
    locals.top=native_screen_top_16_56cd90;
    locals.right=(native_screen_rect_width_640_56cdac-
                  native_screen_rect_inner_width_384_56cda4)/native_screen_half_2_56c8d0+
                  native_screen_rect_inner_width_384_56cda4;
    locals.bottom=native_screen_top_16_56cd90+native_screen_height_448_56d7c0;
    screen_draw_rect_423650(&locals.left,
        (static_cast<NativeScreenInf*>(task)->alpha_18<<24)|
        static_cast<NativeScreenInf*>(task)->field_20);
    return 1;
}
}
