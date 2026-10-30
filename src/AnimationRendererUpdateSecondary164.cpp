// Whole original 164B/46-i386 Renderer update of secondary list.
// Native 511B child remains separately source absent / NONEXACT.
#include "LockRegistry.hpp"
#include "NativeSpawnAnimationPoolView.hpp"
#include "NativeSpawnRendererView.hpp"
#include "NativeAnimationRendererUpdate.hpp"
#include "IntrusiveLink.hpp"
#include "Animation.hpp"
#include <mutex>
#include <cstdint>
namespace th20 {

int __fastcall animation_renderer_update_secondary_449a70(AnimationPoolOwner* pool) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(9));
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(pool)+0xD8)=0;
    animation_list_update_secondary_449b20(reinterpret_cast<NativeSpawnRendererView*>(
        reinterpret_cast<NativeRendererPoolSelector*>(reinterpret_cast<std::uint8_t*>(pool)+0x6C8)->renderer_index_449490(0)));
    return 1;
}
}
