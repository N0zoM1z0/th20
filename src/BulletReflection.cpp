// Native complete Bullet vertical-boundary reflection and its actual
// typed controller/vector and command-slot interfaces. Original naming is
// inferred; full code and relocations are compared to the locked PE.
#include "Bullet.hpp"
#include "MotionMath.hpp"
namespace th20 {
extern const float native_448;
extern const float native_pi;
extern const float native_two;
std::int32_t Bullet::reflect_at_y_limit() {
    float upper = context->bullet_controller()->vector_4c_ref().y <= 0.0f
        ? commands.at(4).vector_18.y
        : context->bullet_controller()->vector_4c_ref().y;
    if (position.y >= native_448/native_two + upper/native_two) {
        if (!(commands.at(4).word_3c & 0x10)) {
            angle = -static_cast<float>(angle);
            position.y = (native_448 + upper) - position.y;
        }
        return 1;
    }
    return 0;
}
}

namespace th20 {
ExtendedCommand& BulletExtendedCommands::at(std::int32_t index) { return slots[index]; }
Vector2& BulletController::vector_4c_ref() { return vector_4c; }
} // namespace th20

namespace th20 {
// The two complete horizontal edge checks use the same controller dimensions
// and original command index as vertical reflection, with separate full native
// float, angle and position flow (including original unordered comparisons).
int Bullet::reflect_at_right_x() {
    float limit = context->bullet_controller()->vector_4c_ref().x <= 0.0f
        ? commands.at(4).vector_18.x
        : context->bullet_controller()->vector_4c_ref().x;
    if (position.x >= limit / native_two) {
        if (!(commands.at(4).word_3c & 0x10)) {
            angle = -static_cast<float>(angle) - native_pi;
            angle = add_angles(static_cast<float>(angle), 0.0f);
            position.x = limit - position.x;
        }
        return 1;
    }
    return 0;
}
int Bullet::reflect_at_left_x() {
    float limit = context->bullet_controller()->vector_4c_ref().x <= 0.0f
        ? commands.at(4).vector_18.x
        : context->bullet_controller()->vector_4c_ref().x;
    if (position.x < -limit / native_two) {
        if (!(commands.at(4).word_3c & 0x10)) {
            angle = -static_cast<float>(angle) - native_pi;
            angle = add_angles(static_cast<float>(angle), 0.0f);
            position.x = -limit - position.x;
        }
        return 1;
    }
    return 0;
}
} // namespace th20
