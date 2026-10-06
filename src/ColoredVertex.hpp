#pragma once

#include "Vector3.hpp"

#include <cstddef>
#include <cstdint>

namespace th20 {

// REF-021: ScreenInf's untextured D3D9 quad uses four 20-byte vertices.
struct ColoredVertex {
    Vector3 position;
    float reciprocal_w;
    std::uint32_t color;

    ColoredVertex();
};

static_assert(sizeof(ColoredVertex) == 20);
static_assert(offsetof(ColoredVertex, position) == 0);
static_assert(offsetof(ColoredVertex, reciprocal_w) == 12);
static_assert(offsetof(ColoredVertex, color) == 16);

} // namespace th20
