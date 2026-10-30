#pragma once
// Two native 24-byte Animation intrusive lists, used by the full original
// 922B AnimationFile::spawn Boss and four renderer registration helpers.
// Original underlying renderer ownership remains externally unresolved.
#include "AnimationHandle.hpp"
#include "IntrusiveLink.hpp"
#include <cstddef>
namespace th20 {
class Animation;
struct NativeSpawnRendererView {
    IntrusiveList<Animation> main;
    IntrusiveList<Animation> secondary;
    AnimationHandle spawn_normal_44b7f0(Animation* anim);
    AnimationHandle spawn_flag2_44b840(Animation* anim);
    AnimationHandle spawn_flag4_44b8e0(Animation* anim);
    AnimationHandle spawn_flag6_44b890(Animation* anim);
};
static_assert(sizeof(IntrusiveList<Animation>)==0x18);
static_assert(offsetof(NativeSpawnRendererView,secondary)==0x18);
}
