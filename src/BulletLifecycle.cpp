#include "Bullet.hpp"
#include "Session.hpp"
#include "AnimationRuntimeOwner.hpp"

namespace th20 {
// The real animation-owner pointer and method ABI share one narrow declaration.
void Bullet::select_context(std::int32_t index) {
    view_index = index;
    context = &session.context(view_index);
}

IntrusiveList<Bullet>& BulletController::free_list() { return free; }

void Bullet::deactivate() {
    if (state == 0) return;
    link.detach();
    context->bullet_controller()->free_list().prepend(&link);
    state = 0;
    timer_4f8 = 0;
    timer_508 = 0;
    timer_4a0 = 0;
    timer_4b0 = 0;
    timer_4c0 = 0;
    field_54 = 0;
    field_2c = 0;
    flags.bits &= ~1u;
    flags.bits &= ~0x100u;
    flags.bits &= ~0x200u;
    flags.bits &= ~0x40u;
    animation_handle.retire();
    current_animation_pool->release_animation(animation);
    metadata.reset();
}
} // namespace th20
