// Original 0x00478610 callback adapter transfers Bomb spawn position to ANM.
#include "NativeBombPulseAnimationCallbacks.hpp"
#include "NativeBombPulseViews.hpp"
#include "Animation.hpp"
namespace th20 {
std::int32_t NativeBombPulseAnimationDelegate::update_478610(Animation* animation) {
    reinterpret_cast<NativeAnimationPositionRelayView*>(animation)->set_position_forward_450320(
        reinterpret_cast<NativeBombPulse*>(animation->user_data)->spawn_position);
    return 0;
}
}
