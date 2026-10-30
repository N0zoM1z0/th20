// Genuine original compound Vector2 operators (72B and 77B).
// These modify their receiver but return a Vector2 by VALUE (native thiscall
// hidden result pointer), unlike conventional reference-return operators.
#include "Vector2.hpp"
namespace th20 {
Vector2 Vector2::operator*=(float factor) {
    x*=factor;
    y*=factor;
    return *this;
}
Vector2 Vector2::operator+=(const Vector2& other) {
    x+=other.x;
    y+=other.y;
    return *this;
}
} // namespace th20
