#pragma once

#include "Vector3.hpp"

namespace th20 {

// XY operations preserve the destination's z lane. Rotation permits aliasing.
void polar(Vector3& destination, float direction, float length);
void rotate_xy(Vector3& destination, const Vector3& input, float direction);
float vector_direction(const Vector3& input);
float floor_scalar(float value);
float angle_difference(float first, float second);

} // namespace th20
