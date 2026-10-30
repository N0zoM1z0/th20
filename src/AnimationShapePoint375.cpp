// Whole original 375B/100-i386 POINTLIST game renderer strict exact.
// Authentic typed vertex[0], 5 native E8/4 HIGHLOW and original 375/375
// relocated bytes match without unused locals or assembly.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "SpriteVertices.hpp"
#include "Graphics.hpp"
#include <cstdint>
namespace th20 {
std::int32_t __fastcall graphics_disable_depth_writes(Graphics*);
extern const float native_one;

std::int32_t AnimationDrawDetailedOwner::draw_shape_43d830(
        float x,float y,std::uint32_t color) {
    if (reinterpret_cast<std::uintptr_t>(
            &(*reinterpret_cast<SpriteColoredVertex (*)[65536]>(
                *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80)))[0])
            >= reinterpret_cast<std::uintptr_t>(
                &reinterpret_cast<SpriteColoredVertex*>(reinterpret_cast<std::uint8_t*>(this)+0x7C00E80)[0x10000])) return 0;
    SpriteColoredVertex* const vertex=*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80);
    flush_draws();
    vertex[0].position.x=x+*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    vertex[0].position.y=y+*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    vertex[0].position.z=0.0f;
    vertex[0].reciprocal_w=native_one;
    vertex[0].color=color;
    graphics_disable_depth_writes(&process_graphics);
    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=1;
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(2);
    process_graphics.get_device()->SetFVF(0x44);
    process_graphics.get_device()->DrawPrimitiveUP(D3DPT_POINTLIST,1,
        *reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80),sizeof(SpriteColoredVertex));
    ++*reinterpret_cast<SpriteColoredVertex**>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E80);
    ++*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0xC4);
    return 0;
}
}
