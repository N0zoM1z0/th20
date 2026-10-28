#include "BulletVelocityMagnitude.hpp"
#include "RenderMesh.hpp"
#include "ScalarMath.hpp"

namespace th20 {
float bullet_velocity_magnitude(const Vector3& velocity) {
    return scalar_math::square_root(squared_norm_xy(velocity));
}
}
