// Whole original native 35B sqrt(double)->float adapter at 0x00439850.
// This may be generated CRT/inline-library glue, so preserve source
// exactness while holding origin review; do NOT credit game-authored bytes.
#include <cmath>
namespace th20 {
float __cdecl native_sqrt_439850(float angle_scale) {
    return static_cast<float>(std::sqrt(static_cast<double>(angle_scale)));
}
}
