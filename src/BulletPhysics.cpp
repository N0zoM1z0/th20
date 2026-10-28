// Entire original game Bullet physics state machine, including the native
// four-way state dispatch and its real post-increment / Timer / interpolation
// protocol. The 1,404B command11 and 12,140B command sequencer remain
// separate external full game methods, not synthetic subbranches.
#include "Bullet.hpp"
#include "Animation.hpp"
#include "AnimationFile.hpp"
#include "ClockScalar.hpp"
#include "BulletWrapBounds.hpp"
#include "MotionMath.hpp"

namespace th20 {
extern const float native_one;


std::int32_t Bullet::update_physics() {
    flags.bits |= 0x400u;
    timer_508++;
    if (((flags.bits >> 3) & 1u) != 0) {
        deactivate();
        return -1;
    }
    const float previous_clock = static_cast<float>(default_timer_clock);
    if (state != 2 && state != 3 && state != 4 && !((flags.bits >> 9) & 1u)) {
        default_timer_clock.set(timer_4d8.fraction() * timer_4e8.fraction());
    }
    if (((command_flags.words.low >> 22) & 1u) != 0) {
        scale = interpolation_474.sample();
        if (interpolation_474.duration_value() == 0) {
            command_flags.words.low &= ~0x400000u;
            if (scale == native_one) flags.bits &= ~0x40u;
        }
    }
    switch (state) {
    case 2:
        position += velocity / 2.0f;
reset_command_timers:
        timer_4d8 = native_one;
        timer_4e8 = native_one;
        default_timer_clock.set(native_one);
        if (animation->variables().field_00 == 0) break;
        state = 1;
        [[fallthrough]];
    case 1: {
        std::int32_t completed;
command_loop:
        if (!((command_flags.words.low >> 26) & 1u)) {
            run_extended_commands();
            if (state == 2) goto reset_command_timers;
        }
        completed=0;
        if (command_flags.words.low & 0x1u) completed += advance_command0();
        if ((command_flags.words.low >> 2) & 1u) completed += advance_command1();
        if ((command_flags.words.low >> 21) & 1u) completed += advance_command10();
        if ((command_flags.words.low >> 3) & 1u) completed += advance_command2();
        if ((command_flags.words.low >> 4) & 1u) completed += advance_command3();
        if ((command_flags.words.low >> 6) & 1u) completed += handle_boundary();
        if ((command_flags.words.low >> 31) & 1u) completed += advance_command7();
        if ((command_flags.words.low >> 17) & 1u) completed += advance_command8();
        if ((command_flags.words.low >> 19) & 1u) completed += advance_command9();
        if ((command_flags.words.low >> 8) & 1u) completed += advance_command11();
        if ((command_flags.words.low >> 30) & 1u) {
            if (commands.at(5).timer.at_most(0)) {
                command_flags.words.low &= ~0x40000000u;
                ++completed;
            } else {
                commands.at(5).timer--;
            }
        }
        if ((command_flags.words.low >> 26) & 1u) {
            if (commands.at(13).timer.at_most(0)) {
                command_flags.words.low &= ~0x4000000u;
                flags.bits &= ~0x200u;
                ++completed;
                goto command_loop;
            } else {
                flags.bits |= 0x200u;
                commands.at(13).timer--;
            }
        }
        if (completed != 0) goto command_loop;
        if (!((flags.bits >> 9) & 1u)) {
            position += velocity * static_cast<float>(default_timer_clock);
        }
        break;
    }
    case 3:
        timer_4d8 = native_one;
        timer_4e8 = native_one;
        default_timer_clock.set(native_one);
        position += (velocity * static_cast<float>(default_timer_clock)) / 2.0f;
        break;
    case 4:
        timer_4d8 = native_one;
        timer_4e8 = native_one;
        default_timer_clock.set(native_one);
        break;
    }
after_motion:
    if (animation->sprite_data() != nullptr) {
        if (((command_flags.words.low >> 12) & 1u) != 0) wrap_screen();
        if (!((command_flags.words.low >> 8) & 1u) && static_cast<std::int32_t>(command_index) < 1) {
            float height = animation->sprite_data()->extent_48 * scale;
            float width = animation->sprite_data()->extent_4c * scale;
            if (bullet_wrap_outside_with_floor(position,width,height)) {
                deactivate();
                default_timer_clock.set(previous_clock);
                return -1;
            }
        }
    }
    if (field_18 != 0) --field_18;
    if (static_cast<std::int32_t>(command_index) > 0) --command_index;
    if (!((flags.bits >> 9) & 1u) && animation->update() != 0) {
        deactivate();
        default_timer_clock.set(previous_clock);
        return -1;
    }
    default_timer_clock.set(previous_clock);
    return 0;
}
} // namespace th20
