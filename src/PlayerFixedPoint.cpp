// Original Player option fixed-coordinate scaling: native 128.0f and
// two separately truncated x/y lanes, not a generic integer conversion.
#include "Rectangle.hpp"
#include "Vector2.hpp"

namespace th20 {
extern const float native_128;
void IntPoint::assign_scaled(const Vector2& position) {
    x = static_cast<std::int32_t>(position.x * native_128);
    y = static_cast<std::int32_t>(position.y * native_128);
}
} // namespace th20
