#pragma once

#include <cstdint>
#include <cstddef>

namespace th20 {

// Actual atlas return value and Job rectangle, with no owning resources.
struct IntPoint {
    std::int32_t x;
    std::int32_t y;

    IntPoint(std::int32_t x, std::int32_t y);
};

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
