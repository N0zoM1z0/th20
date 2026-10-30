#pragma once
// Native original 108B/127B child-Handle lookup chain using actual Animation
// and AnimationHandle storage. These are zero-extra-storage ABI views.
#include "Animation.hpp"
#include "AnimationHandle.hpp"
namespace th20 {
struct NativeAnimationHandleLookupView : Animation {
    AnimationHandle find_child_handle_44c830(int identifier, int ordinal);
};
struct NativeAnimationHandleForwardView : AnimationHandle {
    AnimationHandle find_child_handle_44c7b0(int identifier, int ordinal);
};
static_assert(sizeof(NativeAnimationHandleLookupView)==sizeof(Animation));
static_assert(sizeof(NativeAnimationHandleForwardView)==sizeof(AnimationHandle));
}
