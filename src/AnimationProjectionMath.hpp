#pragma once
// Original source-owned game projection math; Vector3 arithmetic returns
// a float via x87 ST0; the output-transform helper is a receiver member.
namespace th20 {
struct Vector3;
float animation_vector3_length(const Vector3& vector);
}
