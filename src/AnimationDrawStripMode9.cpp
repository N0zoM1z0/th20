// Whole original 612B/182-i386 Animation strip9 renderer, strict exact.
// Eleven real E8 and five Graphics PE HIGHLOW source physical fields are
// independently attested; full original 612/612 bytes zero-difference replay.
// Its enclosing original 5993B Animation Draw Boss remains NONEXACT.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "Graphics.hpp"
#include "GraphicsApi.hpp"
#include "SpriteVertices.hpp"
#include <cstdint>

namespace th20 {
std::uint32_t __fastcall animation_draw_enabled(Animation*);

std::int32_t AnimationDrawDetailedOwner::draw_strip_mode9(Animation* animation,
        void* stream, std::int32_t vertex_count) {
    if (vertex_count<3) return -1;
    if (!animation_draw_enabled(animation)) return -1;
    if ((animation->base.flags.word_04&1u)==0) return -1;
    if (*reinterpret_cast<const std::uint8_t*>(reinterpret_cast<const std::uint8_t*>(animation)+0x493)==0) return -1;
    if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E70))
        flush_draws();
    if (((animation->base.flags.word_04>>21)&1u)==0) {
        animation->base.flags.word_04 |= 0x200000u;
        auto* vertex=reinterpret_cast<SpriteTexturedVertex*>(stream);
        for (std::int32_t i=0;i<vertex_count;++i) {
            vertex->position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
            vertex->position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
            ++vertex;
        }
    }
    SpriteData* sprite=animation->sprite_data();
    if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08)!=sprite->texture_id) {
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08)=sprite->texture_id;
        process_graphics.get_device()->SetTexture(0,
            reinterpret_cast<AnimationQuadSubmitOwner*>(this)->texture_for_sprite(
                *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08)));
    }
    if (*reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)!=3) {
        process_graphics.get_device()->SetFVF(0x144);
        process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(6),0);
        process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(3),0);
        *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=3;
    }

    std::uint8_t render_mode;
    // Native original calls the real texture-state method immediately
    // before evaluating the true Animation+0x4A0 2-bit mode field. A
    // sequenced C++ expression preserves this required order and avoids
    // a non-native /Od NOP between two separate statements.
    if ((reinterpret_cast<AnimationQuadSubmitOwner*>(this)->prepare_texture_states(animation), animation->base.flags.bits_08.field_4_5) !=3)
        render_mode=0;
    else
        render_mode=3;
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->select_render_color_mode(render_mode);
    process_graphics.get_device()->DrawPrimitiveUP(
        D3DPT_TRIANGLESTRIP,vertex_count-2,stream,sizeof(SpriteTexturedVertex));
    return 0;
}
}
