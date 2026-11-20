// Original 500B second virtual entry of the six-slot Bomb vtable at
// 0x0056FB0C. Natural C++ source-present frontier, not yet whole exact.
#include "Bomb.hpp"
#include "Player.hpp"
#include "EnemyController.hpp"
#include "Card.hpp"
#include "SoundInf.hpp"
#include "AnimationFile.hpp"
#include "Animation.hpp"
#include "Angle.hpp"
#include "AnimationHandle.hpp"
#include "NativeBombPulseViews.hpp"
#include <cstdint>
namespace th20 {
extern const float native_negative_pi, native_two;
struct NativeCardCaptureRefreshView { void refresh_487bb0(); };
std::int32_t NativeBombPulse::start(std::int32_t) {
    Vector3 current_position;
    spawn_position=player(0)->position_ref();
    spawn_heading=native_negative_pi/native_two;
    process_sound.request_effect(0x31,0);

    AnimationFile* first_file=player(0)->animation_file_ref();
    pulse_handle=first_file->spawn("pl01",0x33,spawn_position,0.0f,-1,nullptr);
    reinterpret_cast<NativeBombEffectHandleView*>(&pulse_handle)->bind_owner_450850(this);
    pulse_handle.set_entry_callback_forward_44f100(bomb_pulse_animation_callback_478380);

    AnimationFile* second_file=player(0)->animation_file_ref();
    handle_74=second_file->spawn("pl01",0x41,spawn_position,0.0f,-1,nullptr);
    reinterpret_cast<NativeBombEffectHandleView*>(&handle_74)->bind_owner_450850(this);
    handle_74.set_entry_callback_forward_44f100(bomb_pulse_animation_callback_478380);

    current_position=spawn_position;
    reinterpret_cast<NativeCardCaptureRefreshView*>(card(0))->refresh_487bb0();
    reinterpret_cast<NativeBombPlayerView*>(player(0))->set_invulnerability_479060(120);
    reinterpret_cast<NativeBombEnemyCounterView*>(enemy_controller(0))->advance_477f40(1);
    (void)create_bomb_pulse_auxiliary_425090(8,3,60,240,30);
    reinterpret_cast<NativeBombPlayerView*>(player(0))->mark_bomb_used_4790a0();
    return 0;
}
}
