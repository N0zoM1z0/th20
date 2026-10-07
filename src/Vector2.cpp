#include "Vector2.hpp"

namespace th20 {

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2 Vector2::operator+(const Vector2& other) const { return Vector2(x+other.x,y+other.y); }
Vector2 Vector2::operator-(const Vector2& other) const { return Vector2(x-other.x,y-other.y); }
Vector2 Vector2::operator*(float factor) const { return Vector2(x*factor,y*factor); }

} // namespace th20
