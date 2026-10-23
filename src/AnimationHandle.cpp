#include "AnimationHandle.hpp"

namespace th20 {

AnimationHandle::AnimationHandle() noexcept : value(0) {}

void AnimationHandle::operator=(std::uint32_t input) { value = input; }

void AnimationHandle::interrupt_offset_7(std::int32_t event) {
    interrupt(static_cast<std::int32_t>(static_cast<std::uint32_t>(event) + 7u));
}
} // namespace th20
