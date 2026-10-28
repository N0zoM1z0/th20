// Whole original 211-byte Bullet movement/collision routing method.
// Preserve the real nested command-state and collision short-circuit ABI;
// the larger child physics/collision functions remain external/unaccepted.
#include "Bullet.hpp"
namespace th20 {
std::int32_t Bullet::step_update() {
    if ((((flags.bits >> 10) & 1u) == 0) && update_physics() != 0) return -1;
    if (animation_handle != 0u) animation_handle.set_position(position);
    switch (state) {
        case 2:
            if (timer_4f8.at_least(8) && process_collision(0) == 1) break;
            [[fallthrough]];
        case 1:
            // The original short-circuit expression uses the return value
            // only in boolean evaluation; the expression's result is unused.
            (((flags.bits >> 9) & 1u) == 0) && process_collision(0);
    }
    flags.bits &= ~0x400u;
    return 0;
}
}
