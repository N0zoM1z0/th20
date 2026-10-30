// Native 19B array-end pointer at 0x0045ECA0. Both original callers iterate
// three 0x3C0-byte ribbon segments and this returns their one-past-end.
// Compiler/STL versus game-source ownership remains unproven.
#include "NativeRibbonPolygonGroup.hpp"
namespace th20 {
NativeRibbonSegment* NativeRibbonSegmentArray::end_45eca0() {
    return reinterpret_cast<NativeRibbonSegment*>(
        reinterpret_cast<std::uint8_t*>(this) + sizeof(elements));
}
} // namespace th20
