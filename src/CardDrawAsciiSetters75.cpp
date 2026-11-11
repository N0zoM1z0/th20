// Three original Card/AsciiInf rendering-state methods. The real fields
// are font +0x1A1E0, layer +0x1A1EC and packed color alpha byte +0x1A1C3.
// These three physical original 25B heads have no E8/HIGHLOW relocations;
// no new AsciiInf object or hand-crafted instruction is introduced.
#include "TextLine.hpp"
#include "NativeCardAsciiDrawView.hpp"
#include <cstdint>
#include <cstddef>
namespace th20 {
// The real AsciiInf layout independently establishes these owners.
static_assert(offsetof(AsciiInf,font)==0x1A1E0);
static_assert(offsetof(AsciiInf,layer)==0x1A1EC);
static_assert(offsetof(AsciiInf,color)+3==0x1A1C3);
void NativeCardAsciiDrawView::set_font_488b00(std::int32_t value){reinterpret_cast<AsciiInf*>(this)->font=value;}
void NativeCardAsciiDrawView::set_layer_488a00(std::int32_t value){reinterpret_cast<AsciiInf*>(this)->layer=value;}
void NativeCardAsciiDrawView::set_color_alpha_488940(std::uint8_t value){*(reinterpret_cast<std::uint8_t*>(this)+0x1A1C3)=value;}
}
