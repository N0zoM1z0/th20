#include "EnemyState.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"
#include "AnimationFile.hpp"
#include "Animation.hpp"
#include <cstdint>

namespace th20 {

// Natural C++ reconstruction of the original 398-byte opcode-303 operation
// at 0x00496A00. The instruction index selects an EnemyAnimationLink; a
// nonnegative script creates a non-spatial flag-2 animation from the selected
// EnemyController file and updates the primary animation dimensions.
int EnemyState::spawn_animation() {
    const std::int32_t index = integer_argument(0);
    const std::int32_t script = integer_argument(1);
    if (animations.size() < static_cast<std::uint32_t>(index) + 1u)
        animations.resize(static_cast<std::uint32_t>(index) + 1u);

    animations[index].handle.retire();
    if (script >= 0) {
        auto* file = context->enemy_controller()->animation_file(field_1c);
        const std::int32_t layer =
            static_cast<std::int32_t>(static_cast<std::uint32_t>(field_34) + 7u);
        const std::int32_t spawn_script = integer_argument(1);
        animations[index].handle = file->spawn_flag2(nullptr, spawn_script, layer, nullptr);

        if (index == 0) {
            field_24 = integer_argument(1);
            field_20 = field_1c;
        }

        Animation* animation = animations[index].handle.resolve();
        if (index == 0) {
            vector_170.x = animation->height();
            vector_170.y = animation->width();
        }

        if ((flags.word_00 >> 5) & 1u)
            animations[index].clear_flag0_recursively();
    }
    return 0;
}

} // namespace th20
