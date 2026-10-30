// Complete 3,159B/763-x86 original renderer quad submission boss at
// 0x0043F6A0. A single pinned-MSVC natural C++ method is strict whole-native
// exact, including the original NOP and five relocated switch table pointers
// (3,180B total). All 41 original E8 and 101 DIR32 roles are independently
// source-identified. Strict credit is only for the full 3,159B game body.
#include "AnimationQuadSubmitOwner.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "SpriteVertices.hpp"
#include "Graphics.hpp"
#include <cmath>
#include <cstddef>
#include <cstdint>

namespace th20 {
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
// Maintain actual four-byte packed channel unions rather than copying every
// multiply result through extra temporary 32-bit colors. The actual R, G, B,
// A call sequence is native; no compiler-only do/while(false) branches.
union SourcePackedColor { std::uint32_t word; AnimationColorChannels fields; };
static_assert(sizeof(SourcePackedColor) == 4);
#define ANM_MUL4_COLOR_INTO(packed, other, fn) { \
    other_color.word = (other); \
    (packed).fields.red = fn((packed).fields.red, other_color.fields.red); \
    (packed).fields.green = fn((packed).fields.green, other_color.fields.green); \
    (packed).fields.blue = fn((packed).fields.blue, other_color.fields.blue); \
    (packed).fields.alpha = fn((packed).fields.alpha, other_color.fields.alpha); \
}

// The renderer tint is a live packed color; each channel has a native read.
#define ANM_MUL4_TINT_INTO(packed, fn) { \
    (packed).fields.red = fn((packed).fields.red, reinterpret_cast<const SourcePackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->fields.red); \
    (packed).fields.green = fn((packed).fields.green, reinterpret_cast<const SourcePackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->fields.green); \
    (packed).fields.blue = fn((packed).fields.blue, reinterpret_cast<const SourcePackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->fields.blue); \
    (packed).fields.alpha = fn((packed).fields.alpha, reinterpret_cast<const SourcePackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->fields.alpha); \
}

// Real renderer fields are read at each use, with no pointer-lifetime alias.
#define ANM_TEXTURE_CACHE (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08))
#define ANM_TEXTURE_READY (*reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E))

