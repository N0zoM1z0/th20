#pragma once

#include <cstdint>

namespace th20 {

// Non-owning renderer-state interface embedded at offset zero in the native
// AnimationPool owner view. It has no data or virtual dispatch; these methods
// retain their independently recovered native thiscall entry points.
struct NativeAnimationResetHooks {
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

} // namespace th20
