// Original 51B particle-grid virtual event. The group contains a real Timer
// and this event forwards its 300-frame delta through the folded 26B helper.
#include "NativeParticleGridGroup.hpp"

namespace th20 {
std::int32_t NativeParticleGridGroup::interrupt(std::int32_t event) {
    switch (event) {
    case 1:
        timer_1930 += 300;
        break;
    default:
        break;
    }
    return 0;
}
}
