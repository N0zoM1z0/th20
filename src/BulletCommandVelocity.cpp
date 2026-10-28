// Original game-specific Bullet command 1/10 velocity and direction updates.
// Both whole bodies use the same exact XY velocity magnitude and native
// scalar math/ClockScalar ABI, while preserving distinct command slots.
#include "Bullet.hpp"
#include "ClockScalar.hpp"
#include "ScalarMath.hpp"
#include "BulletVelocityMagnitude.hpp"

namespace th20 {
extern const float native_velocity_threshold;
std::int32_t Bullet::advance_command1() {
    if (commands.at(1).timer.at_least(commands.at(1).word_30)) {
        command_flags.words.low &= ~4u;
        return 1;
    } else {
        float delta_speed = commands.at(1).scalar_10 * static_cast<float>(default_timer_clock);
        float prior_speed = speed;
        speed = prior_speed + delta_speed;
        velocity += commands.at(1).vector_24 * static_cast<float>(default_timer_clock);
        float abs_x = scalar_math::absolute(velocity.x);
        if (abs_x > native_velocity_threshold ||
            scalar_math::absolute(velocity.y) > native_velocity_threshold) {
            angle = scalar_math::arctangent(velocity.y,velocity.x);
            speed = bullet_velocity_magnitude(velocity);
        }
    }
    commands.at(1).timer++;
    return 0;
}

std::int32_t Bullet::advance_command10() {
    if (commands.at(10).timer.at_least(commands.at(10).word_30)) {
        command_flags.words.low &= ~2097152u;
        return 1;
    } else {
        float delta_speed = commands.at(10).scalar_10 * static_cast<float>(default_timer_clock);
        float prior_speed = speed;
        speed = prior_speed + delta_speed;
        velocity += commands.at(10).vector_24 * static_cast<float>(default_timer_clock);
        float abs_x = scalar_math::absolute(velocity.x);
        if (abs_x > native_velocity_threshold ||
            scalar_math::absolute(velocity.y) > native_velocity_threshold) {
            angle = scalar_math::arctangent(velocity.y,velocity.x);
            speed = bullet_velocity_magnitude(velocity);
        }
    }
    commands.at(10).timer++;
    return 0;
}
} // namespace th20
