// Game-owned 2,245B glyph compositor at 0x00416420. SOURCE-PRESENT,
// NONEXACT: its two native pixel-format branches and 16B PMR-vector
// offsets are reconstructed, but the full Win32/PMR EH lowering is open.
#include "NativeGlyphCanvasView.hpp"
#include "NativeGlyphMaskOffsets.hpp"
#include "DiagnosticAllocator.hpp"
#include "EffectParameters.hpp"
#include <cstdint>
#include <cstring>
#include <memory_resource>
#include <vector>
namespace th20 {
// Native original 16-bit color word is default-constructed before
// alpha/RGB nibbles are subsequently assigned on the true ARGB4444 path.
struct NativeGlyphColor4444 {
    std::uint16_t packed;
    NativeGlyphColor4444() : packed(0) {}
};
bool NativeGlyphCanvasView::composite_glyph_mask_416420(
    std::int32_t rows,std::int32_t start,std::int32_t end,
    std::uint32_t color,float radius) {
    // The original makes a separately owned copy of the current bitmap
    // before applying any alpha changes to the live mapped DIB memory.
    const std::int32_t row_stride=pixel_stride_4156c0();
    const std::int32_t length=row_stride*rows;
    auto* original=process_allocator->allocate_array<std::uint8_t>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\grpfont.cpp:615 u_char",length);
    std::memcpy(original,bitmap_pixels_4156a0(),length);
    const auto pixel_format=*reinterpret_cast<const std::int32_t*>(
        reinterpret_cast<const std::uint8_t*>(this)+0x100);
    if (pixel_format==0x15) {
        GlyphMaskOffsets offsets;
        const float radius_squared=radius*radius;
        for (std::int32_t delta_y=0;delta_y<static_cast<std::int32_t>(radius_squared);++delta_y) {
            for (std::int32_t delta_x=0;delta_x<static_cast<std::int32_t>(radius_squared);++delta_x) {
                if (static_cast<float>(delta_x*delta_x+delta_y*delta_y)<radius_squared &&
                    (delta_x!=0 || delta_y!=0)) {
                    const GlyphMaskOffset displacement{delta_x,delta_y};
                    offsets.emplace_back(displacement);
                }
            }
        }
        const PackedColor opaque(color);
        const std::uint32_t outlined=opaque.value^0xff000000u;
        for (std::int32_t y=0;y<rows;++y) {
            auto* dest=reinterpret_cast<std::uint32_t*>(
                bitmap_pixels_4156a0()+y*row_stride+start*4);
            for (std::int32_t x=start;x<end;++x,++dest) {
                if (reinterpret_cast<const std::uint8_t*>(dest)[3]!=0) {
                    const auto* stencil=reinterpret_cast<const std::uint32_t*>(original);
                    const std::int32_t row_words=row_stride/4;
                    bool touches_outline=false;
                    for (const GlyphMaskOffset& off:offsets) {
                        if (((x-off.x>=0 && y-off.y>=0) &&
                             (stencil[(y-off.y)*row_words+x-off.x]>>24)!=0xff) ||
                            ((x+off.x<canvas_width_415800() && y-off.y>=0) &&
                             (stencil[(y-off.y)*row_words+x+off.x]>>24)!=0xff) ||
                            ((x-off.x>=0 && y+off.y<rows) &&
                             (stencil[(y+off.y)*row_words+x-off.x]>>24)!=0xff) ||
                            ((x+off.x<canvas_width_415800() && y+off.y<rows) &&
                             (stencil[(y+off.y)*row_words+x+off.x]>>24)!=0xff)) {
                            touches_outline=true;
                            break;
                        }
                    }
                    if (touches_outline) {
                        *dest=outlined;
                    } else {
                        auto* channels=reinterpret_cast<std::uint8_t*>(dest);
                        channels[0]=static_cast<std::uint8_t>(opaque.value);
                        channels[1]=static_cast<std::uint8_t>(opaque.value>>8);
                        channels[2]=static_cast<std::uint8_t>(opaque.value>>16);
                    }
                }
            }
        }
    } else if (pixel_format==0x1a) {
        GlyphMaskOffsets offsets;
        const float radius_squared=radius*radius;
        for (std::int32_t delta_y=0;delta_y<static_cast<std::int32_t>(radius_squared);++delta_y) {
            for (std::int32_t delta_x=0;delta_x<static_cast<std::int32_t>(radius_squared);++delta_x) {
                if (static_cast<float>(delta_x*delta_x+delta_y*delta_y)<radius_squared &&
                    (delta_x!=0 || delta_y!=0)) {
                    const GlyphMaskOffset displacement{delta_x,delta_y};
                    offsets.emplace_back(displacement);
                }
            }
        }
        const PackedColor unpacked(color);
        NativeGlyphColor4444 packed_color;
        packed_color.packed=static_cast<std::uint16_t>(
              ((unpacked.value>>4)&0xf)
             |(((unpacked.value>>12)&0xf)<<4)
             |(((unpacked.value>>20)&0xf)<<8)
             |((((unpacked.value>>28)&0xf)^0xf)<<12));
        for (std::int32_t y=0;y<rows;++y) {
            auto* dest=reinterpret_cast<std::uint16_t*>(
                bitmap_pixels_4156a0()+y*row_stride+start*2);
            for (std::int32_t x=start;x<end;++x,++dest) {
                const auto* stencil=reinterpret_cast<const std::uint16_t*>(original);
                bool touches_outline=false;
                for (const GlyphMaskOffset& off:offsets) {
                    const std::int32_t row_pixels=row_stride/2;
                    if (((x-off.x>=0 && y-off.y>=0) &&
                         (stencil[(y-off.y)*row_pixels+x-off.x]>>12)!=0xf) ||
                        ((x+off.x<canvas_width_415800() && y-off.y>=0) &&
                         (stencil[(y-off.y)*row_pixels+x+off.x]>>12)!=0xf) ||
                        ((x-off.x>=0 && y+off.y<rows) &&
                         (stencil[(y+off.y)*row_pixels+x-off.x]>>12)!=0xf) ||
                        ((x+off.x<canvas_width_415800() && y+off.y<rows) &&
                         (stencil[(y+off.y)*row_pixels+x+off.x]>>12)!=0xf)) {
                        touches_outline=true;
                        break;
                    }
                }
                if (touches_outline) {
                    *dest=packed_color.packed;
                } else {
                    // The original retains the destination alpha nibble.
                    *dest=static_cast<std::uint16_t>((*dest&0xf000)|(packed_color.packed&0x0fff));
                }
            }
        }
    }
    process_allocator->release_array(original);
    return true;
}
} // namespace th20
