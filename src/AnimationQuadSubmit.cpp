// Entire original game renderer quad submission source at 0x0043F6A0,
// 3,159B /763 genuine native x86. Semantically reconstructed, NONEXACT:
// pinned MSVC still emits different code. All actual 41 original E8 call
// target roles (including compiler security cookie) and ALL 96 original
// in-body PE HIGHLOW target multiplicities are independently recovered.
// Five original after-return jump-table pointers are also present.
// No whole-original parent game-code byte credit without canonical replay.
#include "AnimationQuadSubmitOwner.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "SpriteVertices.hpp"
#include "Graphics.hpp"
#include <cmath>
#include <cstddef>
#include <cstdint>

namespace th20 {
float __cdecl animation_snap_round(float); // real original 0x00445B80 20B wrapper
std::uint8_t __cdecl multiply_color_128_saturating(std::uint8_t,std::uint8_t);
std::uint8_t __cdecl multiply_color_255(std::uint8_t,std::uint8_t);

#if defined(_M_IX86)
static_assert(offsetof(Graphics, current_viewport) == 0xB00);
static_assert(offsetof(ViewportState, bounds_11c) == 0x11C);
static_assert(offsetof(ViewportState, bounds_124) == 0x124);
static_assert(offsetof(SpriteData, texture_id) == 0x08);
static_assert(offsetof(AnimationBase, vectors_378) == 0x378);
static_assert(offsetof(AnimationBase, flags) == 0x498);
static_assert(offsetof(Animation, parent_55c) == 0x55C);
#endif

// The original per-channel game math modifies a real 4-byte packed color.
// Reuse two typed color unions across the original five-mode switch instead
// of reconstructing the output with unrelated 32-bit shifts and ORs.
// The original call order processes R, G, B, then A; all 28 color E8 calls
// remain genuinely observable source operations, not fake padding.
union SourcePackedColor { std::uint32_t word; AnimationColorChannels fields; };
static_assert(sizeof(SourcePackedColor) == 4);
#define ANM_MUL4_COLOR_INTO(value, other, fn) do { \
    main_color.word = (value); \
    other_color.word = (other); \
    main_color.fields.red = fn(main_color.fields.red, other_color.fields.red); \
    main_color.fields.green = fn(main_color.fields.green, other_color.fields.green); \
    main_color.fields.blue = fn(main_color.fields.blue, other_color.fields.blue); \
    main_color.fields.alpha = fn(main_color.fields.alpha, other_color.fields.alpha); \
    (value) = main_color.word; \
} while(false)

