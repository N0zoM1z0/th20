#pragma once
#include <windows.h>
#include <d3d9.h>
#include <cstddef>
#include <cstdint>
#include <functional>
#include "NativeGlyphCanvasStorage.hpp"
namespace th20 {
// Nonowning typed view of the real game glyph-render job at +0x00..+0x57.
// The D3D upload method proves +0x04 is a texture COM pointer (not the
// provisional color word), and +0x28 is a completion byte pointer.
// Earlier native constructors have a compatible 0x58-byte physical layout;
// their public field/parameter names need separate ABI reconciliation.
struct NativeGlyphUploadJobView {
    NativeGlyphCanvasStorage* canvas;
    IDirect3DTexture9* target_texture;
    RECT upload_rectangle;
    RECT pixel_rectangle;
    std::uint8_t* completion_flag;
    std::uint32_t unresolved_2c;
    std::function<void()> callback;
    void upload_4145d0();
};
#if defined(_M_IX86)
static_assert(sizeof(NativeGlyphUploadJobView)==0x58);
static_assert(offsetof(NativeGlyphUploadJobView,canvas)==0x00);
static_assert(offsetof(NativeGlyphUploadJobView,target_texture)==0x04);
static_assert(offsetof(NativeGlyphUploadJobView,upload_rectangle)==0x08);
static_assert(offsetof(NativeGlyphUploadJobView,pixel_rectangle)==0x18);
static_assert(offsetof(NativeGlyphUploadJobView,completion_flag)==0x28);
static_assert(offsetof(NativeGlyphUploadJobView,callback)==0x30);
#endif
// The original DiagnosticAllocator object offers a separately unresolved
// 97B canvas release entrypoint. This is only a borrowed interface to it.
struct NativeGlyphAllocatorBorrow {
    void release_canvas_413be0(NativeGlyphCanvasStorage* canvas);
};
}
