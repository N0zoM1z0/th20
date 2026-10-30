// Complete strict-native original game shape ring/strip renderer 1468B.
// All 387 original x86 instruction heads, native 0x2C frame/RET 0x28,
// eleven game/runtime E8 site targets and 26 PE HIGHLOW site targets are
// independently attested; entire original 1468B canonical replay exact.
// The enclosing 5993B Animation Draw dispatcher remains NONEXACT.
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
extern const float native_two;
extern const float native_one;
extern const float native_pi;
extern const float native_negative_pi;
struct NativeShapeGraphicsView { std::int32_t set_render_state(std::int32_t,std::int32_t); };
std::int32_t __fastcall graphics_disable_depth_writes(Graphics*);

std::int32_t AnimationDrawDetailedOwner::draw_shape_43ab20(
    float x,float y,float size_x,float size_y,float radius,float thickness,
    float rotation,std::int32_t segment_count,
    std::uint32_t inside_color,std::uint32_t outside_color) {
    // The original owner has a fixed pool of 0x10000 typed 20B vertices
    // starting at this+0x7C00E80, with a live write cursor at +0x7D40E80.
    if (reinterpret_cast<std::uintptr_t>(*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)+(segment_count+2))>=
        reinterpret_cast<std::uintptr_t>(&reinterpret_cast<SpriteColoredVertex*>(reinterpret_cast<std::uint8_t*>(this)+0x7C00E80)[0x10000])) return 0;
    if (segment_count<2) return 0;

    SpriteColoredVertex* current=*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80);
    float current_angle=native_negative_pi;
    const float step=(native_pi*native_two)/static_cast<float>(segment_count);
    flush_draws();
    const float half_thickness=thickness/native_two;

    for (std::int32_t i=0;i<segment_count+1;++i) {
        polar2(*reinterpret_cast<Vector2*>(&current->position),current_angle,radius-half_thickness);
        current->position.z=0.0f;
        current->reciprocal_w=native_one;
        if (i<segment_count/4 || i==segment_count) {
            current->position.x-=size_x/native_two;
            current->position.y-=size_y/native_two;
        } else if (i<(segment_count*2)/4) {
            current->position.x+=size_x/native_two;
            current->position.y-=size_y/native_two;
        } else if (i<(segment_count*3)/4) {
            current->position.x+=size_x/native_two;
            current->position.y+=size_y/native_two;
        } else if (i<segment_count) {
            current->position.x-=size_x/native_two;
            current->position.y+=size_y/native_two;
        }
        current->color=inside_color;
        rotate_xy(*reinterpret_cast<Vector2*>(&current->position),
                  *reinterpret_cast<const Vector2*>(&current->position),rotation);
        current->position.x+=x;
        current->position.y+=y;
        current->position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
        current->position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);

        ++current;  // original cursor now designates the second strip vertex
        polar2(*reinterpret_cast<Vector2*>(&current->position),current_angle,radius+half_thickness);
        current->position.z=0.0f;
        current->reciprocal_w=native_one;
        if (i<segment_count/4 || i==segment_count) {
            current->position.x-=size_x/native_two;
            current->position.y-=size_y/native_two;
        } else if (i<(segment_count*2)/4) {
            current->position.x+=size_x/native_two;
            current->position.y-=size_y/native_two;
        } else if (i<(segment_count*3)/4) {
            current->position.x+=size_x/native_two;
            current->position.y+=size_y/native_two;
        } else if (i<segment_count) {
            current->position.x-=size_x/native_two;
            current->position.y+=size_y/native_two;
        }
        current->color=outside_color;
        rotate_xy(*reinterpret_cast<Vector2*>(&current->position),
                  *reinterpret_cast<const Vector2*>(&current->position),rotation);
        current->position.x+=x;
        current->position.y+=y;
        current->position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
        current->position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
        ++current;
        current_angle=add_angles(current_angle,step);
    }
    graphics_disable_depth_writes(&process_graphics);
    reinterpret_cast<NativeShapeGraphicsView*>(&process_graphics)->set_render_state(0x17,8);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=1;
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(2);
    process_graphics.get_device()->SetFVF(0x44);
    process_graphics.get_device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
        segment_count*2,*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80),sizeof(SpriteColoredVertex));
    *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)+=segment_count*2+2;
    ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC4);
    return 0;
}
} // namespace th20
