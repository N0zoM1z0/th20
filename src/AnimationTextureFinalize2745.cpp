// Original complete 2745B/759-i386 game Renderer alpha-fringe finalizer.
// SOURCE-PRESENT, NONEXACT: the natural C++20 four-format scan emits
// the correct 17 native E8 roles but a shorter code body and a folded
// five-target jump table. The whole original boundary is never shortened.
// CORE/RECON-1101 native PE proof documents the compiler frontier.
// Each of four pixel formats has its own original nested scan, so keep
// the distinct 139B/183B/183B/187B nearest-neighbor callee graph.
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
    if (surface!=nullptr) {
        D3DSURFACE_DESC description;
        D3DLOCKED_RECT locked;
        surface->GetDesc(&description);
        surface->LockRect(&locked,nullptr,0);
        switch (description.Format) {
        case D3DFMT_UNKNOWN:
        case D3DFMT_A8R8G8B8: {
            std::uint32_t rgb[3]{0,0,0};
            for (std::uint32_t y=0;y<description.Height;++y) {
                auto* pixel=reinterpret_cast<Texel8888*>(
                    static_cast<std::uint8_t*>(locked.pBits)+locked.Pitch*y);
                for (std::uint32_t x=0;x<description.Width;++x) {
                    if (pixel->alpha==0) {
                        rgb[0]=0;rgb[1]=0;rgb[2]=0;
                        std::uint32_t count=0;

                        if (x!=0) accumulate_texel8888(rgb,pixel-1,count);
                        if (x<description.Width-1) accumulate_texel8888(rgb,pixel+1,count);
                        if (y!=0) accumulate_texel8888(rgb,pixel-locked.Pitch/4,count);
                        if (y<description.Height-1) accumulate_texel8888(rgb,pixel+locked.Pitch/4,count);
                        if (count>1) { rgb[0]/=count; rgb[1]/=count; rgb[2]/=count; }

                        pixel->red=static_cast<std::uint8_t>(rgb[0]);
                        pixel->green=static_cast<std::uint8_t>(rgb[1]);
                        pixel->blue=static_cast<std::uint8_t>(rgb[2]);
                    }
                    ++pixel;
                }
            }
            break;
        }
        case D3DFMT_A1R5G5B5: {
            std::uint32_t rgb[3]{0,0,0};
            for (std::uint32_t y=0;y<description.Height;++y) {
                auto* pixel=reinterpret_cast<Texel1555*>(
                    static_cast<std::uint8_t*>(locked.pBits)+locked.Pitch*y);
                for (std::uint32_t x=0;x<description.Width;++x) {
                    if (pixel->alpha==0) {
                        rgb[0]=0;rgb[1]=0;rgb[2]=0;
                        std::uint32_t count=0;

                        if (x!=0) accumulate_texel1555(rgb,pixel-1,count);
                        if (x<description.Width-1) accumulate_texel1555(rgb,pixel+1,count);
                        if (y!=0) accumulate_texel1555(rgb,pixel-locked.Pitch/2,count);
                        if (y<description.Height-1) accumulate_texel1555(rgb,pixel+locked.Pitch/2,count);
                        if (count>1) {rgb[0]/=count;rgb[1]/=count;rgb[2]/=count;}

                        pixel->red=static_cast<std::uint16_t>(rgb[0]);
                        pixel->green=static_cast<std::uint16_t>(rgb[1]);
                        pixel->blue=static_cast<std::uint16_t>(rgb[2]);
                    }
                    ++pixel;
                }
            }
            break;
        }
        case D3DFMT_A4R4G4B4: {
            std::uint32_t rgb[3]{0,0,0};
            for (std::uint32_t y=0;y<description.Height;++y) {
                auto* pixel=reinterpret_cast<Texel4444*>(
                    static_cast<std::uint8_t*>(locked.pBits)+locked.Pitch*y);
                for (std::uint32_t x=0;x<description.Width;++x) {
                    if (pixel->alpha==0) {
                        rgb[0]=0;rgb[1]=0;rgb[2]=0;
                        std::uint32_t count=0;

                        if (x!=0) accumulate_texel4444(rgb,pixel-1,count);
                        if (x<description.Width-1) accumulate_texel4444(rgb,pixel+1,count);
                        if (y!=0) accumulate_texel4444(rgb,pixel-locked.Pitch/2,count);
                        if (y<description.Height-1) accumulate_texel4444(rgb,pixel+locked.Pitch/2,count);
                        if (count>1) {rgb[0]/=count;rgb[1]/=count;rgb[2]/=count;}

                        pixel->red=static_cast<std::uint16_t>(rgb[0]);
                        pixel->green=static_cast<std::uint16_t>(rgb[1]);
                        pixel->blue=static_cast<std::uint16_t>(rgb[2]);
                    }
                    ++pixel;
                }
            }
            break;
        }
        case D3DFMT_A8R3G3B2: {
            std::uint32_t rgb[3]{0,0,0};
            for (std::uint32_t y=0;y<description.Height;++y) {
                auto* pixel=reinterpret_cast<Texel8332*>(
                    static_cast<std::uint8_t*>(locked.pBits)+locked.Pitch*y);
                for (std::uint32_t x=0;x<description.Width;++x) {
                    if (pixel->alpha==0) {
                        rgb[0]=0;rgb[1]=0;rgb[2]=0;
                        std::uint32_t count=0;

                        if (x!=0) accumulate_texel8332(rgb,pixel-1,count);
                        if (x<description.Width-1) accumulate_texel8332(rgb,pixel+1,count);
                        if (y!=0) accumulate_texel8332(rgb,pixel-locked.Pitch/2,count);
                        if (y<description.Height-1) accumulate_texel8332(rgb,pixel+locked.Pitch/2,count);
                        if (count>1) {rgb[0]/=count;rgb[1]/=count;rgb[2]/=count;}

                        pixel->red=static_cast<std::uint16_t>(rgb[0]);
                        pixel->green=static_cast<std::uint16_t>(rgb[1]);
                        pixel->blue=static_cast<std::uint16_t>(rgb[2]);
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
