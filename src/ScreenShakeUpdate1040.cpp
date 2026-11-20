// Original 1040B ScreenInf mode-1 shake callback at 0x004249F0.
// The scalar shake coordinates and camera lanes are real Graphics
// ViewportState::points fields; the callback uses ScreenInf's Timer.
#include "NativeScreenEffect.hpp"
#include "NativeScreenShakeChannels.hpp"
#include "Graphics.hpp"
#include "GameRandom.hpp"
#include <cstdint>
namespace th20 {
extern GameRandom native_polygon_random_5ba4c4;
std::int32_t __cdecl screen_update_shake_4249f0(void* task) {
    if (native_screen_stopped_5ba518!=0) return 7;
    static_cast<NativeScreenInf*>(task)->timer_30++;
    if (static_cast<NativeScreenInf*>(task)->timer_30.at_least(
            static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->field_1c))) return 7;

    volatile float fraction=static_cast<NativeScreenInf*>(task)->timer_30.fraction();
    float amplitude=static_cast<float>(
        static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->field_24)-
        static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->field_20))*fraction;
    amplitude/=static_cast<float>(static_cast<std::int32_t>(
        static_cast<NativeScreenInf*>(task)->field_1c));
    amplitude+=static_cast<float>(static_cast<std::int32_t>(
        static_cast<NativeScreenInf*>(task)->field_20));

    switch (native_polygon_random_5ba4c4.bounded(3)) {
    case 0:
    default:
        process_graphics.viewports[3].points[0].x=0.0f;
        process_graphics.viewports[1].points[static_cast<NativeScreenInf*>(task)->view_40].x=0.0f;
        process_graphics.viewports[0].points[static_cast<NativeScreenInf*>(task)->view_40].x=0.0f;
        process_graphics.viewports[5].points[static_cast<NativeScreenInf*>(task)->view_40].x=0.0f;
        break;
    case 1: {
        process_graphics.viewports[3].points[0].x=amplitude;
        const float scaled=amplitude*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[static_cast<NativeScreenInf*>(task)->view_40].x=scaled;
        process_graphics.viewports[0].points[static_cast<NativeScreenInf*>(task)->view_40].x=scaled;
        process_graphics.viewports[5].points[static_cast<NativeScreenInf*>(task)->view_40].x=scaled;
        break;
    }
    case 2: {
        process_graphics.viewports[3].points[0].x=-amplitude;
        const float scaled=(-amplitude)*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[static_cast<NativeScreenInf*>(task)->view_40].x=scaled;
        process_graphics.viewports[0].points[static_cast<NativeScreenInf*>(task)->view_40].x=scaled;
        process_graphics.viewports[5].points[static_cast<NativeScreenInf*>(task)->view_40].x=scaled;
        break;
    }
    }

    switch (native_polygon_random_5ba4c4.bounded(3)) {
    case 0:
    default:
        process_graphics.viewports[1].points[static_cast<NativeScreenInf*>(task)->view_40].y=0.0f;
        process_graphics.viewports[3].points[2].y=0.0f;
        process_graphics.viewports[0].points[static_cast<NativeScreenInf*>(task)->view_40].y=0.0f;
        process_graphics.viewports[5].points[static_cast<NativeScreenInf*>(task)->view_40].y=0.0f;
        break;
    case 1: {
        process_graphics.viewports[3].points[0].y=amplitude;
        const float scaled=amplitude*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[static_cast<NativeScreenInf*>(task)->view_40].y=scaled;
        process_graphics.viewports[0].points[static_cast<NativeScreenInf*>(task)->view_40].y=scaled;
        process_graphics.viewports[5].points[static_cast<NativeScreenInf*>(task)->view_40].y=scaled;
        break;
    }
    case 2: {
        process_graphics.viewports[3].points[0].y=-amplitude;
        const float scaled=(-amplitude)*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[static_cast<NativeScreenInf*>(task)->view_40].y=scaled;
        process_graphics.viewports[0].points[static_cast<NativeScreenInf*>(task)->view_40].y=scaled;
        process_graphics.viewports[5].points[static_cast<NativeScreenInf*>(task)->view_40].y=scaled;
        break;
    }
    }
    return 1;
}
}
