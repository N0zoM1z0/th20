// Original 19B ribbon radius-array and point-array one-past-end helpers.
// Their distinct native call edges are part of the source-absent 538B Boss.
#include "NativeRibbonArraySpans.hpp"
#include <cstdint>
namespace th20 {
float* NativeRibbonScalarSpan::end_45dca0() {
    return reinterpret_cast<float*>(reinterpret_cast<std::uint8_t*>(this) + sizeof(values));
}
Vector2* NativeRibbonPointSpan::end_45dcc0() {
    return reinterpret_cast<Vector2*>(reinterpret_cast<std::uint8_t*>(this) + sizeof(values));
}
} // namespace th20
