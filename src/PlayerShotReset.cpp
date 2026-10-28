// Complete native PlayerShot lifetime and controller reset chain.
// Independently exact physical originals: 269B reset, 32B timer wrapper,
// 166B PlayerShot retire, 55B controller recycle, 41B heap ownership.
// The distinct 67B DamageHandle::resolve callee remains unimplemented.
#include "PlayerStorage.hpp"
#include "DamageRegion.hpp"
#include "DiagnosticAllocator.hpp"
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

// Complete original 41B owned-shot bit predicate.
bool PlayerShot::heap_owned() const {
    return (state_14 & 0x01000000u) ? true : false;
}

// Actual 55B PlayerShotController recycle: return only pool-owned shots.
void PlayerShotController::return_to_free(PlayerShot* shot) {
    if (!shot->heap_owned()) {
        auto& list = free;
        list.prepend(&shot->link);
    }
}

// Complete original 166B PlayerShot retirement and conditional destruction.
// The independent DamageHandle::resolve callee remains a separate native
// method to reconstruct and does not gain exact credit from this caller.
void PlayerShot::retire() {
    field_9c = 0;
    { handle_18.retire(); }
    if (context->hit_controller()) {
        DamageRegion* region = damage.resolve();
        if (region) { region->retire(); }
    }
    link.detach();
    auto* controller = owner;
    controller->return_to_free(this);
    auto previous = state_14;
    state_14 = 0;
    if (previous & 0x01000000u) {
        process_allocator->release_object(this);
    }
}
}
