#include "EnemyState.hpp"
#include "AnimationHandleSetFlag0Recursive.hpp"
#include <cstdint>

namespace th20 {

// Native case 53 / opcode 503 clears the supplied low fourteen flag bits.
// When bit five is no longer active, every current animation handle restores
// flag zero recursively on its resolved Animation subtree.
int execute_enemy_animation_flags_clear_opcode(EnemyState& state) {
    const std::uint32_t bits = static_cast<std::uint32_t>(state.integer_argument(0)) & 0x3fffu;
    state.flags.word_00 &= ~bits;
    if ((state.flags.word_00 & 0x20u) == 0) {
        for (auto& link : state.animations)
            set_animation_handle_flag0_recursively(&link.handle);
    }
    return 0;
}

} // namespace th20
