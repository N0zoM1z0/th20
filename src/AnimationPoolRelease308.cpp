// Entire original 308B game-owned AnimationPool retirement.
// Two separate original array-base computations are intentional: the first
// clears active and the second inserts a free link at the head, not append.
// Native physical insert_after has a whole exact 76B folded original body;
// no second 76B game credit and no invented 96MB owner allocation.
#include "NativeAnimationPoolReleaseViews.hpp"
#include "AnimationCallback.hpp"
#include "DiagnosticAllocator.hpp"
#include "Animation.hpp"
#include "IntrusiveLink.hpp"
#include <array>
#include <cstdint>
namespace th20 {
std::int32_t AnimationPoolOwner::release_animation(Animation* animation) {
    if(animation->callback) {
        animation->callback->slot_0c();
        process_allocator->release_object(animation->callback);
        animation->callback=nullptr;
    }
    reinterpret_cast<NativeAnimationGeometryReleaseView*>(animation)->release_geometry_44c5f0();
    animation->link_4ec.detach();
    animation->link_53c.detach();
    animation->parent_558=nullptr;
    animation->parent_55c=nullptr;
    if(reinterpret_cast<NativeAnimationPoolRecordView*>(this)->belongs_to_pool_44d970(animation)) {
        auto& pool=*reinterpret_cast<std::array<PooledAnimation,65536>*>(
            reinterpret_cast<std::uint8_t*>(this)+0x710);
        pool[animation->index].active=0;
        auto* free_list = reinterpret_cast<IntrusiveLink<Animation>*>(
            reinterpret_cast<std::uint8_t*>(this)+0x6000718);
        auto& separate_records = *reinterpret_cast<std::array<PooledAnimation,65536>*>(
            reinterpret_cast<std::uint8_t*>(this)+0x710);
        free_list->insert_after(&separate_records[animation->index].free_link);
        animation->release_resources();
        animation->handle=0;
    } else {
        process_allocator->release_object(animation);
        animation=nullptr;
    }
    return 0;
}
}
