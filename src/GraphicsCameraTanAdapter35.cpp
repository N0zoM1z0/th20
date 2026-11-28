// Original 35-byte float/double tangent adapter at 0x00439850.
// Its compiler/library authorship remains under review.
#include <cmath>
namespace th20 {
float __cdecl native_tan_439850(float angle_scale) {
    return static_cast<float>(std::tan(static_cast<double>(angle_scale)));
}
}
