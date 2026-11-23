#include "LaserParameters.hpp"
#include "LaserInfiniteInf.hpp"
#include "LaserBeamInf.hpp"

namespace th20 {

void Laser::set_parameter_flag(std::uint32_t) {}
void Laser::set_angle(float value) { angle = value; }
void Laser::set_speed(float value) { speed = value; }
void Laser::set_field_7c(float value) { field_7c = value; }
void Laser::set_parameter_vector_704(const Vector3& value) {
    *reinterpret_cast<Vector3*>(reinterpret_cast<std::byte*>(this) + 0x704) = value;
}
void Laser::set_parameter_field_714(float value) {
    *reinterpret_cast<float*>(reinterpret_cast<std::byte*>(this) + 0x714) = value;
}
void Laser::set_handle(std::uint32_t value) { handle = value; }

void LaserInfiniteInf::set_position(const Vector3& value) {
    position = value;
    parameters.position = value;
}
void LaserInfiniteInf::set_parameter_velocity(const Vector3& value) {
    parameters.velocity = value;
}
void LaserInfiniteInf::set_angular_velocity(float value) {
    parameters.angular_velocity = value;
}
void LaserBeamInf::set_parameter_flag(std::uint32_t value) {
    parameters.flags = (parameters.flags & ~1u) | (value & 1u);
}

} // namespace th20
