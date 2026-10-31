#pragma once
#include <windows.h>
#include <cstddef>
#include <cstdint>
namespace th20 {
// Native allocation is proven 0x124 bytes and the first observed resource
// members start at +0x100. The preceding 0x100 bytes are genuine allocated
// storage with unresolved glyph/render state, not invented padding or RTTI.
// NativeGlyphCanvasView is the borrowing interface for this same storage.
struct NativeGlyphCanvasStorage {
    std::uint8_t unresolved_glyph_state_00[0x100];
    std::int32_t format, width, height, byte_count, stride;
    HDC device_context;
    HGDIOBJ previous_object;
    HBITMAP bitmap;
    void* pixel_bytes;
    NativeGlyphCanvasStorage();
};
#if defined(_M_IX86)
static_assert(sizeof(NativeGlyphCanvasStorage)==0x124);
static_assert(offsetof(NativeGlyphCanvasStorage,format)==0x100);
static_assert(offsetof(NativeGlyphCanvasStorage,byte_count)==0x10C);
static_assert(offsetof(NativeGlyphCanvasStorage,stride)==0x110);
static_assert(offsetof(NativeGlyphCanvasStorage,device_context)==0x114);
static_assert(offsetof(NativeGlyphCanvasStorage,previous_object)==0x118);
static_assert(offsetof(NativeGlyphCanvasStorage,bitmap)==0x11C);
static_assert(offsetof(NativeGlyphCanvasStorage,pixel_bytes)==0x120);
#endif
}
