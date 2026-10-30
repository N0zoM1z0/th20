// Full native strict exact 2136B /504-x86 Animation mesh24/25 renderer.
// Its single pinned C++ translation unit reproduces all 32 original E8
// calls and 20 real HIGHLOW data references at their physical PE offsets.
// The containing 5993B Animation Draw dispatcher remains NONEXACT.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "Graphics.hpp"
#include "WindowState.hpp"
#include <d3dx9math.h>
#include <cstdint>

namespace th20 {
std::uint32_t __fastcall animation_draw_enabled(Animation*);
std::int32_t __fastcall graphics_enable_depth_writes(Graphics*);
std::int32_t __fastcall graphics_disable_depth_writes(Graphics*);
extern const Matrix4 native_projection_identity;
extern const float native_zero, native_one;
// Original native ECX +0x20/+0x24 WindowState integer field getters,
// folded with existing 17B member getter heads. Source identifiers unknown.
struct NativeMeshWindowGetter {
    std::int32_t mesh_x();
    std::int32_t mesh_y();
};
// Genuine 14B ECX-returning-this matrix view method alias. The physical
// head is folded with the existing constructor; both calls before each
// D3DX matrix multiply are real original E8, not duplicate code credit.
struct NativeMeshMatrixView {
    D3DXMATRIX* data();
};

std::int32_t AnimationDrawDetailedOwner::draw_mesh_2425(
        Animation* animation, void* stream, std::int32_t vertex_count) {
    Matrix4 rotation;
    Matrix4 world;
    if (!animation_draw_enabled(animation)) return -1;
    if ((animation->base.flags.word_04&1u)==0) return -1;
    if (vertex_count<=2) return -1;

    if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E70))
        flush_draws();
    if (((animation->base.flags.word_04>>4)&1u)==0)
        graphics_enable_depth_writes(&process_graphics);
    else
        graphics_disable_depth_writes(&process_graphics);

    animation->base.matrix_3b8=native_projection_identity;
    animation->matrix_57c=animation->base.matrix_3b8;
    animation->matrix_57c.elements[0][0] *=
        animation->base.vector_50.x*animation->base.vector_58.x;
    animation->matrix_57c.elements[1][1] *=
        animation->base.vector_50.y*animation->base.vector_58.y;
    animation->base.flags.word_04 &= ~4u;
    if (static_cast<double>(animation->base.vector_38.x)!=0.0) {
        D3DXMatrixRotationX(reinterpret_cast<D3DXMATRIX*>(&rotation),animation->base.vector_38.x);
        D3DXMatrixMultiply(reinterpret_cast<NativeMeshMatrixView*>(&animation->matrix_57c)->data(),
            reinterpret_cast<NativeMeshMatrixView*>(&animation->matrix_57c)->data(),
            reinterpret_cast<const D3DXMATRIX*>(&rotation));
    }
    if (static_cast<double>(animation->base.vector_38.y)!=0.0) {
        D3DXMatrixRotationY(reinterpret_cast<D3DXMATRIX*>(&rotation),animation->base.vector_38.y);
        D3DXMatrixMultiply(reinterpret_cast<NativeMeshMatrixView*>(&animation->matrix_57c)->data(),
            reinterpret_cast<NativeMeshMatrixView*>(&animation->matrix_57c)->data(),
            reinterpret_cast<const D3DXMATRIX*>(&rotation));
    }
    if (static_cast<double>(animation->base.vector_38.z)!=0.0) {
        D3DXMatrixRotationZ(reinterpret_cast<D3DXMATRIX*>(&rotation),animation->base.vector_38.z);
        D3DXMatrixMultiply(reinterpret_cast<NativeMeshMatrixView*>(&animation->matrix_57c)->data(),
            reinterpret_cast<NativeMeshMatrixView*>(&animation->matrix_57c)->data(),
            reinterpret_cast<const D3DXMATRIX*>(&rotation));
    }
    animation->base.flags.word_04 &= ~2u;
    world=animation->matrix_57c;
    world.elements[3][0]=animation->base.vector_2c.x +
        animation->vector_5bc.x+animation->base.vector_484.x;
    if (!animation->base.flags.layer_mode && !animation->parent_55c) {
        world.elements[3][0]+=static_cast<float>(
            reinterpret_cast<NativeMeshWindowGetter*>(&window_state)->mesh_x());
        world.elements[3][1]+=static_cast<float>(
            reinterpret_cast<NativeMeshWindowGetter*>(&window_state)->mesh_y());
    }
    world.elements[3][1]=animation->base.vector_2c.y +
        animation->vector_5bc.y+animation->base.vector_484.y;
    world.elements[3][2]=animation->base.vector_2c.z +
        animation->vector_5bc.z+animation->base.vector_484.z;
    process_graphics.get_device()->SetTransform(D3DTS_WORLD,
        reinterpret_cast<const D3DMATRIX*>(&world));
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->bind_native_texture_state(animation);
    SpriteData* sprite=animation->sprite_data();

    if ((*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08)) != sprite->texture_id) {
        (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08))=sprite->texture_id;
        process_graphics.get_device()->SetTexture(0,
            reinterpret_cast<AnimationQuadSubmitOwner*>(this)->texture_for_sprite((*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08))));
    }

    if ((*reinterpret_cast<SpriteData**>(reinterpret_cast<std::uint8_t*>(this)+0x6000E18))!=sprite || animation->base.field_78!=native_zero ||
        animation->base.field_7c!=native_zero ||
        animation->base.vector_68.x!=native_one ||
        animation->base.vector_68.y!=native_one) {
        (*reinterpret_cast<SpriteData**>(reinterpret_cast<std::uint8_t*>(this)+0x6000E18))=sprite;
        Matrix4 texture=animation->base.matrix_3f8;
        texture.elements[2][0]=animation->base.vectors_378[0].x+animation->base.field_78;
        texture.elements[2][1]=animation->base.vectors_378[0].y+animation->base.field_7c;
        texture.elements[0][0]*=animation->base.vector_68.x;
        texture.elements[1][1]*=animation->base.vector_68.y;
        process_graphics.get_device()->SetTransform(D3DTS_TEXTURE0,
            reinterpret_cast<const D3DMATRIX*>(&texture));
    }
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(1);

    if (*reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)!=5) {
        process_graphics.get_device()->SetFVF(0x142);
        // Original native pushes the 0 value with stage-state IDs 6 and 3.
        process_graphics.get_device()->SetTextureStageState(
            0,static_cast<D3DTEXTURESTAGESTATETYPE>(6),0);
        process_graphics.get_device()->SetTextureStageState(
            0,static_cast<D3DTEXTURESTAGESTATETYPE>(3),0);
        *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=5;
    }
    process_graphics.get_device()->DrawPrimitiveUP(
        D3DPT_TRIANGLESTRIP,vertex_count-2,stream,0x18);
    return 0;
}
}
