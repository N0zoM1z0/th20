// Original whole 60B ribbon segment constructor at 0x0045D610.
// Real 60 Vector2 positions and 60 AnimationHandle color cells are
// default-constructed before the 60 float radius values are zeroed.
// Only radius is value-initialized; this is the native no-EH ABI.
#include "NativeRibbonPolygonGroup.hpp"
namespace th20 {
NativeRibbonSegment::NativeRibbonSegment() noexcept : radius_2d0{} {}
}
