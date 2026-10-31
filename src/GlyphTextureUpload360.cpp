// Whole original 360B/128-i386 TH20 D3D9 font bitmap upload Boss.
// This is the native game-specific GDI-to-D3D9 texture transfer, not a
// stand-in for virtual COM calls or the separately exact font producer.
// The shared real 0x58-byte NativeGlyphRenderJob now owns this original
// operator() const body, plus its independently exact ctor and destructor.
// The resource/layout owner is not duplicated into a parallel upload view.
// Original game 360B bitmap-to-D3D texture upload; prototype typed owner.
#include "NativeGlyphRenderJob.hpp"
#include "NativeGlyphCanvasView.hpp"
#include "NativeGlyphCanvasStorage.hpp"
#include "DiagnosticAllocator.hpp"
#include <windows.h>
#include <d3d9.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
namespace th20 {
void NativeGlyphRenderJob::operator()() const {
    IDirect3DSurface9* surface;
    reinterpret_cast<IDirect3DTexture9*>(target_texture)->GetSurfaceLevel(0,&surface);
    D3DLOCKED_RECT mapped;
    surface->LockRect(&mapped,reinterpret_cast<const RECT*>(&geometry),0);
    auto* destination=static_cast<std::uint8_t*>(mapped.pBits);
    auto* source=reinterpret_cast<NativeGlyphCanvasView*>(canvas)->bitmap_pixels_4156a0();
    source+=reinterpret_cast<NativeGlyphCanvasView*>(canvas)->pixel_stride_4156c0()*texture_region.field_b;
    for (std::int32_t row=0;row<geometry.field_d-geometry.field_b;++row) {
        std::memcpy(destination,source+texture_region.field_a,
                    static_cast<std::size_t>((texture_region.field_c-texture_region.field_a)*4));
        destination+=mapped.Pitch;
        source+=reinterpret_cast<NativeGlyphCanvasView*>(canvas)->pixel_stride_4156c0();
    }
    surface->UnlockRect();
    if(surface){surface->Release();surface=nullptr;}
    reinterpret_cast<NativeGlyphCanvasView*>(canvas)->release_surface_416360();
    // The real allocator template owns the 97B native object-release body.
    process_allocator->release_object(canvas);
    if (completion_flag) *completion_flag=1;
    if (callback) callback();
}
}
