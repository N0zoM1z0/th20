// Native Card finish status helpers, whole original non-relocated contributions.
#include "NativeCardFinishViews.hpp"
#include "Card.hpp"
namespace th20 {
std::int32_t NativeCardPlayView::is_paused_488800() const {
    return *reinterpret_cast<const std::int32_t*>(
        reinterpret_cast<const std::uint8_t*>(this)+0x10)==1;
}
std::uint32_t NativeCardEndFlagView::requires_extra_sound_488880() {
    return (reinterpret_cast<Card*>(this)->spell_flags.bits>>7)&1u;
}
}
