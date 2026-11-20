// Original 221B ScreenInf hold callback at 0x00424180.
#include "NativeScreenEffect.hpp"
#include <cstdint>
namespace th20 {
extern const float native_screen_alpha_128_56cd98;
extern const float native_screen_duration_8_56d7bc;
std::int32_t __cdecl screen_update_hold_424180(void* task) {
    if (static_cast<NativeScreenInf*>(task)->field_2c==0) {
        if (static_cast<NativeScreenInf*>(task)->field_1c!=0 &&
            static_cast<NativeScreenInf*>(task)->timer_30.at_most(
                static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->field_1c))) {
            static_cast<NativeScreenInf*>(task)->alpha_18=static_cast<std::uint32_t>(
                static_cast<std::int32_t>((static_cast<NativeScreenInf*>(task)->timer_30.fraction()*
                    native_screen_alpha_128_56cd98)/static_cast<float>(static_cast<std::int32_t>(
                        static_cast<NativeScreenInf*>(task)->field_1c))));
        }
    } else {
        if (static_cast<NativeScreenInf*>(task)->timer_30.at_most(8)) {
            static_cast<NativeScreenInf*>(task)->alpha_18=0x80u-static_cast<std::uint32_t>(
                static_cast<std::int32_t>((static_cast<NativeScreenInf*>(task)->timer_30.fraction()*
                    native_screen_alpha_128_56cd98)/native_screen_duration_8_56d7bc));
        } else {
            return 7;
        }
    }
    static_cast<NativeScreenInf*>(task)->timer_30++;
    return 1;
}
}
