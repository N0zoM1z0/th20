#pragma once

#include "Vector2.hpp"
#include "Vector3.hpp"

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

// Four cyclic rectangle edges, shared by intersection routines.
extern const int rectangle_edges[4][2];
// These distances use XY even when the input has a z lane. Scalar endpoint
// arguments are interleaved: x1, x2, y1, y2. Results return through ST0.
float squared_norm_xy(float, float);
float norm_xy(float, float);
float squared_distance_xy(float, float, float, float);
float distance_xy(float, float, float, float);
float squared_distance_xy(const Vector3&, const Vector3&);
float distance_xy(const Vector3&, const Vector3&);
// A vertical line returns full-EAX 1, slope 0 and its x as intercept.
int line_parameters(float&, float&, float, float, float, float);
// Failure leaves outputs unchanged; vertical tolerances are 0.01 and 0.001.
int segment_intersection_point(float&, float&, float,float,float,float,float,float,float,float);
// Uses a finite +/-1000 line. The native corner-rotation gate tests line
// direction rather than rectangle direction. Output z lanes remain unchanged.
int line_rectangle_intersections(Vector3&,Vector3&,const Vector3&,float,float,float,float,float,float);
// Planar nearest point; the complete output inherits center.z.
float nearest_width_segment(const Vector3&,float,float,const Vector3&,Vector3&);
// Boundary-only segment tests return false for nonpositive side counts.
bool segment_regular_polygon(float,float,float,float,float,float,float,float,int);
bool segment_star(float,float,float,float,float,float,float,float,float,int);
bool rectangle_circle(float,float,float,float,float,float,float,float);
// Finite sampling and rotated signed dimensions preserve native behavior.
bool rectangle_ellipse(float,float,float,float,float,float,float,float,float,float);
// Polygon/star center shortcuts use the unrotated rectangle.
bool rectangle_regular_polygon(float,float,float,float,float,float,float,float,float,int);
bool rectangle_rectangle(float,float,float,float,float,float,float,float,float,float);
bool rectangle_star(float,float,float,float,float,float,float,float,float,float,int);
bool rectangle_contains_any_four(float,float,float,float,float,const Vector2*);
// Inclusive rotated point test, unlike strict axis-aligned rectangle_point.
bool rotated_rectangle_point(float,float,float,float,float,float,float);

} // namespace th20::geometry
