// Four independently native-exact renderer enqueue and handle-registration
// functions sharing one original two-list owner with AnimationFile::spawn.
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "IntrusiveLink.hpp"
#include "AnimationHandle.hpp"
#include "NativeSpawnRendererView.hpp"
#include <cstdint>
namespace th20 {
struct NativeRendererPoolRegister : AnimationPoolOwner {
    AnimationHandle register_44c8f0(Animation* anim);
};
AnimationHandle NativeSpawnRendererView::spawn_normal_44b7f0(Animation* anim) {
    anim->field_4e8=reinterpret_cast<std::uintptr_t>(this);
    auto* const list=&main;
    list->append(&anim->link_4ec);
    return reinterpret_cast<NativeRendererPoolRegister*>(current_animation_pool)->register_44c8f0(anim);
}
AnimationHandle NativeSpawnRendererView::spawn_flag2_44b840(Animation* anim) {
    anim->field_4e8=reinterpret_cast<std::uintptr_t>(this);
    auto* const list=&main;
    list->prepend(&anim->link_4ec);
    return reinterpret_cast<NativeRendererPoolRegister*>(current_animation_pool)->register_44c8f0(anim);
}
AnimationHandle NativeSpawnRendererView::spawn_flag4_44b8e0(Animation* anim) {
    anim->field_4e8=reinterpret_cast<std::uintptr_t>(this);
    auto* const list=&secondary;
    list->append(&anim->link_4ec);
    return reinterpret_cast<NativeRendererPoolRegister*>(current_animation_pool)->register_44c8f0(anim);
}
AnimationHandle NativeSpawnRendererView::spawn_flag6_44b890(Animation* anim) {
    anim->field_4e8=reinterpret_cast<std::uintptr_t>(this);
    auto* const list=&secondary;
    list->prepend(&anim->link_4ec);
    return reinterpret_cast<NativeRendererPoolRegister*>(current_animation_pool)->register_44c8f0(anim);
}
}
