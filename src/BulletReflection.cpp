// Native complete Bullet vertical-boundary reflection and its actual
// typed controller/vector and command-slot interfaces. Original naming is
// inferred; full code and relocations are compared to the locked PE.
#include "Bullet.hpp"
namespace th20 {
extern const float native_448;
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
