#pragma once
// Non-owning native Renderer/AnimationPool view. Original pool layout beyond
// the three physical offsets below has not been recovered; no giant storage
// or duplicate process allocation is invented here.
#include "AnimationRuntimeOwner.hpp"
#include <cstdint>
namespace th20 {
struct NativeRendererSlot72 { std::uint8_t unclassified_00[0x48]; };
static_assert(sizeof(NativeRendererSlot72)==0x48);
struct NativeRendererPoolSelector {
    void* renderer_index_449490(std::int32_t view);
};
struct NativeSpawnAnimationPoolView : AnimationPoolOwner {
    // Real native +0x6C4 mode preference and +0x6C8 72-byte pool slot array.
    int prefer_alternate_44c8a0();
    void* choose_renderer_44c8c0(int view);
};
}
