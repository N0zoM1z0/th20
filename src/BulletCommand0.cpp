// Whole native Bullet command-0 timed speed interpolation. The original
// 16-frame gating, Angle conversion, polar call and timer advance are retained.
#include "Bullet.hpp"
#include "MotionMath.hpp"
namespace th20 {
extern const float native_five;
extern const float native_sixteen;
std::int32_t Bullet::advance_command0() {
    if (commands.at(0).timer.at_most(16)) {
        float remaining = native_five - commands.at(0).timer.fraction() * native_five / native_sixteen;
        float length = remaining + speed;
        float direction = static_cast<float>(angle);
        polar(velocity, direction, length);
    } else {
        command_flags.words.low &= ~1u;
        return 1;
    }
    commands.at(0).timer++;
    return 0;
}
}
