// Whole original 1204B/354-x86 polygon TRIANGLESTRIP Boss strict exact.
// Genuine by-VALUE Vector2 compound returns, 20 original E8/8 HIGHLOW
// roles and all 1204/1204 relocated native bytes independently verified.
// The original reserves count+1 and publishes count vertices even after
// generating TWO source vertices per input; preserve this observable state.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "SpriteVertices.hpp"
#include "Graphics.hpp"
#include "Vector2.hpp"
#include "MotionMath.hpp"
#include "BulletCommand11Geometry.hpp"
#include <cstdint>
namespace th20 {
extern const float native_one, native_two, native_negative_pi;

std::int32_t AnimationDrawDetailedOwner::draw_polygon_outline_43d370(
        std::int32_t count, const Vector2* origin, const Vector2* points,
        const std::uint32_t* colors, float thickness, std::uint8_t closed) {
    if (reinterpret_cast<std::uintptr_t>(
            &(*reinterpret_cast<SpriteColoredVertex (*)[65536]>(
                *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)))[count+1])
            >= reinterpret_cast<std::uintptr_t>(
                &reinterpret_cast<SpriteColoredVertex*>(reinterpret_cast<std::uint8_t*>(this)+0x7C00E80)[0x10000])) return 0;
    if (count<2) return 0;
    SpriteColoredVertex* current=*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80);
    flush_draws();
    Vector2 direction;
    Vector2 next;
    thickness/=native_two;
    for (std::int32_t i=0;i<count;++i) {
        if (i==0) {
            direction=points[1]-points[0];
            if (closed) {
                next=points[0]-points[count-1];
                direction+=next;
            }
        } else if (i==count-1) {
            direction=points[count-1]-points[count-2];
            if (closed) {
                direction=points[1]-points[0];
                next=points[0]-points[count-1];
                direction+=next;
            }
        } else {
            direction=points[i]-points[i-1];
            next=points[i+1]-points[i];
            direction+=next;
        }
        rotate_xy(next,direction,native_negative_pi/native_two);
        normalize_vector2(direction,next);
        direction*=thickness;
        current->position.x=points[i].x+origin->x+direction.x;
        current->position.y=points[i].y+origin->y+direction.y;
        current->position.z=0.0f;
        current->reciprocal_w=native_one;
        current->color=*colors;
        current->position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
        current->position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
        ++current;
        current->position.x=(points[i].x+origin->x)-direction.x;
        current->position.y=(points[i].y+origin->y)-direction.y;
        current->position.z=0.0f;
        current->reciprocal_w=native_one;
        current->color=*colors;
        current->position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
        current->position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
        ++current;
        ++colors;
    }
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=1;
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(2);
    process_graphics.get_device()->SetFVF(0x44);
    process_graphics.get_device()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,count*2-2,
        *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80),sizeof(SpriteColoredVertex));
    *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)+=count;
    ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC4);
    return 0;
}
}
