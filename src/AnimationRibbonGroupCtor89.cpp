// Complete original 89B ribbon AnimationCallback group constructor.
// One ODR-consistent C++20 derived class owns 3x0x3C0 segment array,
// real virtual table and timer, plus native zeroed four-byte terminal field.
// Its genuinely implicit destructor also emits the original folded 20B
// destructor and 49B scalar-deleting wrapper without novtable tricks.
#include "NativeRibbonPolygonGroup.hpp"
namespace th20 {
NativeRibbonGroup::NativeRibbonGroup(Animation* owner)
    : AnimationCallback(owner), control_b48_float(0.0f), timer_b4c(),
      resource_token_b5c(nullptr) {}
} // namespace th20
