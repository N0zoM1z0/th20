#include "AnimationHandle.hpp"
#include "Animation.hpp"

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

void AnimationHandle::interrupt_offset_7(std::int32_t event) {
    interrupt(static_cast<std::int32_t>(static_cast<std::uint32_t>(event) + 7u));
}
} // namespace th20
