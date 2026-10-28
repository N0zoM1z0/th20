#pragma once
#include <cstdint>

namespace th20 {
struct Animation;
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
    AnimationFile* file_by_index(std::int32_t index);
    void select_view(std::int32_t view_index);
    Animation* resolve_handle(std::uint32_t index);
    void set_handle_position(std::uint32_t index, const Vector3& position);
};
extern AnimationPoolOwner* current_animation_pool;
} // namespace th20
