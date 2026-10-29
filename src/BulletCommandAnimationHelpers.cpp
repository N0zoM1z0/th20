// Original Bullet command helper operations, independently confirmed from the
// locked native callers. Source-level member/free-function spelling is open;
// one-argument __fastcall preserves the original ECX receiver ABI.
#include "Animation.hpp"

namespace th20 {

void __fastcall set_animation_flag_byte_01_zero(Animation* animation) {
    animation->base.flags.bytes_00.field_01 = 0;
}

void __fastcall set_animation_flag_byte_01_one(Animation* animation) {
    animation->base.flags.bytes_00.field_01 = 1;
}

void __fastcall set_animation_flag_byte_01_two(Animation* animation) {
    animation->base.flags.bytes_00.field_01 = 2;
}

void __fastcall interrupt_animation_mode2(Animation* animation) {
    animation->interrupt(2);
}

} // namespace th20
