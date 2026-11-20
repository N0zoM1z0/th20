// Original 82B ScreenInf solid-alpha update callback at 0x00424460.
#include "NativeScreenEffect.hpp"
#include <cstdint>
namespace th20 {
std::int32_t __cdecl screen_update_solid_424460(void* task) {
    static_cast<NativeScreenInf*>(task)->alpha_18=0xffu;
    if (static_cast<NativeScreenInf*>(task)->timer_30.at_least(
            static_cast<std::int32_t>(static_cast<NativeScreenInf*>(task)->field_1c))) return 7;
    static_cast<NativeScreenInf*>(task)->timer_30++;
    return 1;
}
}
