// Complete native three-coordinate squared depth and square-root wrapper.
// These functions are independent native E8 calls of original mode7/8
// drawing and do not yet establish the exactness of their render callers.
#include "AnimationDepthMath.hpp"
#include "Vector3.hpp"
#include "ScalarMath.hpp"

namespace th20 {
float __cdecl animation_depth_squared(const Vector3& delta) {
    return delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
}
float __cdecl animation_depth(const Vector3& delta) {
    return scalar_math::square_root(animation_depth_squared(delta));
}
}
