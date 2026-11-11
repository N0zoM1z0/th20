// Original Card HUD bit0 reset at 0x00487B90: real 32B whole exact,
// called by the 875B Card periodic update if the Timer reaches 60 frames
// while the Card+0x78 bit9 is clear. The large HUD owner is borrowed;
// no fabricated 0x3344-byte aggregate is allocated.
#include "NativeCardTickViews.hpp"
#include <cstdint>
namespace th20 {
void NativeCardTickUiView::clear_ui_flag0_487b90() {
    *reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uint8_t*>(this)+0x3344)&=~1u;
}
}
