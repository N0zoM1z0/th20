// Whole original 104B format initialization/fallback for TH20 text bitmaps.
// The three calls always use the genuine 0x00415120 native GDI initializer;
// this view does not claim that still-unreconstructed callee is exact.
#include "NativeGlyphCanvasView.hpp"
namespace th20 {
bool NativeGlyphCanvasView::ensure_format_4153d0(
    std::int32_t width,std::int32_t height,std::int32_t pixel_format) {
    if (create_gdi_surface_415120(width,height,pixel_format)) return true;
    if (pixel_format == 0x19 || pixel_format == 0x1A) {
        return create_gdi_surface_415120(width,height,0x15);
    }
    if (pixel_format == 0x17) {
        return create_gdi_surface_415120(width,height,0x16);
    }
    return false;
}
}
