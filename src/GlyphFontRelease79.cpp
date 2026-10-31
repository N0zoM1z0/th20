// Entire original TH20 glyph font resource release at 0x004155B0.
// The genuine 22 native HFONT handles are held by the original static
// std::array. A range-based reference loop selects its authentic
// _Unchecked_begin/_Unchecked_end helpers and actual GDI DeleteObject.
#include "NativeGlyphFontResources.hpp"
namespace th20 {
void release_glyph_fonts_4155b0() {
    for (auto& handle : native_glyph_fonts_5b66f0) {
        DeleteObject(handle);
    }
}
}
