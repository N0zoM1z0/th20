// Complete original 4347B/1063-x86 Animation Mode8 renderer, strict exact.
// Full 4372/4372 native canonical relocation replay includes original 1B
// after-RET NOP and six genuine 32-bit PE code-pointer case table entries.
// Independent original 101 E8, 39 body HIGHLOW and six case pointers match;
// the enclosing original 5993B Draw dispatcher remains NONEXACT.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "Animation.hpp"
#include "Graphics.hpp"
#include "WindowState.hpp"
#include "AnimationFile.hpp"
#include "SpriteVertices.hpp"
#include <d3dx9math.h>
#include <cstdint>

namespace th20 {
std::uint32_t __fastcall animation_draw_enabled(Animation*);
std::int32_t __fastcall graphics_enable_depth_writes(Graphics*);
std::int32_t __fastcall graphics_disable_depth_writes(Graphics*);
std::uint8_t __cdecl multiply_color_128_saturating(std::uint8_t,std::uint8_t);
extern const float native_one, native_zero, native_half;
struct NativeMode8MatrixView { D3DXMATRIX* data(); };
struct NativeMode8RotationBits { std::uint8_t low2:2; std::uint8_t mode:3; std::uint8_t high3:3; };
union Mode8PackedColor { std::uint32_t word; AnimationColorChannels lanes; };
static_assert(sizeof(Mode8PackedColor)==4);
#define MODE8_ROTATE(axis, angle) { \
    if (static_cast<double>(angle)!=0.0) { \
        D3DXMatrixRotation##axis(reinterpret_cast<D3DXMATRIX*>(&rotation),angle); \
        D3DXMatrixMultiply(reinterpret_cast<NativeMode8MatrixView*>(&animation->matrix_57c)->data(), \
            reinterpret_cast<NativeMode8MatrixView*>(&animation->matrix_57c)->data(), \
            reinterpret_cast<const D3DXMATRIX*>(&rotation)); \
    } \
}

