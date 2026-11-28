// Laser extended-command steppers. They follow the same timer-gated pattern
// as the Bullet commands: command 1 and 10 accelerate the velocity vector,
// command 2 turns and accelerates, command 3 performs counted turns.
#include "Angle.hpp"
#include "ClockScalar.hpp"
#include "LaserCurveInf.hpp"
#include "LaserLineInf.hpp"
#include "MotionMath.hpp"
#include "ScalarMath.hpp"
#include "SoundInf.hpp"

namespace th20 {

extern const float native_velocity_threshold;

LaserExtendedCommands::LaserExtendedCommands() noexcept {}

ExtendedCommand& LaserExtendedCommands::at(std::int32_t index) {
    return slots[index];
}

std::int32_t Laser::advance_command1() { return 0; }
std::int32_t Laser::advance_command10() { return 0; }
std::int32_t Laser::advance_command2() { return 0; }
std::int32_t Laser::advance_command3() { return 0; }

std::int32_t LaserLineInf::advance_command1() {
    if (commands.at(1).timer.at_least(commands.at(1).word_30)) {
        reinterpret_cast<std::uint32_t&>(active_commands) &= ~4u;
        return 1;
    } else {
        float delta_speed = commands.at(1).scalar_10 * static_cast<float>(default_timer_clock);
        float prior_speed = field_7c;
        field_7c = prior_speed + delta_speed;
        velocity += commands.at(1).vector_24 * static_cast<float>(default_timer_clock);
        float abs_x = scalar_math::absolute(velocity.x);
        if (abs_x > native_velocity_threshold ||
            scalar_math::absolute(velocity.y) > native_velocity_threshold) {
            angle = scalar_math::arctangent(velocity.y, velocity.x);
        }
    }
    commands.at(1).timer++;
    return 0;
}

// The Curve body is identical and folds with the Line body at 0x004D58D0.
std::int32_t LaserCurveInf::advance_command1() {
    if (commands.at(1).timer.at_least(commands.at(1).word_30)) {
        reinterpret_cast<std::uint32_t&>(active_commands) &= ~4u;
        return 1;
    } else {
        float delta_speed = commands.at(1).scalar_10 * static_cast<float>(default_timer_clock);
        float prior_speed = field_7c;
        field_7c = prior_speed + delta_speed;
        velocity += commands.at(1).vector_24 * static_cast<float>(default_timer_clock);
        float abs_x = scalar_math::absolute(velocity.x);
        if (abs_x > native_velocity_threshold ||
            scalar_math::absolute(velocity.y) > native_velocity_threshold) {
            angle = scalar_math::arctangent(velocity.y, velocity.x);
        }
    }
    commands.at(1).timer++;
    return 0;
}

std::int32_t LaserLineInf::advance_command10() {
    if (commands.at(10).timer.at_least(commands.at(10).word_30)) {
        reinterpret_cast<std::uint32_t&>(active_commands) &= ~2097152u;
        return 1;
    } else {
        float delta_speed = commands.at(10).scalar_10 * static_cast<float>(default_timer_clock);
        float prior_speed = field_7c;
        field_7c = prior_speed + delta_speed;
        velocity += commands.at(10).vector_24 * static_cast<float>(default_timer_clock);
        float abs_x = scalar_math::absolute(velocity.x);
        if (abs_x > native_velocity_threshold ||
            scalar_math::absolute(velocity.y) > native_velocity_threshold) {
            angle = scalar_math::arctangent(velocity.y, velocity.x);
        }
    }
    commands.at(10).timer++;
    return 0;
}

std::int32_t LaserCurveInf::advance_command2() {
    if (commands.at(2).timer.at_least(commands.at(2).word_30)) {
        reinterpret_cast<std::uint32_t&>(active_commands) &= ~8u;
        return 1;
    } else {
        float a_delta = commands.at(2).scalar_14 * static_cast<float>(default_timer_clock);
        float prior_angle = angle;
        angle = add_angles(prior_angle, a_delta);
        float speed_delta = commands.at(2).scalar_10 * static_cast<float>(default_timer_clock);
        float old_speed = field_7c;
        field_7c = old_speed + speed_delta;
        polar(velocity, angle, field_7c);
    }
    commands.at(2).timer++;
    return 0;
}

std::int32_t LaserLineInf::advance_command3() {
    float new_speed;
    if (commands.at(3).timer.at_least(commands.at(3).word_30)) {
        if (parameters.field_4c >= 0) process_sound.request_effect(parameters.field_4c, 0);
        ++commands.at(3).word_38;
        float a_delta = commands.at(3).scalar_14;
        float prior_angle = angle;
        angle = prior_angle + a_delta;
        field_7c = commands.at(3).scalar_10;
        new_speed = field_7c;
        commands.at(3).timer = 0;
        if (static_cast<std::int32_t>(commands.at(3).word_38) >=
            static_cast<std::int32_t>(commands.at(3).word_34)) {
            polar(velocity, angle, new_speed);
            reinterpret_cast<std::uint32_t&>(active_commands) &= ~0x10u;
            return 1;
        }
    } else {
        new_speed = field_7c - (field_7c * commands.at(3).timer.fraction()) /
                    static_cast<float>(static_cast<std::int32_t>(commands.at(3).word_30));
    }
    polar(velocity, angle, new_speed);
    commands.at(3).timer++;
    return 0;
}

std::int32_t LaserCurveInf::advance_command3() {
    float new_speed;
    if (commands.at(3).timer.at_least(commands.at(3).word_30)) {
        if (parameters.motion_sound >= 0) process_sound.request_effect(parameters.motion_sound, 0);
        ++commands.at(3).word_38;
        float a_delta = commands.at(3).scalar_14;
        float prior_angle = angle;
        angle = prior_angle + a_delta;
        field_7c = commands.at(3).scalar_10;
        new_speed = field_7c;
        commands.at(3).timer = 0;
        if (static_cast<std::int32_t>(commands.at(3).word_38) >=
            static_cast<std::int32_t>(commands.at(3).word_34)) {
            polar(velocity, angle, new_speed);
            reinterpret_cast<std::uint32_t&>(active_commands) &= ~0x10u;
            return 1;
        }
    } else {
        new_speed = field_7c - (field_7c * commands.at(3).timer.fraction()) /
                    static_cast<float>(static_cast<std::int32_t>(commands.at(3).word_30));
    }
    polar(velocity, angle, new_speed);
    commands.at(3).timer++;
    return 0;
}

} // namespace th20
