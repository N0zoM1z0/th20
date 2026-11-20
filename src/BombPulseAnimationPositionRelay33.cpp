// Native 0x00450320 Animation* receiver delegates to the real pool.
#include "NativeBombPulseAnimationCallbacks.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"
namespace th20 {
void NativeAnimationPositionRelayView::set_position_forward_450320(const Vector3& position) {
    reinterpret_cast<NativeAnimationPoolPositionView*>(current_animation_pool)->set_animation_position_4502f0(
        reinterpret_cast<Animation*>(this),position);
}
}
