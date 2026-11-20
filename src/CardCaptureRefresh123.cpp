// Original 123B Card capture/bomb state update at 0x00487BB0.
#include "Card.hpp"
#include "NativeCardCaptureTimeoutView.hpp"
#include "Bomb.hpp"
namespace th20 {
struct NativeCardBombActiveView { bool active_478130() const; };
struct NativeCardCaptureRefreshView { void refresh_487bb0(); };
void NativeCardCaptureRefreshView::refresh_487bb0() {
    if (reinterpret_cast<Card*>(this)->active()) {
        if (reinterpret_cast<NativeCardCaptureTimeoutView*>(this)->elapsed_4887d0()) {
            reinterpret_cast<Card*>(this)->bonus = 0;
            reinterpret_cast<Card*>(this)->spell_flags.bits &= ~2u;
            reinterpret_cast<Card*>(this)->spell_flags.bits &= ~0x20u;
        } else if (reinterpret_cast<NativeCardBombActiveView*>(reinterpret_cast<Card*>(this)->context->bomb_controller())->active_478130()) {
            reinterpret_cast<Card*>(this)->spell_flags.bits |= 0x20u;
        }
    }
}
}
