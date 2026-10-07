#pragma once

#include <cstddef>

namespace th20 {

// REF-018: Card position and native vector arithmetic use three float lanes.
struct Vector3 {
    float x;
    float y;
    float z;

    // Native unchecked access returns a reference to the actual float subobject.
    // Requires index in [0,2]; byte addressing keeps the named coordinate storage.
    float& operator[](int index);
    Vector3();
    Vector3(float x, float y, float z);
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3& operator-=(const Vector3& other);
    Vector3 operator*(float factor) const;
    Vector3& operator*=(float factor);
    Vector3& operator+=(const Vector3& other);
};

static_assert(sizeof(Vector3) == 12);
static_assert(offsetof(Vector3, x) == 0);
static_assert(offsetof(Vector3, y) == 4);
static_assert(offsetof(Vector3, z) == 8);

} // namespace th20
