#pragma once
// Actual Bomb-derived object and independent, non-allocating view methods.
#include "Bomb.hpp"
#include "AnimationHandle.hpp"
#include "Angle.hpp"
#include "Vector3.hpp"
#include <cstdint>
namespace th20 {
class Animation;
std::int32_t __cdecl bomb_pulse_animation_callback_478380(Animation* animation);
void* __cdecl create_bomb_pulse_auxiliary_425090(
    std::int32_t mode,std::int32_t variant,std::int32_t length,
    std::int32_t radius,std::int32_t strength);
struct NativeBombEffectHandleView : AnimationHandle {
    void bind_owner_450850(void* owner);
};
struct NativeBombPlayerView {
    void set_invulnerability_479060(std::int32_t frames);
    void mark_bomb_used_4790a0();
};
struct NativeBombEnemyCounterView {
    void advance_477f40(std::int32_t delta);
};
class NativeBombPulse : public Bomb {
public:
    Vector3 spawn_position;
    Angle spawn_heading;
    AnimationHandle pulse_handle;
    std::int32_t start(std::int32_t index) override;
};
#if defined(_M_IX86)
static_assert(sizeof(Bomb)==0xb8);
static_assert(sizeof(NativeBombPulse)==0xcc);
#endif
}
