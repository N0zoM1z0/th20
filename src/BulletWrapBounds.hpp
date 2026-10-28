#pragma once
#include "Vector3.hpp"
#include <cstdint>

namespace th20 {
// Two original, complete playfield-exit tests. They differ only in the
// vertical lower threshold: screen zero versus an original -64.0f margin.
std::int32_t bullet_wrap_outside(const Vector3& position, float width, float height);
std::int32_t bullet_wrap_outside_with_floor(const Vector3& position,
                                            float width, float height);
} // namespace th20
