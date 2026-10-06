#include "Rectangle.hpp"

#include <array>
#include <cassert>
#include <cstdint>
#include <limits>
#include <vector>

struct Box {
    int x, y, width, height;
};

int main() {
    std::vector<Box> boxes;
    for (int x = -2; x <= 2; ++x)
        for (int y = -2; y <= 2; ++y)
            for (int width = 0; width <= 2; ++width)
                for (int height = 0; height <= 2; ++height)
                    boxes.push_back({x, y, width, height});

    // An independent lattice intersection checks inclusive edges and corners.
    for (const Box& a : boxes) {
        for (const Box& b : boxes) {
            bool expected = false;
            for (int px = -2; px <= 4; ++px) {
                for (int py = -2; py <= 4; ++py) {
                    const bool in_a = px >= a.x && px <= a.x + a.width &&
                                      py >= a.y && py <= a.y + a.height;
                    const bool in_b = px >= b.x && px <= b.x + b.width &&
                                      py >= b.y && py <= b.y + b.height;
                    expected |= in_a && in_b;
                }
            }
            assert(th20::rectangles_overlap(a.x, a.y, a.width, a.height,
                                           b.x, b.y, b.width, b.height) == expected);
        }
    }

    constexpr auto low = std::numeric_limits<std::int32_t>::min();
    constexpr auto high = std::numeric_limits<std::int32_t>::max();
    // Overflow changes the endpoint ordering; it must not invoke signed UB.
    assert(!th20::rectangles_overlap(high, 0, 1, 0, high, 0, 0, 0));
    assert(!th20::rectangles_overlap(0, high, 0, 1, 0, high, 0, 0));
    assert(th20::rectangles_overlap(low, 0, -1, 0, 0, 0, 0, 0));
    assert(th20::rectangles_overlap(0, low, 0, -1, 0, 0, 0, 0));
    assert(th20::rectangles_overlap(high, high, 0, 0, high, high, 0, 0));
}
