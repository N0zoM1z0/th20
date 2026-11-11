// Original Card process registration, whole native 121B/41-i386 exact:
// bind player Context, publish the Card owner, register update/draw
// callbacks as genuine native 0x28/0x0C priorities, reset Timer to zero.
#include "Card.hpp"
#include "Session.hpp"
#include "FunctionChainController.hpp"
#include "NativeCardTickViews.hpp"
#include <cstdint>
namespace th20 {
std::int32_t NativeCardSetupView::register_callbacks_487b10(std::int32_t index) {
    reinterpret_cast<Card*>(this)->bind_context(index);
    session.context(index).set_card(reinterpret_cast<Card*>(this));
    reinterpret_cast<Card*>(this)->update_node = register_update_disabled(
        0x28,reinterpret_cast<FunctionChainCallback>(&card_tick_callback_4885d0),this);
    reinterpret_cast<Card*>(this)->draw_node = register_draw_disabled(
        0x0C,reinterpret_cast<FunctionChainCallback>(&card_draw_callback_488680),this);
    reinterpret_cast<Card*>(this)->age = 0;
    return 0;
}
}
