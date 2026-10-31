// Complete original 82B native glyph pixel-format table selection.
// Iterate the 24-byte descriptors until their signed -1 sentinel or the
// requested format matches, then return null only when querying -1 itself.
#include "NativeGlyphCanvasView.hpp"
#include "NativeGlyphPixelFormat.hpp"
namespace th20 {
// Actual physical descriptor table starts at PE VA 0x005AE078. The PE owns
// the contents, this translation unit only declares the borrowed data.
extern const NativeGlyphPixelFormat native_glyph_pixel_formats_5ae078[];
const NativeGlyphPixelFormat* NativeGlyphCanvasView::pixel_format_415640(
    std::int32_t format) {
    std::int32_t index=0;
    for (; native_glyph_pixel_formats_5ae078[index].code!=-1 &&
           native_glyph_pixel_formats_5ae078[index].code!=format; ++index) {}
    if (format==-1) return nullptr;
    return &native_glyph_pixel_formats_5ae078[index];
}
}
