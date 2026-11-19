#pragma once

#include "Vector2.hpp"

namespace th20 {
// Original 95-byte screen-coordinate normalization leaf at 0x00438EB0.
void normalize_coordinates_438eb0(Vector2* output, const Vector2* input);
} // namespace th20
