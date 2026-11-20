#pragma once
// Borrowed existing native Renderer/AnimationPool owner; never allocated.
// Original device-reset state lives far into the actual game object,
// at the physical +0x06000E08...+0x06000E10 offsets.
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
};
}
