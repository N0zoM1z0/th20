#pragma once
#include "AnimationHandle.hpp"
#include "Context.hpp"
#include "Identifier32.hpp"
#include "IntrusiveLink.hpp"
#include "Motion.hpp"
#include "Rectangle.hpp"
#include "Timer.hpp"
#include "Vector2.hpp"
#include <array>

namespace th20 {
// EXACT-076: real native Option, Feedback and Shot storage protocols. Names
// containing offsets describe observed storage with unresolved gameplay roles.
// The enclosing 0x1485c Player and its untouched +0x14850 region remain open.

struct PlayerWordFlags { std::uint32_t bits; };
struct PlayerOptionState { std::uint32_t flags; std::uint8_t focused; };
// Shot +0xdc is a damage identifier, independently resolved by the native
// consumer. This scalar constructor shares PackedColor's physical head.
struct DamageHandle {
    std::uint32_t value;
    explicit DamageHandle(std::uint32_t initial=0);
};
struct PlayerOption {
    std::uint32_t state;
    Vector3 position, previous_position, vectors_1c[7];
    IntPoint fixed_position, previous_fixed_position, offsets[7];
    IntPoint point_b8,point_c0;
    Vector3 vector_c8;
    Identifier32 identifier_d4;
    float field_d8;
    AnimationHandle handle_dc,handle_e0;
    Timer timer_e4;
    std::uint32_t field_f4,field_f8,field_fc;
    PlayerOptionState state_100;
    std::uint32_t field_108,field_10c;
    float field_110;
    AnimationHandle handle_114;
    std::uint32_t field_118,field_11c,field_120;
    std::int32_t player_index;
    Context* context;
    PlayerOption() noexcept;
};
struct PlayerFeedback {
    Timer timer_00,timer_10,timer_20;
    std::uint32_t field_30,field_34,field_38,field_3c;
    Vector3 vector_40;
    AnimationHandle handle_4c;
    std::uint8_t enabled;
    std::int32_t player_index;
    Context* context;
    PlayerFeedback();
};
struct PlayerCollisionBounds {
    float normal_radius,focus_radius;
    Vector3 normal_extent,focus_extent;
    PlayerCollisionBounds();
};
struct PlayerMotionParameters {
    float field_00,field_04,field_08,field_0c,field_10;
    PlayerMotionParameters() noexcept;
};
struct PlayerShotController;
struct PlayerShot {
    IntrusiveLink<PlayerShot> link;
    std::uint32_t state_14;
    AnimationHandle handle_18;
    Timer timer_1c,timer_2c;
    PlayerWordFlags flags_3c;
    std::uint32_t field_40,field_44,field_48,field_4c;
    Motion motion;
    Identifier32 identifier_98;
    std::uint32_t field_9c;
    AnimationHandle handle_a0;
    std::int32_t field_a4,field_a8,field_ac;
    Vector2 extent;
    std::array<std::uint32_t,8> words_b8;
    std::uint32_t record_index;
    DamageHandle damage;
    std::array<std::uint32_t,8> words_e0;
    Vector3 vector_100;
    std::uint32_t field_10c,field_110;
    std::uint8_t byte_114;
    std::int32_t player_index;
    PlayerShotController* owner;
    Context* context;
    PlayerShot();
};
// Native 0x4f41d0 constructs exactly 256 typed Shot objects at stride 0x124.
// Its full nonthrowing EH protocol establishes the array owner's contract;
// child construction retains its separately observed potentially throwing ABI.
// The original class/template spelling is unknown.
struct PlayerShotPool {
    PlayerShot slots[256];
    PlayerShotPool() noexcept;
};
struct PlayerShotController {
    PlayerShotPool pool;
    Timer timer_12400,timer_12410,timer_12420;
    IntrusiveList<PlayerShot> active,free;
    std::uint32_t field_12460,field_12464;
    std::uint32_t counters_12468[30],counters_124e0[30];
    std::uint32_t field_12558;
    PlayerWordFlags flags_1255c;
    Identifier32 identifier_12560;
    float field_12564;
    Timer timer_12568;
    std::uint32_t field_12578;
    std::uint8_t byte_1257c;
    Timer timer_12580;
    std::int32_t player_index;
    Context* context;
    PlayerShotController();
};
// No explicit padding fields: byte flags and pointers use native alignment.
static_assert(sizeof(PlayerOptionState)==8);
#if defined(_M_IX86)
static_assert(sizeof(PlayerOption)==0x12c);
static_assert(offsetof(PlayerOption,state_100)==0x100);
static_assert(offsetof(PlayerOption,context)==0x128);
static_assert(sizeof(PlayerFeedback)==0x5c);
static_assert(sizeof(PlayerCollisionBounds)==0x20);
static_assert(sizeof(PlayerMotionParameters)==0x14);
static_assert(sizeof(PlayerShot)==0x124);
static_assert(offsetof(PlayerShot,damage)==0xdc);
static_assert(offsetof(PlayerShot,context)==0x120);
static_assert(sizeof(PlayerShotController)==0x12598);
static_assert(offsetof(PlayerShotController,active)==0x12430);
static_assert(offsetof(PlayerShotController,context)==0x12594);
#endif
}
