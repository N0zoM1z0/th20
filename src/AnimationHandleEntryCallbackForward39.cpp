// Native original 39B Handle callback setter; 56B fallback resolver first,
// then the original full 25B Animation callback field setter at 0x00438A50.
#include "AnimationHandle.hpp"
#include "Animation.hpp"
namespace th20 {
void AnimationHandle::set_entry_callback_forward_44f100(AnimationEntryCallback callback) {
    Animation* receiver=resolve_or_resident_44cf10();
    receiver->set_field_5dc(callback);
}
}
