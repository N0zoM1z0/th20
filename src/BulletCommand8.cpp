// Complete original Bullet command8 position-interpolation and velocity path.
// Preserve the exact VectorInterpolation<Vector3> native sample result and
// original Timer early-exit/else with common trailing increment.
#include "Bullet.hpp"
#include "MotionMath.hpp"
#include "ScalarMath.hpp"
namespace th20 {
extern const float native_velocity_threshold;
std::int32_t Bullet::advance_command8() {
    if (commands.at(8).timer.at_least(commands.at(8).word_30)) {
        command_flags.words.low &= ~0x20000u;
        position = commands.at(8).vector_24;
        speed = commands.at(8).scalar_10;
        polar(velocity, static_cast<float>(angle), speed);
        velocity.z = 0.0f;
        return 1;
    } else {
        if (commands.at(8).timer.equals(0)) {
            interpolation_420.set_start(position);
        }
        Vector3 old_position = position;
        velocity = interpolation_420.sample() - old_position;
        float abs_x = scalar_math::absolute(velocity.x);
        if (abs_x > native_velocity_threshold ||
            scalar_math::absolute(velocity.y) > native_velocity_threshold) {
            angle = scalar_math::arctangent(velocity.y, velocity.x);
        }
        velocity.z = 0.0f;
    }
    commands.at(8).timer++;
    return 0;
}
}
