// Full original player-owned 777-byte Bullet rectangle hit/graze boss.
// Real focused/unfocused PlayerCollisionBounds, four reusable AABB limits,
// native 48px graze diameter, FrontInf dialogue and exact Player hit flow.
#include "Player.hpp"
#include "HudGauge.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace th20 {
extern FrontInf* process_front;
extern const float native_graze_diameter;
extern const float native_two;

std::int32_t Player::collision_rectangle(const Vector3& bullet_position,
                                         const Vector2& extents, std::int32_t mode) {
    Vector2 minimum, maximum;
    Vector3 player_minimum, player_maximum;

    if (focused_mode()) {
        player_minimum = position_ref() - collision_bounds.focus_extent;
        player_maximum = position_ref() + collision_bounds.focus_extent;
    } else {
        player_minimum = position_ref() - collision_bounds.normal_extent;
        player_maximum = position_ref() + collision_bounds.normal_extent;
    }

    minimum.x = bullet_position.x - extents.x / native_two;
    minimum.y = bullet_position.y - extents.y / native_two;
    maximum.x = extents.x / native_two + bullet_position.x;
    maximum.y = extents.y / native_two + bullet_position.y;

    if (maximum.x < player_minimum.x || maximum.y < player_minimum.y ||
        player_maximum.x < minimum.x || player_maximum.y < minimum.y) {
        minimum.x = bullet_position.x - native_graze_diameter / native_two;
        minimum.y = bullet_position.y - native_graze_diameter / native_two;
        maximum.x = native_graze_diameter / native_two + bullet_position.x;
        maximum.y = native_graze_diameter / native_two + bullet_position.y;
        if (maximum.x < player_minimum.x || maximum.y < player_minimum.y ||
            player_maximum.x < minimum.x || player_maximum.y < minimum.y) {
            return 0;
        }
        return 2;
    }
    if (process_front != nullptr && process_front->has_dialogue()) return 0;
    if (mode != 0) return 2;
    if (state_value() == 2) return 0;
    if (state_value() == 4) return 0;
    if (state_value() == 3) return 0;
    if (timer_2050.greater_than(0)) return 1;
    apply_player_hit();
    return 1;
}
} // namespace th20
