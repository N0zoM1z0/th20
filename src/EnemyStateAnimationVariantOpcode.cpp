#include "EnemyState.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"
#include "AnimationFile.hpp"
#include "Animation.hpp"
#include <cstdint>

namespace th20 {

// Native jump-table case 10 covers opcodes 48, 173, 177, 201 and 316. The
// second operand selects field_28 directly when negative, otherwise field_28
// plus five and the selector. Unlike opcode 303 this path always spawns.
int execute_enemy_animation_spawn_mapped(EnemyState& state) {
    const std::int32_t index = state.integer_argument(0);
    const std::int32_t selector = state.integer_argument(1);
    const std::uint32_t storage_index = static_cast<std::uint32_t>(index);
    const std::uint32_t required_size = storage_index + 1u;
    if (state.animations.size() < required_size)
        state.animations.resize(required_size);

    auto& link = state.animations[storage_index];
    link.handle.retire();

    auto* file = state.context->enemy_controller()->animation_file(state.field_1c);
    const std::int32_t layer = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(state.field_34) + 7u);
    const std::int32_t script = selector < 0
        ? state.field_28
        : static_cast<std::int32_t>(static_cast<std::uint32_t>(state.field_28) +
                                    5u + static_cast<std::uint32_t>(selector));
    link.handle = file->spawn_flag2(nullptr, script, layer, nullptr);

    Animation* animation = link.handle.resolve();
    if (index == 0) {
        state.vector_170.x = animation->height();
        state.vector_170.y = animation->width();
    }

    if ((state.flags.word_00 >> 5) & 1u)
        link.clear_flag0_recursively();
    return 0;
}

} // namespace th20

namespace th20 {

// Native jump-table case 12 covers opcodes 41 and 318. It replaces link zero
// from field_28, resets the secondary animation identity and clears bit 4.
int execute_enemy_animation_spawn_primary_from_field(EnemyState& state) {
    auto& link = state.animations[0];
    link.handle.retire();

    auto* file = state.context->enemy_controller()->animation_file(state.field_1c);
    const std::int32_t layer = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(state.field_34) + 7u);
    const std::int32_t script = state.field_28;
    link.handle = file->spawn_flag2(nullptr, script, layer, nullptr);

    state.field_2c = 0;
    state.field_24 = state.field_28;
    state.field_20 = state.field_1c;
    state.flags.word_04 &= ~0x10u;
    return 0;
}

} // namespace th20
