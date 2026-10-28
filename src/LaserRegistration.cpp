#include "LaserParameters.hpp"

namespace th20 {

// The native 0x004C9300 member is a complete 75-byte registration boundary.
// The surrounding type-specific factory 0x004D47F0 and concrete Laser
// constructors/virtual initializers are separate, still-unreconstructed code.
void LaserController::register_laser(Laser* chosen) {
    auto* link = &chosen->link;
    link->initialize(chosen);
    auto* list = &active;
    list->prepend(&chosen->link);
    ++count;
}

} // namespace th20
