#include "Motion.hpp"

namespace th20 {

float Motion::position_x() const { return position.x; }
float Motion::position_y() const { return position.y; }
void Motion::set_position_x(float value) { position.x = value; }
void Motion::set_position_y(float value) { position.y = value; }
void Motion::set_angle(float value) noexcept { angle_1c = value; }
void Motion::set_speed(float value) { value_18 = value; }
void Motion::select_linear() { flags.fields.mode = 0; }
void Motion::select_orbit() { flags.fields.mode = 2; }
void Motion::select_elliptic() { flags.fields.mode = 3; }

} // namespace th20
