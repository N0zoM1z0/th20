#pragma once
#include <cstdint>
namespace th20 {
// Non-owning view of the native 0x124-byte font bitmap surface. No instance,
// hidden base, vtable or allocation ownership is invented by this interface.
struct NativeGlyphPixelFormat;
struct NativeGlyphCanvasView {
    // Original 681B bitmap/DC creator is source-present, but not exact.
    bool release_surface_416360();
    const NativeGlyphPixelFormat* pixel_format_415640(std::int32_t format);
    bool create_gdi_surface_415120(std::int32_t width,
                                   std::int32_t height,
                                   std::int32_t pixel_format);
    bool ensure_format_4153d0(std::int32_t width,
                              std::int32_t height,
                              std::int32_t pixel_format);
    // Three distinct native 20-byte accessors observed directly in the
    // original 2,227B text core /2,245B glyph compositor call graph.
    void* device_context_415620() const;
    std::uint8_t* bitmap_pixels_4156a0() const;
    std::int32_t pixel_stride_4156c0() const;
    // Original glyph compositor reads this width four times from +0x104.
    std::int32_t canvas_width_415800() const;
};
}
