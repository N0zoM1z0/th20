// Original 0x00450850 live animation-handle owner forwarding wrapper.
#include "NativeBombPulseViews.hpp"
#include "Animation.hpp"
namespace th20 {
void NativeBombEffectHandleView::bind_owner_450850(void* owner) {
    resolve_or_resident_44cf10()->user_data=owner;
}
}
