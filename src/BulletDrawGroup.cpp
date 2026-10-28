// Complete nonexact original BulletController single draw-group iteration.
// The 273-byte original uses a distinct /Od float argument/temp ownership.
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
        if ((current->animation->base.flags.field_0a >> 5) != 0) {
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
