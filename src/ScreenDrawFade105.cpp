// Original 105B ScreenInf fade draw callback at 0x00424F30.
#include "NativeScreenEffect.hpp"
#include <cstdint>
namespace th20 {
extern std::int32_t native_screen_draw_extent_x_5b87f8;
extern std::int32_t native_screen_draw_extent_y_5b87fc;
extern void __cdecl screen_draw_rect_423650(const float* rectangle,std::uint32_t color);
std::int32_t __cdecl screen_draw_fade_424f30(void* task) {
    float rectangle[4]={0.0f,0.0f,static_cast<float>(native_screen_draw_extent_x_5b87f8),
        static_cast<float>(native_screen_draw_extent_y_5b87fc)};
    screen_draw_rect_423650(rectangle,
        (static_cast<NativeScreenInf*>(task)->alpha_18<<24)|
        static_cast<NativeScreenInf*>(task)->field_20);
    return 1;
}
}
