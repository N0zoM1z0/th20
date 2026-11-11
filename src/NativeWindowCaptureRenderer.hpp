#pragma once
// Borrowed physical Animation/Renderer owner, not a new game allocation.
// Four real 40B surface-copy commands at Renderer+0x18; the first signed
// word determines whether this frame's command is pending (>= 0).
#include "NativeRendererSurfaceBlitView.hpp"
#include <cstddef>
#include <cstdint>
namespace th20 {
struct NativeWindowCaptureRenderer {
    std::uint8_t retained_00[0x18];
    NativeSurfaceBlitCommand pending[4];
    void prepare_frame_41bfc0();
};
static_assert(offsetof(NativeWindowCaptureRenderer, pending) == 0x18);
static_assert(sizeof(NativeSurfaceBlitCommand) == 0x28);
}
