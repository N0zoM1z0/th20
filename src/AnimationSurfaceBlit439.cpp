// TH20 original 439B Renderer D3D9 sprite-rectangle surface copy Boss.
// Source-present candidate; whole native original extent/ABI is separate.
#include "NativeRendererSurfaceBlitView.hpp"
#include "AnimationFile.hpp"
#include <d3d9.h>
#include <d3dx9tex.h>
#include <array>
#include <cstdint>
namespace th20 {
extern IDirect3DSurface9* source_texture_surface_5c4ee4;
void NativeRendererSurfaceBlitView::blit_surface_rect_44bb10(const NativeSurfaceBlitCommand* command) {
    auto& files=*reinterpret_cast<std::array<AnimationFile*,42>*>(
        reinterpret_cast<std::uint8_t*>(this)+0x06000730);
    if (files[command->file_index]->textures[command->texture_index].texture == nullptr)
        return;
    flush_draws();
    auto& second_files=*reinterpret_cast<std::array<AnimationFile*,42>*>(
        reinterpret_cast<std::uint8_t*>(this)+0x06000730);
    IDirect3DSurface9* surface;
    if (second_files[command->file_index]->textures[command->texture_index].texture
            ->GetSurfaceLevel(0,&surface)!=D3D_OK)
        return;
    RECT source{command->src_left,command->src_top,
        command->src_left+command->src_width,command->src_top+command->src_height};
    RECT destination{command->dest_left,command->dest_top,
        command->dest_left+command->dest_width,command->dest_top+command->dest_height};
    if (D3DXLoadSurfaceFromSurface(surface,nullptr,&destination,
            source_texture_surface_5c4ee4,nullptr,&source,D3DX_FILTER_POINT,0)!=D3D_OK) {
        surface->Release();
        return;
    }
    auto& third_files=*reinterpret_cast<std::array<AnimationFile*,42>*>(
        reinterpret_cast<std::uint8_t*>(this)+0x06000730);
    third_files[command->file_index]->textures[command->texture_index].texture->AddDirtyRect(nullptr);
    surface->Release();
}
}
