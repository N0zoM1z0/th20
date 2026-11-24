#include "NativeGraphicsModeAction.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Vector3.hpp"

#include <d3dx9math.h>
#include <cstdint>
#include <cstring>

namespace th20 {
extern const float native_viewport_near_56f280;
extern const float native_viewport_far_571e9c;
void normalize_vector3_45cf10(Vector3& output, const Vector3& input);

void NativeGraphicsModeAction::recompute_view_4d9f60(ViewportState* state) {
    if (current_animation_pool)
        current_animation_pool->flush_draws();

    const Vector3 eye = state->vector_00 + state->vector_3c;
    const Vector3 target = state->vector_24 + eye;
    D3DXMatrixLookAtLH(reinterpret_cast<D3DXMATRIX*>(&state->view),
                       reinterpret_cast<const D3DXVECTOR3*>(&eye),
                       reinterpret_cast<const D3DXVECTOR3*>(&target),
                       reinterpret_cast<const D3DXVECTOR3*>(&state->vector_18));
    D3DXMatrixPerspectiveFovLH(
        reinterpret_cast<D3DXMATRIX*>(&state->projection), state->field_of_view,
        static_cast<float>(state->viewport.width) /
            static_cast<float>(state->viewport.height),
        native_viewport_near_56f280, native_viewport_far_571e9c);

    device->SetTransform(D3DTS_VIEW,
        reinterpret_cast<const D3DMATRIX*>(&state->view));
    device->SetTransform(D3DTS_PROJECTION,
        reinterpret_cast<const D3DMATRIX*>(&state->projection));

    const Vector3 camera_up = state->vector_18;
    const Vector3 camera_direction = state->vector_24;
    const Vector3 cross{
        camera_direction.y * camera_up.z - camera_direction.z * camera_up.y,
        camera_direction.z * camera_up.x - camera_direction.x * camera_up.z,
        camera_direction.x * camera_up.y - camera_direction.y * camera_up.x};
    normalize_vector3_45cf10(state->vector_0c, cross);
}

void NativeGraphicsModeAction::select_view_477520(int index) {
    current_viewport = &viewports[index];
    recompute_current_4da1f0(current_viewport, &current_viewport->viewport);
    recompute_view_4d9f60(current_viewport);
    device->SetViewport(
        reinterpret_cast<const D3DVIEWPORT9*>(&current_viewport->adjusted_viewport));

    auto* pool = reinterpret_cast<std::uint8_t*>(current_animation_pool);
    *reinterpret_cast<float*>(pool + 0xD0) =
        static_cast<float>(current_viewport->offset_x);
    *reinterpret_cast<float*>(pool + 0xD4) =
        static_cast<float>(current_viewport->offset_y);
    std::memcpy(pool + 0xC8, &current_viewport->points[2].x, sizeof(float));
    std::memcpy(pool + 0xCC, &current_viewport->points[2].y, sizeof(float));
    field_b04 = 0;
}

} // namespace th20
