#include "AnimationFile.hpp"
#include "Animation.hpp"

namespace th20 {

// Zero-storage derived ABI view over the original AnimationFile receiver.
// The inherited base remains at offset zero; no file object or layout changes.
struct NativeAnimationFileSpriteApplyView : AnimationFile {
    std::int32_t apply_sprite(Animation* animation,std::int32_t sprite_index);
};
extern const float native_256;
static_assert(sizeof(NativeAnimationFileSpriteApplyView)==sizeof(AnimationFile));

std::int32_t NativeAnimationFileSpriteApplyView::apply_sprite(
    Animation* animation,std::int32_t sprite_index) {
    if(bytes==nullptr) return -1;
    animation->base.field_20=sprite_index;
    SpriteData* const sprite=this->sprite(sprite_index);
    animation->base.vectors_378[2].x=sprite->u0;
    animation->base.vectors_378[0].x=animation->base.vectors_378[2].x;
    animation->base.vectors_378[3].x=sprite->u1;
    animation->base.vectors_378[1].x=animation->base.vectors_378[3].x;
    animation->base.vectors_378[1].y=sprite->v0;
    animation->base.vectors_378[0].y=animation->base.vectors_378[1].y;
    animation->base.vectors_378[3].y=sprite->v1;
    animation->base.vectors_378[2].y=animation->base.vectors_378[3].y;
    animation->base.vector_398.x=sprite->u1-sprite->u0;
    animation->base.vector_398.y=sprite->v1-sprite->v0;
    animation->base.vector_70.x=sprite->extent_4c;
    animation->base.vector_70.y=sprite->extent_48;
    animation->base.matrix_3b8=identity_matrix;
    animation->base.matrix_3f8=identity_matrix;
    animation->base.matrix_3b8.elements[0][0]=animation->base.vector_70.x/native_256;
    animation->base.matrix_3b8.elements[1][1]=animation->base.vector_70.y/native_256;
    animation->base.matrix_3f8.elements[0][0]=
        (animation->base.vector_70.x/sprite->extent_20)*sprite->scale_50;
    animation->base.matrix_3f8.elements[1][1]=
        (animation->base.vector_70.y/sprite->extent_1c)*sprite->scale_54;
    animation->matrix_57c=animation->base.matrix_3b8;
    animation->base.field_3a8=static_cast<std::int32_t>(sprite->left);
    animation->base.field_3ac=static_cast<std::int32_t>(sprite->top);
    animation->base.field_3b0=static_cast<std::int32_t>(sprite->right);
    animation->base.field_3b4=static_cast<std::int32_t>(sprite->bottom);
    return 0;
}

} // namespace th20
