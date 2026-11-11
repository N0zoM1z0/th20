#include "Card.hpp"
#include <cstdint>
namespace th20 {
// Original 23B Card bit-8 getter at 0x004888A0. The two native game
// callers (875B Card tick, 6,073B battle controller) pass actual Card*
// receivers. A borrowed view preserves the real Card+0x78 flag ABI;
// this is not allocated and introduces no extra object storage.
struct NativeCardBit8GetterView {
    std::uint32_t flag8_value_4888a0() const;
};
std::uint32_t NativeCardBit8GetterView::flag8_value_4888a0() const {
    return (reinterpret_cast<const Card*>(this)->spell_flags.bits>>8)&1u;
}
}
