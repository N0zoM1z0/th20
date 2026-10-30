#pragma once
// Distinct original game-owned animation depth helpers; both cdecl and
// original length returned on x87 ST0. Never conflate with the CRT sqrt.
namespace th20 {
struct Vector3;
float animation_depth_squared(const Vector3& delta);
float animation_depth(const Vector3& delta);
}
