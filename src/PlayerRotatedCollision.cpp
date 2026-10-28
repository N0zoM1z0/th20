// Entire original 661-byte Player rotated rectangle/circle hit-and-graze
// boss, two full native geometry intersections, true Player collision radius
// and focused-mode margins, genuine dialogue/invulnerability/hit handling.
#include "Player.hpp"
#include "HudGauge.hpp"
#include "CollisionGeometry.hpp"
#include "Context.hpp"
#include "PlayerRecord.hpp"

namespace th20 {
extern FrontInf* process_front;
extern const float native_radius_hundred;
extern const float native_rotated_graze_margin;

std::int32_t Player::collision_rectangle_circle(const Vector3& source,
                                                float width,float height,
                                                float angle,std::int32_t mode) {
    Vector3 bullet_position;
    bullet_position=source;
    float selected_radius;
    if (focused_mode()) selected_radius=collision_bounds.focus_radius;
    else selected_radius=collision_bounds.normal_radius;
    float radius = selected_radius;
    radius=static_cast<float>(context->player_record()->collision_radius_multiplier())*radius/native_radius_hundred;
    float graze_radius;
    if (focused_mode()) graze_radius=collision_bounds.focus_radius+native_rotated_graze_margin;
    else graze_radius=collision_bounds.normal_radius+native_rotated_graze_margin;
    if (!geometry::rectangle_circle(bullet_position.x,bullet_position.y,angle,height,width,
                                    position_ref().x,position_ref().y,graze_radius)) return 0;
    if (!geometry::rectangle_circle(bullet_position.x,bullet_position.y,angle,height,width,
                                    position_ref().x,position_ref().y,radius)) return 2;
    if (process_front && process_front->has_dialogue()) return 0;
    if (mode != 0) return 2;
    if (state_value()==2) return 0;
    if (state_value()==4) return 0;
    if (state_value()==3) return 0;
    if (timer_2050.greater_than(0)) return 0;
    apply_player_hit();
    return 1;
}
} // namespace th20
