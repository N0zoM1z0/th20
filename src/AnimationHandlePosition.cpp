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
void AnimationPoolOwner::set_handle_position(std::uint32_t index,const Vector3& position) {
    Animation* animation = resolve_handle(index);
    if (animation == nullptr) return;
    animation->vector_5bc = position;
}
}
