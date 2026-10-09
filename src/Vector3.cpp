#include "Vector3.hpp"

namespace th20 {

float& Vector3::operator[](int index) {
    return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + index * sizeof(float));
}

Vector3::Vector3() noexcept : x(0.0f), y(0.0f), z(0.0f) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3& Vector3::operator-=(const Vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float factor) const {
    return Vector3(x * factor, y * factor, z * factor);
}

Vector3 Vector3::operator/(float divisor) const {
    return Vector3(x / divisor, y / divisor, z / divisor);
}

Vector3& Vector3::operator*=(float factor) {
    x *= factor;
    y *= factor;
    z *= factor;
    return *this;
}

Vector3& Vector3::operator+=(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

} // namespace th20

namespace th20 {
Vector3& Vector3::operator/=(float divisor) {
    x /= divisor; y /= divisor; z /= divisor;
    return *this;
}
} // namespace th20
