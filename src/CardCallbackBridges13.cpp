// Two original Card-specific C callback bridges, each complete 13B/6-i386.
// Published by the original native 121B Card registration function.
// The update bridge calls the newly exact 875B Card frame owner; the
// draw bridge calls the separate source-absent original 797B draw owner.
#include "NativeCardTickViews.hpp"
namespace th20 {
std::int32_t __cdecl card_tick_callback_4885d0(NativeCardTickView* card) {
    return card->update_486f60();
}
std::int32_t __cdecl card_draw_callback_488680(NativeCardDrawView* card) {
    return card->draw_487590();
}
}
