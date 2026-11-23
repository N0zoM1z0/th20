#pragma once

namespace th20 {

// Contiguous float matrix value. Construction clears all sixteen elements.
struct Matrix4 {
    float elements[4][4];
    Matrix4();
};

// Native 0x00472840 matrix identity helper; returns the output matrix.
Matrix4* matrix_identity(Matrix4* output);

static_assert(sizeof(Matrix4) == 64);

} // namespace th20
