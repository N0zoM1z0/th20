// Complete original AnimationHandle comparison and position protocol.
// Uses the real four-byte handle, external Renderer handle resolution and
// the original full Animation Vector3 position value owner at +0x5BC.
#include "AnimationHandle.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"
#include "Vector3.hpp"
namespace th20 {
bool AnimationHandle::operator!=(std::uint32_t input) const {
    return value != input;
}
void AnimationHandle::set_position(const Vector3& position) {
    current_animation_pool->set_handle_position(value,position);
}
// Entire native 246-byte pool-owned animation interruption, including
// the original exception-safe IntrusiveIterator lifetime and child walk.
// Resolves the handle through the real separate pool resolver; an invalid
// handle exits before iterator construction. Each child receives the
// original integer interruption event; the 456B handle resolver is
// independently WHOLE STRICT EXACT, not an unresolved helper.
void AnimationPoolOwner::interrupt_handle(std::uint32_t index, std::int32_t event) {
    Animation* animation = resolve_handle(index);
    if (!animation) return;
    {
        auto& children = animation->child_links[1];
        IntrusiveIterator<Animation> iterator = children.begin();
        IntrusiveIterator<Animation>* end = children.end();
        for (; iterator.differs(end); iterator.advance()) {
            IntrusiveLink<Animation>* link = iterator.get();
            link->node_access()->interrupt(event);
        }
    }
}

void AnimationPoolOwner::set_handle_position(std::uint32_t index,const Vector3& position) {
    Animation* animation = resolve_handle(index);
    if (animation == nullptr) return;
    animation->vector_5bc = position;
}
}
