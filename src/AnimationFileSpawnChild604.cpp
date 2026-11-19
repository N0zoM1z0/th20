#include "AnimationFile.hpp"
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "LockRegistry.hpp"
#include "NativeSpawnRendererView.hpp"
#include <mutex>

namespace th20 {

AnimationHandle AnimationFile::spawn_child(std::int32_t script,Animation* parent,std::uint32_t flags) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(9));
    ++field_68;
    Animation* const animation=current_animation_pool->allocate_animation();
    const std::uint32_t renderer_value=parent->field_4e8;
    animation->base.field_14=parent->base.field_14;
    animation->base.flags.word_04|=0x200u;
    animation->vector_5bc=Vector3(0.0f,0.0f,0.0f);
    animation->field_4e8=renderer_value;
    if((flags&4u)!=0) animation->base.flags.word_04|=0x40000u;
    else animation->base.flags.word_04&=~0x40000u;
    bind_animation(animation,script,parent);
    AnimationHandle result;
    animation->field_574=flags;
    if(renderer_value!=0) {
        if((flags&4u)!=0 && (flags&2u)!=0) {
            result=reinterpret_cast<NativeSpawnRendererView*>(renderer_value)->spawn_flag6_44b890(animation);
            animation->base.flags.bits_08.mode=0;
        } else if((flags&4u)!=0) {
            result=reinterpret_cast<NativeSpawnRendererView*>(renderer_value)->spawn_flag4_44b8e0(animation);
            animation->base.flags.bits_08.mode=0;
        } else if((flags&2u)!=0) {
            result=reinterpret_cast<NativeSpawnRendererView*>(renderer_value)->spawn_flag2_44b840(animation);
        } else {
            result=reinterpret_cast<NativeSpawnRendererView*>(renderer_value)->spawn_normal_44b7f0(animation);
        }
    }
    parent->child_links[1].insert_after(&animation->child_links[0]);
    return result;
}

} // namespace th20
