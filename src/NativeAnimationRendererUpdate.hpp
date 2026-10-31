#pragma once
// Two adjacent original renderer update methods. Both 150B/164B
// wrappers are strict exact; their complete 508B/511B list-walking C++
// sources remain NONEXACT solely at the shared MSVC 10B list preclear ABI.
#include "AnimationRuntimeOwner.hpp"
#include "IntrusiveLink.hpp"
namespace th20 {
class Animation;
struct NativeSpawnRendererView;
void __fastcall animation_list_update_449870(IntrusiveList<Animation>* list);
int __fastcall animation_renderer_update_4497d0(AnimationPoolOwner* pool);
int __cdecl animation_renderer_update_if_running_450880(AnimationPoolOwner* pool);
void __fastcall animation_list_update_secondary_449b20(NativeSpawnRendererView* renderer);
int __fastcall animation_renderer_update_secondary_449a70(AnimationPoolOwner* pool);
}
