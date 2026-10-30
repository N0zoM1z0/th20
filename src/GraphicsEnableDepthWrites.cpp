// Whole native original 92B Graphics D3D9 Z-write state enable leaf.
// The original Graphics+0xDBC cache is set to one, only after flushing the
// game animation pool. The device's true vtable +0xE4 sets render state 14.
#include "Graphics.hpp"
#include "AnimationRuntimeOwner.hpp"

namespace th20 {
#if defined(_M_IX86)
static_assert(offsetof(Graphics,field_dbc)==0xDBC);
#endif
std::int32_t __fastcall graphics_enable_depth_writes(Graphics* graphics) {
    if (graphics->field_dbc != 1) {
        current_animation_pool->flush_draws();
        graphics->field_dbc = 1;
        return graphics->device->SetRenderState(D3DRS_ZWRITEENABLE, 1);
    } else {
        return 0;
    }
}
}
