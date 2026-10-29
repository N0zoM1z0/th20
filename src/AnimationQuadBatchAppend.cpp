// Whole original 352-byte renderer quad batch append at 0x0043E9B0.
// Six complete 28-byte POD vertices are naturally copied via native x86
// rep movsd, with capacity checked against the actual original pool tail.
// All field offsets are original game owner byte offsets: no padded owner
// or separate render manager is allocated, and no assembler is involved.
#include "AnimationQuadSubmitOwner.hpp"
#include "SpriteVertices.hpp"
#include <cstdint>
namespace th20 {
// Expanding the true owner lvalue at each original copy site preserves the
// native unoptimized pointer loads. A cached temporary changes x86 output.
#define DRAW_CURSOR (*reinterpret_cast<SpriteTexturedVertex**>( \
    reinterpret_cast<std::uint8_t*>(this) + 0x7C00E74))
#define DRAW_CAPACITY_POOL reinterpret_cast<SpriteTexturedVertex*>( \
    reinterpret_cast<std::uint8_t*>(this) + 0x6000E74)
#define DRAW_QUEUED_COUNT (*reinterpret_cast<std::uint32_t*>( \
    reinterpret_cast<std::uint8_t*>(this) + 0x6000E70))
std::int32_t AnimationQuadSubmitOwner::append_quad(SpriteTexturedVertex* source) {
    // Six vertices must fit before the native fixed-capacity pool tail.
    if (!(&DRAW_CURSOR[0] < &DRAW_CAPACITY_POOL[0xFFFFA])) return 1;
    DRAW_CURSOR[0] = source[0];
    DRAW_CURSOR[3] = source[1];
    DRAW_CURSOR[1] = DRAW_CURSOR[3];
    DRAW_CURSOR[4] = source[2];
    DRAW_CURSOR[2] = DRAW_CURSOR[4];
    DRAW_CURSOR[5] = source[3];
    DRAW_CURSOR += 6;
    ++DRAW_QUEUED_COUNT;
    return 0;
}

#undef DRAW_CURSOR
#undef DRAW_CAPACITY_POOL
#undef DRAW_QUEUED_COUNT
} // namespace th20
