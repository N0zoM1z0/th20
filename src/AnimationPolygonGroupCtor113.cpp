// Original 113B polygon Motion group ctor. Genuine AnimationCallback base,
// real std::array<three segment> member, Timer and Vector3 initialization.
#include "NativePolygonMotionGroup.hpp"
namespace th20 {
NativePolygonMotionGroup::NativePolygonMotionGroup(Animation* owner)
    : AnimationCallback(owner), control_b84_float(0.0f), timer_b88(),
      value_b98(nullptr), saved_position_b9c(), use_animation_position_ba8(1) {
    // Native +0xB84 is initialized as a real float member.
}
// The generated 49B deleting wrapper is whole exact; ordinary destructor
// still emits 29B vs original 20B and is NOT an accepted native unit.
NativePolygonMotionGroup::~NativePolygonMotionGroup() = default;
} // namespace th20
