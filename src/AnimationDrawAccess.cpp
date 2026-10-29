// Original game Animation draw-Boss field access and recursive parent scale.
// These complete native functions are separate children of the 5,993-byte
// renderer/Animation submission dispatcher; their exactness does not make
// that large parent itself exact or establish whole-game linkage.
#include "Animation.hpp"

namespace th20 {

std::uint32_t __fastcall animation_draw_color_490(Animation* animation) {
    return animation->base.color_490;
}

std::uint32_t __fastcall animation_draw_color_494(Animation* animation) {
    return animation->base.color_494;
}

std::uint32_t __fastcall animation_draw_enabled(Animation* animation) {
    return animation->base.flags.bit_10;
}

float __fastcall animation_inherited_aux_scale_x(Animation* animation) {
    float parent_scale = 1.0f;
    if (animation->parent_558 && !((animation->base.flags.word_04 >> 12) & 1u)) {
        parent_scale = animation_inherited_aux_scale_x(animation->parent_558);
    }
    return animation->base.vector_58.x * parent_scale;
}

} // namespace th20
