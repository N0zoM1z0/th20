#include "Motion.hpp"
#include <cstring>

namespace th20 {

Motion::Motion() : position(), velocity(), value_18(0.0f), angle_1c(),
    value_20(0.0f), value_24(0.0f), angle_28(), value_2c(0.0f), angle_30(),
    value_34(0.0f), vector_38(), flags{} {}

void Motion::set_motion_vector(const Vector3& value) { vector_38 = value; }

void Motion::update() {
    update_velocity();
    update_position();
}

int Motion::outside_bounds(float x, float y, float width, float height) const {
    return x - width / 2.0f > position.x || position.x > x + width / 2.0f ||
        y - height / 2.0f > position.y || position.y > y + height / 2.0f ? 1 : 0;
}

} // namespace th20

namespace th20 {
Vector3& Motion::position_ref() { return position; }
void Motion::set_position(const Vector3& input) { position = input; }
void Motion::clear() { std::memset(static_cast<void*>(this), 0, sizeof(*this)); }
} // namespace th20
