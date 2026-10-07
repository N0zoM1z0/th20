#pragma once

#include <cstddef>

namespace th20 {

// Actual two-float value constructed in Bullet, Region and LaserSegment.
struct Vector2 {
    float x;
    float y;

    Vector2();
    Vector2(float x, float y);
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float factor) const;
};

static_assert(sizeof(Vector2) == 8);
static_assert(offsetof(Vector2, y) == 4);

} // namespace th20
