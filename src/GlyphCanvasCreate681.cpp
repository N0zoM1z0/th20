// Entire game-owned original 681B/176-i386 GDI glyph canvas lifecycle.
// NONEXACT: real source compiles to 684B under pinned MSVC; all original
// Win32/GDI IAT field positions and semantic calls are independently verified.
#include "NativeGlyphCanvasView.hpp"
#include "NativeGlyphPixelFormat.hpp"
#include <windows.h>
#include <cstdint>
#include <cstring>
namespace th20 {
// Real descriptor fields read by the native 681B DIB creator. Pixel format
// code, bits/pixel and four observed packed masks occupy six native words;
// the complete lookup table remains a separately unresolved provider.

#if defined(_M_IX86)
static_assert(sizeof(BITMAPV4HEADER)==0x6C);
#endif
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
 auto* bytes=reinterpret_cast<std::uint8_t*>(this);
 *reinterpret_cast<HDC*>(bytes+0x114)=hdc;
 *reinterpret_cast<HBITMAP*>(bytes+0x11C)=bitmap;
 *reinterpret_cast<void**>(bytes+0x120)=pixels;
 *reinterpret_cast<std::int32_t*>(bytes+0x10C)=info.bV4SizeImage;
 *reinterpret_cast<HGDIOBJ*>(bytes+0x118)=previous;
 *reinterpret_cast<std::int32_t*>(bytes+0x104)=width;
 *reinterpret_cast<std::int32_t*>(bytes+0x108)=height;
 *reinterpret_cast<std::int32_t*>(bytes+0x100)=format;
 *reinterpret_cast<std::int32_t*>(bytes+0x110)=stride;
 // The native code re-reads the committed resource format after the GDI
 // allocation and publication, rather than trusting the original argument.
 const auto committed_format=*reinterpret_cast<std::int32_t*>(bytes+0x100);
 if (committed_format==0x15) {
  const std::uint32_t opaque_pixel=0xff000000u;
  auto* writer=static_cast<std::uint32_t*>(pixels);
  for (std::int32_t offset=0;offset<*reinterpret_cast<std::int32_t*>(bytes+0x10C);offset+=4,++writer) {
   *writer=opaque_pixel;
  }
 } else if (committed_format==0x1A) {
  const std::uint16_t translucent_pixel=0xf000;
  auto* writer=static_cast<std::uint16_t*>(pixels);
  for (std::int32_t offset=0;offset<*reinterpret_cast<std::int32_t*>(bytes+0x10C);offset+=2,++writer) {
   *writer=translucent_pixel;
  }
 }
 return true;
}
}
