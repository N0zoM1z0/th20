#include "BulletWrapBounds.hpp"

namespace th20 {
extern const float native_two;
extern const float native_left_wrap_width;
extern const float native_384;
extern const float native_448;
extern const float native_floor_margin;

std::int32_t bullet_wrap_outside(const Vector3& position, float width, float height) {
    std::int32_t outside;
    if (!(position.x + width / native_two <= native_left_wrap_width / native_two ||
          position.x - width / native_two >= native_384 / native_two ||
          position.y + height / native_two <= 0.0f ||
          position.y - height / native_two >= native_448)) {
        outside = 0;
    } else {
        outside = 1;
    }
    return outside;
}

std::int32_t bullet_wrap_outside_with_floor(const Vector3& position,
                                            float width, float height) {
    std::int32_t outside;
    if (!(position.x + width / native_two <= native_left_wrap_width / native_two ||
          position.x - width / native_two >= native_384 / native_two ||
          position.y + height / native_two <= native_floor_margin ||
          position.y - height / native_two >= native_448)) {
        outside = 0;
    } else {
        outside = 1;
    }
    return outside;
}
} // namespace th20
