// Native AnimationHandle retirement and recursive pool-owned subtree marking.
// Original handle index and pool owner have distinct, observed lifetimes.
#include "AnimationHandle.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"

namespace th20 {

void AnimationPoolOwner::mark_animation_tree_for_retirement(Animation* animation) {
    if (!animation) return;
    animation->field_570 = 1;
    if (animation->child_links[1].next_value()) {
        IntrusiveLink<Animation>* children = animation->child_links[1].next_value();
        IntrusiveIterator<Animation> iterator = children->begin();
        IntrusiveIterator<Animation>* end = children->end();
        for (; iterator.differs(end); iterator.advance()) {
            IntrusiveLink<Animation>* link = iterator.get();
            mark_animation_tree_for_retirement(link->node_access());
        }
    }
}

void AnimationPoolOwner::retire_handle(std::uint32_t index) {
    Animation* animation = resolve_handle(index);
    mark_animation_tree_for_retirement(animation);
}

void AnimationHandle::retire() {
    current_animation_pool->retire_handle(value);
    value = 0;
}

} // namespace th20
