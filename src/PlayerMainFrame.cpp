// Complete original 0x004F9C30..0x004FA856 Player main-frame protocol.
// Source-present, NONEXACT: complete original 3111B/783-instruction game
// Player parent has no accepted whole-byte unit. Native audits recover
// BOTH independent original EnemyController getter calls and BOTH original
// floating sprite-scale evaluations, with no fake /sdl security cookie;
// all 67 native E8 and 37 HIGHLOW *counts* now align (sites still differ).
#include "Player.hpp"
#include "InputInf.hpp"
#include "EnemyController.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "AnimationFile.hpp"
#include "ItemResourceOwners.hpp"
#include "Context.hpp"
#include "SoundInf.hpp"
#include <cstdint>

namespace th20 {
extern InputInf* process_input_inf;
extern InputButtonState* process_input_views[4];
extern const IntPoint native_player_direction_table[9]; // original 0x00572C48
extern const float native_one, native_two, native_128;

// Source-level owner of the entire original frame; this is independent of
// the separately exact Player::frame_changed() (25B at 0x004C0CE0).
std::int32_t Player::update_main_frame() {
    std::int32_t dx = 0;
    std::int32_t dy = 0;
    const std::int32_t input_view = process_input_inf->for_view(view_index);

    // The two-bit special movement mode plays its own timed animation and
    // suppresses normal direction decoding until the native mode timer ends.
    if (movement_mode() != 0) {
        if (timer_2070.equals(0)) suspend_option_animations();
        // Original E8 at 0x004F9CBC targets the distinct 22B
        // Timer::operator++(int) at 0x00423540, not the 20B prefix
        // Timer::operator++() at 0x00429400. Both are real native bodies.
        timer_2070++;
        if (movement_mode() == 1) {
            if (timer_2070.equals(1)) process_sound.request_effect(0x51, 0);
            dx = -0x100;
            dy = 0;
            if (timer_2070.equals(8)) {
                dx = 0xC000;
                set_option_field_fc(1);
                set_secondary_option_field_fc(1);
            }
        } else {
            if (timer_2070.equals(1)) process_sound.request_effect(0x50, 0);
            dx = 0x100;
            dy = 0;
            if (timer_2070.equals(8)) {
                dx = -0xC000;
                set_option_field_fc(1);
                set_secondary_option_field_fc(1);
            }
        }
        timer_2070.equals(8);
        if (!timer_2070.at_least(16)) goto finish_normal_movement;
        clear_option_animations();
        set_movement_mode(0);
    }

    // Original input routing is a live, possibly absent process view. Do not
    // invent a fallback device or apply masks to the wrong Player.
    {
            const std::uint32_t diagonal_left_up = (input_view < 0 || process_input_views[input_view] == nullptr)
                ? 0 : process_input_views[input_view]->replay_current_bits(0x50);
            if (diagonal_left_up == 0x50) field_67c = 5;
            else {
                const std::uint32_t diagonal_left_down = (input_view < 0 || process_input_views[input_view] == nullptr)
                    ? 0 : process_input_views[input_view]->replay_current_bits(0x60);
                if (diagonal_left_down == 0x60) field_67c = 7;
                else {
                    const std::uint32_t diagonal_right_up = (input_view < 0 || process_input_views[input_view] == nullptr)
                        ? 0 : process_input_views[input_view]->replay_current_bits(0x90);
                    if (diagonal_right_up == 0x90) field_67c = 6;
                    else {
                        const std::uint32_t diagonal_right_down = (input_view < 0 || process_input_views[input_view] == nullptr)
                            ? 0 : process_input_views[input_view]->replay_current_bits(0xA0);
                        if (diagonal_right_down == 0xA0) field_67c = 8;
                        else {
                            const std::uint32_t left = (input_view < 0 || process_input_views[input_view] == nullptr)
                                ? 0 : process_input_views[input_view]->replay_current_bits(0x20);
                            if (left != 0) field_67c = 2;
                            else {
                                const std::uint32_t up = (input_view < 0 || process_input_views[input_view] == nullptr)
                                    ? 0 : process_input_views[input_view]->replay_current_bits(0x10);
                                if (up != 0) field_67c = 1;
                                else {
                                    const std::uint32_t down = (input_view < 0 || process_input_views[input_view] == nullptr)
                                        ? 0 : process_input_views[input_view]->replay_current_bits(0x40);
                                    if (down != 0) field_67c = 3;
                                    else {
                                        const std::uint32_t right = (input_view < 0 || process_input_views[input_view] == nullptr)
                                            ? 0 : process_input_views[input_view]->replay_current_bits(0x80);
                                        if (right != 0) field_67c = 4;
                                        else field_67c = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }

        // The immutable original deliberately fetches the Context controller
        // twice: first to test presence, then again to read its count.
        // Do not cache one result or mask a missing original E8 behind the
        // compiler's /sdl-induced security-cookie call.
        if (context->enemy_controller() != nullptr &&
            context->enemy_controller()->count() != 0 &&
            timer_654.at_least(4)) {
            const std::uint32_t first_focus =
                (input_view < 0 || process_input_views[input_view] == nullptr)
                    ? 0 : process_input_views[input_view]->replay_current_bits(8);
            const bool new_focus = first_focus != 0;
            if (focused != static_cast<std::uint8_t>(new_focus))
                point_630 = fixed_position;
            const std::uint32_t second_focus =
                (input_view < 0 || process_input_views[input_view] == nullptr)
                    ? 0 : process_input_views[input_view]->replay_current_bits(8);
            focused = static_cast<std::uint8_t>(second_focus != 0);
        } else {
            focused = 0;
            field_20e4 = 30;
        }
    }

    // All nine signed (dx,dy) direction pairs were independently read from
    // the locked original 0x00572C48 table. Multiplication/addition wraps as
    // observed by the 32-bit original IMUL and integer input lanes.
    dx = native_player_direction_table[field_67c].x;
    dy = native_player_direction_table[field_67c].y;
    if (focused_mode()) {
        if (!(handle_60c != std::uint32_t{0})) {
            AnimationFile* effect_file = context->effect_info()->animation_file(0);
            handle_60c = effect_file->spawn("effect", 19, -1, nullptr);
        }
        if (Animation* active = handle_60c.resolve()) {
            // Native original computes BOTH float scale argument expressions
            // independently; sharing a local scale changes original globals
            // and compiler reference fields even though normal values agree.
            if (collision_expansion_enabled()) {
                active->set_scale_58(
                    (collision_expansion - native_one) * native_two + native_one,
                    (collision_expansion - native_one) * native_two + native_one);
            } else {
                active->set_scale_58(native_one, native_one);
            }
        }
        const std::int32_t x_speed = field_67c < 5 ? speed_20b8 : speed_20c0;
        dx = static_cast<std::int32_t>(static_cast<std::uint32_t>(dx) *
                                       static_cast<std::uint32_t>(x_speed));
        const std::int32_t y_speed = field_67c < 5 ? speed_20b8 : speed_20c0;
        dy = static_cast<std::int32_t>(static_cast<std::uint32_t>(dy) *
                                       static_cast<std::uint32_t>(y_speed));
    } else {
        if (handle_60c.is_valid()) {
            current_animation_pool->interrupt_handle(handle_60c.value, 1);
            handle_60c = std::uint32_t{0};
        }
        const std::int32_t x_speed = field_67c < 5 ? speed_20b4 : speed_20bc;
        dx = static_cast<std::int32_t>(static_cast<std::uint32_t>(dx) *
                                       static_cast<std::uint32_t>(x_speed));
        const std::int32_t y_speed = field_67c < 5 ? speed_20b4 : speed_20bc;
        dy = static_cast<std::int32_t>(static_cast<std::uint32_t>(dy) *
                                       static_cast<std::uint32_t>(y_speed));
    }
    {
    const std::int32_t stored_x = static_cast<std::int32_t>(vector_20f0.x * native_128);
    const std::int32_t stored_y = static_cast<std::int32_t>(vector_20f0.y * native_128);
    dx = static_cast<std::int32_t>(
        static_cast<float>(static_cast<std::int32_t>(static_cast<std::uint32_t>(stored_x)
                          + static_cast<std::uint32_t>(dx))) * field_20ec);
    dy = static_cast<std::int32_t>(
        static_cast<float>(static_cast<std::int32_t>(static_cast<std::uint32_t>(stored_y)
                          + static_cast<std::uint32_t>(dy))) * field_20ec);

    }
finish_normal_movement:
    // The native frame selects animation scripts as X direction crosses zero,
    // but keeps its previous direction in 0x674 for each transition.
    if (dx < 0 && static_cast<std::int32_t>(field_674) >= 0)
        animation_file->bind_animation(&animation, animation_scripts[0], nullptr);
    else if (dx == 0 && static_cast<std::int32_t>(field_674) < 0)
        animation_file->bind_animation(&animation, animation_scripts[1], nullptr);
    if (dx > 0 && static_cast<std::int32_t>(field_674) <= 0)
        animation_file->bind_animation(&animation, animation_scripts[2], nullptr);
    else if (dx == 0 && static_cast<std::int32_t>(field_674) > 0)
        animation_file->bind_animation(&animation, animation_scripts[3], nullptr);

    field_674 = static_cast<std::uint32_t>(dx);
    field_678 = static_cast<std::uint32_t>(dy);
    apply_move_delta(dx, dy);
    if (handle_60c.is_valid()) handle_60c.set_position_forward(position_ref());

    // Reverse shift the original 33-slot fixed-position history only when
    // actual horizontal/vertical motion was requested.
    if (dx || dy) {
        for (std::int32_t index = 0;
             index < static_cast<std::int32_t>(points_20fc.size()) - 1; ++index) {
            const auto n = static_cast<std::int32_t>(points_20fc.size());
            const IntPoint saved = points_20fc.at(n - 2 - index);
            points_20fc.at(static_cast<std::int32_t>(points_20fc.size()) - 1 - index) = saved;
        }
        points_20fc.at(0) = fixed_position_ref();
    }

    if (((entity_flags.bits >> 1) & 1u) != 0) ++field_20e8;
    for (auto* option = options.begin(); option != options.end(); ++option)
        update_option_frame(option);
    for (auto* option = secondary_options.begin();
         option != secondary_options.end(); ++option)
        update_option_frame(option);
    if (static_cast<std::int32_t>(field_20e8) >= 30) field_680 = 0;
    return 0;
}
} // namespace th20
