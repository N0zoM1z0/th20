// Original 78B / 27-i386 std::array<NativePolygonSegmentSlot,3> constructor.
// Native array construction is required for the real 0xB7C segment triple.
// The two placement-construction wrappers are source-level entry points for
// the actual segment-array and color-cell array subobjects; only their
// corresponding compiler-generated std::array methods earn native unit credit.
#include "NativePolygonMotionGroup.hpp"
#include "AnimationHandle.hpp"
#include <array>
#include <memory>
namespace th20 {
NativePolygonSegmentArray::NativePolygonSegmentArray() : segments() {}

void construct_polygon_color_cells_45f210(std::array<AnimationHandle,61>& cells) {
    std::construct_at(&cells);
}
} // namespace th20
