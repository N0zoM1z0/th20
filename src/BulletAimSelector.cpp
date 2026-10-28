#include "BulletAimSelector.hpp"
#include "Player.hpp"
#include "EnemyController.hpp"
#include "Enemy.hpp"
#include "Session.hpp"
#include "CollisionGeometry.hpp"
#include "GameRandom.hpp"
#include "Angle.hpp"

namespace th20 {
extern GameRandom process_bullet_random;
// Seven original native immutable float boundaries; true values are
// -999990, 999990, 1999990, 2999990, 3999990, 4999990 and pi.
// They remain external data until game startup/global ownership is resolved.
extern const float native_selector_min;
extern const float native_selector_player_lo;
extern const float native_selector_player_hi;
extern const float native_selector_wobble_lo;
extern const float native_selector_wobble_hi;
extern const float native_selector_random_hi;
extern const float native_pi;

float select_bullet_aim(std::int32_t view_index, float fixed_angle,
                        const Vector3& position, float direction_code,
                        float deviation) {
    if (deviation <= native_selector_min)
        deviation = native_pi;

    // The original nested conditional expression preserves its float
    // intermediate-return slots and the native NaN/threshold comparisons.
    return direction_code <= native_selector_min
        ? fixed_angle
        : ((direction_code >= native_selector_player_lo &&
            direction_code < native_selector_player_hi)
            ? player(view_index)->direction_to(position) + deviation
            : (direction_code >= native_selector_wobble_lo &&
               direction_code < native_selector_wobble_hi)
                ? player(view_index)->direction_to(position)
                      + process_bullet_random.signed_unit() * deviation
                : (direction_code >= native_selector_wobble_hi &&
                   direction_code < native_selector_random_hi)
                    ? process_bullet_random.signed_unit() * deviation
                          + fixed_angle
                    : (direction_code >= native_selector_random_hi
                        ? geometry::direction_xy(
                              position,
                              enemy_controller(view_index)->selected(0)->position_ref())
                        : direction_code));
}
} // namespace th20
