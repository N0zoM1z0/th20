// Native 0x004790A0 Player bit-2 marker after a Bomb has started.
#include "NativeBombPulseViews.hpp"
#include "Player.hpp"
namespace th20 {
void NativeBombPlayerView::mark_bomb_used_4790a0() {
    reinterpret_cast<Player*>(this)->entity_flags.bits |= 4u;
}
}
