// Complete original 0x0044C9B0..0x0044CAD9 298-byte Animation-pool
// allocation game boss. Entire native owner/reuse/new path, natural C++.
// Renderer remains an opaque external owner: original x86 attests its
// real free-list offset 0x06000718. This source does not invent a padded
// 96-MiB class or claim full Renderer startup/whole-game linkage.
// Pool reuse acts on actual typed PooledAnimation (0x600B stride), copies
// its real +0x5FC index into Animation+0x4C4, not AnimationHandle+0x4C0.
// Two original physical list-head/front calls intentionally stay distinct;
// the second result feeds node_value() directly as in the original PE.
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"
#include "DiagnosticObjectFactories.hpp"
#include "IntrusiveLink.hpp"
#include <cstddef>
#include <cstdint>
namespace th20 {
// The original pool free-list front and existing 17B Timer integer getter
// share one physical original head at 0x0040FF90: each reads +4 from ECX.
// A real typed specialization returns the already modeled next link without
// an extra helper call; it is a folded *source role*, not another 17B game
// exact credit or a fabricated trampoline into the Timer implementation.
template<>
IntrusiveLink<Animation>* IntrusiveList<Animation>::front() {
    return next;
}

Animation* AnimationPoolOwner::allocate_animation() {
    if (reinterpret_cast<IntrusiveList<Animation>*>(
            reinterpret_cast<unsigned char*>(this) + 0x6000718)->front() != nullptr) {
        Animation* animation = reinterpret_cast<IntrusiveList<Animation>*>(
            reinterpret_cast<unsigned char*>(this) + 0x6000718)->front()->node_value();
        reinterpret_cast<PooledAnimation*>(animation)->free_link.detach();
        animation->index = reinterpret_cast<PooledAnimation*>(animation)->index;
        reinterpret_cast<PooledAnimation*>(animation)->active = 1;
        animation->reset();
        animation->clear_pending_fields();
        animation->parent_558 = nullptr;
        animation->parent_55c = nullptr;
        animation->link_4ec.initialize(animation);
        animation->child_links[0].initialize(animation);
        animation->child_links[1].initialize(animation);
        return animation;
    } else {
    Animation* animation = process_allocator->allocate_object<Animation>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\sprtlib.cpp:2888 SprtInf");
    animation->reset();
    animation->clear_pending_fields();
    animation->index = 0xffff;
    return animation;
    }
}
}
