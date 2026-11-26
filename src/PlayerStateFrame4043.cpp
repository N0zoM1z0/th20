// Complete native Player state frame and seven-state protocol at 0x004F7430.
// The 4072-byte contribution includes one NOP and seven switch pointers.
// Independent relocation bindings remain incomplete; this owner is NONEXACT.
#include "Player.hpp"
#include "InputInf.hpp"
#include "AnimationFile.hpp"
#include "GameController.hpp"
#include "Bomb.hpp"
#include "Bullet.hpp"
#include "LaserParameters.hpp"
#include "Item.hpp"
#include "HitCtrlInf.hpp"
#include "FrontInfDialogueCommand626.hpp"
#include "NativeViewIndexOwner.hpp"
#include "ClockScalar.hpp"
#include "MotionMath.hpp"

namespace th20 {
extern InputInf* process_input_inf;
extern InputButtonState* process_input_views[4];
extern const float native_one, native_two, native_128;
extern const float player_clear_growth_56f114, player_clear_frames_56f280, player_clear_start_56fa28;
extern const float player_drop_pi_56e0f0, player_drop_spread_56fd48, player_drop_center_56c8dc;
extern const float player_spawn_y_56cda8;
extern const float player_dash_frames_570560, player_scale_threshold_56e730;
extern const float player_drop_target_y_56ed14;
extern const Vector3 player_zero_motion_572664;

std::int32_t Player::update_state_frame() {
    native_view_index_owner_5c0028->set_view_index(view_index);
    const std::int32_t input_view = process_input_inf->for_view(view_index);
    switch (state_value()) {
    case 6:
        timer_644 = 0;
        position = {0.0f, player_spawn_y_56cda8, 0.0f};
        fixed_position = {0, 480};
        break;
    case 0: {
        if (timer_644.at_most(1))
            animation_file->bind_animation(&animation, animation_scripts[0]);
        const std::int32_t fixed_y =
            static_cast<std::int32_t>(static_cast<std::uint32_t>(
                static_cast<std::int32_t>(timer_644)) * static_cast<std::uint32_t>(-0x2800)) / 60 + 0xf000;
        fixed_position_ref().y = fixed_y;
        position_ref().y = static_cast<float>(fixed_position_ref().y) / native_128;
        set_option_field_fc(1);
        {
            auto& history = points_20fc;
            for (auto* current = history.begin(), *end = history.end(); current != end; ++current) {
                IntPoint* slot = current;
                *slot = fixed_position_ref();
            }
        }
        if (timer_644.at_least(30)) {
            context->bullet_controller()->cancel_near_limited(
                position_ref(), 640.0f, 0, 99999, 0);
            context->laser_controller()->cancel_near(position_ref(), 640.0f, 0, 0);
            context->hit_controller()->create_circle(
                position_ref(), 120.0f, 0.0f, 1, 10).enable_damage_flag4();
        } else {
            const float radius = (static_cast<float>(static_cast<std::int32_t>(timer_644)) *
                                  player_clear_growth_56f114) / player_clear_frames_56f280 +
                                  player_clear_start_56fa28;
            context->laser_controller()->cancel_near(vector_638, radius, 0, 1);
            context->laser_controller()->cancel_near(vector_638, radius / 4.0f, 0, 0);
        }
        if (timer_644.at_least(60)) {
            clear_option_animations();
            set_state_value(1);
            timer_644 = 0;
            goto active_state;
        }
        break;
    }
    case 1:
active_state:
        if (timer_644.at_most(1))
            animation_file->bind_animation(&animation, animation_scripts[0]);
        if (current_game_controller->flag_19_set() == 0 &&
            context->bomb_controller() != nullptr && context->bomb_controller()->can_start()) {
            if (((input_view < 0 || process_input_views[input_view] == nullptr)
                 ? 0 : process_input_views[input_view]->replay_pressed_bits(4)) != 0)
                context->bomb_controller()->start_bomb();
        }
        update_main_frame();
        break;
    case 4:
        if (timer_644.at_least(static_cast<std::int32_t>(field_2204))) {
            enter_death_state();
            goto death_state;
        } else {
            if (context->bomb_controller() != nullptr) {
                if (((input_view < 0 || process_input_views[input_view] == nullptr)
                     ? 0 : process_input_views[input_view]->replay_pressed_bits(4)) != 0) {
                    if (context->bomb_controller()->can_start()) {
                        context->bomb_controller()->start_bomb();
                        revive_after_bomb();
                    }
                }
            }
        }
        break;
    case 2: {
death_state:
        if (timer_644.equals(3)) {
            if (player_record(0)->available_option_count() >= 4)
                player_record(0)->consume_power((player_record(0)->starting_power() * 80) / 100);
            else if (player_record(0)->available_option_count() >= 3)
                player_record(0)->consume_power((player_record(0)->starting_power() * 60) / 100);
            else if (player_record(0)->available_option_count() >= 2)
                player_record(0)->consume_power((player_record(0)->starting_power() * 50) / 100);
            else
                player_record(0)->consume_power((player_record(0)->starting_power() * 40) / 100);
            Vector3 target(0.0f, position_ref().y - player_drop_target_y_56ed14, 0.0f);
            const float drop_direction = direction_from(target);
            const std::int32_t item_types[7] = {1, 1, 1, 1, 1, 1, 1};
            for (std::int32_t index = 0; index < 7; ++index) {
                const float angle = ((static_cast<float>(index) * player_drop_pi_56e0f0) /
                                     player_drop_spread_56fd48 + drop_direction) -
                                    (player_drop_pi_56e0f0 * player_drop_center_56c8dc) /
                                     player_drop_spread_56fd48;
                item_controller(0)->spawn(item_types[index], position_ref(), 0xffffffffu,
                                         angle, 3.0f, 0, 0, -1);
            }
            rebuild_option_animations(-1);
        }
        if (timer_644.at_least(30)) {
            if (((entity_flags.bits >> 10) & 1u) != 0)
                context->bullet_controller()->cancel_near(position_ref(), 80.0f, 0);
            if (player_record(0)->clamped_field_b8() < 0) {
                if (timer_644.equals(30)) {
                    if (!native_card_play_5c60fc->is_paused_488800())
                        native_screen_dialogue_transition_5c60bc->finish_dialogue_4e5bd0();
                    timer_644++;
                    break;
                }
            }
            set_state_value(0);
            default_timer_clock.set(native_one);
            hit_controller(0)->create_circle(position_ref(), 32.0f,
                                            16.0f, 30, 150);
            std::int32_t bombs = 0;
            if (player_record(0)->clamped_field_cc() < 2)
                bombs += player_record(0)->clamped_field_d4();
            else
                bombs += player_record(0)->clamped_field_cc();
            player_record(0)->set_field_cc_clamped(bombs);
            vector_638 = position_ref();
            set_position_xy(0.0f, player_spawn_y_56cda8);
            timer_2050 = 280;
            timer_644 = 0;
        }
        break;
    }
    case 3:
        if (timer_644.equals(4)) {}
        else if (timer_644.equals(15)) context->laser_controller()->cancel_all(1, 0);
        else if (timer_644.equals(30)) {}
        break;
    case 5: {
        Vector3 movement;
        direction.to_vector(movement, nullptr, native_one);
        normalize_to_length(movement, movement,
            native_two - (static_cast<float>(static_cast<std::int32_t>(timer_644)) * native_two) /
                         player_dash_frames_570560);
        apply_move_delta(static_cast<std::int32_t>(movement.x * native_128),
                         static_cast<std::int32_t>(movement.y * native_128));
        if (timer_644.at_least(40)) {
            state = 1;
            timer_644 = 0;
        }
        break;
    }
    }
    if (timer_2060.greater_than(0)) timer_2060--;
    if (timer_2050.greater_than(0)) {
        timer_2050--;
        auto& display = animation;
        if (timer_644.every(3) != 0) {
            display.set_secondary_color(0xff0000ffu);
            display.base.flags.bits_09.color_mode = 1;
        } else animation.base.flags.bits_09.color_mode = 0;
    } else {
        animation.base.flags.bits_09.color_mode = 0;
        if (entity_flag5() != 0) {
            auto& display = animation;
            if (timer_644 % 8 < 4) {
                display.set_secondary_color(0xffff0000u);
                display.base.flags.bits_09.color_mode = 1;
            }
        } else if (player_scale_threshold_56e730 < motion_scale_value()) {
            auto& display = animation;
            if (timer_644 % 8 < 4) {
                display.set_secondary_color(0xffffff00u);
                display.base.flags.bits_09.color_mode = 1;
            }
        }
    }
    field_20ec = native_one;
    set_extra_motion(player_zero_motion_572664);
    animation.update();
    if (collision_expansion_enabled() != 0) {
        if (interpolation.duration_value() != 0) collision_expansion = interpolation.sample();
        if (interpolation.duration_value() == 0 || static_cast<std::int32_t>(timer_644) % 3 != 0)
            animation.set_scale(collision_expansion, collision_expansion);
        else animation.set_scale(native_one, native_one);
    } else animation.set_scale(native_one, native_one);
    timer_644++;
    timer_654++;
    shots.update();
    feedback.update();
    return 1;
}
} // namespace th20
