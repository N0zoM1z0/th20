#pragma once

// Receiver type with exactly the native ECX/stack method ABI of the existing
// AnimationPoolOwner. Name is provisional; no separate game owner is stored.
#include "AnimationRuntimeOwner.hpp"
#include <cstdint>

namespace th20 {
class Animation;
struct SpriteTexturedVertex;
extern SpriteTexturedVertex native_quad_vertices[4];

struct AnimationDrawModeOwner : AnimationPoolOwner {
    void setup_quad_a(Animation*, SpriteTexturedVertex*, SpriteTexturedVertex*,
                      SpriteTexturedVertex*, SpriteTexturedVertex*);
    void setup_quad_b(Animation*, SpriteTexturedVertex*, SpriteTexturedVertex*,
                      SpriteTexturedVertex*, SpriteTexturedVertex*);
    std::int32_t render_quad(Animation*, std::int32_t mode);
    std::int32_t draw_quad_mode0(Animation* animation);
    std::int32_t draw_quad_mode1(Animation* animation);
    std::int32_t draw_quad_mode2(Animation* animation);
    std::int32_t draw_quad_mode4(Animation* animation);
    std::int32_t draw_quad_mode5(Animation* animation);
    std::int32_t prepare_quad_mode4(Animation* animation);
    void prepare_quad_mode5(Animation* animation);
};

} // namespace th20
