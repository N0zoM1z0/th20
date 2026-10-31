#pragma once
#include <cstdint>
namespace th20 {
// Non-owning view of the native 0x124-byte font bitmap surface. No instance,
// hidden base, vtable or allocation ownership is invented by this interface.
struct NativeGlyphCanvasView {
    // Entire original 0x00415120 bitmap/DC creation remains a separate Boss.
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
};
}
