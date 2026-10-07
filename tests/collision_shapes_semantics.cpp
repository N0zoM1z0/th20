#include "CollisionGeometry.hpp"
#include "MotionMath.hpp"
#include <cassert>
#include <cmath>
#include <initializer_list>

using namespace th20;
using namespace th20::geometry;

int main() {
    Vector3 input{3.0f, 4.0f, 12.0f};
    Vector3 output;
    normalize_to_length(output, input, 26.0f);
    assert(output.x == 6.0f && output.y == 8.0f && output.z == 24.0f);
    assert(input.x == 3.0f && input.y == 4.0f && input.z == 12.0f);
    normalize_to_length(input, input, 13.0f);
    assert(input.x == 3.0f && input.y == 4.0f && input.z == 12.0f);
    Vector3 tiny{0.005f, 0.0f, 0.0f};
    normalize_to_length(tiny, tiny, 10.0f);
    assert(std::abs(tiny.x - 0.05f) < 0.000001f);
    Vector3 threshold{0.01f, 0.0f, 0.0f};
    normalize_to_length(threshold, threshold, 2.0f);
    assert(threshold.x == 2.0f);
    normalize_to_length(output, Vector3{}, 100.0f);
    assert(output.x == 0.0f && output.y == 0.0f && output.z == 0.0f);
    output = Vector3{6.0f, -8.0f, 10.0f} / 2.0f;
    assert(output.x == 3.0f && output.y == -4.0f && output.z == 5.0f);
    output.z = 123.0f;
    ellipse_polar(output, 0.0f, 7.0f, 4.0f);
    assert(output.x == 7.0f && output.y == 0.0f && output.z == 123.0f);
    ellipse_polar(output, 1.5707963705062866f, 7.0f, 4.0f);
    assert(std::abs(output.x) < 0.000001f && output.y == 4.0f && output.z == 123.0f);

    assert(segment_intersection(0, 0, 4, 4, 0, 4, 4, 0));
    assert(!segment_intersection(0, 0, 1, 1, 2, 0, 3, 1));
    assert(segment_intersection(0, 0, 2, 0, 2, 0, 4, 0));
    assert(segment_intersection(4, 0, 0, 0, 1, 0, 2, 0));
    // Native paired-y comparisons reject these geometrically overlapping lines.
    assert(!segment_intersection(0, 4, 4, 0, 1, 3, 3, 1));
    assert(!segment_intersection(0, 4, 0, 0, 0, 1, 0, 3));
    assert(ellipse_point(3, 0, 0, 0, 3, 2, 0));
    assert(!ellipse_point(3.01f, 0, 0, 0, 3, 2, 0));
    assert(ellipse_point(0, 2.9f, 0, 0, 3, 2, 1.5707963705062866f));
    assert(!ellipse_point(2.9f, 0, 0, 0, 3, 2, 1.5707963705062866f));

    for (int sides : {3, 4, 5, 8, 12}) {
        assert(regular_polygon_point(0, 0, 0, 0, 10, 0, sides));
        assert(!regular_polygon_point(30, 0, 0, 0, 10, 0, sides));
        assert(star_point(0, 0, 0, 0, 10, 5, 0, sides));
        assert(!star_point(30, 0, 0, 0, 10, 5, 0, sides));
        assert(circle_regular_polygon(0, 0, 1, 0, 0, 10, 0, sides));
        assert(!circle_regular_polygon(30, 0, 1, 0, 0, 10, 0, sides));
        assert(circle_star(0, 0, 1, 0, 0, 10, 5, 0, sides));
        assert(!circle_star(30, 0, 1, 0, 0, 10, 5, 0, sides));
    }
    assert(!regular_polygon_point(10, 0, 0, 0, 10, 0, 4));
    assert(!star_point(10, 0, 0, 0, 10, 5, 0, 4));
    assert(regular_polygon_point(100, 100, 0, 0, 10, 0, 0));
    assert(star_point(100, 100, 0, 0, 10, 5, 0, -1));

    assert(circle_ellipse(0, 0, 1, 0, 0, 10, 5, 0));
    assert(circle_ellipse(0, 0, 20, 0, 0, 10, 5, 0));
    assert(!circle_ellipse(100, 0, 2, 0, 0, 10, 5, 0));
    assert(circle_ellipse(10.5f, 0, 1, 0, 0, 10, 5, 0));
    assert(circle_ellipse(11, 0, 1, 0, 0, 10, 5, 0));
    assert(!circle_ellipse(11.1f, 0, 1, 0, 0, 10, 5, 0));
    assert(!circle_ellipse(2, 0, 0.5f, 0, 0, 0.5f, 0.5f, 0));
    assert(circle_ellipse(0, 0, 0.1f, 0, 0, 10, 5, 0));
}
