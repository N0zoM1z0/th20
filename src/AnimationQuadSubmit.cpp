// Full game renderer quad submission routine at original 0x0043F6A0,
// 3,159B/763 real native x86. Semantic C++ candidate: still NONEXACT.
// Uses the already strict real Animation types and D3D9 submission roles;
// no 3,159B whole-function byte credit until complete canonical replay.
#include "AnimationDrawModeOwner.hpp"
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

namespace {
// Each value below is an independently original-PE-observed renderer-owner
// scalar or byte. Do not invent a multi-megabyte source class layout.
template<typename T> T& renderer_field(AnimationPoolOwner* owner,std::size_t offset) {
    return *reinterpret_cast<T*>(reinterpret_cast<std::uint8_t*>(owner)+offset);
}

// Original four-byte packed Animation color channels have native Blue/Green/
// Red/Alpha byte order, not a Ghidra float reinterpretation.
std::uint32_t multiply_channels(std::uint32_t color,std::uint32_t mask,
                                bool divide_255) {
    std::uint32_t result=0;
    for (unsigned channel=0;channel<4;++channel) {
        std::uint8_t a=std::uint8_t(color>>(channel*8));
        std::uint8_t b=std::uint8_t(mask>>(channel*8));
        const std::uint8_t combined=divide_255
            ? multiply_color_255(a,b)
            : multiply_color_128_saturating(a,b);
        result |= std::uint32_t(combined)<<(channel*8);
    }
    return result;
}

bool any_reaches_minimum(const SpriteTexturedVertex (&quad)[4],float min_x,float min_y) {
    bool some_x=false,some_y=false;
    for (const auto& vertex:quad) {
        some_x |= vertex.position.x>=min_x;
        some_y |= vertex.position.y>=min_y;
    }
    return some_x&&some_y;
}
bool any_before_maximum(const SpriteTexturedVertex (&quad)[4],float max_x,float max_y) {
    bool some_x=false,some_y=false;
    for (const auto& vertex:quad) {
        some_x |= vertex.position.x<=max_x;
        some_y |= vertex.position.y<=max_y;
    }
    return some_x&&some_y;
}
}

// The distinct, unsourced native texture/state/submit helper heads are
// provisional declarations only. Their real actual E8 destinations are
// independently attested, not claims that those methods are exact.
struct AnimationQuadSubmitOwner : AnimationDrawModeOwner {
    IDirect3DBaseTexture9* texture_for_sprite(std::uint32_t); // 0x00445A00
    void prepare_texture_states(Animation*);                // 0x00445BA0
    void select_render_color_mode(std::uint8_t);             // 0x00446690
    std::int32_t append_quad(SpriteTexturedVertex*);         // 0x0043E9B0
};

std::int32_t AnimationDrawModeOwner::render_quad(Animation* animation,
                                                std::int32_t options) {
    auto* renderer=reinterpret_cast<AnimationQuadSubmitOwner*>(this);
    SpriteTexturedVertex (&quad)[4]=native_quad_vertices;

    // The original body offsets are owner +C8/+D0, +CC/+D4. They are not
    // Animation offsets, nor Renderer global coordinates.
    const float dx=renderer_field<float>(this,0xC8)+renderer_field<float>(this,0xD0);
    const float dy=renderer_field<float>(this,0xCC)+renderer_field<float>(this,0xD4);
    for (auto& vertex:quad) {
        vertex.position.x+=dx;
        vertex.position.y+=dy;
    }
    if (options&1) {
        // Original native 0x00445B80 normalization is a C-runtime float
        // rounding wrapper; exact rounding-mode details remain to verify.
        quad[0].position.x=std::round(quad[0].position.x)-0.5f;
        quad[2].position.x=quad[0].position.x;
        quad[0].position.y=std::round(quad[0].position.y)-0.5f;
        quad[1].position.y=quad[0].position.y;
        quad[1].position.x=std::round(quad[1].position.x)-0.5f;
        quad[3].position.x=quad[1].position.x;
        quad[2].position.y=std::round(quad[2].position.y)-0.5f;
        quad[3].position.y=quad[2].position.y;
    }

    // The immutable pointer global at 0x005C5840 is exactly the existing
    // process_graphics current_viewport member at Graphics+0xB00. Bounds
    // +11C/+124 are true typed native ViewportState Vector2 members.
    const ViewportState* view=process_graphics.current_viewport;
    if (any_reaches_minimum(quad,view->bounds_11c.x,view->bounds_11c.y) &&
        any_before_maximum(quad,view->bounds_124.x,view->bounds_124.y)) {
        // Original real SpriteData::texture_id at +8, actual custom D3D9
        // texture cache +0x06000E08. Native state transitions flush first.
        SpriteData* sprite=animation->sprite_data();
        std::uint32_t& cached_texture=renderer_field<std::uint32_t>(this,0x6000E08);
        if (cached_texture!=sprite->texture_id) {
            cached_texture=sprite->texture_id;
            flush_draws();
            process_graphics.get_device()->SetTexture(
                0,renderer->texture_for_sprite(cached_texture));
        }
        auto& texture_ready=renderer_field<std::uint8_t>(this,0x6000E0E);
        if (texture_ready!=1) { flush_draws();texture_ready=1; }
        if ((options&2)==0) {
            auto channel_mode=animation->base.flags.color_mode;
            const bool inherited=(animation->base.flags.word_04&(1u<<24))!=0 &&
                                  animation->parent_55c!=nullptr;
            const std::uint32_t tint=renderer_field<std::uint32_t>(this,0x7D40E8C);
            const bool tinted=renderer_field<std::uint32_t>(this,0x7D40E90)!=0;
            auto global_tint=[&](std::uint32_t value) {
                return tinted ? multiply_channels(value,tint,false) : value;
            };
            auto inherit_tint=[&](std::uint32_t value) {
                if (inherited)
                    value=multiply_channels(value,animation->parent_55c->field_5cc,false);
                return value;
            };
            const std::uint32_t color0=animation->base.color_490;
            const std::uint32_t color1=animation->base.color_494;
            switch (channel_mode) {
            case 0:
            case 1: {
                std::uint32_t color=channel_mode==0?color0:color1;
                color=global_tint(inherit_tint(color));
                animation->field_5cc=color;
                for (auto& vertex:quad) vertex.color=color;
                break;
            }
            case 2:
            case 3: {
                std::uint32_t a=global_tint(color0),b=global_tint(color1);
                quad[0].color=a;
                quad[3].color=b;
                quad[1].color=(channel_mode==2?b:a);
                quad[2].color=(channel_mode==2?a:b);
                break;
            }
            case 4: {
                std::uint32_t c=multiply_channels(color0,color1,true);
                c=global_tint(inherit_tint(c));
                animation->field_5cc=c;
                for (auto& vertex:quad)vertex.color=c;
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
        quad[0].u=animation->base.vectors_378[0].x+animation->base.field_78;
        quad[1].u=animation->base.vector_398.x*animation->base.vector_68.x+quad[0].u;
        quad[2].u=animation->base.vectors_378[2].x+animation->base.field_78;
        quad[3].u=animation->base.vector_398.x*animation->base.vector_68.x+quad[2].u;
        quad[0].v=animation->base.vectors_378[0].y+animation->base.field_7c;
        quad[2].v=animation->base.vectors_378[2].y+animation->base.field_7c;
        quad[1].v=animation->base.vector_398.y*animation->base.vector_68.y+quad[0].v;
        quad[3].v=animation->base.vector_398.y*animation->base.vector_68.y+quad[2].v;
        renderer->append_quad(quad);
    }
    return 0;
}
} // namespace th20
