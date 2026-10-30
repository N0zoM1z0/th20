#pragma once
// Zero-extra-storage original Animation/Pool views for native 308B pool
// retirement and its 82B geometry /90B membership/23B array-index helpers.
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"
#include <array>
#include <cstdint>
namespace th20 {
struct NativeAnimationGeometryReleaseView : Animation {
    void release_geometry_44c5f0();
};
struct NativeAnimationPoolRecordView : AnimationPoolOwner {
    int belongs_to_pool_44d970(Animation* animation);
};
static_assert(sizeof(NativeAnimationGeometryReleaseView)==sizeof(Animation));
#if defined(_M_IX86)
static_assert(sizeof(PooledAnimation)==0x600);
#endif
}
