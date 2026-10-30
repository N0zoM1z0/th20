// Whole original 1001B/258-i386 rotated two-radius TRIANGLESTRIP strict exact.
// Original game 15 E8 and 13 HIGHLOW physical roles and entire 1001/1001
// relocated native bytes reproduce the locked source-owned original.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "SpriteVertices.hpp"
#include "Graphics.hpp"
#include "MotionMath.hpp"
#include "ScalarMath.hpp"
#include "Angle.hpp"
#include "Vector2.hpp"
#include <cstdint>

namespace th20 {
extern const float native_one,native_two,native_pi;
std::int32_t __fastcall graphics_disable_depth_writes(Graphics*);
struct NativeRotatedRingGraphicsView { std::int32_t set_render_state(std::int32_t,std::int32_t); };

std::int32_t AnimationDrawDetailedOwner::draw_shape_43c780(
        float x,float y,float width,float height,float thickness,float rotation,
        std::int32_t segment_count,std::uint32_t inner_color,std::uint32_t outer_color) {
    if (reinterpret_cast<std::uintptr_t>(
            &(*reinterpret_cast<SpriteColoredVertex (*)[65536]>(
                *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)))[segment_count+2])
            >= reinterpret_cast<std::uintptr_t>(
                &reinterpret_cast<SpriteColoredVertex*>(reinterpret_cast<std::uint8_t*>(this)+0x7C00E80)[0x10000])) return 0;
    if (segment_count<2) return 0;
    SpriteColoredVertex* current=*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80);
    float current_angle=rotation;
    flush_draws();
    Vector3 offset;
    const float step=(native_pi*native_two)/static_cast<float>(segment_count);
    for (std::int32_t i=0;i<segment_count+1;++i) {
        offset.x=(width-thickness/native_two)*scalar_math::cosine(current_angle);
        offset.y=(height-thickness/native_two)*scalar_math::sine(current_angle);
        rotate_xy(*reinterpret_cast<Vector2*>(&current->position),
                  *reinterpret_cast<const Vector2*>(&offset),rotation);
        current->position.x+=x;
        current->position.y+=y;
        current->position.z=0.0f;
        current->reciprocal_w=native_one;
        current->color=inner_color;
        current->position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
        current->position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
        ++current;
        offset.x=(width+thickness/native_two)*scalar_math::cosine(current_angle);
        offset.y=(height+thickness/native_two)*scalar_math::sine(current_angle);
        rotate_xy(*reinterpret_cast<Vector2*>(&current->position),
                  *reinterpret_cast<const Vector2*>(&offset),rotation);
        current->position.x+=x;
        current->position.y+=y;
        current->position.z=0.0f;
        current->reciprocal_w=native_one;
        current->color=outer_color;
        current->position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
        current->position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
        ++current;
        current_angle=add_angles(current_angle,step);
    }
    graphics_disable_depth_writes(&process_graphics);
    reinterpret_cast<NativeRotatedRingGraphicsView*>(&process_graphics)->set_render_state(0x17,8);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=1;
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(2);
    process_graphics.get_device()->SetFVF(0x44);
    process_graphics.get_device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,segment_count*2,
        *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80),sizeof(SpriteColoredVertex));
    *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)+=segment_count*2+2;
    ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC4);
    return 0;
}
}
