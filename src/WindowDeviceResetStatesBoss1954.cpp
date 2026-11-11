// Original game Window/Graphics D3D9 reset-state Boss 0x0041A2C0
// (1954B/507-i386). Real 24 render, eight texture-stage and six sampler
// device state calls plus five Animation Renderer restore hooks.
// Full 1911B MSVC source candidate retains the native call and data
// destination sequence, including three real float-valued RenderStates
// read before their device calls. The 1954B parent remains NONEXACT
// because the original GS frame/cookie and stack lifetimes differ.
// No synthetic stack arrays or padding to force a size-only match.
#include "Graphics.hpp"
#include "AnimationRuntimeOwner.hpp"
#include <cstdint>
#include <d3d9.h>
namespace th20 {
extern const float native_reset_one_56c8cc;
extern const float native_reset_thousand_56cdb0;
extern const float native_reset_five_thousand_56cdb8;
struct NativeAnimationResetHooks:AnimationPoolOwner {
    void restart_state_41db40();
    void restart_state_41db60();
    void restart_state_41db80();
    void restart_state_41dba0();
    void restart_state_41dbc0();
};
void __cdecl window_frame_initialize_41a2c0() {
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x7),1);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x89),0);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x16),1);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x1B),1);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0xCE),1);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x9),2);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x13),5);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x14),6);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x17),8);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0xAB),1);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0xCF),2);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0xD0),1);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0xD1),1);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0xF),1);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x18),1);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x19),7);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x1C),1);
    const DWORD reset_value_one_56c8cc = *reinterpret_cast<const DWORD*>(&native_reset_one_56c8cc);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x26),reset_value_one_56c8cc);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x23),0);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x8C),3);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x22),0xFFA0A0A0);
    const DWORD reset_value_thousand_56cdb0 = *reinterpret_cast<const DWORD*>(&native_reset_thousand_56cdb0);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x24),reset_value_thousand_56cdb0);
    const DWORD reset_value_five_thousand_56cdb8 = *reinterpret_cast<const DWORD*>(&native_reset_five_thousand_56cdb8);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0x25),reset_value_five_thousand_56cdb8);
    process_graphics.get_device()->SetRenderState(static_cast<D3DRENDERSTATETYPE>(0xA1),0);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(0x4),4);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(0x5),2);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(0x6),3);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(0x1),4);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(0x2),2);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(0x3),3);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(0x18),2);
    process_graphics.get_device()->SetTextureStageState(0,static_cast<D3DTEXTURESTAGESTATETYPE>(0xB),0);
    process_graphics.get_device()->SetSamplerState(0,static_cast<D3DSAMPLERSTATETYPE>(0x7),0);
    process_graphics.get_device()->SetSamplerState(0,static_cast<D3DSAMPLERSTATETYPE>(0x5),2);
    process_graphics.get_device()->SetSamplerState(0,static_cast<D3DSAMPLERSTATETYPE>(0x6),2);
    process_graphics.get_device()->SetSamplerState(0,static_cast<D3DSAMPLERSTATETYPE>(0x3),3);
    process_graphics.get_device()->SetSamplerState(0,static_cast<D3DSAMPLERSTATETYPE>(0x1),1);
    process_graphics.get_device()->SetSamplerState(0,static_cast<D3DSAMPLERSTATETYPE>(0x2),1);
    if (current_animation_pool) {
        reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)->restart_state_41db40();
        reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)->restart_state_41db60();
        reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)->restart_state_41db80();
        reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)->restart_state_41dba0();
        reinterpret_cast<NativeAnimationResetHooks*>(current_animation_pool)->restart_state_41dbc0();
    }
}
}
