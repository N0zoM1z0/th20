// Entire original game Renderer screenshot-frame pending transfer loop
// at 0x0041BFC0, 88B/28-i386. The 439B D3D9 transfer is already a
// separate whole-exact game method on the actual borrowed Renderer owner.
#include "NativeWindowCaptureRenderer.hpp"
namespace th20 {
void NativeWindowCaptureRenderer::prepare_frame_41bfc0() {
    for (int index=0; index<4; ++index) {
        if (pending[index].file_index>=0) {
            reinterpret_cast<NativeRendererSurfaceBlitView*>(this)
                ->blit_surface_rect_44bb10(&pending[index]);
            pending[index].file_index=-1;
        }
    }
}
}
