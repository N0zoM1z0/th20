// Original three complete 97-byte game renderer quad-draw mode wrappers.
// The four native shared vertices are 28-byte SpriteTexturedVertex records.
// The locally named method receiver is the same existing renderer owner ABI,
// not a separately allocated manager or a claim about historical C++ names.
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"
#include "SpriteVertices.hpp"

namespace th20 {
extern SpriteTexturedVertex native_quad_vertices[4];
static_assert(sizeof(SpriteTexturedVertex) == 0x1C);

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

std::int32_t AnimationDrawModeOwner::draw_quad_mode0(Animation* animation) {
    setup_quad_a(animation, &native_quad_vertices[0], &native_quad_vertices[1],
                 &native_quad_vertices[2], &native_quad_vertices[3]);
    return render_quad(animation, 1);
}

std::int32_t AnimationDrawModeOwner::draw_quad_mode1(Animation* animation) {
    setup_quad_b(animation, &native_quad_vertices[0], &native_quad_vertices[1],
                 &native_quad_vertices[2], &native_quad_vertices[3]);
    return render_quad(animation, 0);
}

std::int32_t AnimationDrawModeOwner::draw_quad_mode2(Animation* animation) {
    setup_quad_a(animation, &native_quad_vertices[0], &native_quad_vertices[1],
                 &native_quad_vertices[2], &native_quad_vertices[3]);
    return render_quad(animation, 0);
}
std::int32_t AnimationDrawModeOwner::draw_quad_mode4(Animation* animation) {
    if (prepare_quad_mode4(animation)) return -1;
    return render_quad(animation, 0);
}

std::int32_t AnimationDrawModeOwner::draw_quad_mode5(Animation* animation) {
    prepare_quad_mode5(animation);
    std::int32_t result = render_quad(animation, 0);
    native_quad_vertices[3].reciprocal_w = 1.0f;
    native_quad_vertices[2].reciprocal_w = 1.0f;
    native_quad_vertices[1].reciprocal_w = 1.0f;
    native_quad_vertices[0].reciprocal_w = 1.0f;
    return result;
}

} // namespace th20
