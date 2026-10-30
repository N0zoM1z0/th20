// Original full 1486B/372-i386 rotated corner projection Boss.
// The real nested lifetime after Angle construction produces an original
// +0x41 compiler NOP naturally; no machine padding, asm or PE edits.
// Original 96-byte corner axis table is owned by AnimationCornerAxisTable.
#include "AnimationCornerProjectionOwner.hpp"
#include "AnimationFile.hpp"
#include "WindowState.hpp"
#include "Angle.hpp"
#include "ScalarMath.hpp"
#include "Vector2.hpp"
#include <cstdint>
namespace th20 {
void __cdecl animation_shape_xy(Vector2&,float,float,float,float,float,float);
extern const float native_half;

void NativeAnimationCornerProjector::project_rotated_corners_43ef20(
        Animation* animation, Vector3* a, Vector3* b, Vector3* c, Vector3* d) {
    SpriteData* const sprite=animation->sprite_data();
    Angle angle(animation->rotation_sum().z+sprite->field_34);
    {
    const float sine=scalar_math::sine(static_cast<float>(angle));
    const float cosine=scalar_math::cosine(static_cast<float>(angle));
    const float* x_offsets=native_quad_axis_layout[0].corners[animation->base.flags.word_10];
    const float* y_offsets=native_quad_axis_layout[1].corners[animation->base.flags.word_14];
    const float offset_x=sprite->field_24-animation->base.vector_80.x;
    const float offset_y=sprite->field_28-animation->base.vector_80.y;
    float scale_x=animation->base.vector_50.x*animation->base.vector_58.x;
    float scale_y=animation->base.vector_50.y*animation->base.vector_58.y;
    if (animation->parent_55c && ((animation->base.flags.word_04>>12)&1)==0) {
        scale_x=animation->parent_55c->base.vector_50.x*animation->parent_55c->base.vector_58.x*scale_x;
        scale_y=animation->parent_55c->base.vector_50.y*animation->parent_55c->base.vector_58.y*scale_y;
    }
    if (animation->base.flags.field_0c==1 || animation->base.flags.field_0c==5) {
        scale_x=scale_x*window_state.scale;
        scale_y=scale_y*window_state.scale;
    } else if (animation->base.flags.field_0c==2 || animation->base.flags.field_0c==6) {
        scale_x=window_state.scale*native_half*scale_x;
        scale_y=window_state.scale*native_half*scale_y;
    }
    float xs[4],ys[4];
    xs[0]=(x_offsets[0]*animation->base.vector_70.x-offset_x)*sprite->field_2c*scale_x;
    ys[0]=(y_offsets[0]*animation->base.vector_70.y-offset_y)*sprite->field_30*scale_y;
    xs[1]=(x_offsets[1]*animation->base.vector_70.x-offset_x)*sprite->field_2c*scale_x;
    ys[1]=(y_offsets[1]*animation->base.vector_70.y-offset_y)*sprite->field_30*scale_y;
    xs[2]=(x_offsets[2]*animation->base.vector_70.x-offset_x)*sprite->field_2c*scale_x;
    ys[2]=(y_offsets[2]*animation->base.vector_70.y-offset_y)*sprite->field_30*scale_y;
    xs[3]=(x_offsets[3]*animation->base.vector_70.x-offset_x)*sprite->field_2c*scale_x;
    ys[3]=(y_offsets[3]*animation->base.vector_70.y-offset_y)*sprite->field_30*scale_y;
    animation->position(*d);
    animation_shape_xy(*reinterpret_cast<Vector2*>(a),xs[0],ys[0],sine,cosine,d->x,d->y);
    animation_shape_xy(*reinterpret_cast<Vector2*>(b),xs[1],ys[1],sine,cosine,d->x,d->y);
    animation_shape_xy(*reinterpret_cast<Vector2*>(c),xs[2],ys[2],sine,cosine,d->x,d->y);
    animation_shape_xy(*reinterpret_cast<Vector2*>(d),xs[3],ys[3],sine,cosine,d->x,d->y);
    const float z=animation->base.vector_2c.z+animation->vector_5bc.z+animation->base.vector_484.z;
    d->z=z;
    c->z=z;
    b->z=z;
    a->z=z;
    }
}
}
