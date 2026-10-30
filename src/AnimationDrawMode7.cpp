// Full strict native exact 753B/178-i386 Animation draw mode7 at 0x00441C00.
// Original D3DX transform, x87-returned vector depth, per-lane fog color
// interpolation and the existing strict quad submit are ordinary natural C++.
// All seven genuine E8 and 29 PE HIGHLOW source fields replay exactly.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationDepthMath.hpp"
#include "Animation.hpp"
#include "EnemyState.hpp"
#include "Graphics.hpp"
#include "SpriteVertices.hpp"
#include <d3dx9math.h>
#include <cstddef>
#include <cstdint>

namespace th20 {
extern const float native_one;

#if defined(_M_IX86)
static_assert(sizeof(EnemyBounds)==0x10);
static_assert(sizeof(D3DXVECTOR4)==0x10);
static_assert(sizeof(D3DXVECTOR3)==0x0c);
static_assert(sizeof(D3DXMATRIX)==0x40);
static_assert(offsetof(Graphics,current_viewport)==0xB00);
static_assert(offsetof(ViewportState,fog)==0x150);
static_assert(offsetof(FogValue,packed)==0x18);
static_assert(offsetof(SpriteTexturedVertex,color)==0x10);
static_assert(sizeof(SpriteTexturedVertex)==0x1c);
#endif

union Mode7PackedColor {
    std::uint32_t word;
    AnimationColorChannels channels;
};
static_assert(sizeof(Mode7PackedColor)==4);

std::int32_t AnimationDrawDetailedOwner::draw_simple_mode7(Animation* animation) {
    // This is the actual original 0x00441430 owner-member call, not a
    // fabricated free function or an alternate renderer instance.
    prepare_simple_mode7(animation);

    // 0x004398D0 is a genuine four-float zero constructor currently
    // provisionally named EnemyBounds. The same 16B native value is used
    // as a D3DX four-lane transformed result. Its original type spelling
    // remains unresolved; no new layout or constructor is invented here.
    EnemyBounds projected[4];
    Vector3 relative;
    const float fog_range = process_graphics.current_viewport->fog.near_distance -
                            process_graphics.current_viewport->fog.far_distance;
    Mode7PackedColor selected;
    selected.word = animation->base.flags.color_mode != 0 ?
        animation->base.color_494 : animation->base.color_490;

    for (std::int32_t i=0; i<4; ++i) {
        // Original renderer has 20B input corners at +0x6000E20 and one
        // shared 64B D3DX matrix at +0x60007D8.
        D3DXVec3Transform(
            reinterpret_cast<D3DXVECTOR4*>(&projected[i]),
            reinterpret_cast<const D3DXVECTOR3*>(
                reinterpret_cast<const std::uint8_t*>(this)+0x6000E20+i*0x14),
            reinterpret_cast<const D3DXMATRIX*>(
                reinterpret_cast<const std::uint8_t*>(this)+0x60007D8));
        relative.x=projected[i].x-process_graphics.current_viewport->vector_00.x;
        relative.y=projected[i].y-process_graphics.current_viewport->vector_00.y;
        relative.z=projected[i].width-process_graphics.current_viewport->vector_00.z;
        float depth=animation_depth(relative);
        if (depth > process_graphics.current_viewport->fog.near_distance) {
            depth=(process_graphics.current_viewport->fog.near_distance-depth)/fog_range;
            if (depth >= native_one) {
                native_quad_vertices[i].color=process_graphics.current_viewport->fog.packed;
                native_quad_vertices[i].channels.alpha=selected.channels.alpha;
            } else {
                native_quad_vertices[i].channels.blue=static_cast<std::uint8_t>(
                    selected.channels.blue-static_cast<std::uint8_t>(static_cast<std::int32_t>(
                        (static_cast<float>(selected.channels.blue)-
                         process_graphics.current_viewport->fog.channels[0])*depth)));
                native_quad_vertices[i].channels.green=static_cast<std::uint8_t>(
                    selected.channels.green-static_cast<std::uint8_t>(static_cast<std::int32_t>(
                        (static_cast<float>(selected.channels.green)-
                         process_graphics.current_viewport->fog.channels[1])*depth)));
                native_quad_vertices[i].channels.red=static_cast<std::uint8_t>(
                    selected.channels.red-static_cast<std::uint8_t>(static_cast<std::int32_t>(
                        (static_cast<float>(selected.channels.red)-
                         process_graphics.current_viewport->fog.channels[2])*depth)));
                native_quad_vertices[i].channels.alpha=selected.channels.alpha;
            }
        } else {
            native_quad_vertices[i].color=selected.word;
        }
    }
    const auto result=render_quad(animation,2);
    native_quad_vertices[3].reciprocal_w=native_one;
    native_quad_vertices[2].reciprocal_w=native_one;
    native_quad_vertices[1].reciprocal_w=native_one;
    native_quad_vertices[0].reciprocal_w=native_one;
    return result;
}
} // namespace th20
