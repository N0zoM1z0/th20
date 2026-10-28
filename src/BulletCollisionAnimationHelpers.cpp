// Complete native Bullet collision Animation and AnimationHandle protocols.
// Every Animation setter uses real AnimationBase members and genuine flag
// bitfields. Handle interrupt itself reads the value; the const bridge only
// calls the established non-const original member ABI on a live handle.
#include "Animation.hpp"
#include "AnimationHandle.hpp"

namespace th20 {

void Animation::set_collision_color_mode(std::uint8_t value) {
    base.flags.color_mode = value;
}

void Animation::set_base_position(const Vector3& value) {
    base.vector_2c = value;
}

void Animation::set_tint_channels(std::uint8_t red, std::uint8_t green,
                                  std::uint8_t blue, std::uint8_t alpha) {
    base.channels_494.red = red;
    base.channels_494.green = green;
    base.channels_494.blue = blue;
    base.channels_494.alpha = alpha;
}

void __fastcall cancel_animation_handle(const AnimationHandle& handle) {
    const_cast<AnimationHandle&>(handle).interrupt(1);
}
void __fastcall cancel_animation_handle_mode2(const AnimationHandle& handle) {
    const_cast<AnimationHandle&>(handle).interrupt(2);
}
void __fastcall cancel_animation_handle_mode3(const AnimationHandle& handle) {
    const_cast<AnimationHandle&>(handle).interrupt(3);
}
void __fastcall interrupt_animation_mode3(Animation* animation) {
    animation->interrupt(3);
}
} // namespace th20