std::int32_t AnimationDrawDetailedOwner::draw_simple_mode8(Animation* animation) {
    Matrix4 rotation;
    Matrix4 world;
    Matrix4 texture;
    if (!animation_draw_enabled(animation)) return -1;
    if ((animation->base.flags.word_04 & 1u)==0) return -1;
    // Real source byte is the AnimationBase packed alpha at +0x493;
    // direct field-alias access avoids a false byte-array index multiply.
    if (*reinterpret_cast<const std::uint8_t*>(reinterpret_cast<const std::uint8_t*>(animation)+0x493)==0) return -1;
    if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E70)) flush_draws();
    if (((animation->base.flags.word_04 >>4)&1u)!=0)
        graphics_disable_depth_writes(&process_graphics);
    else
        graphics_enable_depth_writes(&process_graphics);
    if (((animation->base.flags.word_04>>26)&1u)==0) {
        animation->matrix_57c=animation->base.matrix_3b8;
        animation->matrix_57c.elements[0][0]*=animation->base.vector_50.x*animation->base.vector_58.x;
        animation->matrix_57c.elements[1][1]*=animation->base.vector_50.y*animation->base.vector_58.y;
        animation->base.flags.word_04 &= ~4u;
        if (animation->base.flags.field_0c==1 || animation->base.flags.field_0c==5) {
            animation->matrix_57c.elements[0][0]*=window_state.scale;
            animation->matrix_57c.elements[1][1]*=window_state.scale;
        } else if (animation->base.flags.field_0c==2 || animation->base.flags.field_0c==6) {
            animation->matrix_57c.elements[0][0]*=window_state.scale*native_half;
            animation->matrix_57c.elements[1][1]*=window_state.scale*native_half;
        }
        Vector3 angles=animation->rotation_sum();
        switch (reinterpret_cast<const NativeMode8RotationBits*>(&animation->base.flags.field_0a)->mode) {
        case 0:
            MODE8_ROTATE(X,angles.x);
            MODE8_ROTATE(Y,angles.y);
            MODE8_ROTATE(Z,angles.z);
            break;
        case 1:
            MODE8_ROTATE(X,angles.x);
            MODE8_ROTATE(Z,angles.z);
            MODE8_ROTATE(Y,angles.y);
            break;
        case 2:
            MODE8_ROTATE(Y,angles.y);
            MODE8_ROTATE(X,angles.x);
            MODE8_ROTATE(Z,angles.z);
            break;
        case 3:
            MODE8_ROTATE(Y,angles.y);
            MODE8_ROTATE(Z,angles.z);
            MODE8_ROTATE(X,angles.x);
            break;
        case 4:
            MODE8_ROTATE(Z,angles.z);
            MODE8_ROTATE(X,angles.x);
            MODE8_ROTATE(Y,angles.y);
            break;
        case 5:
            MODE8_ROTATE(Z,angles.z);
            MODE8_ROTATE(Y,angles.y);
            MODE8_ROTATE(X,angles.x);
            break;
        default:break;
        }
        animation->base.flags.word_04 &= ~2u;
    }
    world=*reinterpret_cast<const Matrix4*>(reinterpret_cast<NativeMode8MatrixView*>(&animation->matrix_57c)->data());
    world.elements[3][0]=animation->base.vector_2c.x+animation->vector_5bc.x+
        animation->base.vector_484.x-animation->base.vector_80.x*
        animation->base.vector_50.x*animation->base.vector_58.x;
    world.elements[3][1]=animation->base.vector_2c.y+animation->vector_5bc.y+
        animation->base.vector_484.y-animation->base.vector_80.y*
        animation->base.vector_50.y*animation->base.vector_58.y;
    // Native geometry writes the original already constructed 64B world
    // matrix's translation row in place; no extra temporary Vector3.
    animation->transform_position(*reinterpret_cast<Vector3*>(world.elements[3]));
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->bind_native_texture_state(animation);
    Mode8PackedColor color;
    color.word=animation->base.flags.color_mode != 0 ? animation->base.color_494:animation->base.color_490;
    if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E90)) {
        color.lanes.red=multiply_color_128_saturating(color.lanes.red,reinterpret_cast<const Mode8PackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->lanes.red);
        color.lanes.green=multiply_color_128_saturating(color.lanes.green,reinterpret_cast<const Mode8PackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->lanes.green);
        color.lanes.blue=multiply_color_128_saturating(color.lanes.blue,reinterpret_cast<const Mode8PackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->lanes.blue);
        color.lanes.alpha=multiply_color_128_saturating(color.lanes.alpha,reinterpret_cast<const Mode8PackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->lanes.alpha);
    }

    if ((*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E04))!=color.word) {
        flush_draws();
        (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E04))=color.word;
        process_graphics.get_device()->SetRenderState(D3DRS_TEXTUREFACTOR,(*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E04)));
    }
    world.elements[3][2]=animation->base.vector_2c.z+animation->vector_5bc.z+animation->base.vector_484.z;
    process_graphics.get_device()->SetTransform(D3DTS_WORLD,reinterpret_cast<const D3DMATRIX*>(&world));
    SpriteData* sprite=animation->sprite_data();

    if ((*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08))!=sprite->texture_id) {
        (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08))=sprite->texture_id;
        flush_draws();
        process_graphics.get_device()->SetTexture(0,
            reinterpret_cast<AnimationQuadSubmitOwner*>(this)->texture_for_sprite((*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08))));
    }

    if ((*reinterpret_cast<SpriteData**>(reinterpret_cast<std::uint8_t*>(this)+0x6000E18))!=sprite || animation->base.field_78!=native_zero ||
        animation->base.field_7c!=native_zero ||
        animation->base.vector_68.x!=native_one || animation->base.vector_68.y!=native_one) {
        (*reinterpret_cast<SpriteData**>(reinterpret_cast<std::uint8_t*>(this)+0x6000E18))=sprite;
        texture=*reinterpret_cast<const Matrix4*>(reinterpret_cast<NativeMode8MatrixView*>(&animation->base.matrix_3f8)->data());
        texture.elements[2][0]=animation->base.vectors_378[0].x+animation->base.field_78;
        texture.elements[2][1]=animation->base.vectors_378[0].y+animation->base.field_7c;
        texture.elements[0][0]*=animation->base.vector_68.x;
        texture.elements[1][1]*=animation->base.vector_68.y;
        process_graphics.get_device()->SetTransform(D3DTS_TEXTURE0,reinterpret_cast<const D3DMATRIX*>(&texture));
    }

    if ((*reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E))!=2) {
        process_graphics.get_device()->SetStreamSource(0,
            *reinterpret_cast<IDirect3DVertexBuffer9**>(reinterpret_cast<std::uint8_t*>(this)+0x6000E1C),0,0x14);
        process_graphics.get_device()->SetFVF(0x102);
        (*reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E))=2;
    }
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(1);
    const std::int32_t corner_index=animation->base.flags.word_14*3+animation->base.flags.word_10;
    process_graphics.get_device()->DrawPrimitive(D3DPT_TRIANGLESTRIP,
        corner_index*4,2);
    return 0;
}
#undef MODE8_ROTATE
}
