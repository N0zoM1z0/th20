// CORE/RECON-990: original whole 35B member forwarding bridge.
// Distinct from AnimationHandle::interrupt at 0x0044EF90; this method
// calls our native exact 261B descendant event/VM path at 0x0044EFC0.
#include "AnimationHandle.hpp"
#include "NativeEventDescendantPoolView.hpp"
namespace th20 {
void AnimationHandle::update_descendants_event_44f0d0(std::int32_t event) {
    reinterpret_cast<NativeEventDescendantPoolView*>(current_animation_pool)->update_descendants_44efc0(value,event);
}
}
