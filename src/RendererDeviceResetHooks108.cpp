// Five distinct game-owned Renderer reset leaf methods from the
// original 1954B Window D3D9 state restoration Boss.
// Each literal is an authentic store into the large native
// AnimationPoolOwner record, not a temporary or hand-inserted opcode.
#include "NativeAnimationResetHooksView.hpp"
#include <cstdint>
namespace th20 {
void NativeAnimationResetHooks::restart_state_41db40() {
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0C)=0x0B;
}
void NativeAnimationResetHooks::restart_state_41db60() {
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0D)=0xFF;
}
void NativeAnimationResetHooks::restart_state_41db80() {
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=0xFF;
}
void NativeAnimationResetHooks::restart_state_41dba0() {
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08)=0xFFFFFFFFu;
}
void NativeAnimationResetHooks::restart_state_41dbc0() {
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E10)=0xFF;
}
}
