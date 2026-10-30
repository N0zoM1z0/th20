#include "NativeRibbonTrailGroup.hpp"
#include <memory>
namespace th20 {
void construct_native_trail_colors_64(std::array<AnimationHandle,64>& cells) {
    std::construct_at(&cells);
}
}
