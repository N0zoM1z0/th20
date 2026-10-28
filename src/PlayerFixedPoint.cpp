// Original Player option fixed-coordinate scaling: native 128.0f and
// two separately truncated x/y lanes, not a generic integer conversion.
#include "Rectangle.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace th20 {
extern const float native_128;
void IntPoint::assign_scaled(const Vector2& position) {
    x = static_cast<std::int32_t>(position.x * native_128);
    y = static_cast<std::int32_t>(position.y * native_128);
}
// Entire original 70-byte /Od member: both signed fixed coordinates
// become floats divided by original 128.0f; Z is reset to 0.
void IntPoint::to_vector3(Vector3& output) const {
    output.x = static_cast<float>(x) / native_128;
    output.y = static_cast<float>(y) / native_128;
    output.z = 0.0f;
}

} // namespace th20
