#include "BulletRayMath.hpp"

namespace th20 {

float cross_components(const Vector2& left, const Vector2& right) {
    return left.x * right.y - left.y * right.x;
}

float dot_components(const Vector2& left, const Vector2& right) {
    return left.x * right.x + left.y * right.y;
}

} // namespace th20
