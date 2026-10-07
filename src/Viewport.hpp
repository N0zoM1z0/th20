#pragma once
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "FogValue.hpp"
#include <cstdint>
namespace th20 {
// Default construction preserves matrix elements, as in the native SDK value.
struct TransformMatrix {
    float elements[4][4];
    TransformMatrix();
};
struct NativeViewport {
    std::uint32_t x, y, width, height;
    float min_z, max_z;
};
struct ViewportState {
    Vector3 vector_00, vector_0c, vector_18, vector_24;
    Vector3 vector_30, vector_3c, vector_48;
    float field_of_view;
    std::uint32_t field_58, field_5c;
    TransformMatrix view, projection;
    NativeViewport viewport;
    std::uint32_t field_f8;
    std::int32_t offset_x, offset_y;
    NativeViewport adjusted_viewport;
    Vector2 bounds_11c, bounds_124;
    Vector2 points[3];
    Vector3 final_vector;
    FogValue fog;
    ViewportState();
};
static_assert(sizeof(ViewportState)==0x16c);
}
