// Native 0x00478380 entry callback: delegate's empty C++ receiver is genuine.
#include "NativeBombPulseViews.hpp"
#include "NativeBombPulseAnimationCallbacks.hpp"
namespace th20 {
std::int32_t __cdecl bomb_pulse_animation_callback_478380(Animation* animation) {
    NativeBombPulseAnimationDelegate delegate;
    return delegate.update_478610(animation);
}
}
