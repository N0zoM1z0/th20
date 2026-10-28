// Complete game-owned Bullet command-2 angle/speed interpolation path.
// Both clock-gated scalar updates, Angle normalization, polar motion and
// terminal Timer advance reproduce their original complete control flow.
#include "Bullet.hpp"
#include "ClockScalar.hpp"
#include "Angle.hpp"
#include "MotionMath.hpp"
namespace th20 {
std::int32_t Bullet::advance_command2() {
    if (commands.at(2).timer.at_least(commands.at(2).word_30)) {
        command_flags.words.low &= ~8u;
        return 1;
    } else {
        float a_delta = commands.at(2).scalar_14 * static_cast<float>(default_timer_clock);
        float prior_angle = static_cast<float>(angle);
        angle = add_angles(prior_angle,a_delta);
        float speed_delta = commands.at(2).scalar_10 * static_cast<float>(default_timer_clock);
        float old_speed = speed;
        speed = old_speed + speed_delta;
        float new_speed = speed;
        float new_angle = static_cast<float>(angle);
        polar(velocity,new_angle,new_speed);
    }
    commands.at(2).timer++;
    return 0;
}
}
