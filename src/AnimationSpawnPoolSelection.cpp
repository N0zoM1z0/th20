// Three complete original native RendererPool selection/index operations.
// Original class storage is opaque; all three actual offsets and stride are
// original-PE observed, and the same pool view is used by AnimationFile::spawn.
#include "NativeSpawnAnimationPoolView.hpp"
namespace th20 {
void* NativeRendererPoolSelector::renderer_index_449490(std::int32_t view) {
    return &reinterpret_cast<NativeRendererSlot72*>(this)[view];
}
int NativeSpawnAnimationPoolView::prefer_alternate_44c8a0() {
    return *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x6C4);
}
void* NativeSpawnAnimationPoolView::choose_renderer_44c8c0(int view) {
    auto* const views=reinterpret_cast<NativeRendererPoolSelector*>(
        reinterpret_cast<std::uint8_t*>(this)+0x6C8);
    return views->renderer_index_449490(view);
}
}
