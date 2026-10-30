// Original complete 280B Graphics::set viewport, using the genuine
// +0x278 0x16C-stride ViewportState, device SetViewport and native Pool floats.
// The original 806B category action calls this exact same C++ method symbol.
// Research original full 280B viewport switching (noncanonical until replay).
#include "Graphics.hpp"
#include "NativeGraphicsModeAction.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Viewport.hpp"
#include <cstdint>
#include <d3d9.h>
namespace th20 {
void NativeGraphicsModeAction::set_mode_44f720(int index,int unused) {
    current_viewport=&viewports[index];
    unused=0;
    recompute_current_4da1f0(current_viewport,&current_viewport->adjusted_viewport);
    prepare_device_4da120(current_viewport);
    device->SetViewport(reinterpret_cast<const D3DVIEWPORT9*>(&current_viewport->adjusted_viewport));
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd0)=static_cast<float>(current_viewport->offset_x);
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xd4)=static_cast<float>(current_viewport->offset_y);
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xc8)=
        *reinterpret_cast<std::uint32_t*>(&current_viewport->points[0].x);
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<unsigned char*>(current_animation_pool)+0xcc)=
        *reinterpret_cast<std::uint32_t*>(&current_viewport->points[0].y);
}
}
