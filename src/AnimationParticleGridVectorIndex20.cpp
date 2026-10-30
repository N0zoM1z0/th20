#include "Vector3.hpp"
#include <array>
namespace th20 {
void emit_index200(std::array<Vector3,200>& coords, std::size_t i) { (void)&coords[i]; }
}
