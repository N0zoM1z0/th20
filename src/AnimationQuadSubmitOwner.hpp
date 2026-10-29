#pragma once
// Local, provisionally named derived renderer ABI. No new instance/storage;
// original method signatures remain subject to native PE attestation.
#include "AnimationDrawModeOwner.hpp"
#include <cstdint>

struct IDirect3DBaseTexture9;
namespace th20 {
struct AnimationQuadSubmitOwner : AnimationDrawModeOwner {
    IDirect3DBaseTexture9* texture_for_sprite(std::uint32_t);
    void prepare_texture_states(Animation*);
    void bind_native_texture_state(Animation*); // actual original 0x00445BC0
    void select_render_color_mode(std::uint8_t);
    std::int32_t append_quad(SpriteTexturedVertex*);
};
} // namespace th20
