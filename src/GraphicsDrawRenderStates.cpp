// Original game Graphics render-state cache transitions from the Animation
// draw dispatcher. The native D3D9 vtable +0xE4 is SetRenderState.
#include "Graphics.hpp"
#include "AnimationRuntimeOwner.hpp"

namespace th20 {
#if defined(_M_IX86)
static_assert(offsetof(Graphics, render_value) == 0xDB8);
static_assert(offsetof(Graphics, field_dbc) == 0xDBC);
#endif

std::int32_t __fastcall graphics_enable_fog(Graphics* graphics) {
    if (graphics->render_value != 1) {
        current_animation_pool->flush_draws();
        graphics->render_value = 1;
        return graphics->device->SetRenderState(D3DRS_FOGENABLE, 1);
    } else {
        return 0;
    }
}

std::int32_t __fastcall graphics_disable_fog(Graphics* graphics) {
    if (graphics->render_value != 0) {
        current_animation_pool->flush_draws();
        graphics->render_value = 0;
        return graphics->device->SetRenderState(D3DRS_FOGENABLE, 0);
    } else {
        return 0;
    }
}

std::int32_t __fastcall graphics_disable_depth_writes(Graphics* graphics) {
    if (graphics->field_dbc != 0) {
        current_animation_pool->flush_draws();
        graphics->field_dbc = 0;
        return graphics->device->SetRenderState(D3DRS_ZWRITEENABLE, 0);
    } else {
        return 0;
    }
}

} // namespace th20
