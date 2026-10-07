#pragma once

#include "Vector3.hpp"
#include "Vector2.hpp"
#include <cstdint>

namespace th20 {

// XY operations preserve the destination's z lane. Rotation permits aliasing.
void polar(Vector3& destination, float direction, float length);
void ellipse_polar(Vector3& destination, float direction, float axis_x, float axis_y);
// Below magnitude 0.01, multiply the original vector rather than divide it.
// The complete three-lane result permits destination/input aliasing.
void normalize_to_length(Vector3& destination, const Vector3& input, float length);
// The native scalar head is shared by actual Vector2 and Vector3 values.
// Both explicit instantiations preserve the same XY-only operation and ABI.
template<class Coordinate>
void rotate_xy(Coordinate& destination, const Coordinate& input, float direction);
// Forward traversal permits identical arrays and preserves each destination z.
// Count signedness is unproved; the established domain is a valid array length.
template<class Coordinate>
void rotate_xy_array(Coordinate* destination, const Coordinate* input,
                     float direction, std::uint32_t count);
float vector_direction(const Vector3& input);
float floor_scalar(float value);
float angle_difference(float first, float second);

} // namespace th20
