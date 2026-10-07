#pragma once

#include "Vector3.hpp"

namespace th20 {

// XY operations preserve the destination's z lane. Rotation permits aliasing.
void polar(Vector3& destination, float direction, float length);
void ellipse_polar(Vector3& destination, float direction, float axis_x, float axis_y);
// Below magnitude 0.01, multiply the original vector rather than divide it.
// The complete three-lane result permits destination/input aliasing.
void normalize_to_length(Vector3& destination, const Vector3& input, float length);
void rotate_xy(Vector3& destination, const Vector3& input, float direction);
float vector_direction(const Vector3& input);
float floor_scalar(float value);
float angle_difference(float first, float second);

} // namespace th20
