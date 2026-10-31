// Original complete 562B game Renderer D3D9 texture upload Boss.
// CORE/RECON-1100: pinned MSVC C++20 WHOLE strict-native exact. The
// original native texture format argument is remapped in place and the
// D3DX filtering expression is a true direct API argument; no artificial
// temporary, padding, assembly or shortened target comparison.
// The separate 2745B native texture finalizer is now WHOLE STRICT EXACT
// (CORE/RECON-1103), including the real post-return 53B data comparison.
#include "NativeRendererTextureMemoryView.hpp"
#include "AnimationFile.hpp"
#include "Graphics.hpp"
#include "NativeAnimationFileLoadView.hpp"
#include <d3d9.h>
#include <d3dx9tex.h>
#include <cstdint>
namespace th20 {
extern float native_texture_scale_5b8818;
extern const float native_texture_nominal_scale_56c8d0;
extern const float native_texture_scale_factor_56e0ec;
extern const std::uint32_t texture_byte_sizes[9];
// Existing Renderer owner, non-allocating view; actual Renderer layout
// is not reconstructed by this texture code.

std::int32_t NativeRendererTextureMemoryView::create_uploaded_texture_44e8f0(
    TextureRecord* record, std::int32_t native_format,
    std::int32_t /*original_parameter_10*/,
    std::int32_t width, std::int32_t height,
    std::int32_t left,std::int32_t top,
    std::int32_t clipped_width,std::int32_t clipped_height) {
    native_format=static_cast<std::int32_t>(
        select_texture_format(static_cast<std::uint32_t>(native_format)));
    record->flags.bits&=~3u;
    const std::int32_t clip_w=width>clipped_width?clipped_width:width;
    const std::int32_t clip_h=height>clipped_height?clipped_height:height;
    RECT source_rect{left,top,left+clip_w,top+clip_h};
    if (reinterpret_cast<const NativeAnmGroupHeader*>(record->header)->reserved_22!=0 && native_texture_nominal_scale_56c8d0>native_texture_scale_5b8818) {
        width=static_cast<std::int32_t>(static_cast<float>(width)*native_texture_scale_5b8818*native_texture_scale_factor_56e0ec);
        height=static_cast<std::int32_t>(static_cast<float>(height)*native_texture_scale_5b8818*native_texture_scale_factor_56e0ec);
    }
    RECT dest_rect{0,0,width,height};
    const D3DFORMAT fmt=texture_api_formats[native_format];
    auto* device=process_graphics.get_device();
    D3DXCreateTexture(device,width,height,1,0,fmt,D3DPOOL_MANAGED,&record->texture);
    IDirect3DSurface9* surface=nullptr;
    record->texture->GetSurfaceLevel(0,&surface);

    if (D3DXLoadSurfaceFromFileInMemory(surface,nullptr,&dest_rect,
        record->external_bytes,record->external_size,&source_rect,(reinterpret_cast<const NativeAnmGroupHeader*>(record->header)->reserved_22!=0 && native_texture_nominal_scale_56c8d0>native_texture_scale_5b8818) ? 0x30004 : D3DX_FILTER_NONE,0,nullptr)!=D3D_OK) {
        if (surface!=nullptr) {surface->Release();surface=nullptr;}
        return -1;
    }
    if (surface!=nullptr) {surface->Release();surface=nullptr;}
    finalize_uploaded_texture_451910(record->texture);
    record->bytes_per_pixel=texture_byte_sizes[native_format];
    return width*height*texture_byte_sizes[native_format];
}
}
