#pragma once

#include "Viewport.hpp"

namespace th20 {

struct Graphics;

// Non-owning zero-data interface for methods recovered on the native
// Graphics receiver. Graphics inherits this at offset zero; method symbols
// retain the original NativeGraphicsModeAction owner name.
struct NativeGraphicsModeAction {
    void set_mode_44f720(int mode, int variant);
    void set_mode_44f700(int mode, int variant);
    void set_clip_41dce0(int value);
    void reset_stage_4dda60();
    void reset_view_4ddf80();
    void set_render_state_4d9db0(int mode, int value);
    void recompute_current_4da1f0(ViewportState* state, NativeViewport* adjusted);
    void prepare_device_4da120(ViewportState* state);
    void recompute_view_4d9f60(ViewportState* state);
    void select_view_477520(int index);
};

} // namespace th20
