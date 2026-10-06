#include "CollisionGeometry.hpp"

namespace th20::geometry {

float absolute(float value) {
    return 0.0f > value ? -value : value;
}

bool circle_point(float x, float y, float center_x, float center_y, float radius) {
    return (center_x - x) * (center_x - x) +
           (center_y - y) * (center_y - y) <= radius * radius;
}

bool rectangle_point(float x, float y, float center_x, float center_y,
                     float width, float height) {
    return absolute(x - center_x) < width / 2.0f &&
           absolute(y - center_y) < height / 2.0f;
}

} // namespace th20::geometry
