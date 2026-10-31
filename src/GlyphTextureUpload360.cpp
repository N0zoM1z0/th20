// Whole original 360B/128-i386 TH20 D3D9 font bitmap upload Boss.
// This is the native game-specific GDI-to-D3D9 texture transfer, not a
// stand-in for virtual COM calls or the separately exact font producer.
// The receiver view borrows the actual 0x58-byte queued render job.
// Original game 360B bitmap-to-D3D texture upload; prototype typed owner.
#include "NativeGlyphUploadJobView.hpp"
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
void NativeGlyphUploadJobView::upload_4145d0() {
    IDirect3DSurface9* surface;
    target_texture->GetSurfaceLevel(0,&surface);
    D3DLOCKED_RECT mapped;
    surface->LockRect(&mapped,&upload_rectangle,0);
    auto* destination=static_cast<std::uint8_t*>(mapped.pBits);
    auto* source=reinterpret_cast<NativeGlyphCanvasView*>(canvas)->bitmap_pixels_4156a0();
    source+=reinterpret_cast<NativeGlyphCanvasView*>(canvas)->pixel_stride_4156c0()*pixel_rectangle.top;
    for (std::int32_t row=0;row<upload_rectangle.bottom-upload_rectangle.top;++row) {
        std::memcpy(destination,source+pixel_rectangle.left,
                    static_cast<std::size_t>((pixel_rectangle.right-pixel_rectangle.left)*4));
        destination+=mapped.Pitch;
        source+=reinterpret_cast<NativeGlyphCanvasView*>(canvas)->pixel_stride_4156c0();
    }
    surface->UnlockRect();
    if(surface){surface->Release();surface=nullptr;}
    reinterpret_cast<NativeGlyphCanvasView*>(canvas)->release_surface_416360();
    reinterpret_cast<NativeGlyphAllocatorBorrow*>(process_allocator)->release_canvas_413be0(canvas);
    if (completion_flag) *completion_flag=1;
    if (callback) callback();
}
}
