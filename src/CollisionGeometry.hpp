#pragma once

namespace th20::geometry {

// Native comparison-based absolute value preserves negative zero and NaN sign.
float absolute(float value);
bool circle_point(float x, float y, float center_x, float center_y, float radius);
// Axis-aligned rectangle uses full dimensions and excludes its boundary.
bool rectangle_point(float x, float y, float center_x, float center_y,
                     float width, float height);

// Native collinear handling orders endpoints by x, then compares paired y.
// This preserves the game's descending/vertical segment boundary behavior.
bool segment_intersection(float ax, float ay, float bx, float by,
                          float cx, float cy, float dx, float dy);
bool ellipse_point(float x, float y, float center_x, float center_y,
                   float axis_x, float axis_y, float direction);
// Polygon tests exclude points whose radial segment touches an edge.
// Nonpositive counts retain the native vacuous true result.
bool regular_polygon_point(float x, float y, float center_x, float center_y,
                           float radius, float direction, int sides);
bool star_point(float x, float y, float center_x, float center_y,
                float radius_a, float radius_b, float direction, int sides);
bool circle_regular_polygon(float x, float y, float radius, float center_x, float center_y,
                            float shape_radius, float direction, int sides);
bool circle_star(float x, float y, float radius, float center_x, float center_y,
                 float radius_a, float radius_b, float direction, int sides);
// Uses native containment shortcuts followed by at least eight perimeter samples.
bool circle_ellipse(float x, float y, float radius, float center_x, float center_y,
                    float axis_x, float axis_y, float direction);

} // namespace th20::geometry
