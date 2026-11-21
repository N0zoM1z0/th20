#include "EnemyState.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"

namespace th20 {

void EnemyAnimationLink::clear_flag0_recursively() {
    Animation* animation = current_animation_pool->resolve_handle(handle.value);
    if (!animation)
        return;
    animation->clear_flag0_recursively();
}


} // namespace th20
