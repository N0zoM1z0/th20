// Original complete 662-byte game-owned Bullet cancellation path. Genuine
// AnimationHandle return objects, distinct handle-mode forwarders, actual
// context effects, positional sound, item drops and float Timer assignments.
#include "Bullet.hpp"
#include "Animation.hpp"
#include "ItemResourceOwners.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "ClockScalar.hpp"
#include "SoundInf.hpp"

namespace th20 {
extern const float native_one;

void __fastcall cancel_animation_handle(const AnimationHandle& handle);
void __fastcall cancel_animation_handle_mode3(const AnimationHandle& handle);

std::int32_t Bullet::cancel(std::int32_t mode) {
    const std::int32_t original_view=view_index;
    current_animation_pool->select_view(view_index);
    animation->activate_display(1);
    cancel_animation_handle(animation_handle);
    if (((flags.bits >> 9)&1u)==0) {
        if (cancel_script>=0) {
            BulletController* owner=context->bullet_controller();
            AnimationFile* file=context->bullet_controller()->animation_file();
            const std::int32_t script_id=cancel_script;
            const std::uint32_t value=file->spawn("bullet",script_id,position,0.0f,-1,nullptr).value;
            const std::uint32_t handle_copy=value;
            const std::int32_t index_copy=index;
            owner->store_cancel_handle(index_copy,handle_copy);
            if (((flags.bits >> 11)&3u)==1) {
                cancel_animation_handle_mode3(context->bullet_controller()->get_cancel_handle(index));
            }
            if (((flags.bits >> 11)&3u)==2) {
                EffectParameters parameters;
                parameters.vector_00=position;
                parameters.vector_00.z=0.0f;
                parameters.color.value=color.value;
                context->effect_info()->spawn_effect(4,parameters,0);
            }
        }
        process_sound.request_effect_at(0x47,position.x);
        cancel_drops(position,mode);
    }
    position += (velocity * static_cast<float>(default_timer_clock)) / 2.0f;
    state=4;
    timer_4d8 = native_one;
    timer_4e8 = native_one;
    timer_4f8=0;
    current_animation_pool->select_view(original_view);
    return 0;
}
}
