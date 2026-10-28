#include "AnimationHandle.hpp"
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"

namespace th20 {

AnimationHandle::AnimationHandle() noexcept : value(0) {}

void AnimationHandle::operator=(std::uint32_t input) { value = input; }

Animation* AnimationHandle::find_child(std::int32_t identifier, std::int32_t ordinal) {
    Animation* animation = resolve();
    Animation* result;
    if (animation) result = animation->find_child(identifier, ordinal);
    else result = nullptr;
    return result;
}

// Original 45-byte member validity: full resolve() (including stale-ID
// clearing) is observed, and the returned pointer is tested for null.
bool AnimationHandle::is_valid() {
    return resolve() != nullptr;
}

// The native 26-byte wrapper forwards the live position through the
// actual AnimationHandle member position setter. This is not an alias
// for the underlying setter's separate original physical entry.
void AnimationHandle::set_position_forward(const Vector3& position) {
    set_position(position);
}

// Native 35-byte bridge from a four-byte AnimationHandle to the
// genuine pool owner's two-argument handle/event interruption protocol.
void AnimationHandle::interrupt(std::int32_t event) {
    current_animation_pool->interrupt_handle(value, event);
}

void AnimationHandle::interrupt_offset_7(std::int32_t event) {
    interrupt(static_cast<std::int32_t>(static_cast<std::uint32_t>(event) + 7u));
}
} // namespace th20
