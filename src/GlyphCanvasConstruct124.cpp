// Exact original 124B GDI font bitmap owner constructor at 0x00414200.
// The native caller provides a real 0x124-byte allocation. The constructor
// clears that whole valid storage, then explicitly publishes the observed
// GDI defaults in the exact native member initialization sequence.
#include "NativeGlyphCanvasStorage.hpp"
#include <cstring>
namespace th20 {
NativeGlyphCanvasStorage::NativeGlyphCanvasStorage() noexcept {
    std::memset(this,0,sizeof(*this));
    format=-1;
    width=0;
    height=0;
    device_context=nullptr;
    bitmap=nullptr;
    previous_object=nullptr;
    pixel_bytes=nullptr;
}
}
