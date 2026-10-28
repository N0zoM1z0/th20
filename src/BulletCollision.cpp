// Complete original 2,018-byte Bullet collision/graze lifecycle, using
// true typed Player circle/rectangle collisions, real animation handle
// hidden results, time-gated graze rewards, player hit effects and fade.
#include "Bullet.hpp"
#include "Player.hpp"
#include "PlayerRecord.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "ItemResourceOwners.hpp"
#include "BulletCollisionHandle.hpp"
#include "ClockScalar.hpp"
#include "GameRandom.hpp"
#include "WeaponStoneInfo.hpp"
#include "Weapon.hpp"
#include "SoundInf.hpp"

namespace th20 {
extern const Vector3 native_zero_position;
extern const float native_zero, native_one;
extern GameRandom process_bullet_random, process_bullet_visual_random;
PlayerRecord* player_record(std::int32_t index);
void __fastcall cancel_animation_handle_mode2(const AnimationHandle& handle);
void __fastcall cancel_animation_handle_mode3(const AnimationHandle& handle);
void __fastcall interrupt_animation_mode3(Animation* animation);

std::int32_t Bullet::process_collision(std::int32_t mode) {
    std::int32_t result = 0;
    std::int32_t converted_graze = 0;
    animation->set_collision_color_mode(0);
    animation->set_base_position(native_zero_position);
    if (((flags.bits >> 1) & 1u) != 0) {
      if (size.x > native_zero) {
    timer_4d8 = native_one;
    if (((flags.bits >> 6) & 1u) == 0) {
        if (((flags.bits >> 4) & 1u) == 0) {
            Player* target = context->player();
            result = target->collision_rectangle(position,size,mode);
        } else {
            Player* target = context->player();
            float unscaled_radius = size.x;
            result = target->collision_circle(position,unscaled_radius,mode);
        }
    } else if (((flags.bits >> 4) & 1u) == 0) {
        Vector2 extent = size * scale;
        Player* target = context->player();
        result = target->collision_rectangle(position,extent,mode);
    } else {
        Player* target = context->player();
        float radius = size.x * scale;
        result = target->collision_circle(position,radius,mode);
    }
    if (converted_graze != 0 && result == 0) result = 2;
    if (result == 0) {
        timer_4c0++;
        if (timer_4c0.at_least(60) && field_4d4 == 0) {
            field_4d4 = 3;
            timer_4a0 = 0;
        }
    }
    if (result == 1 && field_18 == 0) {
    hit_effect:
        state = 3;
        animation->interrupt(1);
        if (bullet_animation_handle_valid(animation_handle) != 0) {
            animation_handle.interrupt(1);
        }
        if (cancel_script >= 0) {
            AnimationFile* file = context->bullet_controller()->animation_file();
            const std::int32_t script = cancel_script;
            Animation* effect_animation = file->spawn(nullptr,script,position,0.0f,-1,nullptr).resolve();
            if (((flags.bits >> 11) & 3u) == 1) {
                interrupt_animation_mode3(effect_animation);
            }
            Vector3 animation_offset = (velocity * static_cast<float>(default_timer_clock)) * 10.0f;
            effect_animation->interpolate_position(30,6,native_zero_position,animation_offset);
            if (((flags.bits >> 11) & 3u) == 2) {
                EffectParameters effect;
                effect.vector_00 = position;
                effect.color.value = color.value;
                context->effect_info()->spawn_effect(4,effect,0);
            }
        }
    } else {
        if (result == 2) {
        if (field_4d4 != 0) {
            if (timer_4a0.every(static_cast<std::int32_t>(field_4d0))) {
                Player* target = context->player();
                std::uint32_t graze_color = color.get();
                target->record_bullet_graze(position,graze_color);
                timer_4a0 = 0;
                --field_4d4;
                if (player_record(0)->graze_enabled()) {
                    player_record(0)->add_bullet_graze(1);
                    if (player_record(0)->bullet_graze_count() > 22 && field_18 == 0) {
                        weapon_stone_info(0)->passive_weapon()->set_passive(1);
                        if (player_record(0)->field_2f_value() != 0) {
                            PlayerRecord* r=player_record(0);
                            std::uint32_t choice=process_bullet_random.next() % 10 + 7;
                            r->set_bullet_graze(choice);
                        } else {
                            PlayerRecord* r=player_record(0);
                            std::uint32_t choice=process_bullet_random.next() % 10;
                            r->set_bullet_graze(choice);
                        }
                        goto hit_effect;
                    }
                }
            }
        }
        timer_4a0++;
        timer_4b0++;
        timer_4c0 = 0;
        if (((command_flags.words.high >> 1) & 1u) == 0) {
            if (timer_4b0.at_most(1)) cancel_animation_handle_mode2(animation_handle);
            std::int32_t alpha = 208 - (timer_4b0 * 2);
            if (alpha > 255) alpha = 255;
            if (alpha < 96) alpha = 96;
            animation->set_collision_color_mode(1);
            animation->set_tint_channels(0xff,static_cast<std::uint8_t>(alpha),0x80,0xff);
            const float y = process_bullet_visual_random.signed_range(native_one);
            const float x = process_bullet_visual_random.signed_range(native_one);
            Vector3 random_offset(x,y,0.0f);
            animation->set_base_position(random_offset);
        }
        } else {
            if (timer_4b0 != 0) cancel_animation_handle_mode3(animation_handle);
            timer_4b0 = 0;
        }
    }
      }
    }
    return result;
}
} // namespace th20
