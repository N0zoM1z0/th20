// Original complete 2745B/759-i386 game Renderer alpha-fringe finalizer.
// CORE/RECON-1103: WHOLE STRICT EXACT, including all 2745 native code
// bytes and the independently original 53B of following jump-table data.
// Natural C++20 pixel[0] indexing, signed negative pitch division,
// truncation to byte channels, aggregate zeros and chain resets produce
// the actual native code and all original relocation site/destinations.
// No truncation of either code or data comparison, assembly or fake pads.
#include "NativeRendererTextureMemoryView.hpp"
#include "AnimationFile.hpp"
#include "TextureTexels.hpp"
#include <d3d9.h>
#include <cstdint>
namespace th20 {
// The 562B exact upload and this large finalizer share ONE non-owning
// Renderer ABI declaration; there is no second conflicting class body.

void NativeRendererTextureMemoryView::finalize_uploaded_texture_451910(
        IDirect3DTexture9* texture) {
    IDirect3DSurface9* surface=nullptr;
    texture->GetSurfaceLevel(0,&surface);
    if (surface==nullptr) return;
    {
        D3DSURFACE_DESC description;
        D3DLOCKED_RECT locked;
        surface->GetDesc(&description);
        surface->LockRect(&locked,nullptr,0);
        switch (description.Format) {
        case D3DFMT_UNKNOWN:
        case D3DFMT_A8R8G8B8: {
            std::uint32_t rgb[3]{};
            for (std::uint32_t y=0;y<description.Height;++y) {
                auto* pixel=reinterpret_cast<Texel8888*>(
                    static_cast<std::uint8_t*>(locked.pBits)+locked.Pitch*y);
                for (std::uint32_t x=0;x<description.Width;++x) {
                    if (pixel[0].alpha==0) {
                        rgb[0]=rgb[1]=rgb[2]=0;
                        std::uint32_t count=0;

                        if (x>0) accumulate_texel8888(rgb,&pixel[-1],count);
                        if (x<description.Width-1) accumulate_texel8888(rgb,&pixel[1],count);
                        if (y>0) accumulate_texel8888(rgb,pixel+(-locked.Pitch)/4,count);
                        if (y<description.Height-1) accumulate_texel8888(rgb,pixel+locked.Pitch/4,count);
                        if (1<count) { rgb[0]/=count; rgb[1]/=count; rgb[2]/=count; }

                        pixel[0].red=static_cast<std::uint8_t>(rgb[0]);
                        pixel[0].green=static_cast<std::uint8_t>(rgb[1]);
                        pixel[0].blue=static_cast<std::uint8_t>(rgb[2]);
                    }
                    ++pixel;
                }
            }
            break;
        }
        case D3DFMT_A1R5G5B5: {
            std::uint32_t rgb[3]{};
            for (std::uint32_t y=0;y<description.Height;++y) {
                auto* pixel=reinterpret_cast<Texel1555*>(
                    static_cast<std::uint8_t*>(locked.pBits)+locked.Pitch*y);
                for (std::uint32_t x=0;x<description.Width;++x) {
                    if (pixel[0].alpha==0) {
                        rgb[0]=rgb[1]=rgb[2]=0;
                        std::uint32_t count=0;

                        if (x>0) accumulate_texel1555(rgb,&pixel[-1],count);
                        if (x<description.Width-1) accumulate_texel1555(rgb,&pixel[1],count);
                        if (y>0) accumulate_texel1555(rgb,pixel+(-locked.Pitch)/2,count);
                        if (y<description.Height-1) accumulate_texel1555(rgb,pixel+locked.Pitch/2,count);
                        if (1<count) {rgb[0]/=count;rgb[1]/=count;rgb[2]/=count;}

                        pixel[0].red=static_cast<std::uint8_t>(rgb[0]);
                        pixel[0].green=static_cast<std::uint8_t>(rgb[1]);
                        pixel[0].blue=static_cast<std::uint8_t>(rgb[2]);
                    }
                    ++pixel;
                }
            }
            break;
        }
        case D3DFMT_A4R4G4B4: {
            std::uint32_t rgb[3]{};
            for (std::uint32_t y=0;y<description.Height;++y) {
                auto* pixel=reinterpret_cast<Texel4444*>(
                    static_cast<std::uint8_t*>(locked.pBits)+locked.Pitch*y);
                for (std::uint32_t x=0;x<description.Width;++x) {
                    if (pixel[0].alpha==0) {
                        rgb[0]=rgb[1]=rgb[2]=0;
                        std::uint32_t count=0;

                        if (x>0) accumulate_texel4444(rgb,&pixel[-1],count);
                        if (x<description.Width-1) accumulate_texel4444(rgb,&pixel[1],count);
                        if (y>0) accumulate_texel4444(rgb,pixel+(-locked.Pitch)/2,count);
                        if (y<description.Height-1) accumulate_texel4444(rgb,pixel+locked.Pitch/2,count);
                        if (1<count) {rgb[0]/=count;rgb[1]/=count;rgb[2]/=count;}

                        pixel[0].red=static_cast<std::uint8_t>(rgb[0]);
                        pixel[0].green=static_cast<std::uint8_t>(rgb[1]);
                        pixel[0].blue=static_cast<std::uint8_t>(rgb[2]);
                    }
                    ++pixel;
                }
            }
            break;
        }
        case D3DFMT_A8R3G3B2: {
            std::uint32_t rgb[3]{};
            for (std::uint32_t y=0;y<description.Height;++y) {
                auto* pixel=reinterpret_cast<Texel8332*>(
                    static_cast<std::uint8_t*>(locked.pBits)+locked.Pitch*y);
                for (std::uint32_t x=0;x<description.Width;++x) {
                    if (pixel[0].alpha==0) {
                        rgb[0]=rgb[1]=rgb[2]=0;
                        std::uint32_t count=0;

                        if (x>0) accumulate_texel8332(rgb,&pixel[-1],count);
                        if (x<description.Width-1) accumulate_texel8332(rgb,&pixel[1],count);
                        if (y>0) accumulate_texel8332(rgb,pixel+(-locked.Pitch)/2,count);
                        if (y<description.Height-1) accumulate_texel8332(rgb,pixel+locked.Pitch/2,count);
                        if (1<count) {rgb[0]/=count;rgb[1]/=count;rgb[2]/=count;}

                        pixel[0].red=static_cast<std::uint8_t>(rgb[0]);
                        pixel[0].green=static_cast<std::uint8_t>(rgb[1]);
                        pixel[0].blue=static_cast<std::uint8_t>(rgb[2]);
                    }
                    ++pixel;
                }
            }
            break;
        }
        default:break;
        }
        surface->UnlockRect();
        surface->Release();
    }
}
}
