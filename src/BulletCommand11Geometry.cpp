#include "BulletCommand11Geometry.hpp"
#include "CollisionGeometry.hpp"
#include "ScalarMath.hpp"

namespace th20 {
// Original game epsilon at 0x0056E1A0 is 0.01f. Its independent
// native destination is bound in the strict manifest, not defined here.
extern const float native_0_01;

void normalize_vector2(Vector2& output, const Vector2& input) {
    float magnitude = scalar_math::square_root(input.x * input.x + input.y * input.y);
    if (geometry::absolute(magnitude) < native_0_01) {
        output = input;
    } else {
        output.x = input.x / magnitude;
        output.y = input.y / magnitude;
    }
}
} // namespace th20
