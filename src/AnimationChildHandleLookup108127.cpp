// Two full original native 108B/127B child AnimationHandle lookups.
// Real hidden return-by-value ABI, original recursive find_child/resolve,
// original zero-Handle fallback. No manual x86, fake NOP or stack padding.
#include "NativeAnimationChildHandleLookup.hpp"
namespace th20 {
AnimationHandle NativeAnimationHandleLookupView::find_child_handle_44c830(int identifier,int ordinal) {
    Animation* const child=find_child(identifier,ordinal);
    if(child) return child->handle;
    AnimationHandle empty;
    empty = 0u;
    return empty;
}
AnimationHandle NativeAnimationHandleForwardView::find_child_handle_44c7b0(int identifier,int ordinal) {
    AnimationHandle empty;
    Animation* child=resolve();
    empty=0u;
    return child ? reinterpret_cast<NativeAnimationHandleLookupView*>(child)->find_child_handle_44c830(identifier,ordinal) : empty;
}
}
