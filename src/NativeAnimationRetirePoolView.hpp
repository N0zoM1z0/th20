#pragma once
// Original 411B renderer retirement queue and the still nonexact 508B
// list-update caller share one non-owning AnimationPoolOwner view.
#include "AnimationRuntimeOwner.hpp"
#include "IntrusiveLink.hpp"
namespace th20 {
class Animation;
struct NativeAnimationRetirePoolView : AnimationPoolOwner {
    void queue_retired_animation_44f840(Animation* animation,
                                         IntrusiveList<Animation>* pending);
};
}
