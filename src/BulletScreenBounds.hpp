#pragma once
#include "Vector3.hpp"
#include <cstdint>
namespace th20 {
// Complete native integer-result edge check for the Bullet cancellation
// gameplay frame. It uses the original locked x86 single-precision objects.
std::int32_t bullet_position_outside_screen(const Vector3& position,
                                            float half_width, float half_height);
} // namespace th20
