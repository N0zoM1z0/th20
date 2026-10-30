// Whole native original 766B/201-x86 dual-radius TRIANGLESTRIP strict exact.
// Real 20B inner/outer vertices with shared pointer, separate thickness/2
// and actual native step calculation; all seven original E8/eight PE
// HIGHLOW targets and complete 766/766 original code bytes replay exact.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "SpriteVertices.hpp"
#include "Graphics.hpp"
#include "MotionMath.hpp"
#include "Angle.hpp"
#include "Vector2.hpp"
#include <cstdint>

namespace th20 {
void polar2(Vector2&,float,float);
extern const float native_one,native_pi,native_two;

std::int32_t AnimationDrawDetailedOwner::draw_shape_43be80(
        float x,float y,float radius,float thickness,float start_angle,
        std::int32_t segment_count,std::uint32_t inner_color,
        std::uint32_t outer_color) {
    if (reinterpret_cast<std::uintptr_t>(
            &(*reinterpret_cast<SpriteColoredVertex (*)[65536]>(
                *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)))[segment_count*2+2])
            >= reinterpret_cast<std::uintptr_t>(
                &reinterpret_cast<SpriteColoredVertex*>(reinterpret_cast<std::uint8_t*>(this)+0x7C00E80)[0x10000])) return 0;
    if (segment_count<2) return 0;
    flush_draws();
    SpriteColoredVertex* current=*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80);
    float current_angle=start_angle;
    const float inner_radius=radius-thickness/native_two;
    const float outer_radius=radius+thickness/native_two;
    start_angle=(native_pi*native_two)/static_cast<float>(segment_count);
    for (std::int32_t i=0;i<segment_count+1;++i) {
        polar2(*reinterpret_cast<Vector2*>(&current->position),current_angle,inner_radius);
        current->position.x+=x;
        current->position.y+=y;
        current->position.z=0.0f;
        current->reciprocal_w=native_one;
        current->color=inner_color;
        current->position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
        current->position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
        ++current;
        polar2(*reinterpret_cast<Vector2*>(&current->position),current_angle,outer_radius);
        current->position.x+=x;
        current->position.y+=y;
        current->position.z=0.0f;
        current->reciprocal_w=native_one;
        current->color=outer_color;
        current->position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
        current->position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
        ++current;
        current_angle=add_angles(current_angle,start_angle);
    }
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
