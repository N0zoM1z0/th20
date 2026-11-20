#include "Item.hpp"
#include "Session.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "PlayerRecord.hpp"
#include "WeaponStoneInfo.hpp"
#include "ItemRewardHelpers.hpp"
#include "NativeViewIndexOwner.hpp"
#include "HudGauge.hpp"
#include "SoundInf.hpp"
#include "ClockScalar.hpp"
#include "MotionMath.hpp"
#include "CollisionGeometry.hpp"
#include "ScalarMath.hpp"

namespace th20 {
extern const float native_one_56c8cc;
extern const float native_screen_half_2_56c8d0;
extern const float native_screen_top_16_56cd90;
extern const float native_screen_height_448_56d7c0;
extern const float native_screen_rect_inner_width_384_56cda4;
extern const float native_zero_56e0e8;
extern const float native_item_speed_scale_step_56ef28;
extern const float native_item_gravity_570558;
extern const float native_item_attraction_speed_max_56f7a8;
extern const float native_item_attraction_speed_increment_56fbf8;
extern const float native_item_attraction_radius_56cda0;
extern const float native_item_motion_divisor_56c8d8;
extern const float native_screen_margin_8_56d7bc;
std::uint32_t __fastcall animation_draw_enabled(Animation* animation);
std::int32_t ItemInf::update_main() {
    native_view_index_owner_5c0028->set_view_index(view_index);
    special_count=0;
    processed=0;

    IntrusiveList<Item>* active_list=&active;
    auto iterator=active_list->begin();
    IntrusiveIterator<Item>* end=active_list->end();
    while (iterator.differs(end)) {
        IntrusiveLink<Item>* item_link=iterator.get();
        if (item_link->node_access()->state!=0) {
            if (item_link->node_access()->state==5) {
                --item_link->node_access()->delay;
                if (item_link->node_access()->delay<0)
                    item_link->node_access()->activate();
                goto next_item;
            }

            if (item_link->node_access()->state==1) {
                if (item_link->node_access()->delay>0) {
                    --item_link->node_access()->delay;
                    if (item_link->node_access()->delay<1) {
                        item_link->node_access()->spawn_effect();
                        goto next_item;
                    }
                }

                Player* owner=context->player();
                if (owner->state_value()==2)
                    goto attract_with_velocity;
                if (context->player()->state_value()==4)
                    goto attract_with_velocity;
                Player* target=context->player();
                const float target_motion_y=target->motion_parameter_10_value();
                if (target_motion_y<=target->position_ref().y)
                    goto attract_with_velocity;

                item_link->node_access()->attraction_speed=context->player()->motion_parameter_00_value();
                item_link->node_access()->state=3;
                goto chase_player;
            }

            if (item_link->node_access()->state==2) {
                const Vector3 fall_delta=item_link->node_access()->velocity*static_cast<float>(default_timer_clock);
                item_link->node_access()->position+=fall_delta;
                const float gravity=static_cast<float>(default_timer_clock)*native_item_gravity_570558;
                item_link->node_access()->velocity.y+=gravity;
                if (item_link->node_access()->velocity.y>=native_zero_56e0e8)
                    item_link->node_access()->state=1;
                if (item_link->node_access()->position.y>native_screen_top_16_56cd90+
                                     native_screen_height_448_56d7c0+
                                     native_screen_margin_8_56d7bc)
                    goto retire_item;
                const float abs_x=scalar_math::absolute(item_link->node_access()->position.x);
                if (abs_x>=native_screen_rect_inner_width_384_56cda4/
                           native_screen_half_2_56c8d0+native_screen_margin_8_56d7bc)
                    goto retire_item;
                goto collision_test;
            }

            if (item_link->node_access()->state==3)
                goto chase_player;

            if (item_link->node_access()->state==4) {
                Player* owner=context->player();
                if (owner->state_value()==2)
                    goto attract_from_state4;
                if (context->player()->state_value()==4)
                    goto attract_from_state4;
                Player* target=context->player();
                const float target_motion_y=target->motion_parameter_10_value();
                if (target_motion_y<=target->position_ref().y)
                    goto attract_from_state4;
                item_link->node_access()->attraction_speed=
                    context->player()->motion_parameter_00_value();
                item_link->node_access()->state=3;
                goto chase_player;
            }
            goto collision_test;
        }
        goto next_item;

attract_with_velocity:
        if (!context->bomb_controller()->active_for(0x3c) &&
            !current_front->has_dialogue()) {
            const Vector3 clock_delta=item_link->node_access()->velocity*
                static_cast<float>(default_timer_clock);
            const Vector3 scaled_delta=clock_delta*speed_scale;
            item_link->node_access()->position+=scaled_delta;
            const float clock=static_cast<float>(default_timer_clock);
            const float gravity=clock*native_item_gravity_570558*speed_scale;
            item_link->node_access()->velocity.y+=gravity;
            if (native_zero_56e0e8<=item_link->node_access()->velocity.y)
                item_link->node_access()->velocity.x=0.0f;
            if (native_screen_half_2_56c8d0<item_link->node_access()->velocity.y)
                item_link->node_access()->velocity.y=native_screen_half_2_56c8d0;
            if (item_link->node_access()->position.y<=native_screen_top_16_56cd90+
                                  native_screen_height_448_56d7c0+
                                  native_screen_margin_8_56d7bc) {
                const float abs_x=scalar_math::absolute(item_link->node_access()->position.x);
                if (abs_x<native_screen_rect_inner_width_384_56cda4/
                          native_screen_half_2_56c8d0+native_screen_margin_8_56d7bc)
                    goto collision_test;
            }
            goto retire_item;
        }
        item_link->node_access()->attraction_speed=context->player()->motion_parameter_00_value();
        item_link->node_access()->state=3;

chase_player:
        {
            Player* target=context->player();
            const float direction=target->direction_to(item_link->node_access()->position);
            polar(item_link->node_access()->velocity,direction,item_link->node_access()->attraction_speed);
            const Vector3 movement=item_link->node_access()->velocity*
                static_cast<float>(default_timer_clock);
            item_link->node_access()->position+=movement;
            if (item_link->node_access()->attraction_speed<=native_item_attraction_speed_max_56f7a8 &&
                native_item_attraction_speed_max_56f7a8!=item_link->node_access()->attraction_speed)
                item_link->node_access()->attraction_speed+=native_item_attraction_speed_increment_56fbf8;
            if (context->player()->state_value()==4) {
                item_link->node_access()->state=1;
                item_link->node_access()->velocity.x=0.0f;
                item_link->node_access()->velocity.y=0.0f;
            }
        }
        goto collision_test;

attract_from_state4:
        if (!context->bomb_controller()->active_for(0x3c) &&
            !current_front->has_dialogue()) {
            Player* target=context->player();
            const float direction=target->direction_to(item_link->node_access()->position);
            polar(item_link->node_access()->velocity,direction,item_link->node_access()->attraction_speed);
            const Vector3 movement=item_link->node_access()->velocity*
                static_cast<float>(default_timer_clock);
            item_link->node_access()->position+=movement;
            if (item_link->node_access()->attraction_speed<=native_item_attraction_speed_max_56f7a8 &&
                native_item_attraction_speed_max_56f7a8!=item_link->node_access()->attraction_speed)
                item_link->node_access()->attraction_speed+=native_item_attraction_speed_increment_56fbf8;
            if (context->player()->state_value()==4) {
                item_link->node_access()->state=1;
                item_link->node_access()->velocity.x=0.0f;
                item_link->node_access()->velocity.y=0.0f;
            }
            goto collision_test;
        }
        item_link->node_access()->attraction_speed=context->player()->motion_parameter_00_value();
        item_link->node_access()->state=3;
        goto chase_player;

collision_test:
        if (context->player()->state_value()!=2) {
            Player* target=context->player();
            const Vector3& target_position=target->position_ref();
            const float collision_x=context->player()->motion_parameter_04_value();
            const float collision_y=context->player()->motion_parameter_04_value();
            const float collision_radius=collision_y*collision_x;
            const float player_distance=geometry::squared_distance_xy(
                target_position,item_link->node_access()->position);
            if (player_distance<collision_radius)
                goto pickup_item;

            if (attract!=0) {
                const float attraction_distance=geometry::squared_distance_xy(
                    attraction_center,item_link->node_access()->position);
                if (attraction_distance<native_item_attraction_radius_56cda0)
                    goto pickup_item;
            }

            if (item_link->node_access()->state!=4 && item_link->node_access()->state!=3 && item_link->node_access()->state!=2) {
                Player* nearby=context->player();
                const Vector3& nearby_position=nearby->position_ref();
                const float proximity_x=context->player()->motion_parameter_08_value();
                const float proximity_y=context->player()->motion_parameter_08_value();
                const float proximity_radius=proximity_y*proximity_x;
                const float proximity_distance=geometry::squared_distance_xy(
                    nearby_position,item_link->node_access()->position);
                if (proximity_distance<proximity_radius) {
                    const float attraction_speed=
                        context->player()->motion_parameter_00_value();
                    item_link->node_access()->attraction_speed=attraction_speed/
                        native_item_motion_divisor_56c8d8;
                    item_link->node_access()->state=4;
                }
            }
        }
        if (animation_draw_enabled(&item_link->node_access()->animation)!=0)
            item_link->node_access()->animation.update();
        if (animation_draw_enabled(&item_link->node_access()->secondary_animation)!=0)
            item_link->node_access()->secondary_animation.update();
        item_link->node_access()->attachment.set_position(item_link->node_access()->position);
        item_link->node_access()->timer++;
        ++processed;
        goto next_item;

pickup_item:
        switch (item_link->node_access()->type-1) {
        case 0:
            item_award_reward_type_0(item_link->node_access());
            break;
        case 1:
        case 14:
            item_award_reward_type_1(item_link->node_access());
            break;
        case 2:
            item_award_reward_type_2(item_link->node_access());
            break;
        case 3:
            player_record(0)->tick_progress_c0(1);
            break;
        case 4:
            player_record(0)->advance_progress_c4();
            break;
        case 5:
            player_record(0)->tick_progress_d0(1);
            break;
        case 6:
            player_record(0)->advance_progress_cc(1);
            break;
        case 7:
            item_award_life_reward(item_link->node_access());
            break;
        case 8:
        case 12:
            weapon_stone_info(0)->process_item_drop(1);
            player_record(0)->add_field_44(1);
            if (stone_enemy_controller()->byte_b0_value()==0) {
                player_record(0)->add_field_5c(1);
                player_record(0)->add_field_64(10);
            }
            break;
        case 9:
            weapon_stone_info(0)->process_item_drop(1);
            player_record(0)->add_field_44(1);
            if (stone_enemy_controller()->byte_b0_value()==0) {
                player_record(0)->add_field_5c(1);
                player_record(0)->add_field_68(10);
            }
            break;
        case 10:
            weapon_stone_info(0)->process_item_drop(1);
            player_record(0)->add_field_44(1);
            if (stone_enemy_controller()->byte_b0_value()==0) {
                player_record(0)->add_field_5c(1);
                player_record(0)->add_field_6c(10);
            }
            break;
        case 11:
            weapon_stone_info(0)->process_item_drop(1);
            player_record(0)->add_field_44(1);
            if (stone_enemy_controller()->byte_b0_value()==0) {
                player_record(0)->add_field_5c(1);
                player_record(0)->add_field_70(10);
            }
            break;
        }
        process_sound.request_effect_at(0x25,item_link->node_access()->position.x);
retire_item:
        item_link->node_access()->retire();
next_item:
        iterator.advance();
    }

    if (speed_scale<=native_one_56c8cc &&
        native_one_56c8cc!=speed_scale)
        set_speed_scale(speed_scale+native_item_speed_scale_step_56ef28);
    attract=0;
    return 1;
}
}
