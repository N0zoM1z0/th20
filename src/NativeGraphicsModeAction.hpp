#pragma once
// One non-owning original Graphics receiver shared across the complete
// 806B Renderer mode-selection Boss and its actual 280B viewport setter.
// The native call targets of all additional methods remain separately open.
#include "Graphics.hpp"
#include "Viewport.hpp"
namespace th20 {
struct NativeGraphicsModeAction : Graphics {
    void set_mode_44f720(int mode,int variant);
    void set_mode_44f700(int mode,int variant);
    void set_clip_41dce0(int value);
    void reset_stage_4dda60();
    void reset_view_4ddf80();
    void set_render_state_4d9db0(int mode,int value);
    void recompute_current_4da1f0(ViewportState* state,NativeViewport* adjusted);
    void prepare_device_4da120(ViewportState* state);
};
static_assert(sizeof(NativeGraphicsModeAction)==sizeof(Graphics));
}
