// Complete-function, NONEXACT source frontier for the game-owned
// Player option rebuild state machine at original 0x004FACA0 (1,518B).
// Script words at +0x88 and +0xA8 in the actual PlayerShotData resource are
// observed, but the enclosing serialized resource schema is not established.
// This source is not a canonical native match or a finished game runtime.
#include "Player.hpp"
#include "PlayerRecord.hpp"
#include "WeaponStoneInfo.hpp"
#include "ShotData.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Session.hpp"

namespace th20 {
extern const float native_minus_999;
void __fastcall cancel_animation_handle(const AnimationHandle&);

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
                const std::int32_t variant = weapon_stone_info(0)->option_script_variant();
                const std::int32_t script = reinterpret_cast<const std::int32_t*>(shot_data)[0xA8/4+variant];
                option->handle_e0.value = file->spawn_flag2(nullptr,script,-1,nullptr).value;
            }
            Animation* animation = option->handle_e0.resolve();
            animation->vector_5bc_ref().y = native_minus_999;
        }
    } else {
        PlayerOption* option = &options.at(0);
        for (std::uint32_t i=0; i<10; ++i,++option) {
            cancel_animation_handle(option->handle_e0);
            option->handle_e0.value = 0;
        }
    }

    if (context->player()->active_option_count() != count) {
        PlayerOption* option = &options.at(0);
        std::uint32_t i=0;
        for (; static_cast<std::int32_t>(i)<count; ++i,++option) {
            option->state_100.focused = player(0)->focused_mode();
            option->handle_dc.retire();
            option->field_f8 = i;

            const Vector2* unfocused = context->weapon_stone_info()->unfocused_offset(count,i);
            option->offsets[0].assign_scaled(*unfocused);
            const Vector2* focused = context->weapon_stone_info()->focused_offset(count,i);
            option->offsets[1].assign_scaled(*focused);

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

            if (context->player()->animation_file_ref() != nullptr) {
                AnimationFile* file = context->player()->animation_file_ref();
                const std::int32_t variant = weapon_stone_info(0)->option_script_variant();
                const std::int32_t script = reinterpret_cast<const std::int32_t*>(shot_data)[0x88/4+variant];
                option->handle_dc.value = file->spawn(nullptr,script,14,nullptr).value;
            }
            Animation* animation = option->handle_dc.resolve();
            animation->vector_5bc_ref().y = native_minus_999;
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
