#pragma once
#include <cstdint>

namespace th20 {
struct Vector3;
// Native whole three-dimensional difference, XY-squared-distance predicate.
// Return is full EAX integer, not an AL-only bool; callers use this ABI.
std::int32_t bullet_distance_within(const Vector3& first,
                                    const Vector3& second, float radius);
} // namespace th20
