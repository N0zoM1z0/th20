#pragma once
#include "Vector3.hpp"

namespace th20 {
// Actual native Bullet XY velocity magnitude, returned through x87 ST0.
float bullet_velocity_magnitude(const Vector3& velocity);
}
