// Entire original 681B/176-i386 game-owned GDI bitmap surface creator.
// Resource publication uses the original receiver directly, not a cached
// bytes alias; after publication the code switches on the committed format.
// In each alpha-fill arm the pixel pointer is acquired before constructing
// its meaningful 32-bit or 16-bit alpha value, as in native machine code.
#include "NativeGlyphCanvasView.hpp"
#include "NativeGlyphPixelFormat.hpp"
#include <windows.h>
#include <cstdint>
#include <cstring>
#if defined(_M_IX86)
static_assert(sizeof(BITMAPV4HEADER)==0x6C);
#endif
namespace th20 {

bool NativeGlyphCanvasView::create_gdi_surface_415120(
    std::int32_t width,std::int32_t height,std::int32_t format) {
 release_surface_416360();
 BITMAPV4HEADER info;
 std::memset(&info,0,sizeof(info));
 const auto* descriptor=pixel_format_415640(format);
 if (descriptor==nullptr) return false;
 const std::int32_t stride = (((width * static_cast<std::int32_t>(descriptor->bits_per_pixel)) / 8)+3)/4*4;
 info.bV4Size=sizeof(info);
 info.bV4Width=width;
 info.bV4Height=-(height+1);
 info.bV4Planes=1;
 info.bV4BitCount=static_cast<WORD>(descriptor->bits_per_pixel);
 info.bV4SizeImage=height*stride;
 if (format!=0x18 && format!=0x16) {
  info.bV4V4Compression=BI_BITFIELDS;
  info.bV4RedMask=descriptor->red_mask;
  info.bV4GreenMask=descriptor->green_mask;
  info.bV4BlueMask=descriptor->blue_mask;
  info.bV4AlphaMask=descriptor->alpha_mask;
 }
 void* pixels=nullptr;
 auto bitmap=CreateDIBSection(nullptr,reinterpret_cast<BITMAPINFO*>(&info),DIB_RGB_COLORS,&pixels,nullptr,0);
 if (bitmap==nullptr) return false;
 auto hdc=CreateCompatibleDC(nullptr);
 auto previous=SelectObject(hdc,bitmap);
 *reinterpret_cast<HDC*>(reinterpret_cast<std::uint8_t*>(this)+0x114)=hdc;
 *reinterpret_cast<HBITMAP*>(reinterpret_cast<std::uint8_t*>(this)+0x11C)=bitmap;
 *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this)+0x120)=pixels;
 *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x10C)=info.bV4SizeImage;
 *reinterpret_cast<HGDIOBJ*>(reinterpret_cast<std::uint8_t*>(this)+0x118)=previous;
 *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x104)=width;
 *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x108)=height;
 *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x100)=format;
 *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x110)=stride;
 switch(*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x100)) {
 case 0x15: {
  auto* writer=static_cast<std::uint32_t*>(pixels);
  std::uint32_t opaque_pixel=0xff000000u;
  for (std::int32_t offset=0;offset<*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x10C);offset+=4,++writer) {
   *writer=opaque_pixel;
  }
  break;
 }
 case 0x1A: {
  auto* writer=static_cast<std::uint16_t*>(pixels);
  std::uint16_t translucent_pixel=0xf000;
  for (std::int32_t offset=0;offset<*reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x10C);offset+=2,++writer) {
   *writer=translucent_pixel;
  }
  break;
 }
 default: break;
 }
 return true;
}
}
