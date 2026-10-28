// Original complete 966-byte Player state reset root, provisional C++.
// External Player/shot state callees retain original typed member ABIs;
// exact linker ownership of those separate game subsystems remains open.
#include "Player.hpp"
#include "ShotData.hpp"
#include "Session.hpp"
namespace th20 {
extern const float native_one;
extern const float native_two;
extern const float native_five;
extern const float native_thirty;
extern const float native_seventy;
extern const float native_128;
extern const float native_three;
extern const float native_ten;
template<class T,unsigned Count>
T* PlayerValues<T,Count>::begin() {return values;}
void Player::reset_initial_state() {
    state = 1;
    timer_644 = 0;
    timer_654 = 0;
    entity_flags.bits &= ~1u;
    entity_flags.bits &= ~8u;
    handle_60c.retire();
    handle_60c = 0u;
    handle_610.retire();
    handle_610 = 0u;
    shots.reset_all();
    clear_option_animations();
    rebuild_option_animations(-1);
    field_20ec = native_one;
    clear_entity_flag2();
    interpolation.stop();
    collision_expansion = native_one;
    // Establish the default clock before refreshing the recent position history.
    {
        set_clock_scale(native_one);
    }
    auto* history = &points_20fc;
    for (IntPoint* current=history->begin(),* finish=history->end();current != finish; ++current) {
        IntPoint* slot = current;
        *slot = fixed_position_ref();
    }
    field_2204=8;
    speed_20b4=static_cast<std::int32_t>(shot_data->normal_speed * native_128);
    speed_20b8=static_cast<std::int32_t>(shot_data->focused_speed * native_128);
    speed_20bc=static_cast<std::int32_t>(shot_data->lateral_speed * native_128);
    speed_20c0=static_cast<std::int32_t>(shot_data->diagonal_speed * native_128);
    motion_parameters.field_00=native_five;
    motion_parameters.field_04=native_thirty;
    motion_parameters.field_08=native_seventy;
    motion_parameters.field_0c=native_seventy;
    motion_parameters.field_10=native_128;
    collision_bounds.normal_radius=native_three;
    collision_bounds.focus_radius=native_three;
    const float half_normal=collision_bounds.normal_radius/native_two;
    collision_bounds.normal_extent.y=half_normal;
    collision_bounds.normal_extent.x=half_normal;
    collision_bounds.normal_extent.z=native_ten/native_two;
    const float half_focus=collision_bounds.focus_radius/native_two;
    collision_bounds.focus_extent.y=half_focus;
    collision_bounds.focus_extent.x=half_focus;
    collision_bounds.focus_extent.z=native_ten/native_two;
    field_2204=8;
    animation_scripts[0]=0;
    animation_scripts[1]=1;
    animation_scripts[2]=2;
    animation_scripts[3]=3;
    animation_scripts[4]=4;
    if (player_table().clamped_field_1e4() == 0 &&
        session.flag0_value() == 0 && view_index == 1)
        enter_special_state();
}
} // namespace th20
