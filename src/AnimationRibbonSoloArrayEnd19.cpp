#include "NativeRibbonSoloGroup.hpp"
#include <cstdint>
namespace th20 {
NativeRibbonSegment* NativeRibbonSoloSegmentArray::end_45dce0() {
    return reinterpret_cast<NativeRibbonSegment*>(reinterpret_cast<std::uint8_t*>(this)+sizeof(elements));
}
}
