#pragma once

namespace th20::geometry {

// Native comparison-based absolute value preserves negative zero and NaN sign.
float absolute(float value);
bool circle_point(float x, float y, float center_x, float center_y, float radius);
// Axis-aligned rectangle uses full dimensions and excludes its boundary.
bool rectangle_point(float x, float y, float center_x, float center_y,
                     float width, float height);

} // namespace th20::geometry
