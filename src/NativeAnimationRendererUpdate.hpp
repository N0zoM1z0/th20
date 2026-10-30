#pragma once
// Two adjacent original renderer update methods. The 150B wrapper is whole
// exact; its 508B list-walking callee remains under separate reconstruction.
#include "AnimationRuntimeOwner.hpp"
#include "IntrusiveLink.hpp"
namespace th20 {
class Animation;
void __fastcall animation_list_update_449870(IntrusiveList<Animation>* list);
int __fastcall animation_renderer_update_4497d0(AnimationPoolOwner* pool);
}
