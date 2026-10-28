// Full native Player position view at 0x460850 (19B) and 157-byte
// direction-to-target at 0x4FF350. Constants are three independently
// identified original PE floating objects: zero, pi, and two. Their
// original variable names are inferred and no definitions are fabricated.
#include "Player.hpp"
#include "ScalarMath.hpp"
namespace th20 {
extern const float native_zero;
extern const float native_pi;
extern const float native_two;
Vector3& Player::position_ref() { return position; }
float Player::direction_to(const Vector3& target) {
    const float dx=position_ref().x-target.x;
    const float dy=position_ref().y-target.y;
    if (dy==native_zero && dx==native_zero)
        return native_pi/native_two;
    return scalar_math::arctangent(dy,dx);
}
}
