// Complete 139B original Render Target texture creation from the Renderer.
// This is a genuine thiscall method of the non-owning Renderer ABI view.
#include "NativeRendererTextureCreate.hpp"
#include "AnimationFile.hpp"
#include "Graphics.hpp"
#include "EclDiagnostic.hpp"
#include <d3d9.h>
namespace th20 {
std::int32_t NativeRendererTextureOwner::create_render_target_44c150(
    TextureRecord* record, std::int32_t width, std::int32_t height) {
    record->flags.bits = (record->flags.bits & ~3u) | 1u;
    auto* device = process_graphics.get_device();
    if (device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET,
                              D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT,
                              &record->texture, nullptr) != 0) {
        ecl_diagnostic_hint("error D3DXCreateTexture\n");
    }
    std::int32_t bytes_per_pixel;
    if (process_graphics.presentation.BackBufferFormat == D3DFMT_A8R8G8B8)
        bytes_per_pixel = 4;
    else
        bytes_per_pixel = 2;
    record->bytes_per_pixel = bytes_per_pixel;
    return 0;
}
}
