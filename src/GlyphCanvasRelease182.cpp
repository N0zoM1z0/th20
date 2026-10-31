// Complete 182-byte game-owned GDI bitmap/DC resource release.
// This is a native boolean return, not the old speculative void method.
// The receiver itself is read directly at every real native field access:
// caching a duplicate bytes pointer would add a false compiler stack slot.
#include "NativeGlyphCanvasView.hpp"
#include <windows.h>
#include <cstdint>
namespace th20 {
bool NativeGlyphCanvasView::release_surface_416360() {
    if (*reinterpret_cast<HDC*>(reinterpret_cast<std::uint8_t*>(this)+0x114)!=nullptr) {
        SelectObject(
            *reinterpret_cast<HDC*>(reinterpret_cast<std::uint8_t*>(this)+0x114),
            *reinterpret_cast<HGDIOBJ*>(reinterpret_cast<std::uint8_t*>(this)+0x118));
        DeleteDC(*reinterpret_cast<HDC*>(reinterpret_cast<std::uint8_t*>(this)+0x114));
        DeleteObject(*reinterpret_cast<HGDIOBJ*>(reinterpret_cast<std::uint8_t*>(this)+0x11C));
        *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x100)=-1;
        *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x104)=0;
        *reinterpret_cast<std::int32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x108)=0;
        *reinterpret_cast<HDC*>(reinterpret_cast<std::uint8_t*>(this)+0x114)=nullptr;
        *reinterpret_cast<HBITMAP*>(reinterpret_cast<std::uint8_t*>(this)+0x11C)=nullptr;
        *reinterpret_cast<HGDIOBJ*>(reinterpret_cast<std::uint8_t*>(this)+0x118)=nullptr;
        *reinterpret_cast<void**>(reinterpret_cast<std::uint8_t*>(this)+0x120)=nullptr;
        return true;
    }
    return false;
}
}
