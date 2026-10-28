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
    T* begin();
    T& at(std::int32_t index);
    T* end();
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
    AnimationFile* animation_file_ref() const;
    std::int32_t draw();
    std::int32_t frame_changed();
    PlayerShot* find_shot(std::int32_t identifier);
    ~Player() override;
    void enable() override;
    std::int32_t load_shot_data(PlayerShotData** output,const char* path);
    bool focused_mode();
    std::int32_t state_value() const;
    void apply_player_hit();
    void record_bullet_graze(const Vector3& position, std::uint32_t bullet_color);
    std::int32_t collision_rectangle(const Vector3& bullet_position,
                                    const Vector2& extents, std::int32_t mode);
    std::int32_t collision_rectangle_circle(const Vector3& position,
                                           float width, float height, float angle,
                                           std::int32_t mode);
    std::int32_t collision_circle(const Vector3& bullet_position,
                                  float bullet_radius, std::int32_t mode);
    std::uint32_t collision_expansion_enabled() const;
    void set_entity_flag_10(std::uint32_t value);
    std::int32_t damage_limit();
    PlayerFeedback* feedback_value();
    void clear_option_animations();
    void reset_initial_state();
    void rebuild_option_animations(std::int32_t mode);
    std::int32_t active_option_count() const;
    void set_option_field_fc(std::int32_t value);
    void enter_special_state();
    void clear_entity_flag2();
    IntPoint& fixed_position_ref();
    void set_clock_scale(float value);
    Vector3& position_ref();
    float direction_to(const Vector3& target);
};
Player* player(std::int32_t index);
#if defined(_M_IX86)
static_assert(sizeof(Player)==0x1485c);
static_assert(offsetof(Player,entity_flags)==0x14);
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
