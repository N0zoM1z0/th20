#include "Rectangle.hpp"

namespace th20 {

IntPoint::IntPoint(std::int32_t x, std::int32_t y) : x(x), y(y) {}

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
