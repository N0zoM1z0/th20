#pragma once
// Both native corner projection methods save an unused ECX receiver. The
// original source class name is unknown; no runtime state is allocated here.
#include "Animation.hpp"
#include "Vector3.hpp"
namespace th20 {
struct NativeQuadAxisLayout { float corners[3][4]; };
static_assert(sizeof(NativeQuadAxisLayout) == 0x30);
extern const NativeQuadAxisLayout native_quad_axis_layout[2];
extern Vector3 native_projection_world_position;
struct NativeAnimationCornerProjector {
    void project_corners_43eb40(Animation* animation,
                                Vector3* a, Vector3* b, Vector3* c, Vector3* d);
    // Complete natural source exists; 1486B original, 1485B NONEXACT C++.
    void project_rotated_corners_43ef20(Animation* animation,
                                        Vector3* a, Vector3* b, Vector3* c, Vector3* d);
};
}
