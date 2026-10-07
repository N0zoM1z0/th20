#include "Angle.hpp"
#include "MotionMath.hpp"

namespace th20 {
namespace {
constexpr float pi = 3.1415927410125732f;
}

float normalize_angle(float value) {
    if (value > pi) {
        int count = 0;
        do {
            value = value - pi * 2.0f;
            if (count++ > 32) break;
        } while (value > pi);
    } else if (value < -pi) {
        int count = 0;
        do {
            value = pi * 2.0f + value;
            if (count++ > 32) break;
        } while (value < -pi);
    }
    return value;
}

Angle::Angle() : value(0.0f) {}
Angle::Angle(float input) : value(0.0f) { value = normalize_angle(input); }

Angle::operator float() const { return value; }

Angle& Angle::operator=(float input) {
    value = normalize_angle(input);
    return *this;
}

Angle& Angle::operator+=(float input) {
    value = normalize_angle(value + input);
    return *this;
}

Angle Angle::operator+(float input) const { return Angle(value + input); }

Angle Angle::operator-(const Angle& other) const {
    return Angle(angle_difference(value, other.value));
}

} // namespace th20
