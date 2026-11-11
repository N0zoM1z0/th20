#include "IntrusiveListAnimation.hpp"
// Original whole 150B/44-i386 RendererPool lock+one-list update wrapper.
// The original E8 targets the now independently whole-exact 508B
// Renderer list update; this 150B wrapper remains independently exact.
#include "Animation.hpp"
#include "NativeSpawnAnimationPoolView.hpp"
#include "NativeAnimationRendererUpdate.hpp"
#include "IntrusiveLink.hpp"
#include "LockRegistry.hpp"
#include <cstdint>
#include <mutex>
namespace th20 {
int __fastcall animation_renderer_update_4497d0(AnimationPoolOwner* pool) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(9));
    animation_list_update_449870(reinterpret_cast<IntrusiveList<Animation>*>(
      reinterpret_cast<NativeRendererPoolSelector*>(reinterpret_cast<std::uint8_t*>(pool)+0x6C8)->renderer_index_449490(0)));
    return 1;
}
}