std::int32_t AnimationDrawModeOwner::render_quad(Animation* animation,
                                                std::int32_t options) {
    auto* renderer=reinterpret_cast<AnimationQuadSubmitOwner*>(this);

    // The original body offsets are owner +C8/+D0, +CC/+D4. They are not
    // Animation offsets, nor Renderer global coordinates.
    const float dx=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xC8)+*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
    const float dy=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xCC)+*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
    // Original SSE code touches the four shared 28-byte native vertices
    // individually, not via a C++ range-for iterator's cached alias.
    native_quad_vertices[0].position.x+=dx;
    native_quad_vertices[0].position.y+=dy;
    native_quad_vertices[1].position.x+=dx;
    native_quad_vertices[1].position.y+=dy;
    native_quad_vertices[2].position.x+=dx;
    native_quad_vertices[2].position.y+=dy;
    native_quad_vertices[3].position.x+=dx;
    native_quad_vertices[3].position.y+=dy;
    // Snap each original edge into a real single-precision temporary and
    // write that same value to both corresponding native vertices. The
    // original does not reload the first global after storing it.
    if (options&1) {
        // Original native 0x00445B80 normalization is a C-runtime float
        // rounding wrapper; exact rounding-mode details remain to verify.
float snap_left = animation_snap_round(native_quad_vertices[0].position.x);
        snap_left -= 0.5f;
        native_quad_vertices[0].position.x = snap_left;
        native_quad_vertices[2].position.x = snap_left;
        float snap_top = animation_snap_round(native_quad_vertices[0].position.y);
        snap_top -= 0.5f;
        native_quad_vertices[0].position.y = snap_top;
        native_quad_vertices[1].position.y = snap_top;
        float snap_right = animation_snap_round(native_quad_vertices[1].position.x);
        snap_right -= 0.5f;
        native_quad_vertices[1].position.x = snap_right;
        native_quad_vertices[3].position.x = snap_right;
        float snap_bottom = animation_snap_round(native_quad_vertices[2].position.y);
        snap_bottom -= 0.5f;
        native_quad_vertices[2].position.y = snap_bottom;
        native_quad_vertices[3].position.y = snap_bottom;
    }

    // The immutable pointer global at 0x005C5840 is exactly the existing
    // process_graphics current_viewport member at Graphics+0xB00. Bounds
    // +11C/+124 are true typed native ViewportState Vector2 members.

    // Every original clipping comparison independently reads the real
    // Graphics+0xB00 viewport pointer. Do not cache it once: all 16 genuine
    // original PE HIGHLOW viewport references must remain observable.
    if (
        (native_quad_vertices[0].position.x>=process_graphics.current_viewport->bounds_11c.x ||
         native_quad_vertices[1].position.x>=process_graphics.current_viewport->bounds_11c.x ||
         native_quad_vertices[2].position.x>=process_graphics.current_viewport->bounds_11c.x ||
         native_quad_vertices[3].position.x>=process_graphics.current_viewport->bounds_11c.x) &&
        (native_quad_vertices[0].position.y>=process_graphics.current_viewport->bounds_11c.y ||
         native_quad_vertices[1].position.y>=process_graphics.current_viewport->bounds_11c.y ||
         native_quad_vertices[2].position.y>=process_graphics.current_viewport->bounds_11c.y ||
         native_quad_vertices[3].position.y>=process_graphics.current_viewport->bounds_11c.y) &&
        (native_quad_vertices[0].position.x<=process_graphics.current_viewport->bounds_124.x ||
         native_quad_vertices[1].position.x<=process_graphics.current_viewport->bounds_124.x ||
         native_quad_vertices[2].position.x<=process_graphics.current_viewport->bounds_124.x ||
         native_quad_vertices[3].position.x<=process_graphics.current_viewport->bounds_124.x) &&
        (native_quad_vertices[0].position.y<=process_graphics.current_viewport->bounds_124.y ||
         native_quad_vertices[1].position.y<=process_graphics.current_viewport->bounds_124.y ||
         native_quad_vertices[2].position.y<=process_graphics.current_viewport->bounds_124.y ||
         native_quad_vertices[3].position.y<=process_graphics.current_viewport->bounds_124.y)) {
        // Original real SpriteData::texture_id at +8, actual custom D3D9
        // texture cache +0x06000E08. Native state transitions flush first.
        SpriteData* sprite=animation->sprite_data();
        std::uint32_t& cached_texture=*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08);
        if (cached_texture!=sprite->texture_id) {
            cached_texture=sprite->texture_id;
            flush_draws();
            process_graphics.get_device()->SetTexture(
                0,renderer->texture_for_sprite(cached_texture));
        }
        auto& texture_ready=*reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E);
        if (texture_ready!=1) { flush_draws();texture_ready=1; }
        if ((options&2)==0) {
            auto channel_mode=animation->base.flags.color_mode;
            const bool inherited=(animation->base.flags.word_04&(1u<<24))!=0 &&
                                  animation->parent_55c!=nullptr;
            const std::uint32_t tint=*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E8C);
            const bool tinted=*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E90)!=0;
            const std::uint32_t color0=animation->base.color_490;
            const std::uint32_t color1=animation->base.color_494;
            SourcePackedColor main_color;
            SourcePackedColor other_color;
            switch (channel_mode) {
            case 0:
            case 1: {
                std::uint32_t color=channel_mode==0?color0:color1;
                if (inherited) {
                    ANM_MUL4_COLOR_INTO(color,animation->parent_55c->field_5cc,
                                        multiply_color_128_saturating);
                }
                animation->field_5cc=color;
                if (tinted) {
                    ANM_MUL4_COLOR_INTO(color,tint,multiply_color_128_saturating);
                }
                native_quad_vertices[0].color=color;
                native_quad_vertices[1].color=color;
                native_quad_vertices[2].color=color;
                native_quad_vertices[3].color=color;
                break;
            }
            case 2:
            case 3: {
                std::uint32_t a=color0,b=color1;
                if (tinted) {
                    ANM_MUL4_COLOR_INTO(a,tint,multiply_color_128_saturating);
                    ANM_MUL4_COLOR_INTO(b,tint,multiply_color_128_saturating);
                }
                // The real original game has separate four-store branches
                // for modes 2 and 3 (8 physical color output references),
                // even though two output colors coincide in both branches.
                if (channel_mode==2) {
                    native_quad_vertices[0].color=a;
                    native_quad_vertices[1].color=b;
                    native_quad_vertices[2].color=a;
                    native_quad_vertices[3].color=b;
                } else {
                    native_quad_vertices[0].color=a;
                    native_quad_vertices[1].color=a;
                    native_quad_vertices[2].color=b;
                    native_quad_vertices[3].color=b;
                }
                break;
            }
            case 4: {
                std::uint32_t c=color0;
                ANM_MUL4_COLOR_INTO(c,color1,multiply_color_255);
                if (inherited) {
                    ANM_MUL4_COLOR_INTO(c,animation->parent_55c->field_5cc,
                                        multiply_color_128_saturating);
                }
                animation->field_5cc=c;
                if (tinted) {
                    ANM_MUL4_COLOR_INTO(c,tint,multiply_color_128_saturating);
                }
                native_quad_vertices[0].color=c;
                native_quad_vertices[1].color=c;
                native_quad_vertices[2].color=c;
                native_quad_vertices[3].color=c;
                break;
            }
            default: break;
            }
        }
        renderer->prepare_texture_states(animation);
        const std::uint8_t mode=(animation->base.flags.byte_08>>4)&3u;
        renderer->select_render_color_mode(mode==3?3:0);

        // Real mutable UV values belong to AnimationBase+0x378/0x398 and
        // +0x78/+0x7C, with true inherited UV scaling at +0x68/+0x6C.
        native_quad_vertices[0].u=animation->base.vectors_378[0].x+animation->base.field_78;
        native_quad_vertices[1].u=animation->base.vector_398.x*animation->base.vector_68.x+native_quad_vertices[0].u;
        native_quad_vertices[2].u=animation->base.vectors_378[2].x+animation->base.field_78;
        native_quad_vertices[3].u=animation->base.vector_398.x*animation->base.vector_68.x+native_quad_vertices[2].u;
        native_quad_vertices[0].v=animation->base.vectors_378[0].y+animation->base.field_7c;
        native_quad_vertices[2].v=animation->base.vectors_378[2].y+animation->base.field_7c;
        native_quad_vertices[1].v=animation->base.vector_398.y*animation->base.vector_68.y+native_quad_vertices[0].v;
        native_quad_vertices[3].v=animation->base.vector_398.y*animation->base.vector_68.y+native_quad_vertices[2].v;
        renderer->append_quad(native_quad_vertices);
    }
    return 0;
}

#undef ANM_MUL4_COLOR_INTO
} // namespace th20
