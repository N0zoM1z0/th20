#pragma once

#include "Vector2.hpp"

namespace th20 {
// Native full two-lane cross/dot products used by Bullet command 11.
// The original shared game geometry helper names remain inferred.
void normalize_vector2(Vector2& output, const Vector2& input);
} // namespace th20
