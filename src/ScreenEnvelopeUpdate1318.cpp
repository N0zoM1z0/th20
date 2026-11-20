// Original 1318B ScreenInf mode-0 envelope callback at 0x004244C0.
// Screen values are written into the actual Graphics viewport point channels.
#include "NativeScreenEffect.hpp"
#include "Graphics.hpp"
#include "GameController.hpp"
#include "GameRandom.hpp"
#include <cstdint>
namespace th20 {
extern std::int32_t native_screen_stopped_5ba518;
extern GameController* current_game_controller;
extern GameRandom native_polygon_random_5ba4c4;
extern float native_texture_scale_5b8818;
extern const float native_camera_min_z_56c8cc;
extern const double native_unsigned_double_bias_56cdd0[2];

std::int32_t __cdecl screen_update_envelope_4244c0(void* task) {
    if (native_screen_stopped_5ba518!=0) return 7;
    if (current_game_controller!=nullptr) {
        if (current_game_controller->update_suppressed()!=0 ||
            current_game_controller->animation_frozen()!=0 ||
            ((current_game_controller->game_flags.bits>>4)&1u)!=0 ||
            ((current_game_controller->game_flags.bits>>5)&1u)!=0 ||
            ((current_game_controller->game_flags.bits>>6)&1u)!=0) return 1;
    } else {
        return 1;
    }

    reinterpret_cast<NativeScreenInf*>(task)->timer_30++;
    float progress;
    if (reinterpret_cast<NativeScreenInf*>(task)->timer_30.less_than(
            static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_20))) {
        progress=reinterpret_cast<NativeScreenInf*>(task)->timer_30.fraction()/
            static_cast<float>(static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_20));
    } else {
        if (static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->timer_30)<
            static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_20)+
            static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_24)) {
            progress=native_camera_min_z_56c8cc;
        } else {
            if (static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->timer_30)<
                static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_20)+
                static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_24)+
                static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_28)) {
                const std::int32_t remaining=static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_20)+
                    static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_24)+
                    static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_28)-
                    static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->timer_30);
                const double remaining_double=static_cast<double>(remaining)+
                    native_unsigned_double_bias_56cdd0[static_cast<std::uint32_t>(remaining)>>31];
                const std::int32_t duration=static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_28);
                progress=static_cast<float>(remaining_double)/static_cast<float>(
                    static_cast<double>(duration)+
                    native_unsigned_double_bias_56cdd0[static_cast<std::uint32_t>(duration)>>31]);
            } else {
                return 7;
            }
        }
    }
    progress=static_cast<float>(static_cast<std::int32_t>(reinterpret_cast<NativeScreenInf*>(task)->field_1c))*progress;

    const std::int32_t x_mode=static_cast<std::int32_t>(native_polygon_random_5ba4c4.bounded(3));
    if (x_mode==0) {
        process_graphics.viewports[3].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=0.0f;
        process_graphics.viewports[1].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=0.0f;
        process_graphics.viewports[0].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=0.0f;
        process_graphics.viewports[5].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=0.0f;
    } else if (x_mode==1) {
        process_graphics.viewports[3].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=progress;
        const float scaled=progress*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=scaled;
        process_graphics.viewports[0].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=scaled;
        process_graphics.viewports[5].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=scaled;
    } else if (x_mode==2) {
        process_graphics.viewports[3].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=-progress;
        const float scaled=(-progress)*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=scaled;
        process_graphics.viewports[0].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=scaled;
        process_graphics.viewports[5].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].x=scaled;
    }

    const std::int32_t y_mode=static_cast<std::int32_t>(native_polygon_random_5ba4c4.bounded(3));
    if (y_mode==0) {
        process_graphics.viewports[3].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=0.0f;
        process_graphics.viewports[1].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=0.0f;
        process_graphics.viewports[0].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=0.0f;
        process_graphics.viewports[5].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=0.0f;
    } else if (y_mode==1) {
        process_graphics.viewports[3].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=progress;
        const float scaled=progress*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=scaled;
        process_graphics.viewports[0].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=scaled;
        process_graphics.viewports[5].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=scaled;
    } else if (y_mode==2) {
        process_graphics.viewports[3].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=-progress;
        const float scaled=(-progress)*native_texture_scale_5b8818;
        process_graphics.viewports[1].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=scaled;
        process_graphics.viewports[0].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=scaled;
        process_graphics.viewports[5].points[reinterpret_cast<NativeScreenInf*>(task)->view_40].y=scaled;
    }

    return 1;
}
}
