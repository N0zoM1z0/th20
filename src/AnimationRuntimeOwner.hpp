#pragma once
#include <cstdint>

namespace th20 {
struct Animation;
// Only the independently observed external ABI is declared here. The
// Renderer/Animation owner layout, allocation and original spelling remain
// unresolved; its pointer is published by native startup at 0x005C0028.
// Keep one definition across separate native callers rather than inventing
// different classes with coincidentally equivalent calling conventions.
struct AnimationPoolOwner {
    std::int32_t release_animation(Animation* animation);
    void select_draw_layer(std::int32_t layer, std::int32_t view_index);
    std::int32_t draw(Animation* animation);
};
extern AnimationPoolOwner* current_animation_pool;
} // namespace th20
