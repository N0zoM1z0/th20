// Original complete 284B Graphics viewport clip switch at 0x0041DCE0.
// The receiver shares the genuine previously proven 280B mode switch ABI,
// but its native preparation uses the unadjusted viewport and point index 2.
#include "Graphics.hpp"
#include "NativeGraphicsModeAction.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Viewport.hpp"
#include <cstdint>
#include <d3d9.h>
namespace th20 {
void NativeGraphicsModeAction::set_clip_41dce0(int index) {
    current_viewport=&viewports[index];
    recompute_current_4da1f0(current_viewport,&current_viewport->viewport);
    prepare_device_4da120(current_viewport);
    device->SetViewport(reinterpret_cast<const D3DVIEWPORT9*>(&current_viewport->adjusted_viewport));
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd0)=static_cast<float>(current_viewport->offset_x);
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd4)=static_cast<float>(current_viewport->offset_y);
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xc8)=
        *reinterpret_cast<std::uint32_t*>(&current_viewport->points[2].x);
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xcc)=
        *reinterpret_cast<std::uint32_t*>(&current_viewport->points[2].y);
    field_b04=0;
}
}
