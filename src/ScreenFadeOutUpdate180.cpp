// Original 180B ScreenInf fade-out callback at 0x004240C0.
#include "NativeScreenEffect.hpp"
#include "NativeScreenShakeChannels.hpp"
#include <cstdint>
namespace th20 {
extern const float native_screen_alpha_max_56cd9c;
std::int32_t __cdecl screen_update_fade_out_4240c0(void* task) {
    if (native_screen_stopped_5ba518!=0) return 7;
    if (static_cast<NativeScreenInf*>(task)->field_1c!=0) {
        const float fraction=static_cast<NativeScreenInf*>(task)->timer_30.fraction();
        static_cast<NativeScreenInf*>(task)->alpha_18=static_cast<std::uint32_t>(
            static_cast<std::int32_t>(native_screen_alpha_max_56cd9c-
                (fraction*native_screen_alpha_max_56cd9c)/static_cast<float>(
                    static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->field_1c))));
        if (static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->alpha_18)<0)
            static_cast<NativeScreenInf*>(task)->alpha_18=0;
    }
    if (static_cast<NativeScreenInf*>(task)->timer_30.at_least(
            static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->field_1c))) return 7;
    static_cast<NativeScreenInf*>(task)->timer_30++;
    return 1;
}
}