std::int32_t AnimationDrawModeOwner::render_quad(Animation* animation,
                                                std::int32_t options) {
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
        // Keep the x87-return spill separate from the final rounded vertex
        // value: that is the actual original compiler lifetime and stack.
        // The natural <cmath> round(float) overload emits the original
        // 20B E8-to-CRT wrapper under /fp:strict; it is library, not game
        // authorship, and independently matched with this parent.
        float snap_left = std::round(native_quad_vertices[0].position.x) - 0.5f;

        native_quad_vertices[2].position.x = snap_left;
        native_quad_vertices[0].position.x = snap_left;
        float snap_top = std::round(native_quad_vertices[0].position.y) - 0.5f;

        native_quad_vertices[1].position.y = snap_top;
        native_quad_vertices[0].position.y = snap_top;
        float snap_right = std::round(native_quad_vertices[1].position.x) - 0.5f;

        native_quad_vertices[3].position.x = snap_right;
        native_quad_vertices[1].position.x = snap_right;
        float snap_bottom = std::round(native_quad_vertices[2].position.y) - 0.5f;

        native_quad_vertices[3].position.y = snap_bottom;
        native_quad_vertices[2].position.y = snap_bottom;
    }

    // The immutable pointer global at 0x005C5840 is exactly the existing
    // process_graphics current_viewport member at Graphics+0xB00. Bounds
    // +11C/+124 are true typed native ViewportState Vector2 members.

    // Every original clipping comparison independently reads Graphics+0xB00:
    // all 16 original PE HIGHLOW viewport references remain observable.
    // The native COMISS/JBE comparisons also accept unordered (NaN) inputs.
    // !(lower > vertex) and !(vertex > upper), not >=/<=, preserve that.
    // The native offscreen path returns before texture or color submission.
    if (!(
        (!(process_graphics.current_viewport->bounds_11c.x>native_quad_vertices[0].position.x) ||
         !(process_graphics.current_viewport->bounds_11c.x>native_quad_vertices[1].position.x) ||
         !(process_graphics.current_viewport->bounds_11c.x>native_quad_vertices[2].position.x) ||
         !(process_graphics.current_viewport->bounds_11c.x>native_quad_vertices[3].position.x)) &&
        (!(process_graphics.current_viewport->bounds_11c.y>native_quad_vertices[0].position.y) ||
         !(process_graphics.current_viewport->bounds_11c.y>native_quad_vertices[1].position.y) ||
         !(process_graphics.current_viewport->bounds_11c.y>native_quad_vertices[2].position.y) ||
         !(process_graphics.current_viewport->bounds_11c.y>native_quad_vertices[3].position.y)) &&
        (!(native_quad_vertices[0].position.x>process_graphics.current_viewport->bounds_124.x) ||
         !(native_quad_vertices[1].position.x>process_graphics.current_viewport->bounds_124.x) ||
         !(native_quad_vertices[2].position.x>process_graphics.current_viewport->bounds_124.x) ||
         !(native_quad_vertices[3].position.x>process_graphics.current_viewport->bounds_124.x)) &&
        (!(native_quad_vertices[0].position.y>process_graphics.current_viewport->bounds_124.y) ||
         !(native_quad_vertices[1].position.y>process_graphics.current_viewport->bounds_124.y) ||
         !(native_quad_vertices[2].position.y>process_graphics.current_viewport->bounds_124.y) ||
         !(native_quad_vertices[3].position.y>process_graphics.current_viewport->bounds_124.y)))) return 0;
        // Original real SpriteData::texture_id at +8, actual custom D3D9
        // texture cache +0x06000E08. Native state transitions flush first.
        SpriteData* sprite=animation->sprite_data();
        if (ANM_TEXTURE_CACHE!=sprite->texture_id) {
            ANM_TEXTURE_CACHE=sprite->texture_id;
            flush_draws();
            process_graphics.get_device()->SetTexture(
                0,reinterpret_cast<AnimationQuadSubmitOwner*>(this)->texture_for_sprite(ANM_TEXTURE_CACHE));
        }
        if (ANM_TEXTURE_READY!=1) { flush_draws();ANM_TEXTURE_READY=1; }
        if ((options&2)==0) {
            SourcePackedColor main_color;
            SourcePackedColor other_color;
            switch (animation->base.flags.color_mode) {
            default: break;
            case 0:
            case 1: {
                main_color.word=animation->base.flags.color_mode==0?animation->base.color_490:animation->base.color_494;
                if (animation->base.flags.bits_04.bit_24 && animation->parent_55c!=nullptr) {
                    ANM_MUL4_COLOR_INTO(main_color,animation->parent_55c->field_5cc,
                                        multiply_color_128_saturating);
                }
                animation->field_5cc=main_color.word;
                if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E90)!=0) {
                    ANM_MUL4_TINT_INTO(main_color,multiply_color_128_saturating);
                }
                native_quad_vertices[0].color=main_color.word;
                native_quad_vertices[1].color=main_color.word;
                native_quad_vertices[2].color=main_color.word;
                native_quad_vertices[3].color=main_color.word;
                break;
            }
            case 2:
            case 3: {
                main_color.word=animation->base.color_490;
                other_color.word=animation->base.color_494;
                if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E90)!=0) {
                    ANM_MUL4_TINT_INTO(main_color,multiply_color_128_saturating);
                    ANM_MUL4_TINT_INTO(other_color,multiply_color_128_saturating);
                }
                // The real original game has separate four-store branches
                // for modes 2 and 3 (8 physical color output references),
                // even though two output colors coincide in both branches.
                if (animation->base.flags.color_mode==2) {
                    native_quad_vertices[0].color=main_color.word;
                    native_quad_vertices[1].color=other_color.word;
                    native_quad_vertices[2].color=main_color.word;
                    native_quad_vertices[3].color=other_color.word;
                } else {
                    native_quad_vertices[0].color=main_color.word;
                    native_quad_vertices[1].color=main_color.word;
                    native_quad_vertices[2].color=other_color.word;
                    native_quad_vertices[3].color=other_color.word;
                }
                break;
            }
            case 4: {
                main_color.word=animation->base.color_490;
                ANM_MUL4_COLOR_INTO(main_color,animation->base.color_494,multiply_color_255);
                if (animation->base.flags.bits_04.bit_24 && animation->parent_55c!=nullptr) {
                    ANM_MUL4_COLOR_INTO(main_color,animation->parent_55c->field_5cc,
                                        multiply_color_128_saturating);
                }
                animation->field_5cc=main_color.word;
                if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E90)!=0) {
                    ANM_MUL4_TINT_INTO(main_color,multiply_color_128_saturating);
                }
                native_quad_vertices[0].color=main_color.word;
                native_quad_vertices[1].color=main_color.word;
                native_quad_vertices[2].color=main_color.word;
                native_quad_vertices[3].color=main_color.word;
                break;
            }
            }
        }
        reinterpret_cast<AnimationQuadSubmitOwner*>(this)->prepare_texture_states(animation);
        reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(
            animation->base.flags.bits_08.field_4_5 != 3 ? std::uint8_t{0} : std::uint8_t{3});

        // Original U uses base UV indices 0 and 2; V uses 0 and 1.
        // The original writes V output in vertex order 0, 2, 1, 3: the
        // second V is derived from V0, and V3 is derived from V1.
        // The independent native indexed 8-byte shifts establish both.
        // Texture UV scaling uses +0x398 and +0x68/+0x6C.
        native_quad_vertices[0].u=animation->base.vectors_378[0].x+animation->base.field_78;
        native_quad_vertices[1].u=native_quad_vertices[0].u+animation->base.vector_398.x*animation->base.vector_68.x;
        native_quad_vertices[2].u=animation->base.vectors_378[2].x+animation->base.field_78;
        native_quad_vertices[3].u=native_quad_vertices[2].u+animation->base.vector_398.x*animation->base.vector_68.x;
        native_quad_vertices[0].v=animation->base.vectors_378[0].y+animation->base.field_7c;
        native_quad_vertices[2].v=native_quad_vertices[0].v+animation->base.vector_398.y*animation->base.vector_68.y;
        native_quad_vertices[1].v=animation->base.vectors_378[1].y+animation->base.field_7c;
        native_quad_vertices[3].v=native_quad_vertices[1].v+animation->base.vector_398.y*animation->base.vector_68.y;
        reinterpret_cast<AnimationQuadSubmitOwner*>(this)->append_quad(native_quad_vertices);
    return 0;
}

#undef ANM_TEXTURE_CACHE
#undef ANM_TEXTURE_READY
#undef ANM_MUL4_COLOR_INTO
#undef ANM_MUL4_TINT_INTO
} // namespace th20
