// Whole original game-owned 2169B/533-native-x86 closed LINE-STRIP strict exact.
// Natural 5 x20B vertex-ring geometry, true D3D9 type=3 line strip and
// twelve independently original E8 /17 PE HIGHLOW roles are strict 2169/2169.
// The sibling 1980B rectangle is independently whole exact, while their
// enclosing 5993B Animation Draw dispatcher remains NONEXACT.
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
extern const float native_one, native_half;

std::int32_t AnimationDrawDetailedOwner::draw_shape_43b0e0(
        float x,float y,float width,float height,float angle,
        std::uint32_t first_color,std::uint32_t second_color,
        std::int32_t horizontal_anchor,std::int32_t vertical_anchor) {
    // Native capacity bound is the end of a real 65536 x20B vertex pool;
    // receiver +0x7D40E80 holds the mutable vertex write cursor.
    // This five-vertex closed line strip checks the same real 65,536x20B pool.
    if (reinterpret_cast<std::uintptr_t>(
            &(*reinterpret_cast<SpriteColoredVertex (*)[65536]>(*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)))[5])
            >= reinterpret_cast<std::uintptr_t>(
            &reinterpret_cast<SpriteColoredVertex*>(reinterpret_cast<std::uint8_t*>(this)+0x7C00E80)[0x10000])) return 0;
    SpriteColoredVertex* vertices=*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80);
    flush_draws();
    const float sine=scalar_math::sine(angle);
    const float cosine=scalar_math::cosine(angle);
    // Eight original, independently indexed local float anchor lanes.
    float anchors_x[4]{};
    float anchors_y[4]{};
    switch (horizontal_anchor) {
    case 1:
        anchors_x[2]=0.0f; anchors_x[0]=0.0f;
        anchors_x[3]=width; anchors_x[1]=width;
        break;
    case 0: {
        const float left_offset=-width*native_half;
        anchors_x[2]=left_offset; anchors_x[0]=left_offset;
        const float right_offset=width*native_half;
        anchors_x[3]=right_offset; anchors_x[1]=right_offset;
        break;
    }
    case 2: {
        const float left_offset=-width;
        anchors_x[2]=left_offset; anchors_x[0]=left_offset;
        anchors_x[3]=0.0f; anchors_x[1]=0.0f;
        break;
    }
    default:break;
    }
    switch (vertical_anchor) {
    case 1:
        anchors_y[1]=0.0f; anchors_y[0]=0.0f;
        anchors_y[3]=height; anchors_y[2]=height;
        break;
    case 0: {
        const float top_offset=-height*native_half;
        anchors_y[1]=top_offset; anchors_y[0]=top_offset;
        const float bottom_offset=height*native_half;
        anchors_y[3]=bottom_offset; anchors_y[2]=bottom_offset;
        break;
    }
    case 2: {
        const float top_offset=-height;
        anchors_y[1]=top_offset; anchors_y[0]=top_offset;
        anchors_y[3]=0.0f; anchors_y[2]=0.0f;
        break;
    }
    default:break;
    }
    animation_shape_xy(*reinterpret_cast<Vector2*>(&vertices[0].position),anchors_x[0],anchors_y[0],sine,cosine,x,y);
    animation_shape_xy(*reinterpret_cast<Vector2*>(&vertices[1].position),anchors_x[1],anchors_y[1],sine,cosine,x,y);
    // For a closed line strip vertex3 is lower-left; vertex2 is lower-right.
    animation_shape_xy(*reinterpret_cast<Vector2*>(&vertices[3].position),anchors_x[2],anchors_y[2],sine,cosine,x,y);
    animation_shape_xy(*reinterpret_cast<Vector2*>(&vertices[2].position),anchors_x[3],anchors_y[3],sine,cosine,x,y);
    // The actual fifth line vertex closes the shape by copying vertex0 XY/Z.
    vertices[4].position=vertices[0].position;
    vertices[4].position.z=0.0f;
    vertices[3].position.z=0.0f;
    vertices[2].position.z=0.0f;
    vertices[1].position.z=0.0f;
    vertices[0].position.z=0.0f;
    // Native emits eight separate 20B indexed vertex XY offset updates.
    vertices[0].position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    vertices[0].position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    vertices[1].position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    vertices[1].position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    vertices[2].position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    vertices[2].position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    vertices[3].position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    vertices[3].position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    vertices[4].position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    vertices[4].position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    vertices[4].reciprocal_w=native_one;
    vertices[3].reciprocal_w=native_one;
    vertices[2].reciprocal_w=native_one;
    vertices[1].reciprocal_w=native_one;
    vertices[0].reciprocal_w=native_one;
    vertices[4].color=first_color;
    vertices[3].color=first_color;
    vertices[0].color=first_color;
    vertices[2].color=second_color;
    vertices[1].color=second_color;
    graphics_disable_depth_writes(&process_graphics);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=1;
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(2);
    process_graphics.get_device()->SetFVF(0x44);
    process_graphics.get_device()->DrawPrimitiveUP(D3DPT_LINESTRIP,4,*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80),sizeof(SpriteColoredVertex));
    *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)+=5;
    ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC4);
    return 0;
}
}
