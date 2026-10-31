// The *entire* original 1,163-byte game quad-renderer texture-stage
// state machine at 0x00446690. Its native four-branch switch uses a direct
// four-pointer jump table after the genuine 1-byte alignment NOP; compare
// the FULL 1,180-byte COFF extent (code + 1-byte pad + 16B PE table).
// No separate renderer instance or owner storage is introduced. Original
// D3D9 device state method is SetTextureStageState (vtable +0x10C).
// This is a distinct exact child of the separately WHOLE STRICT EXACT
// 3159B quad submit Boss; neither native body is recredited twice.
#include "AnimationQuadSubmitOwner.hpp"
#include "Graphics.hpp"
#include <cstdint>

namespace th20 {
void AnimationQuadSubmitOwner::select_render_color_mode(std::uint8_t mode) {
    // Direct byte-lvalue expression is required for the native stack slots:
    // storing an arbitrary receiver-reference local adds 12 real code bytes.
    if (mode != *reinterpret_cast<std::uint8_t*>(this)) {
        flush_draws();
        switch (mode) {
        // The original 0..3 primary dispatch uses four actual absolute
        // HIGHLOW case pointers; default and explicit mode zero share code.
        case 0:
        default:
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAARG2, 0);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLORARG1, 2);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLORARG2, 0);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAOP, 4);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLOROP, 4);
            break;
        case 1:
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAARG2, 3);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLORARG1, 2);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLORARG2, 3);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAOP, 4);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLOROP, 4);
            break;
        case 2:
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, 0);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAARG2, 0);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLORARG1, 0);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLORARG2, 0);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAOP, 2);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLOROP, 2);
            break;
        case 3:
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAARG2, 0);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLORARG1, 2);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLORARG2, 0);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_ALPHAOP, 3);
            process_graphics.get_device()->SetTextureStageState(0, D3DTSS_COLOROP, 4);
            break;
        }
        *reinterpret_cast<std::uint8_t*>(this) = mode;
    }
}
} // namespace th20
