// Whole native 194B Graphics device matrix stage at 0x004DA120.
// Flush real Renderer, set D3D9 view/projection transforms through the
// actual process-global Graphics device, and propagate the native
// first point into Renderer. No fake allocations or padding.
#include "NativeGraphicsModeAction.hpp"
#include "AnimationRuntimeOwner.hpp"
#include <d3d9.h>
#include <cstdint>
namespace th20 {
void NativeGraphicsModeAction::prepare_device_4da120(ViewportState* state) {
    if (current_animation_pool) {
        current_animation_pool->flush_draws();
    }
    process_graphics.get_device()->SetTransform(D3DTS_VIEW,
            reinterpret_cast<const D3DMATRIX*>(&state->view));
    process_graphics.get_device()->SetTransform(D3DTS_PROJECTION,
            reinterpret_cast<const D3DMATRIX*>(&state->projection));
    if (current_animation_pool) {
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(current_animation_pool)+0xC8)=
            *reinterpret_cast<const std::uint32_t*>(&state->points[0].x);
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(current_animation_pool)+0xCC)=
            *reinterpret_cast<const std::uint32_t*>(&state->points[0].y);
    }
}
}
