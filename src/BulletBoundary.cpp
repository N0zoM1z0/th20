// Full original native Bullet boundary-routing boss (832 bytes).
// Four complete typed reflection functions are called directly. The original
// four-edge geometry predicate at 0x00485420 is now the separately
// reconstructed complete native BulletRectangle.cpp function.
#include "Bullet.hpp"
#include "BulletRectangle.hpp"
#include "SoundInf.hpp"
#include "MotionMath.hpp"
namespace th20 {
extern const float native_zero;
extern const float native_speed_override_threshold;

int Bullet::handle_boundary() {
    if ((context->bullet_controller()->vector_4c_ref().x <= 0.0f &&
         bullet_outside_rectangle(position, 0.0f, 0.0f,
                       commands.at(4).vector_18.x, commands.at(4).vector_18.y)) ||
        (context->bullet_controller()->vector_4c_ref().x > native_zero &&
         bullet_outside_rectangle(position, 0.0f, 0.0f,
                      context->bullet_controller()->vector_4c_ref().x,
                      context->bullet_controller()->vector_4c_ref().y))) {
        std::int32_t reflected = 0;
        if ((commands.at(4).word_3c & 1) && reflect_at_upper_y()) reflected = 1;
        if ((commands.at(4).word_3c & 2) && reflect_at_y_limit()) reflected = 1;
        if ((commands.at(4).word_3c & 8) && reflect_at_right_x()) reflected = 1;
        if ((commands.at(4).word_3c & 4) && reflect_at_left_x()) reflected = 1;
        if (reflected) {
            if (commands.at(4).scalar_10 > native_speed_override_threshold)
                speed = commands.at(4).scalar_10;
            polar(velocity, static_cast<float>(angle), speed);
            ++commands.at(4).word_30;
            if (static_cast<std::int32_t>(field_40) >= 0) process_sound.request_effect(field_40,0);
        }
        if (static_cast<std::int32_t>(commands.at(4).word_30) >= static_cast<std::int32_t>(commands.at(4).word_34)) {
            command_flags.words.low &= ~0x40u;
            return 1;
        }
    }
    return 0;
}
}
