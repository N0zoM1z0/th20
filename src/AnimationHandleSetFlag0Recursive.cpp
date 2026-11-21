#include "AnimationHandleSetFlag0Recursive.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"

namespace th20 {

void __fastcall set_animation_handle_flag0_recursively(AnimationHandle* handle) {
    Animation* animation = current_animation_pool->resolve_handle(handle->value);
    if (!animation)
        return;
    animation->set_flag0_recursively();
}

} // namespace th20
