// Entire original native animation-handle resolver and integer validity
// forwarding wrapper, used by the 2018-byte Bullet collision state machine.
#include "BulletCollisionHandle.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"

namespace th20 {
Animation* AnimationHandle::resolve() {
    Animation* animation = current_animation_pool->resolve_handle(value);
    if (animation == nullptr) value = 0;
    return animation;
}
std::int32_t __fastcall bullet_animation_handle_valid(AnimationHandle& handle) {
    return handle.resolve() != nullptr;
}
} // namespace th20
