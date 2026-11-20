// Original 239B ScreenInf fade-in update callback at 0x00424260.
#include "NativeScreenEffect.hpp"
#include "NativeScreenShakeChannels.hpp"
#include "GameController.hpp"
#include <cstdint>
namespace th20 {
extern GameController* current_game_controller;
extern const float native_screen_alpha_max_56cd9c;
std::int32_t __cdecl screen_update_fade_in_424260(void* task) {
    if (native_screen_stopped_5ba518!=0) return 7;
    if (static_cast<NativeScreenInf*>(task)->field_1c!=0) {
        if (static_cast<NativeScreenInf*>(task)->timer_30.less_than(
                static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->field_1c))) {
            static_cast<NativeScreenInf*>(task)->alpha_18=static_cast<std::uint32_t>(
                static_cast<std::int32_t>((static_cast<NativeScreenInf*>(task)->timer_30.fraction()*
                    native_screen_alpha_max_56cd9c)/static_cast<float>(static_cast<std::int32_t>(
                        static_cast<NativeScreenInf*>(task)->field_1c))));
        } else {
            static_cast<NativeScreenInf*>(task)->alpha_18=0xffu;
        }
        if (static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->alpha_18)<0)
            static_cast<NativeScreenInf*>(task)->alpha_18=0;
    }
    if (static_cast<NativeScreenInf*>(task)->timer_30.at_least(
            static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->field_1c)+2)) return 7;
    if (current_game_controller==nullptr || current_game_controller->update_suppressed()==0)
        static_cast<NativeScreenInf*>(task)->timer_30++;
    return 1;
}
}
