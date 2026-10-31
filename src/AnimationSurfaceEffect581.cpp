// Original 581B Renderer surface transfer and optional per-pixel variation.
// This is the real texture/RECT D3D9 operation and uses actual original
// locked random state for the observed three per-channel pulses.
// CORE/RECON-1092: WHOLE STRICT EXACT original 581/581 game Boss.
// A meaningful nested D3D9 acquired-surface scope after draw-flush
// naturally makes pinned MSVC emit the genuine native flush-boundary NOP.
// No source padding, assembly or fake side effects are needed.
#include "NativeRendererSurfaceBlitView.hpp"
#include "AnimationFile.hpp"
#include "NativeRendererRandomPulse.hpp"
#include "EffectParameters.hpp"
#include <d3d9.h>
#include <d3dx9tex.h>
#include <array>
#include <cstdint>
namespace th20 {
extern NativeRendererRandomPulse native_renderer_pulse_5ba4c4;
void NativeRendererSurfaceBlitView::blit_surface_effect_44be40(
        std::int32_t file_index,std::int32_t texture_index,
        IDirect3DSurface9* source,const RECT* dest_rect,
        const RECT* source_rect,std::int32_t effect) {
    auto& files=*reinterpret_cast<std::array<AnimationFile*,42>*>(
        reinterpret_cast<std::uint8_t*>(this)+0x06000730);
    if (files[file_index]->textures[texture_index].texture==nullptr)
        return;
    flush_draws();
    // The acquired D3D9 surface and its optional locked pixel storage
    // belong to a single nested lifetime scope after the draw flush.
    {
        auto& second_files=*reinterpret_cast<std::array<AnimationFile*,42>*>(
            reinterpret_cast<std::uint8_t*>(this)+0x06000730);
        IDirect3DSurface9* dest_surface;
        if (second_files[file_index]->textures[texture_index].texture
                ->GetSurfaceLevel(0,&dest_surface)!=D3D_OK)
            return;
        if (D3DXLoadSurfaceFromSurface(dest_surface,nullptr,dest_rect,source,
                nullptr,source_rect,D3DX_FILTER_POINT,0)!=D3D_OK) {
            dest_surface->Release();
            return;
        }
        if (effect==1) {
            D3DLOCKED_RECT locked;
            const HRESULT locked_status=dest_surface->LockRect(&locked,dest_rect,0);
            if (locked_status!=D3D_OK) {
                dest_surface->Release();
                return;
            }
            auto* row=static_cast<std::uint32_t*>(locked.pBits);
            for (std::int32_t x=0;x<dest_rect->right-dest_rect->left;++x) {
                auto* pixel=row;
                PackedColor staging;
                for (std::int32_t y=0;y<dest_rect->bottom-dest_rect->top;++y) {
                    staging.value=*pixel;
                    // Access the same four original packed color lanes twice,
                    // keeping C++ integer promotion signed before division.
                    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(pixel)+1)=static_cast<std::uint8_t>(
                        *reinterpret_cast<const std::uint8_t*>(reinterpret_cast<const std::uint8_t*>(&staging)+1)-(*reinterpret_cast<const std::uint8_t*>(reinterpret_cast<const std::uint8_t*>(&staging)+1)*native_renderer_pulse_5ba4c4.random_byte_449d20())/0x300);
                    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(pixel)+0)=static_cast<std::uint8_t>(
                        *reinterpret_cast<const std::uint8_t*>(reinterpret_cast<const std::uint8_t*>(&staging)+0)-(*reinterpret_cast<const std::uint8_t*>(reinterpret_cast<const std::uint8_t*>(&staging)+0)*native_renderer_pulse_5ba4c4.random_byte_449d20())/0x300);
                    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(pixel)+2)=static_cast<std::uint8_t>(
                        *reinterpret_cast<const std::uint8_t*>(reinterpret_cast<const std::uint8_t*>(&staging)+2)-(*reinterpret_cast<const std::uint8_t*>(reinterpret_cast<const std::uint8_t*>(&staging)+2)*native_renderer_pulse_5ba4c4.random_byte_449d20())/0x500);
                    *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uint8_t*>(pixel)+3)=0xff;
                    ++pixel;
                }
                // The original advances by a count of 32-bit pixels, after
                // its observed unsigned stride shift, not by raw signed bytes.
                row+=static_cast<std::uint32_t>(locked.Pitch)>>2;
            }
            dest_surface->UnlockRect();
        }
        dest_surface->Release();
    }
}
}
