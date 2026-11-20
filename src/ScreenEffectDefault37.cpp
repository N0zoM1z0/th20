// Native whole 37B default-priority ScreenInf creation adapter, 0x00425090.
// The 0x6D update/draw layer and the trailing zero view are real inputs.
#include "NativeScreenEffect.hpp"
namespace th20 {
NativeScreenInf* __cdecl screen_effect_default_425090(std::int32_t mode,
    std::uint32_t p1,std::uint32_t p2,std::uint32_t p3,std::uint32_t p4) {
    return screen_factory_4250f0(mode,p1,p2,p3,p4,0x6d,0);
}
}
