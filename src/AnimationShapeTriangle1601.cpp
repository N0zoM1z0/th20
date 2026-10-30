// Whole original 1601B/394-i386 three-vertex triangle draw strict exact.
// The real six anchored three-float geometry cases, native 3.0f/2.0f
// ratios and D3D9 type5 triangle are preserved; immutable original PE
// 11 E8 + 19 HIGHLOW roles and full 1601/1601 strict bytes accepted.
// The enclosing 5993B Animation main Draw dispatcher is still NONEXACT.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "SpriteVertices.hpp"
#include "Graphics.hpp"
#include "ScalarMath.hpp"
#include "Vector2.hpp"
#include <cstdint>

namespace th20 {
void __cdecl animation_shape_xy(Vector2&, float,float,float,float,float,float);
std::int32_t __fastcall graphics_disable_depth_writes(Graphics*);
extern const float native_one, native_half, native_two, native_three;

std::int32_t AnimationDrawDetailedOwner::draw_shape_43e2c0(
        float x,float y,float width,float height,float angle,
        std::uint32_t first_color,std::uint32_t second_color,
        std::int32_t horizontal_anchor,std::int32_t vertical_anchor) {
    // The original buffer is 65536 source SpriteColoredVertex records,
    // with its live write cursor stored on the original renderer object.
    if (reinterpret_cast<std::uintptr_t>(
            &(*reinterpret_cast<SpriteColoredVertex (*)[65536]>(
                *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)))[3])
            >= reinterpret_cast<std::uintptr_t>(
                &reinterpret_cast<SpriteColoredVertex*>(reinterpret_cast<std::uint8_t*>(this)+0x7C00E80)[0x10000])) return 0;
    SpriteColoredVertex* vertices=*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80);
    flush_draws();
    const float sine=scalar_math::sine(angle);
    const float cosine=scalar_math::cosine(angle);
    float anchors_x[3]{};
    float anchors_y[3]{};
    switch (horizontal_anchor) {
    case 1:
        anchors_x[2]=0.0f; anchors_x[0]=0.0f;
        anchors_x[1]=width;
        break;
    case 0: {
        const float left_offset=-width/native_three;
        anchors_x[2]=left_offset; anchors_x[0]=left_offset;
        anchors_x[1]=(width*native_two)/native_three;
        break;
    }
    case 2: {
        const float left_offset=-width;
        anchors_x[2]=left_offset; anchors_x[0]=left_offset;
        anchors_x[1]=0.0f;
        break;
    }
    default:break;
    }
    switch (vertical_anchor) {
    case 1:
        anchors_y[0]=0.0f;
        anchors_y[1]=height/native_two;
        anchors_y[2]=height;
        break;
    case 0:
        anchors_y[0]=-height*native_half;
        anchors_y[1]=0.0f;
        anchors_y[2]=height*native_half;
        break;
    case 2:
        anchors_y[0]=-height;
        anchors_y[1]=-height/native_two;
        anchors_y[2]=0.0f;
        break;
    default:break;
    }
    animation_shape_xy(*reinterpret_cast<Vector2*>(&vertices[0].position),anchors_x[0],anchors_y[0],sine,cosine,x,y);
    animation_shape_xy(*reinterpret_cast<Vector2*>(&vertices[1].position),anchors_x[1],anchors_y[1],sine,cosine,x,y);
    animation_shape_xy(*reinterpret_cast<Vector2*>(&vertices[2].position),anchors_x[2],anchors_y[2],sine,cosine,x,y);
    vertices[2].position.z=0.0f;
    vertices[1].position.z=0.0f;
    vertices[0].position.z=0.0f;
    vertices[0].position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    vertices[0].position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    vertices[1].position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    vertices[1].position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    vertices[2].position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    vertices[2].position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    vertices[2].reciprocal_w=native_one;
    vertices[1].reciprocal_w=native_one;
    vertices[0].reciprocal_w=native_one;
    vertices[2].color=first_color;
    vertices[0].color=first_color;
    vertices[1].color=second_color;
    graphics_disable_depth_writes(&process_graphics);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=1;
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(2);
    process_graphics.get_device()->SetFVF(0x44);
    process_graphics.get_device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,1,
        *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80),sizeof(SpriteColoredVertex));
    *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)+=3;
    ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC4);
    return 0;
}
}
