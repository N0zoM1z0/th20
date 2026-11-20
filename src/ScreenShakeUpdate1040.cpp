// Original 1040B ScreenInf mode-1 shake callback at 0x004249F0.
// The scalar shake coordinates and all three camera lanes are real
// Graphics::ViewportState::points fields, not independent global buffers.
#include "NativeScreenEffect.hpp"
#include "NativeScreenShakeChannels.hpp"
#include "Graphics.hpp"
#include "GameRandom.hpp"
namespace th20 {
extern GameRandom native_polygon_random_5ba4c4;
std::int32_t __cdecl screen_update_shake_4249f0(void* task) {
    if (native_screen_stopped_5ba518!=0) return 7;
    reinterpret_cast<NativeScreenInf*>(task)->timer_30++;
    if (reinterpret_cast<NativeScreenInf*>(task)->timer_30.at_least(
            static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_1c))) return 7;

    const float amplitude=(reinterpret_cast<NativeScreenInf*>(task)->timer_30.fraction()*
        static_cast<float>(static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_24)-
                           static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_20))) /
        static_cast<float>(static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_1c))+
        static_cast<float>(static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_20));

    const std::int32_t x_mode=static_cast<std::int32_t>(native_polygon_random_5ba4c4.bounded(3));
    if (x_mode==1) {
        process_graphics.viewports[3].points[0].x=amplitude;
        const float scaled=amplitude*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[0].x=scaled;
        process_graphics.viewports[0].points[0].x=scaled;
        process_graphics.viewports[5].points[0].x=scaled;
    } else if (x_mode==2) {
        process_graphics.viewports[3].points[0].x=-amplitude;
        const float scaled=(-amplitude)*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[0].x=scaled;
        process_graphics.viewports[0].points[0].x=scaled;
        process_graphics.viewports[5].points[0].x=scaled;
    } else {
        process_graphics.viewports[3].points[0].x=0.0f;
        process_graphics.viewports[1].points[0].x=0.0f;
        process_graphics.viewports[0].points[0].x=0.0f;
        process_graphics.viewports[5].points[0].x=0.0f;
    }

    const std::int32_t y_mode=static_cast<std::int32_t>(native_polygon_random_5ba4c4.bounded(3));
    if (y_mode==1) {
        process_graphics.viewports[3].points[0].y=amplitude;
        const float scaled=amplitude*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[0].y=scaled;
        process_graphics.viewports[0].points[0].y=scaled;
        process_graphics.viewports[5].points[0].y=scaled;
        return 1;
    }
    if (y_mode==2) {
        process_graphics.viewports[3].points[0].y=-amplitude;
        const float scaled=(-amplitude)*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[0].y=scaled;
        process_graphics.viewports[0].points[0].y=scaled;
        process_graphics.viewports[5].points[0].y=scaled;
        return 1;
    }
    process_graphics.viewports[3].points[2].y=0.0f;
    process_graphics.viewports[1].points[0].y=0.0f;
    process_graphics.viewports[0].points[0].y=0.0f;
    process_graphics.viewports[5].points[0].y=0.0f;
    return 1;
}
}
