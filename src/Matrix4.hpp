#pragma once

namespace th20 {

// Contiguous float matrix value. Construction clears all sixteen elements.
struct Matrix4 {
    float elements[4][4];
    Matrix4();
};

static_assert(sizeof(Matrix4) == 64);

} // namespace th20
