#pragma once

#include <cstdint>
#include <cstddef>

namespace th20 {

struct Vector2;
struct Vector3;

// Actual atlas return value and Player fixed coordinates, without resources.
struct IntPoint {
    std::int32_t x;
    std::int32_t y;

    IntPoint();
    IntPoint(std::int32_t x, std::int32_t y);
    IntPoint operator+(const IntPoint& other) const;
    IntPoint operator-(const IntPoint& other) const;
    IntPoint operator*(std::int32_t factor) const;
    IntPoint operator/(std::int32_t divisor) const;
    // The original addition assignment returns a whole 8-byte value,
    // not a reference to its receiver.
    IntPoint operator+=(const IntPoint& other);
    // Original 70-byte signed fixed-coordinate to presentation vector.
    void to_vector3(Vector3& output) const;
    void assign_scaled(const Vector2& position);
};

// Native two-lane comparison against the same signed scalar.
bool operator!=(const IntPoint& input, std::int32_t amount);

struct IntRectangle {
    std::int32_t x;
    std::int32_t y;
    std::int32_t width;
    std::int32_t height;

    IntRectangle();
};

static_assert(sizeof(IntPoint) == 8);
static_assert(offsetof(IntPoint, y) == 4);
static_assert(sizeof(IntRectangle) == 16);
static_assert(offsetof(IntRectangle, y) == 4);
static_assert(offsetof(IntRectangle, width) == 8);
static_assert(offsetof(IntRectangle, height) == 12);

// REF-022: touching edges overlap; endpoint arithmetic wraps modulo 2^32.
bool rectangles_overlap(std::int32_t x, std::int32_t y,
                        std::int32_t width, std::int32_t height,
                        std::int32_t other_x, std::int32_t other_y,
                        std::int32_t other_width, std::int32_t other_height);

} // namespace th20
