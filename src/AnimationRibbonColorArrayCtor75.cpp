// Force the real 60 four-byte AnimationHandle color array C++20 default ctor.
#include "AnimationHandle.hpp"
#include <array>
#include <memory>
namespace th20 {
void construct_ribbon_color_cells_45d4b0(std::array<AnimationHandle,60>& cells) {
    std::construct_at(&cells);
}
}
