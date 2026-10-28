// Complete original 273-byte BulletController single-group draw loop.
// Still NONEXACT: the true high-three-bit mode and all 82 native mnemonic
// kinds are now reproduced, but /Od emits two extra SSE offset spill/reloads.
// All 8 original relocation targets and whole original boundary remain open
// to strict canonical acceptance until the float argument ABI is closed.
#include "Bullet.hpp"
#include "Animation.hpp"
#include "AnimationRuntimeOwner.hpp"
namespace th20 {
extern const float native_pi;
extern const float native_two;
std::int32_t BulletController::draw_group(std::int32_t group) {
    Bullet* current = draw_heads[group];
    while (current) {
        current->animation->vector_5bc = current->position;
        if (current->animation->base.flags.bits_0a.upper_3 != 0) {
            Animation* a = current->animation;
            float offset = native_pi / native_two;
            float rotation = add_angles(static_cast<float>(current->angle), offset);
            a->set_rotation(rotation);
        }
        if (((current->flags.bits >> 6) & 1u) != 0)
            current->animation->set_scale_58(current->scale, current->scale);
        current_animation_pool->draw(current->animation);
        current = current->draw_next;
    }
    return 1;
}
}
