#pragma once
#include "Vector3.hpp"

namespace th20 {
// The original game-field rectangle excludes crossing radius-expanded points.
// The 224-unit vertical midpoint and float half-dimensions retain native SSE
// comparisons, including the original unordered/NaN outcomes.
int bullet_outside_rectangle(const Vector3& position, float radius_x,
                             float radius_y, float width, float height);
} // namespace th20
