// Complete source of original 542B/164-i386 glyph canvas Alpha Boss.
// Original source has three real 0x15/0x19/0x1A pixel paths; this C++20
// candidate is not yet whole exact due to 16-bit mask/compiler register
// lowering. The fourth original argument is present but its role is open.
#include "NativeGlyphCanvasView.hpp"
#include <cstdint>
namespace th20 {
bool NativeGlyphCanvasView::invert_alpha_417ab0(
    std::int32_t rows,std::int32_t start,
    std::int32_t span,std::int32_t unknown_flag) {
    const std::int32_t count=pixel_stride_4156c0()*rows;
    auto* pixels=bitmap_pixels_4156a0();
    const auto format=*reinterpret_cast<std::int32_t*>(
        reinterpret_cast<std::uint8_t*>(this)+0x100);
    switch(format) {
      case 0x15: {
        for (std::int32_t y=0;y<rows;++y) {
            auto* row=reinterpret_cast<std::uint32_t*>(pixels) + canvas_width_415800()*y+start;
            for(std::int32_t x=0;x<span;++x,++row) {
                reinterpret_cast<std::uint8_t*>(row)[3]^=0xff;
            }
        }
        return true;
      }
      case 0x19: {
        auto* words=reinterpret_cast<std::uint16_t*>(pixels);
        for (std::int32_t i=0;i<count;i+=2,++words) {
            std::uint16_t bit = static_cast<std::uint16_t>((*words >> 15) & 1);
            bit = static_cast<std::uint16_t>((bit ^ 1) & 1);
            *words = static_cast<std::uint16_t>((*words & 0x7fff) | static_cast<std::uint16_t>(bit << 15));
            if (((*words >> 15) & 1) == 0) {
                *words&=0x83ff;
                *words&=0xfc1f;
                *words&=0xffe0;
            }
        }
        return true;
      }
      case 0x1a: {
        for (std::int32_t y=0;y<rows;++y) {
            auto* row=reinterpret_cast<std::uint16_t*>(pixels)+canvas_width_415800()*y+start;
            for (std::int32_t x=0;x<span;++x,++row) {
                *row=static_cast<std::uint16_t>((*row&0x0fff)|(((((*row>>12)^0xf)&0xf)<<12)));
            }
        }
        return true;
      }
      default: return false;
    }
}
}
