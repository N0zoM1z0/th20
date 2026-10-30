// Complete semantic C++ candidate for original 2769B Animation mode6 draw.
// Still NONEXACT until original full i386 and all 28 E8/78 PE HIGHLOW roles
// can be strictly compared. The exact 1378B mode6 setup, 25B depth and
// 3159B quad-submit parents are called by their genuine existing ABIs.
#include "AnimationDrawDetailedOwner.hpp"
#include "Animation.hpp"
#include "AnimationDepthMath.hpp"
#include "Graphics.hpp"
#include "WindowState.hpp"
#include "SpriteVertices.hpp"
#include "Vector3.hpp"
#include <cstdint>
#include <cstddef>

namespace th20 {
extern const float native_one, native_two, native_448;
std::uint8_t __cdecl multiply_color_128_saturating(std::uint8_t a,std::uint8_t b);
std::uint8_t __cdecl multiply_color_255(std::uint8_t a,std::uint8_t b);

union Mode6PackedColor {
    std::uint32_t word;
    AnimationColorChannels lanes;
};
static_assert(sizeof(Mode6PackedColor)==4);

// Native pixel arithmetic uses four actual independent B/G/R/A channel
// calls; keep their ordinary channel order instead of byte-swizzle helpers.
#define ANM6_TINT(value) { \
    (value).lanes.red=multiply_color_128_saturating((value).lanes.red,reinterpret_cast<const Mode6PackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->lanes.red); \
    (value).lanes.green=multiply_color_128_saturating((value).lanes.green,reinterpret_cast<const Mode6PackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->lanes.green); \
    (value).lanes.blue=multiply_color_128_saturating((value).lanes.blue,reinterpret_cast<const Mode6PackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->lanes.blue); \
    (value).lanes.alpha=multiply_color_128_saturating((value).lanes.alpha,reinterpret_cast<const Mode6PackedColor*>(reinterpret_cast<const std::uint8_t*>(this)+0x7D40E8C)->lanes.alpha); \
}
#define ANM6_BLEND_COLOR(value,other) { \
    (value).lanes.red=multiply_color_255((value).lanes.red,(other).lanes.red); \
    (value).lanes.green=multiply_color_255((value).lanes.green,(other).lanes.green); \
    (value).lanes.blue=multiply_color_255((value).lanes.blue,(other).lanes.blue); \
    (value).lanes.alpha=multiply_color_255((value).lanes.alpha,(other).lanes.alpha); \
}

