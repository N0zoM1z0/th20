// Original entire Bullet command-7 player-homing velocity interpolation.
// Real typed clock, Player direction, Vector3 temporary and terminal Timer
// are maintained with the complete native 493-byte control-flow extent.
#include "Bullet.hpp"
#include "Player.hpp"
#include "ClockScalar.hpp"
#include "MotionMath.hpp"
#include "ScalarMath.hpp"
#include "BulletVelocityMagnitude.hpp"
namespace th20 {
std::int32_t Bullet::advance_command7() {
    if (commands.at(7).timer.at_least(commands.at(7).word_30)) {
        command_flags.words.low &= ~0x80000000u;
        return 1;
    } else {
        float relative_direction = context->player()->direction_to(position);
        float offset = commands.at(7).scalar_14;
        float target_direction = add_angles(offset,relative_direction);
        Vector3 target_velocity;
        polar(target_velocity,target_direction,commands.at(7).scalar_10);
        velocity += (target_velocity - velocity) * commands.at(7).vector_24.x;
        velocity.z = 0.0f;
        speed = bullet_velocity_magnitude(velocity);
        angle = vector_direction(velocity);
    }
    commands.at(7).timer++;
    return 0;
}
}
