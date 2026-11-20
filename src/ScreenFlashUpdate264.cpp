// Original 264B ScreenInf flash callback at 0x00424350.
// Alpha is the high byte of the configured color; Timer and repeat count
// are the real fields of the existing NativeScreenInf owner.
#include "NativeScreenEffect.hpp"
#include "NativeScreenShakeChannels.hpp"
#include <cstdint>
namespace th20 {
extern const double native_unsigned_double_bias_56cdd0[2];
std::int32_t __cdecl screen_update_flash_424350(void* task) {
    const std::uint32_t alpha=(static_cast<NativeScreenInf*>(task)->field_24>>24)&0xffu;
    if (native_screen_stopped_5ba518!=0) return 7;

    if (static_cast<NativeScreenInf*>(task)->timer_30.less_than(
            static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->field_1c))) {
        volatile float fraction=static_cast<NativeScreenInf*>(task)->timer_30.fraction();
        const std::int32_t alpha_for_double=static_cast<std::int32_t>(alpha);
        const double alpha_double=static_cast<double>(alpha_for_double)+
            native_unsigned_double_bias_56cdd0[static_cast<std::uint32_t>(alpha_for_double)>>31];
        static_cast<NativeScreenInf*>(task)->alpha_18=alpha-static_cast<std::uint32_t>(
            static_cast<std::int32_t>((fraction*static_cast<float>(alpha_double)) /
                static_cast<float>(static_cast<std::int32_t>(
                    static_cast<NativeScreenInf*>(task)->field_1c))));
        if (static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->alpha_18)<0)
            static_cast<NativeScreenInf*>(task)->alpha_18=0;
    } else {
        static_cast<NativeScreenInf*>(task)->alpha_18=0;
        static_cast<NativeScreenInf*>(task)->field_20=static_cast<std::uint32_t>(
            static_cast<NativeScreenInf*>(task)->field_20-1u);
        if (static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->field_20)<=0) return 7;
        static_cast<NativeScreenInf*>(task)->timer_30=0;
    }
    static_cast<NativeScreenInf*>(task)->timer_30++;
    return 1;
}
}
