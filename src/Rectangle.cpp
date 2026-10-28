#include "Rectangle.hpp"

namespace th20 {

IntPoint::IntPoint() : x(0), y(0) {}
IntPoint::IntPoint(std::int32_t x, std::int32_t y) : x(x), y(y) {}

IntPoint IntPoint::operator+(const IntPoint& other) const {
    return IntPoint(static_cast<std::int32_t>(std::uint32_t(x) + std::uint32_t(other.x)),
                    static_cast<std::int32_t>(std::uint32_t(y) + std::uint32_t(other.y)));
}

// Original 48-byte two-lane signed-coordinate subtraction, with
// native wrapping low-32-bit operations and aggregate hidden return.
IntPoint IntPoint::operator-(const IntPoint& other) const {
    return IntPoint(static_cast<std::int32_t>(std::uint32_t(x) - std::uint32_t(other.x)),
                    static_cast<std::int32_t>(std::uint32_t(y) - std::uint32_t(other.y)));
}

// Complete 45-byte native coordinate scaling, returning an IntPoint by value.
IntPoint IntPoint::operator*(std::int32_t factor) const {
    return IntPoint(static_cast<std::int32_t>(std::uint32_t(x) * std::uint32_t(factor)),
                    static_cast<std::int32_t>(std::uint32_t(y) * std::uint32_t(factor)));
}

// Complete 45-byte native signed per-lane integer division.
IntPoint IntPoint::operator/(std::int32_t divisor) const {
    return IntPoint(x / divisor, y / divisor);
}

// Native 65-byte in-place addition returns a value, not IntPoint&.
IntPoint IntPoint::operator+=(const IntPoint& other) {
    x = static_cast<std::int32_t>(std::uint32_t(x) + std::uint32_t(other.x));
    y = static_cast<std::int32_t>(std::uint32_t(y) + std::uint32_t(other.y));
    return *this;
}

// Native 49-byte whole-point scalar inequality, shared by Player options.
bool operator!=(const IntPoint& input, std::int32_t amount) {
    return input.x != amount || input.y != amount;
}

IntRectangle::IntRectangle() : x(0), y(0), width(0), height(0) {}

bool rectangles_overlap(std::int32_t x, std::int32_t y,
                        std::int32_t width, std::int32_t height,
                        std::int32_t other_x, std::int32_t other_y,
                        std::int32_t other_width, std::int32_t other_height) {
    return x <= static_cast<std::int32_t>(static_cast<std::uint32_t>(other_x) +
                                         static_cast<std::uint32_t>(other_width)) &&
           static_cast<std::int32_t>(static_cast<std::uint32_t>(x) +
                                     static_cast<std::uint32_t>(width)) >= other_x &&
           y <= static_cast<std::int32_t>(static_cast<std::uint32_t>(other_y) +
                                         static_cast<std::uint32_t>(other_height)) &&
           static_cast<std::int32_t>(static_cast<std::uint32_t>(y) +
                                     static_cast<std::uint32_t>(height)) >= other_y;
}

} // namespace th20
