// Complete original 347B RendererPool classification, two real 382B/394B
// whole-exact classification calls, 806B dispatch and 230B staging follow-up.
// The 806B/230B callees remain separately nonexact until scoped replay.
#include "AnimationRuntimeOwner.hpp"
#include "NativeSpawnAnimationPoolView.hpp"
#include "NativeRendererClassificationView.hpp"
#include "NativeRendererClassificationOwner.hpp"
#include "LockRegistry.hpp"
#include <mutex>
#include <cstdint>
namespace th20 {
int NativeRendererClassificationOwner::select_renderer_group_449e40(int identifier) {
    std::lock_guard<std::recursive_mutex> guard(process_locks.slot(9));
    for(int view=0;view<1;++view) {
        auto* first=reinterpret_cast<NativeRendererClassificationView*>(
            reinterpret_cast<NativeRendererPoolSelector*>(reinterpret_cast<std::uint8_t*>(this)+0x6C8)->renderer_index_449490(view));
        int count=first->classify_primary_44a090(identifier);
        if(count!=0) {
            perform_classification_44f3d0(identifier,view);
            apply_renderer_staging_449fa0(reinterpret_cast<NativeRendererClassificationView*>(
                reinterpret_cast<NativeRendererPoolSelector*>(reinterpret_cast<std::uint8_t*>(this)+0x6C8)->renderer_index_449490(view)));
        }
        auto* second=reinterpret_cast<NativeRendererClassificationView*>(
            reinterpret_cast<NativeRendererPoolSelector*>(reinterpret_cast<std::uint8_t*>(this)+0x6C8)->renderer_index_449490(view));
        count=second->classify_secondary_44a210(identifier);
        if(count!=0) {
            perform_classification_44f3d0(identifier,view);
            apply_renderer_staging_449fa0(reinterpret_cast<NativeRendererClassificationView*>(
                reinterpret_cast<NativeRendererPoolSelector*>(reinterpret_cast<std::uint8_t*>(this)+0x6C8)->renderer_index_449490(view)));
        }
    }
    return 1;
}
}
