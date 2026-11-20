// Original 128B ScreenInf solid draw callback at 0x00424E00.
#include "NativeScreenEffect.hpp"
#include "NativeGraphicsModeAction.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Graphics.hpp"
#include <cstdint>
namespace th20 {
extern std::int32_t native_screen_draw_extent_x_5b87f8;
extern std::int32_t native_screen_draw_extent_y_5b87fc;
extern void __cdecl screen_draw_rect_423650(const float* rectangle,std::uint32_t color);
std::int32_t __cdecl screen_draw_solid_424e00(void* task) {
    float rectangle[4]={0.0f,0.0f,static_cast<float>(native_screen_draw_extent_x_5b87f8),
        static_cast<float>(native_screen_draw_extent_y_5b87fc)};
    current_animation_pool->flush_draws();
    reinterpret_cast<NativeGraphicsModeAction*>(&process_graphics)->set_clip_41dce0(2);
    screen_draw_rect_423650(rectangle,
        (static_cast<NativeScreenInf*>(task)->alpha_18<<24)|
        static_cast<NativeScreenInf*>(task)->field_20);
    return 1;
}
}
