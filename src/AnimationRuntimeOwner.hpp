#pragma once
#include <cstdint>

namespace th20 {
class Animation;
struct Vector3;
class AnimationFile;
// Only the independently observed external ABI is declared here. The
// Renderer/Animation owner layout, allocation and original spelling remain
// unresolved; its pointer is published by native startup at 0x005C0028.
// Keep one definition across separate native callers rather than inventing
// different classes with coincidentally equivalent calling conventions.
struct AnimationPoolOwner {
    std::int32_t release_animation(Animation* animation);
    void select_draw_layer(std::int32_t layer, std::int32_t view_index);
    std::int32_t draw(Animation* animation);
    void flush_draws();
    // Original 298B pool allocate/reuse boss is now entire native exact
    // in AnimationPoolAllocate.cpp; the full Renderer owner layout and
    // complete executable linkage remain separate reconstruction tasks.
    Animation* allocate_animation();
    // Original 21B pool-owner wrapper at 0x00435500 invokes the
    // complete, still nonexact 39,470B Animation VM on this instance.
    std::int32_t update_animation(Animation* animation);
    AnimationFile* file_by_index(std::int32_t index);
    void select_view(std::int32_t view_index);
    Animation* resolve_handle(std::uint32_t index);
    // Native 246-byte pool-owner interruption: handle ID then event code.
    // The whole 456-byte resolve_handle remains a separate open function.
    void interrupt_handle(std::uint32_t index, std::int32_t event);
    void set_handle_position(std::uint32_t index, const Vector3& position);
};
extern AnimationPoolOwner* current_animation_pool;
} // namespace th20
