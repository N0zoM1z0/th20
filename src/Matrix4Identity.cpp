#include "Matrix4.hpp"

namespace th20 {

Matrix4* matrix_identity(Matrix4* output) {
    output->elements[3][2] = 0.0f;
    output->elements[3][1] = 0.0f;
    output->elements[3][0] = 0.0f;
    output->elements[2][3] = 0.0f;
    output->elements[2][1] = 0.0f;
    output->elements[2][0] = 0.0f;
    output->elements[1][3] = 0.0f;
    output->elements[1][2] = 0.0f;
    output->elements[1][0] = 0.0f;
    output->elements[0][3] = 0.0f;
    output->elements[0][2] = 0.0f;
    output->elements[0][1] = 0.0f;
    output->elements[3][3] = 1.0f;
    output->elements[2][2] = 1.0f;
    output->elements[1][1] = 1.0f;
    output->elements[0][0] = 1.0f;
    return output;
}

} // namespace th20
