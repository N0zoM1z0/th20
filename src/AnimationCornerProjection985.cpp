// Whole original game 985B/233-i386 sprite corner projection strict exact.
// Two genuine typed 3x4 angle-axis arrays and 16B mode indexing, original
// 6 E8 and 13 PE HIGHLOW physical roles and full 985/985 original bytes.
// Original saved ECX receiver is unused; source class name is provisional.
#include "AnimationCornerProjectionOwner.hpp"
#include "AnimationFile.hpp"
#include "WindowState.hpp"
#include "Vector3.hpp"
#include <cstdint>

namespace th20 {
extern const float native_half;

void NativeAnimationCornerProjector::project_corners_43eb40(
        Animation* animation, Vector3* a, Vector3* b, Vector3* c, Vector3* d) {
    const float* x_offsets=native_quad_axis_layout[0].corners[animation->base.flags.word_10];
    const float* y_offsets=native_quad_axis_layout[1].corners[animation->base.flags.word_14];
    SpriteData* const sprite=animation->sprite_data();
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
    a->x=(x_offsets[0]*animation->base.vector_70.x-offset_x)*sprite->field_2c*scale_x;
    a->y=(y_offsets[0]*animation->base.vector_70.y-offset_y)*sprite->field_30*scale_y;
    b->x=(x_offsets[1]*animation->base.vector_70.x-offset_x)*sprite->field_2c*scale_x;
    b->y=(y_offsets[1]*animation->base.vector_70.y-offset_y)*sprite->field_30*scale_y;
    c->x=(x_offsets[2]*animation->base.vector_70.x-offset_x)*sprite->field_2c*scale_x;
    c->y=(y_offsets[2]*animation->base.vector_70.y-offset_y)*sprite->field_30*scale_y;
    d->x=(x_offsets[3]*animation->base.vector_70.x-offset_x)*sprite->field_2c*scale_x;
    d->y=(y_offsets[3]*animation->base.vector_70.y-offset_y)*sprite->field_30*scale_y;
    animation->position(native_projection_world_position);
    *a+=native_projection_world_position;
    *b+=native_projection_world_position;
    *c+=native_projection_world_position;
    *d+=native_projection_world_position;
    const float z=animation->base.vector_2c.z+animation->vector_5bc.z+animation->base.vector_484.z;
    d->z=z;
    c->z=z;
    b->z=z;
    a->z=z;
}
}
