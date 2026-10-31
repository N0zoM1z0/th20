// Exact original 80-byte folded float zero-byte predicate used by float fill_n.
// This tests the object representation, not floating-point equality: -0.0f
// must remain distinguishable from +0.0f just as in the native memcmp path.
#include <cstring>
namespace th20 {
bool __cdecl particle_float_is_zero(const float* input) {
    float zero = 0.0f;
    return std::memcmp(input, &zero, sizeof(float)) == 0;
}
}