std::int32_t AnimationDrawDetailedOwner::draw_complex_mode6(Animation* animation) {
    if (prepare_complex_mode6(animation)) return -1;

    Vector3 camera_vector;
    const float fog_span=process_graphics.current_viewport->fog.near_distance-
                         process_graphics.current_viewport->fog.far_distance;
    camera_vector=animation->base.vector_2c + animation->vector_5bc +
                  animation->base.vector_484 - process_graphics.current_viewport->vector_00;
    if (animation->base.flags.layer_mode && animation->parent_55c==nullptr) {
        camera_vector.x+=static_cast<float>(window_state.scaled_width)/native_two;
        camera_vector.y+=(static_cast<float>(window_state.scaled_height)-native_448)/native_two;
    }
    float depth=animation_depth(camera_vector);
    const auto channel_mode=animation->base.flags.color_mode;
    Mode6PackedColor main_color, other_color;

    switch(channel_mode) {
    case 0:
    case 1: {
        main_color.word=(animation->base.flags.color_mode==0)?animation->base.color_490:animation->base.color_494;
        if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E90)!=0) { ANM6_TINT(main_color); }
        if (!(depth > process_graphics.current_viewport->fog.near_distance)) {
            native_quad_vertices[0].color=main_color.word;
        } else {
            float fade=(process_graphics.current_viewport->fog.near_distance-depth)/fog_span;
            if (fade>=native_one) return -1;
            // The original fog float channels are truncated to signed int
            // before computing their per-byte normalized differences.
            native_quad_vertices[0].channels.blue=static_cast<std::uint8_t>(
                main_color.lanes.blue-static_cast<std::uint8_t>(static_cast<std::int32_t>(
                    (static_cast<float>(static_cast<std::int32_t>(main_color.lanes.blue)-
                      static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[0])))*fade)));
            native_quad_vertices[0].channels.green=static_cast<std::uint8_t>(
                main_color.lanes.green-static_cast<std::uint8_t>(static_cast<std::int32_t>(
                    (static_cast<float>(static_cast<std::int32_t>(main_color.lanes.green)-
                      static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[1])))*fade)));
            native_quad_vertices[0].channels.red=static_cast<std::uint8_t>(
                main_color.lanes.red-static_cast<std::uint8_t>(static_cast<std::int32_t>(
                    (static_cast<float>(static_cast<std::int32_t>(main_color.lanes.red)-
                      static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[2])))*fade)));
            native_quad_vertices[0].channels.alpha=static_cast<std::uint8_t>(static_cast<std::int32_t>(
                static_cast<float>(main_color.lanes.alpha)*(native_one-fade*fade*fade)));

        }
        if (animation->base.flags.word_04&(1u<<20)) {
            if (!(depth>animation->base.field_4bc)) return -1;
            if (depth<animation->base.field_4b8) {
                float fade=(animation->base.field_4b8-depth)/
                           (animation->base.field_4b8-animation->base.field_4bc);
                native_quad_vertices[0].channels.alpha=static_cast<std::uint8_t>(
                    static_cast<std::int32_t>(static_cast<float>(native_quad_vertices[0].channels.alpha)*(native_one-fade)));
            }
        }
        native_quad_vertices[1].color=native_quad_vertices[0].color;
        native_quad_vertices[2].color=native_quad_vertices[0].color;
        native_quad_vertices[3].color=native_quad_vertices[0].color;
        break;
    }
    case 2:
    case 3: {
        main_color.word=animation->base.color_490;
        other_color.word=animation->base.color_494;
        if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E90)!=0) { ANM6_TINT(main_color); ANM6_TINT(other_color); }
        if (!(depth>process_graphics.current_viewport->fog.near_distance)) {
            native_quad_vertices[0].color=main_color.word;
            native_quad_vertices[3].color=other_color.word;
        } else {
            depth=(process_graphics.current_viewport->fog.near_distance-depth)/fog_span;
            if (depth>=native_one) return -1;
            // In this original mode both endpoints interpolate independently;
            // the original fade of alpha is linear rather than cubic.
            native_quad_vertices[0].channels.blue=static_cast<std::uint8_t>(main_color.lanes.blue-
                static_cast<std::uint8_t>(static_cast<std::int32_t>(
                    static_cast<float>(static_cast<std::int32_t>(main_color.lanes.blue)-
                        static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[0]))*depth)));
            native_quad_vertices[0].channels.green=static_cast<std::uint8_t>(main_color.lanes.green-
                static_cast<std::uint8_t>(static_cast<std::int32_t>(
                    static_cast<float>(static_cast<std::int32_t>(main_color.lanes.green)-
                        static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[1]))*depth)));
            native_quad_vertices[0].channels.red=static_cast<std::uint8_t>(main_color.lanes.red-
                static_cast<std::uint8_t>(static_cast<std::int32_t>(
                    static_cast<float>(static_cast<std::int32_t>(main_color.lanes.red)-
                        static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[2]))*depth)));
            native_quad_vertices[0].channels.alpha=static_cast<std::uint8_t>(static_cast<std::int32_t>(
                static_cast<float>(main_color.lanes.alpha)*(native_one-depth)));
            native_quad_vertices[3].channels.blue=static_cast<std::uint8_t>(other_color.lanes.blue-
                static_cast<std::uint8_t>(static_cast<std::int32_t>(
                    static_cast<float>(static_cast<std::int32_t>(other_color.lanes.blue)-
                        static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[0]))*depth)));
            native_quad_vertices[3].channels.green=static_cast<std::uint8_t>(other_color.lanes.green-
                static_cast<std::uint8_t>(static_cast<std::int32_t>(
                    static_cast<float>(static_cast<std::int32_t>(other_color.lanes.green)-
                        static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[1]))*depth)));
            native_quad_vertices[3].channels.red=static_cast<std::uint8_t>(other_color.lanes.red-
                static_cast<std::uint8_t>(static_cast<std::int32_t>(
                    static_cast<float>(static_cast<std::int32_t>(other_color.lanes.red)-
                        static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[2]))*depth)));
            native_quad_vertices[3].channels.alpha=static_cast<std::uint8_t>(static_cast<std::int32_t>(
                static_cast<float>(other_color.lanes.alpha)*(native_one-depth)));


        }
        if (animation->base.flags.color_mode==2) {
            native_quad_vertices[2].color=native_quad_vertices[0].color;
            native_quad_vertices[1].color=native_quad_vertices[3].color;
        } else {
            native_quad_vertices[1].color=native_quad_vertices[0].color;
            native_quad_vertices[2].color=native_quad_vertices[3].color;
        }
        break;
    }
    case 4: {
        main_color.word=animation->base.color_490;
        other_color.word=animation->base.color_494;
        ANM6_BLEND_COLOR(main_color,other_color);
        if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x7D40E90)!=0) { ANM6_TINT(main_color); }
        if (!(depth>process_graphics.current_viewport->fog.near_distance)) {
            native_quad_vertices[0].color=main_color.word;
        } else {
            float fade=(process_graphics.current_viewport->fog.near_distance-depth)/fog_span;
            if (fade>=native_one) return -1;
            native_quad_vertices[0].channels.blue=static_cast<std::uint8_t>(main_color.lanes.blue-
                static_cast<std::uint8_t>(static_cast<std::int32_t>((static_cast<float>(
                    static_cast<std::int32_t>(main_color.lanes.blue)-static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[0])))*fade)));
            native_quad_vertices[0].channels.green=static_cast<std::uint8_t>(main_color.lanes.green-
                static_cast<std::uint8_t>(static_cast<std::int32_t>((static_cast<float>(
                    static_cast<std::int32_t>(main_color.lanes.green)-static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[1])))*fade)));
            native_quad_vertices[0].channels.red=static_cast<std::uint8_t>(main_color.lanes.red-
                static_cast<std::uint8_t>(static_cast<std::int32_t>((static_cast<float>(
                    static_cast<std::int32_t>(main_color.lanes.red)-static_cast<std::int32_t>(process_graphics.current_viewport->fog.channels[2])))*fade)));
            native_quad_vertices[0].channels.alpha=static_cast<std::uint8_t>(static_cast<std::int32_t>(
                static_cast<float>(main_color.lanes.alpha)*(native_one-fade*fade*fade)));

        }
        native_quad_vertices[1].color=native_quad_vertices[0].color;
        native_quad_vertices[2].color=native_quad_vertices[0].color;
        native_quad_vertices[3].color=native_quad_vertices[0].color;
        break;
    }
    default:break;
    }
    return render_quad(animation,2);
}
#undef ANM6_TINT
#undef ANM6_BLEND_COLOR
} // namespace th20
