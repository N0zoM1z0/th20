#include "Matrix4.hpp"
#include <cstring>

namespace th20 {

Matrix4::Matrix4() { std::memset(this, 0, sizeof(*this)); }

} // namespace th20
