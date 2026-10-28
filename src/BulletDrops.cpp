#include "Bullet.hpp"
#include "BulletScreenBounds.hpp"
#include "Item.hpp"
#include "GameRandom.hpp"

namespace th20 {
extern GameRandom script_random;
extern const float native_32;
extern const float native_neg_pi;
extern const float native_two;
extern const float native_speed;

// Complete native 419-byte cancellation-to-item gameplay routing. Preserve
// original per-branch Context lookups, signed remainder and short-circuit RNG.
void Bullet::cancel_drops(const Vector3& at, std::int32_t mode) {
    if (mode != 0) {
        if (!bullet_position_outside_screen(at, native_32, native_32)) {
            ++context->bullet_controller()->item_counter;
            if (mode == 1) {
                context->item_controller()->spawn_many(&at, 1, 13);
                return;
            }
            if (mode == 4) {
                if ((static_cast<std::int32_t>(context->bullet_controller()->item_counter) % 5 == 0) ||
                    ((static_cast<std::int32_t>(context->bullet_controller()->item_counter) % 5 == 2) &&
                     (script_random.next() % 2 == 0)) ||
                    ((static_cast<std::int32_t>(context->bullet_controller()->item_counter) % 5 == 4) &&
                     (script_random.next() % 3 == 0))) {
                    ItemInf* item_owner = context->item_controller();
                    item_owner->spawn(2, at, 0xffffffffu,
                                      native_neg_pi / native_two, native_speed, 0, 0, -1);
                } else {
                    context->item_controller()->spawn_many(&at, 1, 13);
                }
            }
        }
    }
}
} // namespace th20
