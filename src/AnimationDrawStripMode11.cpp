// Complete original 534B/159-native-x86 Animation strip renderer strict exact.
// Native 28B vertex updates, D3D FVF/texture stage and real ten E8/six
// HIGHLOW fields are independently attested and 534/534 bytes replay exact.
// The original enclosing 5993B Draw dispatcher remains independently NONEXACT.
#include "AnimationDrawDetailedOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "Graphics.hpp"
#include "GraphicsApi.hpp"
#include "SpriteVertices.hpp"
#include <cstdint>

namespace th20 {
std::int32_t __fastcall graphics_disable_depth_writes(Graphics*);

std::int32_t AnimationDrawDetailedOwner::draw_strip_mode11(Animation* animation,
        void* stream, std::int32_t vertex_count) {
    if (vertex_count<3) return -1;
    if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E70))
        flush_draws();
    if (((animation->base.flags.word_04>>21)&1u)==0) {
        animation->base.flags.word_04 |= 0x200000u;
        auto* current=reinterpret_cast<SpriteTexturedVertex*>(stream);
        for (std::int32_t i=0; i<vertex_count; ++i) {
            current->position.x+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD0);
            current->position.y+=*reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this)+0xD4);
            ++current;
        }
    }
    if (*reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)!=3) {
        process_graphics.get_device()->SetFVF(0x144);
        *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=3;
    }
    reinterpret_cast<AnimationQuadSubmitOwner*>(this)->prepare_texture_states(animation);
    SpriteData* sprite=animation->sprite_data();
    if (*reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08)!=sprite->texture_id) {
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08)=sprite->texture_id;
        process_graphics.get_device()->SetTexture(0,
            reinterpret_cast<AnimationQuadSubmitOwner*>(this)->texture_for_sprite(
                *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E08)));
    }
    graphics_disable_depth_writes(&process_graphics);
    if (*reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)!=1) {
        process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(6),0);
        process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(3),0);
        *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6000E0E)=1;
    }
    process_graphics.get_device()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,vertex_count-2,stream,sizeof(SpriteTexturedVertex));
    return 0;
}
} // namespace th20
