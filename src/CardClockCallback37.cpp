// Original 37B/15-i386 C callback: look up real Card 0 twice and
// invoke the independent native 645B clock settlement Boss if present.
// Not an alias to generic compiler or STL code.
#include "Card.hpp"
#include "NativeCardClockViews.hpp"
#include <cstdint>
namespace th20 {
void __cdecl card_clock_update_487560() {
    if (card(0))
        reinterpret_cast<NativeCardClockView*>(card(0))->process_clock_4872d0();
}
}
