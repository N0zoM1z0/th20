#include "BulletRectangle.hpp"

namespace th20 {
// These are independently identified original immutable PE float objects.
extern const float native_two;
extern const float native_frame_origin_y;

int bullet_outside_rectangle(const Vector3& position, float radius_x,
                             float radius_y, float width, float height) {
    int outside;
    if (!(position.x + radius_x <= -width / native_two ||
          position.x - radius_x >= width / native_two ||
          position.y + radius_y <= native_frame_origin_y - height / native_two ||
          position.y - radius_y >= native_frame_origin_y + height / native_two))
        outside = 0;
    else
        outside = 1;
    return outside;
}
} // namespace th20
