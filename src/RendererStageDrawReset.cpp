#include "NativeAnimationResetHooksView.hpp"

#include <cstdint>

namespace th20 {

void NativeAnimationResetHooks::common_init_475170() {
    auto* bytes = reinterpret_cast<std::uint8_t*>(this);
    *reinterpret_cast<std::uint32_t*>(bytes + 0xB8) = 0;
    *reinterpret_cast<std::uint32_t*>(bytes + 0xBC) = 0;
    *reinterpret_cast<std::uint32_t*>(bytes + 0xC0) = 0;
    *reinterpret_cast<std::uint32_t*>(bytes + 0xC4) = 0;
}

void NativeAnimationResetHooks::reset_draw_cache_475120() {
    auto* bytes = reinterpret_cast<std::uint8_t*>(this);
    *reinterpret_cast<std::uint32_t*>(bytes + 0x7D40E90) = 0;
    *reinterpret_cast<std::uint32_t*>(bytes + 0x7D40E8C) = 0x80808080u;
}

void NativeAnimationResetHooks::invalidate_draw_owner_475150() {
    *reinterpret_cast<std::uint8_t*>(this) = 0xFF;
}

void NativeAnimationResetHooks::set_draw_mode_477770(std::uint8_t mode) {
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this) +
                                     0x6000E10) = mode;
}

void NativeAnimationResetHooks::reset_after_stage_draw_4750a0() {
    restart_state_41db80();
    reset_sprite_cache_424080();
    restart_state_41dba0();
    restart_state_41db60();
    restart_state_41db40();
    reset_color_cache_4240a0();
    common_init_475170();
    restart_state_41dbc0();
    reset_draw_cache_475120();
    invalidate_draw_owner_475150();
    auto* bytes = reinterpret_cast<std::uint8_t*>(this);
    *reinterpret_cast<float*>(bytes + 0xCC) = 0.0f;
    *reinterpret_cast<float*>(bytes + 0xC8) = 0.0f;
}

} // namespace th20
