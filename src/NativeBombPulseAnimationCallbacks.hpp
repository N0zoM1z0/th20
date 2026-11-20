#pragma once
#include <cstdint>
namespace th20 {
class Animation;
struct Vector3;
// The original entry callback constructs a stateless C++ delegate and
// invokes its member; no artificial storage or instruction bytes exist.
class NativeBombPulseAnimationDelegate {
public:
    std::int32_t update_478610(Animation* animation);
};
struct NativeAnimationPositionRelayView {
    void set_position_forward_450320(const Vector3& position);
};
struct NativeAnimationPoolPositionView {
    void set_animation_position_4502f0(Animation* animation,const Vector3& position);
};
}
