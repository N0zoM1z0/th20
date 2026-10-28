// Original entire game Bullet command-3 speed/angle transition, including
// all seven switch arms and both interpolating motion paths. The associated
// 28-byte native switch table and two-byte alignment are separately verified.
#include "Bullet.hpp"
#include "Player.hpp"
#include "SoundInf.hpp"
#include "MotionMath.hpp"
namespace th20 {
std::int32_t Bullet::advance_command3() {
    float new_speed;
    if (commands.at(3).timer.at_least(commands.at(3).word_30)) {
        if (static_cast<std::int32_t>(field_40) >= 0) process_sound.request_effect(field_40, 0);
        ++commands.at(3).word_38;
        switch (commands.at(3).word_3c) {
            case 0:
            case 5:
                angle += commands.at(3).scalar_14;
                break;
            case 1:
            case 6:
                angle = context->player()->direction_to(position) + commands.at(3).scalar_14;
                break;
            case 2:
                angle = commands.at(3).scalar_14;
                break;
            case 3:
                angle = commands.at(3).scalar_14;
                break;
            case 4:
                angle = commands.at(3).scalar_14;
                break;
        }
        speed = commands.at(3).scalar_10;
        new_speed = speed;
        commands.at(3).timer = 0;
        if (static_cast<std::int32_t>(commands.at(3).word_38) >=
            static_cast<std::int32_t>(commands.at(3).word_34)) {
            polar(velocity,static_cast<float>(angle),new_speed);
            command_flags.words.low &= ~0x10u;
            return 1;
        }
    } else {
        new_speed = speed - (speed * commands.at(3).timer.fraction()) /
                    static_cast<float>(static_cast<std::int32_t>(commands.at(3).word_30));
    }
    polar(velocity,static_cast<float>(angle),new_speed);
    commands.at(3).timer++;
    return 0;
}
}
