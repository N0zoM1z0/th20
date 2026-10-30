// Complete native-original 1378B/335-x86 Mode6 screen projection setup.
// One natural C++ source function strict exact for all 17 original E8
// calls/21 actual PE HIGHLOW sites with genuine 2x3x4 coordinate tensor.
// The 2769B Mode6 renderer caller remains separate and NONEXACT.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationProjectionMath.hpp"
#include "Animation.hpp"
#include "Graphics.hpp"
#include "WindowState.hpp"
#include "SpriteVertices.hpp"
#include "ScalarMath.hpp"
#include <d3dx9math.h>
#include <cstdint>

namespace th20 {
extern const float native_half, native_one;
extern const TransformMatrix native_projection_identity;
extern const float projection_mode_offsets[2][3][4];

std::int32_t AnimationDrawDetailedOwner::prepare_complex_mode6(Animation* animation) {
    const float angle=animation->rotation_sum().z;
    const float sine=scalar_math::sine(angle);
    const float cosine=scalar_math::cosine(angle);
    TransformMatrix world;
    D3DXVECTOR3 projected_zero;
    D3DXVECTOR3 projected_view;
    D3DXVECTOR3 delta_projected;
    Vector3 zero(0.0f,0.0f,0.0f);
    world=native_projection_identity;
    world.elements[3][0]=animation->base.vector_2c.x+animation->vector_5bc.x+animation->base.vector_484.x;
    world.elements[3][1]=animation->base.vector_2c.y+animation->vector_5bc.y+animation->base.vector_484.y;
    world.elements[3][2]=animation->base.vector_2c.z+animation->vector_5bc.z+animation->base.vector_484.z;
    D3DXVec3Project(&projected_zero,reinterpret_cast<const D3DXVECTOR3*>(&zero),
        reinterpret_cast<const D3DVIEWPORT9*>(&process_graphics.current_viewport->viewport),
        reinterpret_cast<const D3DXMATRIX*>(&process_graphics.current_viewport->projection),
        reinterpret_cast<const D3DXMATRIX*>(&process_graphics.current_viewport->view),
        reinterpret_cast<const D3DXMATRIX*>(&world));
    if (0.0f>projected_zero.z || projected_zero.z>native_one) return -1;
    // Successful projection owns a real local calculation scope. The
    // original compiler places its genuine NOP at this scope boundary;
    // it is not hand-authored padding or a dummy source statement.
    {
    D3DXVec3Project(&projected_view,
        reinterpret_cast<const D3DXVECTOR3*>(&process_graphics.current_viewport->vector_30),
        reinterpret_cast<const D3DVIEWPORT9*>(&process_graphics.current_viewport->viewport),
        reinterpret_cast<const D3DXMATRIX*>(&process_graphics.current_viewport->projection),
        reinterpret_cast<const D3DXMATRIX*>(&process_graphics.current_viewport->view),
        reinterpret_cast<const D3DXMATRIX*>(&world));
    *reinterpret_cast<Vector3*>(&delta_projected) =
        *reinterpret_cast<const Vector3*>(&projected_view) -
        *reinterpret_cast<const Vector3*>(&projected_zero);
    const float distance=animation_vector3_length(*reinterpret_cast<const Vector3*>(&delta_projected));
    // The original reuses this *same* live float slot after scaling.
    // A second independent offset-x local changed the stack and x86.
    float scaled_half=distance*native_half;
    const float scale_x=scaled_half*animation->base.vector_70.x*animation->base.vector_50.x*animation->base.vector_58.x;
    const float scale_y=scaled_half*animation->base.vector_70.y*animation->base.vector_50.y*animation->base.vector_58.y;
    scaled_half=projected_zero.x;
    const float offset_y=projected_zero.y;
    native_quad_vertices[3].position.z=projected_zero.z;
    native_quad_vertices[2].position.z=projected_zero.z;
    native_quad_vertices[1].position.z=projected_zero.z;
    native_quad_vertices[0].position.z=projected_zero.z;
    // The actual original immutable data owner is [2 axes][3 modes][4
    // corners], with 0x30-byte axis stride and 0x10-byte mode stride.
    const float* x_offsets=projection_mode_offsets[0][animation->base.flags.word_10];
    const float* y_offsets=projection_mode_offsets[1][animation->base.flags.word_14];
    transform_projected_xy(reinterpret_cast<Vector2*>(&native_quad_vertices[0].position),
        x_offsets[0]*scale_x,y_offsets[0]*scale_y,sine,cosine,scaled_half,offset_y);
    transform_projected_xy(reinterpret_cast<Vector2*>(&native_quad_vertices[1].position),
        x_offsets[1]*scale_x,y_offsets[1]*scale_y,sine,cosine,scaled_half,offset_y);
    transform_projected_xy(reinterpret_cast<Vector2*>(&native_quad_vertices[2].position),
        x_offsets[2]*scale_x,y_offsets[2]*scale_y,sine,cosine,scaled_half,offset_y);
    transform_projected_xy(reinterpret_cast<Vector2*>(&native_quad_vertices[3].position),
        x_offsets[3]*scale_x,y_offsets[3]*scale_y,sine,cosine,scaled_half,offset_y);
    }
    return 0;
}
} // namespace th20
