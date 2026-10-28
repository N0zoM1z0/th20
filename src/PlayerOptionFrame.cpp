// Complete original 1,081-byte Player per-option frame boss.
// Original 0x004FA860 has 325 native i386 instructions and 40 independent
// E8 / PE HIGHLOW reference fields. This native member pointer ABI is
// deliberate: both original option callbacks use PlayerOption in ECX.
// True __thiscall receiver Player*, real PlayerOption* native stack argument.
// All game-owned member offsets remain type checked through the real headers.
#include "Player.hpp"
#include "PlayerRecord.hpp"
#include "WeaponStoneInfo.hpp"
#include "ShotData.hpp"
#include "Session.hpp"
#include "Vector3.hpp"

#include <cstdint>
#include <utility>

namespace th20 {
void __fastcall cancel_animation_handle(const AnimationHandle&);

std::int32_t Player::update_option_frame(PlayerOption* option) {
    Vector3 presentation_position;
    if (option->state == 0) return 0;

    if (option->state_100.focused != player(0)->focused_mode()) {
        // The native option script for unfocused alternate rendering
        // is only launched above the original clamped option limit.
        if (context->player_record()->clamped_option_units() >=
            context->player_record()->clamped_option_cap()) {
            { option->handle_e0.retire(); }
            auto* file = animation_file_ref();
            auto* table = reinterpret_cast<const std::int32_t*>(
                reinterpret_cast<const std::uint8_t*>(shot_data) + 0xA8);
            const auto displacement = weapon_stone_info(0)->option_script_variant() * 4;
            const auto script = *reinterpret_cast<const std::int32_t*>(
                reinterpret_cast<const std::uint8_t*>(table) + displacement);
            option->handle_e0 = file->spawn(nullptr, script, -1, nullptr);
            option->handle_e0.interrupt_offset_7(0);
        }
        { option->handle_dc.retire(); }
        auto* file = animation_file_ref();
        auto* table = reinterpret_cast<const std::int32_t*>(
            reinterpret_cast<const std::uint8_t*>(shot_data) + 0x88);
        const auto displacement = weapon_stone_info(0)->option_script_variant() * 4;
        const auto script = *reinterpret_cast<const std::int32_t*>(
            reinterpret_cast<const std::uint8_t*>(table) + displacement);
        option->handle_dc = file->spawn(nullptr, script, 14, nullptr);
        option->handle_dc.interrupt_offset_7(0);
        option->state_100.focused = player(0)->focused_mode();
    }

    if (((entity_flags.bits >> 1) & 1u) == 0) {
        if (((option->state_100.flags >> 1) & 1u) == 0) {
            // The original falls through its unfocused branch and jumps
            // to the focused (offsets[1]) branch, preserving callback ECX.
            if (!focused_mode()) {
                option->fixed_position = fixed_position_ref() + option->offsets[0];
                if (option->field_120 != 0) {
                    (option->*(option->field_120))();
                }
            } else {
                option->fixed_position = fixed_position_ref() + option->offsets[1];
                if (option->field_11c != 0) {
                    (option->*(option->field_11c))();
                }
            }
        }
    } else {
        option->fixed_position = fixed_position_ref();
        if (static_cast<std::int32_t>(field_20e8) >= 30) {
            option->state = 0;
            cancel_animation_handle(option->handle_dc);
            cancel_animation_handle(option->handle_e0);
            return 0;
        }
    }

    if (option->field_fc == 0) {
        IntPoint diff;
        if (static_cast<std::int32_t>(field_20e4) >= 30) {
            diff = ((option->fixed_position - option->previous_fixed_position) * static_cast<std::int32_t>(field_20e4)) / 100;
            if (diff != 0) {
                option->previous_fixed_position += diff;
            } else {
                option->previous_fixed_position = option->fixed_position;
            }
        }
    } else {
        --option->field_fc;
        option->previous_fixed_position = option->fixed_position;
    }

    option->previous_fixed_position.to_vector3(presentation_position);
    option->handle_dc.set_position(presentation_position);
    option->handle_e0.set_position(presentation_position);
    option->previous_position = presentation_position;
    return 0;
}
}
