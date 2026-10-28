#include "BulletScreenBounds.hpp"
namespace th20 {
extern const float native_neg_384;
extern const float native_pos_384;
extern const float native_448;
extern const float native_two;
std::int32_t bullet_position_outside_screen(const Vector3& pos,
                                            float width, float height) {
    return ((pos.x + width <= native_neg_384 / native_two) ||
            (pos.x - width >= native_pos_384 / native_two) ||
            (pos.y + height <= 0.0f) ||
            (native_448 <= pos.y - height)) ? 1 : 0;
}
} // namespace th20
