#include "Matrix4.hpp"

namespace th20 {

Matrix4* matrix_identity(Matrix4* output) {
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            output->elements[row][column] = row == column ? 1.0f : 0.0f;
        }
    }
    return output;
}

} // namespace th20
