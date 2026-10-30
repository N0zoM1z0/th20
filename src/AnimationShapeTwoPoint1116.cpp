// Whole original 1116B/282-i386 two-endpoint LINESTRIP native strict exact.
// Original genuinely writes five W1 slots though only two vertices submitted;
// 10 E8 and 13 HIGHLOW original PE roles and 1116/1116 code bytes match.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "SpriteVertices.hpp"
#include "Graphics.hpp"
#include "ScalarMath.hpp"
#include "Vector2.hpp"
#include <cstdint>

namespace th20 {
void __cdecl animation_shape_xy(Vector2&,float,float,float,float,float,float);
std::int32_t __fastcall graphics_disable_depth_writes(Graphics*);
extern const float native_half, native_one;

std::int32_t AnimationDrawDetailedOwner::draw_shape_43cd40(
       float x,float y,float width,float angle,
       std::uint32_t color_first,std::uint32_t color_second,
       std::int32_t horizontal_anchor,std::int32_t /*reserved*/) {
    if (reinterpret_cast<std::uintptr_t>(
          &(*reinterpret_cast<SpriteColoredVertex (*)[65536]>(
              *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)))[2])
          >= reinterpret_cast<std::uintptr_t>(
              &reinterpret_cast<SpriteColoredVertex*>(reinterpret_cast<std::uint8_t*>(this)+0x7C00E80)[0x10000])) return 0;
    auto* vertices=*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80);
    flush_draws();
    const float sine=scalar_math::sine(angle);
    const float cosine=scalar_math::cosine(angle);
    float anchors_x[2]{};
    float anchors_y[2]{};
    switch(horizontal_anchor) {
    case 1:
        anchors_x[0]=0.0f;
        anchors_x[1]=width;
        break;
    case 0:
        anchors_x[0]=-width*native_half;
        anchors_x[1]=width*native_half;
        break;
    case 2:
        anchors_x[0]=-width;
        anchors_x[1]=0.0f;
        break;
    default:break;
    }
    anchors_y[1]=0.0f;
    anchors_y[0]=0.0f;
    animation_shape_xy(*reinterpret_cast<Vector2*>(&vertices[0].position),
                       anchors_x[0],anchors_y[0],sine,cosine,x,y);
    animation_shape_xy(*reinterpret_cast<Vector2*>(&vertices[1].position),
                       anchors_x[1],anchors_y[1],sine,cosine,x,y);
    vertices[1].position.z=0.0f;
    vertices[0].position.z=0.0f;
    vertices[0].position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    vertices[0].position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    vertices[1].position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    vertices[1].position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    vertices[4].reciprocal_w=native_one;
    vertices[3].reciprocal_w=native_one;
    vertices[2].reciprocal_w=native_one;
    vertices[1].reciprocal_w=native_one;
    vertices[0].reciprocal_w=native_one;
    vertices[0].color=color_first;
    vertices[1].color=color_second;
    graphics_disable_depth_writes(&process_graphics);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=1;
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(2);
    process_graphics.get_device()->SetFVF(0x44);
    process_graphics.get_device()->DrawPrimitiveUP(D3DPT_LINESTRIP,1,
           *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80),sizeof(SpriteColoredVertex));
    *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)+=2;
    ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC4);
    return 0;
}
}
