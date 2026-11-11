#include "IntrusiveListAnimation.hpp"
#pragma once
// Both the original 411B recursive renderer retirement queue and its
// 508B/511B exact Renderer-list callers share this non-owning pool view.
#include "AnimationRuntimeOwner.hpp"
#include "IntrusiveLink.hpp"
namespace th20 {
class Animation;
struct NativeAnimationRetirePoolView : AnimationPoolOwner {
    void queue_retired_animation_44f840(Animation* animation,
                                         IntrusiveList<Animation>* pending);
};
}
