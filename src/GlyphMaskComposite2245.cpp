// Game-owned 2,245B glyph compositor at 0x00416420. SOURCE-PRESENT,
// NONEXACT: its two native pixel-format branches and 16B PMR-vector
// offsets are reconstructed, but the full Win32/PMR EH lowering is open.
// The 16-bit live source-pixel stride is now restored alongside the
// four stencil-index E8 calls; the complete parent remains NONEXACT.
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
    // Snapshot the original DIB extent before changing any live pixel data.
    const std::int32_t length=pixel_stride_4156c0()*rows;
    auto* pixels=bitmap_pixels_4156a0();
    auto* original=process_allocator->allocate_array<std::uint8_t>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\core\\grpfont.cpp:615 u_char",length);
    std::memcpy(original,pixels,length);
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
        // One immutable stencil base serves every row and neighbor test.
        const auto* stencil=reinterpret_cast<const std::uint32_t*>(original);
        PackedColor opaque(color);
        const std::int32_t row_words=pixel_stride_4156c0()/4;
        // The native outline color flips only the packed alpha byte in place.
        opaque.channels.alpha = static_cast<std::uint8_t>(opaque.channels.alpha ^ 0xffu);
        std::int32_t row_advance=0;
        // Native update edge reads the live stride before the row test.
        for (std::int32_t y=0;y<rows;
             ++y,row_advance+=pixel_stride_4156c0()) {
            auto* dest=reinterpret_cast<std::uint32_t*>(
                pixels+row_advance+start*4);
            for (std::int32_t x=start;x<end;++x,++dest) {
                if (reinterpret_cast<const PackedColorChannels*>(dest)->alpha!=0) {
                    bool touches_outline=false;
                    for (const GlyphMaskOffset& off:offsets) {
                    // The original has two genuine E8 calls per vector
                    // element to the folded 22B array-index helper.
                    const std::int32_t delta_x=off[0];
                    const std::int32_t delta_y=off[1];
                        if (((x-delta_x>=0 && y-delta_y>=0) &&
                             (stencil[(y-delta_y)*row_words+x-delta_x]>>24)!=0xff) ||
                            ((x+delta_x<canvas_width_415800() && y-delta_y>=0) &&
                             (stencil[(y-delta_y)*row_words+x+delta_x]>>24)!=0xff) ||
                            ((x-delta_x>=0 && y+delta_y<rows) &&
                             (stencil[(y+delta_y)*row_words+x-delta_x]>>24)!=0xff) ||
                            ((x+delta_x<canvas_width_415800() && y+delta_y<rows) &&
                             (stencil[(y+delta_y)*row_words+x+delta_x]>>24)!=0xff)) {
                            touches_outline=true;
                            break;
                        }
                    }
                    if (touches_outline) {
                        *reinterpret_cast<PackedColorChannels*>(dest)=opaque.channels;
                    } else {
                        auto* channels=reinterpret_cast<std::uint8_t*>(dest);
                        channels[0]=opaque.channels.blue;
                        channels[1]=opaque.channels.green;
                        channels[2]=opaque.channels.red;
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
                pixels+y*pixel_stride_4156c0()+start*2);
            for (std::int32_t x=start;x<end;++x,++dest) {
                // Native RGBA4444 reads the *live* per-pixel source row
                // stride here, before enumerating stencil offsets. This
                // mutable scratch address then holds each real guarded
                // neighbor's source address for its alpha-nibble test.
                // Multiplication precedes signed division, as in the PE.
                const std::uint16_t* stencil=&reinterpret_cast<const std::uint16_t*>(original)[((y*pixel_stride_4156c0())/2)+x];
                bool touches_outline=false;
                for (const GlyphMaskOffset& off:offsets) {
                    // The original has two genuine E8 calls per vector
                    // element to the folded 22B array-index helper.
                    const std::int32_t delta_x=off[0];
                    const std::int32_t delta_y=off[1];
                    if (((x-delta_x>=0 && y-delta_y>=0) &&
                         ((stencil=&reinterpret_cast<const std::uint16_t*>(original)[((y-delta_y)*pixel_stride_4156c0()/2)+x-delta_x]), ((*stencil>>12)!=0xf))) ||
                        ((x+delta_x<canvas_width_415800() && y-delta_y>=0) &&
                         ((stencil=&reinterpret_cast<const std::uint16_t*>(original)[((y-delta_y)*pixel_stride_4156c0()/2)+x+delta_x]), ((*stencil>>12)!=0xf))) ||
                        ((x-delta_x>=0 && y+delta_y<rows) &&
                         ((stencil=&reinterpret_cast<const std::uint16_t*>(original)[((y+delta_y)*pixel_stride_4156c0()/2)+x-delta_x]), ((*stencil>>12)!=0xf))) ||
                        ((x+delta_x<canvas_width_415800() && y+delta_y<rows) &&
                         ((stencil=&reinterpret_cast<const std::uint16_t*>(original)[((y+delta_y)*pixel_stride_4156c0()/2)+x+delta_x]), ((*stencil>>12)!=0xf)))) {
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
