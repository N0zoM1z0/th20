// Complete 21-byte original 0x00435500 renderer-owner update wrapper, native exact.
// The 39,470-byte Animation::update VM itself remains separately NONEXACT.
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"
namespace th20 {
std::int32_t AnimationPoolOwner::update_animation(Animation* animation) {
    return animation->update();
}
}
