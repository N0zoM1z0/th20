#include "AnimationHandle.hpp"

namespace th20 {

AnimationHandle::AnimationHandle() noexcept : value(0) {}

void AnimationHandle::operator=(std::uint32_t input) { value = input; }
} // namespace th20
