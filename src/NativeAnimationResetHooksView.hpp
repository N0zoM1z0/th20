#pragma once
// Borrowed existing native Renderer/AnimationPool owner; never allocated.
// Original reset/draw-cache state lives far into the actual game object,
// at +0x06000E08...+0x06000E18 and +0x7D40E8C/+0x7D40E90.
#include "AnimationRuntimeOwner.hpp"
namespace th20 {
struct NativeAnimationResetHooks : AnimationPoolOwner {
    void restart_state_41db40();
    void restart_state_41db60();
    void restart_state_41db80();
    void restart_state_41dba0();
    void restart_state_41dbc0();
    void reset_sprite_cache_424080();
    void reset_color_cache_4240a0();
    void common_init_475170();
    void reset_draw_cache_475120();
    void invalidate_draw_owner_475150();
    void set_draw_mode_477770(std::uint8_t mode);
    void reset_after_stage_draw_4750a0();
};
}
