// Original whole 60B polygon segment constructor. The real 61-element
// Vector2 and AnimationHandle arrays default-construct before the 62-float
// radius array is zeroed. Native noexcept ctor is compiled without /EHsc.
// Only radius is value-initialized in this syntax;
// value-initializing all three would insert nonoriginal early memset calls.
#include "NativePolygonSegmentSlot.hpp"
namespace th20 {
NativePolygonSegmentSlot::NativePolygonSegmentSlot() noexcept : radius{} {}
} // namespace th20
