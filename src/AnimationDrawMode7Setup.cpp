// Whole original 1,996B Animation mode7 transform/quad-corner setup.
// Two real 64B TransformMatrix values, original D3DX XYZ rotations and
// multiply, one native Animation rotation-sum, true parent / window
// position accumulation, four native Vector3 corner objects and the
// original renderer matrix write. The final return is EAX=0 / RET 4.
// The original corner constructors and assignments are real native
// operations, not compiler padding or a fabricated ABI shape.
#include "AnimationDrawDetailedOwner.hpp"
#include "Animation.hpp"
#include "Viewport.hpp"
#include "WindowState.hpp"
#include <d3dx9math.h>
#include <cstdint>

namespace th20 {
extern const float native_two, native_448, native_128, native_negative_128, native_256, native_negative_256;
std::int32_t AnimationDrawDetailedOwner::prepare_simple_mode7(Animation* animation) {
    // Original order constructs the projection value at [ebp-0x80]
    // before the 64B rotation matrix at [ebp-0xC0].
    TransformMatrix transformed;
    TransformMatrix rotation;
    if (!((animation->base.flags.word_04 >> 26) & 1u)) {
        animation->matrix_57c = animation->base.matrix_3b8;
        animation->matrix_57c.elements[0][0] *= animation->base.vector_50.x * animation->base.vector_58.x;
        animation->matrix_57c.elements[1][1] *= animation->base.vector_50.y * animation->base.vector_58.y;
        animation->base.flags.word_04 &= ~4u;
        const Vector3 angles=animation->rotation_sum();
        if (static_cast<double>(angles.x) != 0.0) {
            D3DXMatrixRotationX(reinterpret_cast<D3DXMATRIX*>(&rotation),angles.x);
            D3DXMatrixMultiply(reinterpret_cast<D3DXMATRIX*>(&animation->matrix_57c),
                reinterpret_cast<const D3DXMATRIX*>(&animation->matrix_57c),reinterpret_cast<D3DXMATRIX*>(&rotation));
        }
        if (static_cast<double>(angles.y) != 0.0) {
            D3DXMatrixRotationY(reinterpret_cast<D3DXMATRIX*>(&rotation),angles.y);
            D3DXMatrixMultiply(reinterpret_cast<D3DXMATRIX*>(&animation->matrix_57c),
                reinterpret_cast<const D3DXMATRIX*>(&animation->matrix_57c),reinterpret_cast<D3DXMATRIX*>(&rotation));
        }
        if (static_cast<double>(angles.z) != 0.0) {
            D3DXMatrixRotationZ(reinterpret_cast<D3DXMATRIX*>(&rotation),angles.z);
            D3DXMatrixMultiply(reinterpret_cast<D3DXMATRIX*>(&animation->matrix_57c),
                reinterpret_cast<const D3DXMATRIX*>(&animation->matrix_57c),reinterpret_cast<D3DXMATRIX*>(&rotation));
        }
        animation->base.flags.word_04 &= ~2u;
    }
    transformed = *reinterpret_cast<TransformMatrix*>(&animation->matrix_57c);
    transformed.elements[3][0] += animation->vector_5bc.x + animation->base.vector_2c.x + animation->base.vector_484.x;
    if (animation->base.flags.layer_mode && !animation->parent_55c) {
        transformed.elements[3][0] += static_cast<float>(window_state.scaled_width)/native_two;
        transformed.elements[3][1] += (static_cast<float>(window_state.scaled_height)-native_448)/native_two;
    }
    transformed.elements[3][1] += animation->vector_5bc.y + animation->base.vector_2c.y + animation->base.vector_484.y;
    transformed.elements[3][2] = animation->base.vector_2c.z + animation->vector_5bc.z + animation->base.vector_484.z;
    if (animation->parent_55c && !((animation->base.flags.word_04 >> 12) & 1u)) {
        transformed.elements[3][0] += animation->parent_55c->vector_5bc.x + animation->parent_55c->base.vector_2c.x + animation->parent_55c->base.vector_484.x;
        transformed.elements[3][1] += animation->parent_55c->vector_5bc.y + animation->parent_55c->base.vector_2c.y + animation->parent_55c->base.vector_484.y;
        transformed.elements[3][2] += animation->parent_55c->vector_5bc.z + animation->parent_55c->base.vector_2c.z + animation->parent_55c->base.vector_484.z;
    }
    // Original code really constructs all four 12B local corner vectors,
    // assigns fixed anchor coordinates for each state and clears all Z
    // lanes even though no later PE read of these locals is observed.
    Vector3 corners[4];
    switch (animation->base.flags.word_10) {
    default:
    case 1:
        corners[2].x=0.0f; corners[0].x=0.0f;
        corners[3].x=native_256; corners[1].x=native_256;
        break;
    case 0:
        corners[2].x=native_negative_128; corners[0].x=native_negative_128;
        corners[3].x=native_128; corners[1].x=native_128;
        break;
    case 2:
        corners[2].x=native_negative_256; corners[0].x=native_negative_256;
        corners[3].x=0.0f; corners[1].x=0.0f;
        break;
    }
    switch (animation->base.flags.word_14) {
    default:
    case 1:
        corners[1].y=0.0f; corners[0].y=0.0f;
        corners[3].y=native_256; corners[2].y=native_256;
        break;
    case 0:
        corners[1].y=native_negative_128; corners[0].y=native_negative_128;
        corners[3].y=native_128; corners[2].y=native_128;
        break;
    case 2:
        corners[1].y=native_negative_256; corners[0].y=native_negative_256;
        corners[3].y=0.0f; corners[2].y=0.0f;
        break;
    }
    corners[3].z=0.0f; corners[2].z=0.0f; corners[1].z=0.0f; corners[0].z=0.0f;
    *reinterpret_cast<TransformMatrix*>(reinterpret_cast<std::uint8_t*>(this)+0x60007d8)=transformed;
    return 0;
}
}
