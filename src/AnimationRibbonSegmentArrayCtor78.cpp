// Original 78B native std::array<NativeRibbonSegment,3> constructor.
// Each actual element is 0x3C0 bytes, initialized by whole-exact 60B
// ribbon segment ctor; five native INT3 bytes follow the 78B function.
#include "NativeRibbonPolygonGroup.hpp"
namespace th20 {
NativeRibbonSegmentArray::NativeRibbonSegmentArray() : elements() {}
}
