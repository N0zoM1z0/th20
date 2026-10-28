// Complete native 269B PlayerShotController reset and its independent 32B
// timer-wrapper callee. The original 966B Player reset invokes reset_all.
// Do not credit the separate 166B PlayerShot::retire merely because it
// appears as a callee; that member remains a distinct reconstruction.
#include "PlayerStorage.hpp"
namespace th20 {
void PlayerShotController::reset_timer_12400(std::int32_t value) {
    timer_12400 = value;
}
void PlayerShotController::reset_all() {
    // Iterator and its observed callback registrations must be fully
    // retired before any of the three original controller timers reset.
    {
        auto& list = active;
        auto iterator = list.begin();
        auto* end = list.end();
        for (; iterator.differs(end); iterator.advance()) {
            auto* link = iterator.get();
            link->node_access()->retire();
        }
    }
    reset_timer_12400(-1);
    timer_12410 = -1;
    timer_12420 = 0;
    counters_12468.fill(0);
}
}
