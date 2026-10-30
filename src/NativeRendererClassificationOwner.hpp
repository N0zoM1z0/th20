#pragma once
// Original RendererPool classification owner used by the 347B game Boss.
// It owns NO new renderer storage; the known per-renderer slot starts at
// pool+0x6C8, while deeper RendererPool data remain separately unresolved.
#include "AnimationRuntimeOwner.hpp"
#include "NativeRendererClassificationView.hpp"
namespace th20 {
void __fastcall apply_renderer_staging_449fa0(NativeRendererClassificationView* renderer);
struct NativeRendererClassificationOwner : AnimationPoolOwner {
    int select_renderer_group_449e40(int identifier);
    void perform_classification_44f3d0(int identifier,int view_index);
};
}
