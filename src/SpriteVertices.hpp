#pragma once

#include "Vector3.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

struct SpriteCorner {
    Vector3 position;
    float u, v;
    SpriteCorner();
};

struct SpriteColoredVertex {
    Vector3 position;
    float reciprocal_w;
    std::uint32_t color;
    SpriteColoredVertex();
};

struct SpriteTexturedVertex {
    Vector3 position;
    float reciprocal_w;
    std::uint32_t color;
    float u, v;
    SpriteTexturedVertex();
};

static_assert(sizeof(SpriteCorner) == 20);
static_assert(offsetof(SpriteCorner, u) == 12);
static_assert(sizeof(SpriteColoredVertex) == 20);
static_assert(offsetof(SpriteColoredVertex, color) == 16);
static_assert(sizeof(SpriteTexturedVertex) == 28);
static_assert(offsetof(SpriteTexturedVertex, u) == 20);

} // namespace th20
