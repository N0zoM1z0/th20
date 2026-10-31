#pragma once
// Native Renderer borrow: no stand-alone instance or additional storage.
// Texture file lookup occurs at receiver +0x06000730, 42 slot pointers.
#include "AnimationRuntimeOwner.hpp"
#include <cstdint>
struct IDirect3DSurface9;
struct tagRECT;
namespace th20 {
struct NativeSurfaceBlitCommand {
    std::int32_t file_index, texture_index;
    std::int32_t src_left, src_top, src_width, src_height;
    std::int32_t dest_left, dest_top, dest_width, dest_height;
};
static_assert(sizeof(NativeSurfaceBlitCommand)==40);
struct NativeRendererSurfaceBlitView : AnimationPoolOwner {
    void blit_surface_rect_44bb10(const NativeSurfaceBlitCommand* command);
    void blit_surface_effect_44be40(std::int32_t file_index,std::int32_t texture_index,
        IDirect3DSurface9* source,const tagRECT* dest_rect,
        const tagRECT* source_rect,std::int32_t effect);
};
}
