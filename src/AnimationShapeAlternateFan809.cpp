// Whole original 809B/214-i386 alternating TRIANGLEFAN strict exact.
// The center[0] and genuine signed i%2 per-vertex radius selection,
// 8 E8/8 HIGHLOW original roles and complete 809/809 bytes match.
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
extern const float native_one, native_pi, native_two;
std::int32_t __fastcall graphics_disable_depth_writes(Graphics*);
struct NativeAlternatingFanGraphicsView { std::int32_t set_render_state(std::int32_t,std::int32_t); };

std::int32_t AnimationDrawDetailedOwner::draw_shape_43d9b0(
       float x, float y, float radius_a, float radius_b, float start_angle,
       std::int32_t segment_count, std::uint32_t center_color,
       std::uint32_t perimeter_color) {
    if (reinterpret_cast<std::uintptr_t>(
            &(*reinterpret_cast<SpriteColoredVertex (*)[65536]>(
                *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)))[segment_count+2])
            >= reinterpret_cast<std::uintptr_t>(
                &reinterpret_cast<SpriteColoredVertex*>(reinterpret_cast<std::uint8_t*>(this)+0x7C00E80)[0x10000])) return 0;
    if (segment_count<2) return 0;
    SpriteColoredVertex* current=*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80);
    float current_angle=start_angle;
    flush_draws();
    current[0].position.x=x;
    current[0].position.y=y;
    current[0].position.z=0.0f;
    current[0].reciprocal_w=native_one;
    current[0].color=center_color;
    current[0].position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    current[0].position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    ++current;
    start_angle=(native_pi*native_two)/static_cast<float>(segment_count);
    for (std::int32_t i=0;i<segment_count+1;++i) {
        float chosen_radius;
        if (i%2==0) chosen_radius=radius_a;
        else chosen_radius=radius_b;
        polar2(*reinterpret_cast<Vector2*>(&current->position),current_angle,chosen_radius);
        current->position.x+=x;
        current->position.y+=y;
        current->position.z=0.0f;
        current->reciprocal_w=native_one;
        current->color=perimeter_color;
        current->position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
        current->position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
        ++current;
        current_angle=add_angles(current_angle,start_angle);
    }
    graphics_disable_depth_writes(&process_graphics);
    reinterpret_cast<NativeAlternatingFanGraphicsView*>(&process_graphics)->set_render_state(0x17,8);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=1;
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(2);
    process_graphics.get_device()->SetFVF(0x44);
    process_graphics.get_device()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,segment_count,
        *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80),sizeof(SpriteColoredVertex));
    *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)+=segment_count+2;
    ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC4);
    return 0;
}
}
