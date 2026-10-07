#include "MotionMath.hpp"
#include "ScalarMath.hpp"
#include "CollisionGeometry.hpp"
#include <cmath>

namespace th20 {
namespace {
constexpr float pi = 3.1415927410125732f;
}

void polar(Vector3& destination, float direction, float length) {
    destination.x = std::cos(direction) * length;
    destination.y = std::sin(direction) * length;
}

void ellipse_polar(Vector3& destination, float direction, float axis_x, float axis_y) {
    destination.x = std::cos(direction) * axis_x;
    destination.y = std::sin(direction) * axis_y;
}

void normalize_to_length(Vector3& destination, const Vector3& input, float length) {
    float magnitude = scalar_math::square_root(input.x * input.x + input.y * input.y + input.z * input.z);
    if (geometry::absolute(magnitude) < 0.01f) {
        destination = input * length;
    } else {
        destination = (input / magnitude) * length;
    }
}

template<class Coordinate>
void rotate_xy(Coordinate& destination, const Coordinate& input, float direction) {
    const float sine = scalar_math::sine(direction);
    const float cosine = scalar_math::cosine(direction);
    const float rotated_x = input.x * cosine - input.y * sine;
    destination.y = input.y * cosine + input.x * sine;
    destination.x = rotated_x;
}

template<class Coordinate> void rotate_xy_array(Coordinate* destination, const Coordinate* input, float direction, std::uint32_t count) {
    const float sine = scalar_math::sine(direction);
    const float cosine = scalar_math::cosine(direction);
    while (count != 0) {
        const float rotated_x = input->x * cosine - input->y * sine;
        destination->y = input->y * cosine + input->x * sine;
        destination->x = rotated_x;
        ++destination;
        ++input;
        --count;
    }
}
template void rotate_xy(Vector2&, const Vector2&, float);
template void rotate_xy(Vector3&, const Vector3&, float);
template void rotate_xy_array(Vector2*, const Vector2*, float, std::uint32_t);
template void rotate_xy_array(Vector3*, const Vector3*, float, std::uint32_t);

float vector_direction(const Vector3& input) {
    return scalar_math::arctangent(input.y, input.x);
}

float floor_scalar(float value) {
    return static_cast<float>(std::floor(static_cast<double>(value)));
}

float angle_difference(float first, float second) {
    if (first - second > pi) return first - (pi * 2.0f + second);
    if (second - first > pi) return first - (second - pi * 2.0f);
    return first - second;
}

} // namespace th20
