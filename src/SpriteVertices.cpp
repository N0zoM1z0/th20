#include "SpriteVertices.hpp"

namespace th20 {

SpriteCorner::SpriteCorner() : position(), u(0.0f), v(0.0f) {}

SpriteColoredVertex::SpriteColoredVertex()
    : position(), reciprocal_w(0.0f), color(0xffffffffu) {}

SpriteTexturedVertex::SpriteTexturedVertex()
    : position(), reciprocal_w(0.0f), color(0xffffffffu), u(0.0f), v(0.0f) {}

} // namespace th20
