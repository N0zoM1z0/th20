// Whole original 0x004383A0 338-byte direct AnimationFile VM script loader.
// Complete whole original native 338/338 exact at 0x004383A0, with all
// original five direct calls, three PE HIGHLOW global fields and mode bits.
// Distinct from the earlier strictly exact 32B bind_animation wrapper.
#include "AnimationFile.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"
#include <cstring>

namespace th20 {
void AnimationFile::load_script(Animation* animation, std::int32_t script_index) {
    // Both conditions and their order are native-observed. +0x54 is the
    // loaded script-pointer array, +0x5C is the original atomic stage.
    if (scripts[script_index] == nullptr || stage) {
        // The original zeros the entire real 0x5E4-byte Animation object.
        std::memset(animation, 0, sizeof(Animation));
    } else {
        animation->base.field_440 = static_cast<std::uint16_t>(script_index);
        animation->base.field_18 = id;
        animation->base.field_1c = id;
        // Original +0x4A0 first drops the upper two mode bits, then sets
        // the low two bits to 2 through a separate byte write.
        animation->base.flags.bits_08.other_6_7 = false;
        animation->base.flags.bits_08.mode = 2;
        animation->base.field_24 = script_index;
        animation->base.field_28 = 0;
        animation->timer_4d8 = 0;
        animation->timer_4c8 = 0;
        animation->base.flags.bit_10 = 0;
        animation->field_5dc = nullptr;
        current_animation_pool->update_animation(animation);

        // This owner is still opaque; native x86 independently accesses a
        // real writable counter at pool-owner +0xB8. Byte addressing here
        // documents only this observed member, not a fabricated full class.
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<unsigned char*>(current_animation_pool) + 0xb8) =
        *reinterpret_cast<std::uint32_t*>(reinterpret_cast<unsigned char*>(current_animation_pool) + 0xb8) + 1;
        if (animation->base.flags.bits_08.mode == 2)
            animation->base.flags.bits_08.mode = 1;
    }
}
}
