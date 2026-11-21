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

namespace th20 {
namespace {

void replace_enemy_animation_link(EnemyState& state, std::int32_t index,
                                  std::int32_t script) {
    const std::uint32_t storage_index = static_cast<std::uint32_t>(index);
    const std::uint32_t required_size = storage_index + 1u;
    if (state.animations.size() < required_size)
        state.animations.resize(required_size);

    auto& link = state.animations[storage_index];
    link.handle.retire();
    auto* file = state.context->enemy_controller()->animation_file(state.field_1c);
    const std::int32_t layer = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(state.field_34) + 7u);
    link.handle = file->spawn_flag2(nullptr, script, layer, nullptr);

    Animation* animation = link.handle.resolve();
    if (index == 0) {
        state.vector_170.x = animation->height();
        state.vector_170.y = animation->width();
    }

    if ((state.flags.word_00 >> 5) & 1u)
        link.clear_flag0_recursively();
}

} // namespace

// Native jump-table case 3 (opcode 306): the second operand supplies the
// script. Index zero also publishes the secondary animation identity and bit.
int execute_enemy_animation_secondary_opcode(EnemyState& state) {
    const std::int32_t index = state.integer_argument(0);
    const std::int32_t script = state.integer_argument(1);
    replace_enemy_animation_link(state, index, script);

    if (index == 0) {
        state.flags.word_04 |= 0x10u;
        state.field_28 = script;
        state.field_2c = 0;
        state.field_24 = script;
        state.field_20 = state.field_1c;
    }
    return 0;
}

// Native jump-table case 7 (opcode 313): script comes from field_28 + 5.
int execute_enemy_animation_state_opcode(EnemyState& state) {
    const std::int32_t index = state.integer_argument(0);
    const std::int32_t script = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(state.field_28) + 5u);
    replace_enemy_animation_link(state, index, script);
    return 0;
}

} // namespace th20
