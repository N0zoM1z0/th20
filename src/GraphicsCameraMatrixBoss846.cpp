// Whole original 846B/194-i386 Graphics camera matrix Boss 0x004DA1F0.
// The genuine unsigned 32-bit viewport dimensions need the compiler's
// 0 / 2^32 double conversion table; all natural D3DX9 and Vector3
// calls/arguments produce the original 7 E8 and 20 PE data sites.
// The source does not synthesize conversion instructions or temporaries.
#include "NativeGraphicsModeAction.hpp"
#include "Vector3.hpp"
#include <cstdint>
#include <d3dx9math.h>
namespace th20 {
float __cdecl native_sqrt_439850(float value);
extern const float native_camera_half_divisor_56c8d0;
extern const float native_camera_min_z_56c8cc;
extern const float native_camera_negative_one_56e0f4;
extern const float native_camera_max_z_571ea0;
void NativeGraphicsModeAction::recompute_current_4da1f0(ViewportState* state, NativeViewport* viewport) {
    Vector3 camera_eye(
        static_cast<float>(viewport->x) + static_cast<float>(viewport->width) / native_camera_half_divisor_56c8d0,
        static_cast<float>(viewport->y) + static_cast<float>(viewport->height) / native_camera_half_divisor_56c8d0,
        static_cast<float>(viewport->height >> 1) / native_sqrt_439850(state->field_of_view / native_camera_half_divisor_56c8d0));
    Vector3 camera_target(
        static_cast<float>(state->viewport.x) + static_cast<float>(state->viewport.width) / native_camera_half_divisor_56c8d0,
        static_cast<float>(state->viewport.y) + static_cast<float>(state->viewport.height) / native_camera_half_divisor_56c8d0,
        0.0f);
    Vector3 up(0.0f,native_camera_negative_one_56e0f4,0.0f);
    D3DXMatrixLookAtLH(reinterpret_cast<D3DXMATRIX*>(&state->view),
                       reinterpret_cast<const D3DXVECTOR3*>(&camera_eye),
                       reinterpret_cast<const D3DXVECTOR3*>(&camera_target),
                       reinterpret_cast<const D3DXVECTOR3*>(&up));
    D3DXMatrixPerspectiveFovLH(reinterpret_cast<D3DXMATRIX*>(&state->projection),
                               state->field_of_view,
                               static_cast<float>(viewport->width) / static_cast<float>(viewport->height),
                               native_camera_min_z_56c8cc, native_camera_max_z_571ea0);
}
}
