#include "CollisionGeometry.hpp"
#include "MotionMath.hpp"
#include "Angle.hpp"
namespace th20::geometry {
namespace {
constexpr float pi = 3.1415927410125732f;
}
#ifdef _MSC_VER
#pragma strict_gs_check(push, on)
#endif
bool segment_intersection(float ax, float ay, float bx, float by,
                          float cx, float cy, float dx, float dy) {
    float side_c = (ax - bx) * (cy - ay) + (ay - by) * (ax - cx);
    float side_d = (ax - bx) * (dy - ay) + (ay - by) * (ax - dx);
    if (side_c * side_d > 0.0f) return false;
    if (side_c == 0.0f && side_d == 0.0f) {
        if (ax > bx) {
            side_c = bx; bx = ax; ax = side_c;
            side_c = by; by = ay; ay = side_c;
        }
        if (cx > dx) {
            side_c = dx; dx = cx; cx = side_c;
            side_c = dy; dy = cy; cy = side_c;
        }
        if (dx >= ax && dy >= ay && bx >= cx && by >= cy) return true;
        return false;
    }
    side_c = (cx - dx) * (ay - cy) + (cy - dy) * (cx - ax);
    side_d = (cx - dx) * (by - cy) + (cy - dy) * (cx - bx);
    if (side_c * side_d > 0.0f) return false;
    return true;
}
bool ellipse_point(float x, float y, float center_x, float center_y,
                   float axis_x, float axis_y, float direction) {
    Vector3 delta;
    delta.x = x - center_x;
    delta.y = y - center_y;
    rotate_xy(delta, delta, -direction);
    if (delta.x * delta.x / (axis_x * axis_x) + delta.y * delta.y / (axis_y * axis_y) <= 1.0f) return true;
    return false;
}
bool regular_polygon_point(float x, float y, float center_x, float center_y,
                           float radius, float direction, int sides) {
    Vector3 edge[2];
    Vector3 radial(radius, 0.0f, 0.0f);
    for (int i = 0; i < sides; ++i) {
        rotate_xy(edge[0], radial, direction);
        direction += pi * 2.0f / sides;
        direction = normalize_angle(direction);
        rotate_xy(edge[1], radial, direction);
        edge[0] += {center_x, center_y, 0.0f};
        edge[1] += {center_x, center_y, 0.0f};
        if (segment_intersection(edge[0].x, edge[0].y, edge[1].x, edge[1].y, x, y, center_x, center_y)) return false;
    }
    return true;
}
bool star_point(float x, float y, float center_x, float center_y,
                float radius_a, float radius_b, float direction, int sides) {
    Vector3 edge[2];
    Vector3 radial_a(radius_a, 0.0f, 0.0f);
    Vector3 radial_b(radius_b, 0.0f, 0.0f);
    for (int i = 0; i < sides * 2; ++i) {
        rotate_xy(edge[0], *(i % 2 == 0 ? &radial_a : &radial_b), direction);
        direction += pi * 2.0f / sides / 2.0f;
        direction = normalize_angle(direction);
        rotate_xy(edge[1], *(i % 2 != 0 ? &radial_a : &radial_b), direction);
        edge[0] += {center_x, center_y, 0.0f};
        edge[1] += {center_x, center_y, 0.0f};
        if (segment_intersection(edge[0].x, edge[0].y, edge[1].x, edge[1].y, x, y, center_x, center_y)) return false;
    }
    return true;
}
bool circle_regular_polygon(float x, float y, float radius, float center_x, float center_y,
                            float shape_radius, float direction, int sides) {
    if (circle_point(center_x, center_y, x, y, radius)) return true;
    Vector3 near_point{center_x - x, center_y - y, 0.0f};
    normalize_to_length(near_point, near_point, radius);
    near_point += {x, y, 0.0f};
    return regular_polygon_point(near_point.x, near_point.y, center_x, center_y, shape_radius, direction, sides);
}
bool circle_star(float x, float y, float radius, float center_x, float center_y,
                 float radius_a, float radius_b, float direction, int sides) {
    if (circle_point(center_x, center_y, x, y, radius)) return true;
    Vector3 near_point{center_x - x, center_y - y, 0.0f};
    normalize_to_length(near_point, near_point, radius);
    near_point += {x, y, 0.0f};
    return star_point(near_point.x, near_point.y, center_x, center_y, radius_a, radius_b, direction, sides);
}
bool circle_ellipse(float x, float y, float radius, float center_x, float center_y,
                    float axis_x, float axis_y, float direction) {
    float maximum = axis_x > axis_y ? axis_x : axis_y;
    float minimum = axis_x < axis_y ? axis_x : axis_y;
    if (minimum > radius &&
        ellipse_point(x, y, center_x, center_y, axis_x - radius, axis_y - radius, direction)) return true;
    Vector3 delta;
    delta.x = x - center_x;
    delta.y = y - center_y;
    rotate_xy(delta, delta, -direction);
    if (radius > maximum && delta.x * delta.x + delta.y * delta.y <=
        (radius - maximum) * (radius - maximum)) return true;
    if (radius < 1.0f) return false;
    if (maximum < 1.0f) return false;
    Vector3 perimeter;
    float angle = -pi;
    if (radius > maximum) {
        int count = static_cast<int>(axis_x + axis_y) / 4;
        if (count < 8) count = 8;
        for (int i = 0; i < count; ++i) {
            ellipse_polar(perimeter, angle, axis_x, axis_y);
            angle += pi * 2.0f / count;
            if (circle_point(perimeter.x, perimeter.y, delta.x, delta.y, radius)) return true;
        }
    } else {
        int count = static_cast<int>(radius / 4.0f);
        if (count < 8) count = 8;
        for (int i = 0; i < count; ++i) {
            polar(perimeter, angle, radius);
            angle += pi * 2.0f / count;
            if (ellipse_point(perimeter.x + delta.x, perimeter.y + delta.y,
                              0.0f, 0.0f, axis_x, axis_y, 0.0f)) return true;
        }
    }
    return false;
}
#ifdef _MSC_VER
#pragma strict_gs_check(pop)
#endif
}
