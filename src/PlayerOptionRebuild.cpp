// Whole original Player option rebuild state machine: source-present but
// NONEXACT. Native original 0x004FACA0 covers 1,518B and 418 instructions.
// The table words at +0x88/+0xA8 in the shot-data resource are observed, but
// their enclosing serialized metadata schema is not yet established.
// Never give this parent whole-native exact credit from length alone.
#include "Player.hpp"
#include "PlayerRecord.hpp"
#include "WeaponStoneInfo.hpp"
#include "ShotData.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Session.hpp"

namespace th20 {
void __fastcall cancel_animation_handle(const AnimationHandle&);
void __fastcall clear_animation_handle_value(AnimationHandle&);

void Player::rebuild_option_animations(std::int32_t requested_count) {
    current_animation_pool->select_view(view_index);
    shots.set_flag0(1);

    if (requested_count < 0) {
        requested_count = context->player_record()->available_option_count();
    }
    const std::int32_t count = context->player_record()->available_option_count();
    if (context->player_record()->clamped_option_units() >=
        context->player_record()->clamped_option_cap()) {
        PlayerOption* option = &options.at(0);
        for (std::int32_t i=0; i<count; ++i,++option) {
            option->handle_e0.retire();
            if (context->player()->animation_file_ref() != nullptr) {
                AnimationFile* file = context->player()->animation_file_ref();
                // The shot-data script tables at +0xA8 are not yet
                // semantically classified in the maintained file schema.
                // Original early resource branch uses the independent +0xA8
                // script-table base before computing the index displacement.
                const std::int32_t* script_table = reinterpret_cast<const std::int32_t*>(reinterpret_cast<const std::uint8_t*>(shot_data) + 0xA8);
                const std::int32_t displacement = weapon_stone_info(0)->option_script_variant() * 4;
                const std::int32_t script = *reinterpret_cast<const std::int32_t*>(reinterpret_cast<const std::uint8_t*>(script_table)+displacement);
                option->handle_e0.value = file->spawn_flag2(nullptr,script,-1,nullptr).value;
            }
            option->handle_e0.resolve()->vector_5bc_ref().y = -999.0f;
        }
    } else {
        PlayerOption* option = &options.at(0);
        for (std::uint32_t i=0; i<10; ++i,++option) {
            cancel_animation_handle(option->handle_e0);
            clear_animation_handle_value(option->handle_e0);
        }
    }

    if (context->player()->active_option_count() != count) {
        PlayerOption* option = &options.at(0);
        std::uint32_t i=0;
        for (; static_cast<std::int32_t>(i)<count; ++i,++option) {
            option->state_100.focused = player(0)->focused_mode();
            option->handle_dc.retire();
            option->field_f8 = i;

            IntPoint& first_dest = option->offsets[0];
            first_dest.assign_scaled(*context->weapon_stone_info()->unfocused_offset(count,i));
            IntPoint& second_dest = option->offsets[1];
            second_dest.assign_scaled(*context->weapon_stone_info()->focused_offset(count,i));

            const IntPoint& player_position = context->player()->fixed_position_ref();
            const IntPoint* offset;
            if (context->player()->focused_mode()) {
                offset = &options.at(i).offsets[1];
            } else {
                offset = &options.at(i).offsets[0];
            }
            // The original function uses an eight-byte aligned stack frame;
            // the real aggregate result is used in both position stores.
            alignas(8) IntPoint new_position = player_position + *offset;
            options.at(i).fixed_position = new_position;
            option->previous_fixed_position = option->fixed_position;

            AnimationFile* file = context->player()->animation_file_ref();
            // The original indexes by a 4-byte displacement after first
            // taking the shot-data script-table base, not by direct SIB form.
            const std::int32_t* script_table = reinterpret_cast<const std::int32_t*>(reinterpret_cast<const std::uint8_t*>(shot_data) + 0x88);
            const std::int32_t displacement = weapon_stone_info(0)->option_script_variant() * 4;
            const std::int32_t script = *reinterpret_cast<const std::int32_t*>(reinterpret_cast<const std::uint8_t*>(script_table)+displacement);
            option->handle_dc.value = file->spawn(nullptr,script,14,nullptr).value;
            option->handle_dc.resolve()->vector_5bc_ref().y = -999.0f;
            option->state=2;
            option->field_108=0;
            option->state_100.flags &= ~2u;
            option->field_10c=0;
            weapon_stone_info(0)->initialize_option_pair(option,i);
        }
        for (; i<10; ++i,++option) {
            option->state=0;
            option->field_108=0;
            cancel_animation_handle(option->handle_dc);
        }
        field_680=count;
        context->player()->set_option_field_fc(1);
    }
    PlayerOption* option = &secondary_options.at(0);
    for (std::uint32_t i=0;i<12;++i,++option) {
        option->state=0;
        option->field_108=0;
        option->state_100.flags &= ~2u;
    }
}
} // namespace th20
