// Entire original Player circle hit/graze classifier: true Player position,
// real PlayerRecord radius cap, focused and enlarged bullet radii, and the
// complete native 0/1/2 hit protocol with actual player damage handler.
#include "Player.hpp"
#include "PlayerRecord.hpp"
#include "CollisionGeometry.hpp"
#include "HudGauge.hpp"
#include "Context.hpp"
#include <algorithm>

namespace th20 {
extern FrontInf* process_front;
extern const float native_radius_hundred;
extern const float native_boost_factor;
extern const float native_radius_margin_divisor;
extern const float native_radius_margin_minimum;

std::int32_t PlayerRecord::collision_radius_multiplier() {
    field_e8 = std::clamp(field_e8, 0, 100);
    return field_e8;
}

std::uint32_t Player::collision_expansion_enabled() const {
    return (entity_flags.bits >> 4) & 1u;
}

std::int32_t Player::collision_circle(const Vector3& bullet_position,
                                      float bullet_radius, std::int32_t mode) {
    const float squared_distance = geometry::squared_distance_xy(position_ref(), bullet_position);
    float radius;
    if (focused) {
        radius = collision_bounds.focus_radius;
    } else {
        radius = collision_bounds.normal_radius;
    }
    float adjusted = radius;
    adjusted = static_cast<float>(context->player_record()->collision_radius_multiplier()) * adjusted / native_radius_hundred;
    if (collision_expansion_enabled() != 0) {
        adjusted = collision_expansion * native_boost_factor * adjusted;
    }
    if (squared_distance >= adjusted * adjusted + bullet_radius * bullet_radius) {
        float margin = bullet_radius / native_radius_margin_divisor;
        if (margin < native_radius_margin_minimum) margin = native_radius_margin_minimum;
        if (squared_distance >= (adjusted + margin) * (adjusted + margin) + bullet_radius * bullet_radius) return 0;
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
