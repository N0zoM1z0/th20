// Whole-exact original 542B/164-i386 game glyph canvas Alpha processor.
// Preserve the actual BGRA32, RGB555A1 and RGBA4444 pixel-width layouts,
// the nonzero-alpha branch preserving real RGB channels, and the separate
// row-pointer lifetime of the ARGB4444 path. The fourth native argument is
// observed on the original stack but its purpose remains unidentified.
#include "NativeGlyphCanvasView.hpp"
#include <cstdint>
namespace th20 {
struct NativeGlyphAlpha4444 { std::uint16_t rgb:12;std::uint16_t alpha:4; };
struct NativeGlyphAlpha1555 { std::uint16_t blue:5;std::uint16_t green:5;std::uint16_t red:5;std::uint16_t alpha:1; };
struct BGRA32GlyphPixel { std::uint8_t b,g,r,a; };
#if defined(_M_IX86)
static_assert(sizeof(NativeGlyphAlpha1555)==2);
static_assert(sizeof(NativeGlyphAlpha4444)==2);
static_assert(sizeof(BGRA32GlyphPixel)==4);
#endif
bool NativeGlyphCanvasView::invert_alpha_417ab0(
    std::int32_t rows,std::int32_t start,
    std::int32_t span,std::int32_t unknown_flag) {
    const std::int32_t count=pixel_stride_4156c0()*rows;
    auto* pixels=bitmap_pixels_4156a0();
    switch(*reinterpret_cast<const std::int32_t*>(
        reinterpret_cast<const std::uint8_t*>(this)+0x100)) {
      case 0x15: {
        for (std::int32_t y=0;y<rows;++y) {
            auto* row=reinterpret_cast<std::uint32_t*>(pixels) + canvas_width_415800()*y;
            row += start;
            for(std::int32_t x=0;x<span;++x,++row) {
                reinterpret_cast<BGRA32GlyphPixel*>(row)->a ^= 0xff;
            }
        }
        break;
      }
      case 0x19: {
        auto* words=reinterpret_cast<std::uint16_t*>(pixels);
        for (std::int32_t i=0;i<count;i+=2,++words) {
            reinterpret_cast<NativeGlyphAlpha1555*>(words)->alpha ^= 1;
            if (reinterpret_cast<NativeGlyphAlpha1555*>(words)->alpha != 0) {
                // Keep the native RGB555 color when the new Alpha bit is set.
            } else {
                // After toggling Alpha off, clear three genuine 5-bit RGB
                // subfields independently, in the native red/green/blue order.
                reinterpret_cast<NativeGlyphAlpha1555*>(words)->red=0;
                reinterpret_cast<NativeGlyphAlpha1555*>(words)->green=0;
                reinterpret_cast<NativeGlyphAlpha1555*>(words)->blue=0;
            }
        }
        break;
      }
      case 0x1a: {
        auto* row=reinterpret_cast<std::uint16_t*>(pixels);
        for (std::int32_t y=0;y<rows;++y) {
            row=reinterpret_cast<std::uint16_t*>(pixels)+canvas_width_415800()*y;
            row += start;
            for (std::int32_t x=0;x<span;++x,++row) {
                reinterpret_cast<NativeGlyphAlpha4444*>(row)->alpha ^= 0xf;
            }
        }
        break;
      }
      default: return false;
    }
    return true;
}
}
