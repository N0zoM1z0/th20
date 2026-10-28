#pragma once

#include "Vector2.hpp"

namespace th20 {

// Native four-corner Bullet screen command uses true 8-byte XY values.
float cross_components(const Vector2& left, const Vector2& right);
float dot_components(const Vector2& left, const Vector2& right);

} // namespace th20
