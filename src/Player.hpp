#pragma once
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "PlayerStorage.hpp"
#include "TaskInfo.hpp"

namespace th20 {
// Complete native Player storage. +18 has a floating-angle consumer;
// +1484c has the same floating-zero producer but its role/tag remain unknown.
// Original destruction/activation remain undefined until their ANM/gameplay
// ownership is reconstructed.
template<class T, unsigned Count> struct PlayerValues {
    T values[Count];
    PlayerValues() noexcept;
};
template<class T, unsigned Count>
PlayerValues<T,Count>::PlayerValues() noexcept {}
struct PlayerShotData;
class Player : public TaskInfo {
public:
    std::int32_t state;
    PlayerWordFlags entity_flags;
    Angle direction;
    AnimationFile* animation_file;
    std::uint32_t field_20, field_24;
    Animation animation;
    AnimationHandle handle_60c, handle_610;
    Vector3 position;
    IntPoint fixed_position, point_628, point_630;
    Vector3 vector_638;
    Timer timer_644, timer_654, timer_664;
    std::uint32_t field_674, field_678, field_67c, field_680;
    PlayerValues<PlayerOption,10> options;
    PlayerValues<PlayerOption,12> secondary_options;
    std::uint8_t focused;
    Timer timer_2050, timer_2060, timer_2070;
    PlayerMotionParameters motion_parameters;
    PlayerCollisionBounds collision_bounds;
    std::int32_t speed_20b4, speed_20b8, speed_20bc, speed_20c0;
    Vector3 vector_20c4, vector_20d0;
    IntPoint point_20dc;
    std::uint32_t field_20e4, field_20e8;
    float field_20ec;
    Vector3 vector_20f0;
    PlayerValues<IntPoint,33> points_20fc;
    std::uint32_t field_2204;
    PlayerShotData* shot_data;
    FloatInterpolation interpolation;
    float collision_expansion, clock_scale;
    std::uint32_t field_2240;
    PlayerFeedback feedback;
    std::uint32_t animation_scripts[5];
    PlayerShotController shots;
    Angle value_1484c;
    std::uint32_t field_14850;
    std::int32_t view_index;
    Context* context;
    Player() noexcept;
    ~Player() override;
    void enable() override;
    std::int32_t load_shot_data(PlayerShotData** output,const char* path);
    bool focused_mode();
    std::int32_t damage_limit();
};
#if defined(_M_IX86)
static_assert(sizeof(Player)==0x1485c);
static_assert(offsetof(Player,animation)==0x28);
static_assert(offsetof(Player,options)==0x684);
static_assert(offsetof(Player,secondary_options)==0x123c);
static_assert(offsetof(Player,focused)==0x204c);
static_assert(offsetof(Player,motion_parameters)==0x2080);
static_assert(offsetof(Player,collision_bounds)==0x2094);
static_assert(offsetof(Player,field_20ec)==0x20ec);
static_assert(offsetof(Player,shot_data)==0x2208);
static_assert(offsetof(Player,feedback)==0x2244);
static_assert(offsetof(Player,shots)==0x22b4);
static_assert(offsetof(Player,field_14850)==0x14850);
static_assert(offsetof(Player,context)==0x14858);

#endif
}
