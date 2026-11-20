// Original 0x004502F0 native pool path stores into Animation+0x5BC.
#include "NativeBombPulseAnimationCallbacks.hpp"
#include "Animation.hpp"
namespace th20 {
void NativeAnimationPoolPositionView::set_animation_position_4502f0(Animation* animation,
                                                                     const Vector3& position) {
    animation->vector_5bc=position;
}
}
