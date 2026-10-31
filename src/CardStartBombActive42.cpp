// Exact native 42B Card-start BombController state predicate.
// A borrowed receiver view avoids changing the public BombController ABI;
// the observed +0x18 word is the real BombController::active_state.
#include "Bomb.hpp"
namespace th20 {
struct NativeCardBombActiveView {
    bool active_478130() const;
};
bool NativeCardBombActiveView::active_478130() const {
    return reinterpret_cast<const BombController*>(this)->active_state == 1;
}
}
