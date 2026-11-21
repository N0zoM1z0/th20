#include "EnemyState.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"
#include "AnimationFile.hpp"
#include "Animation.hpp"
#include <cstdint>

namespace th20 {
namespace {

void create_indexed_enemy_animation(EnemyState& state, std::int32_t index,
                                    std::int32_t script, bool reread_script) {
    if (state.animations.size() < static_cast<std::uint32_t>(index) + 1u)
        state.animations.resize(static_cast<std::uint32_t>(index) + 1u);

    state.animations[index].handle.retire();
    if (script < 0)
        return;

    auto* file = state.context->enemy_controller()->animation_file(state.field_1c);
    const std::int32_t layer = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(state.field_34) + 7u);
    const std::int32_t spawn_script = reread_script ? state.integer_argument(1) : script;
    state.animations[index].handle = file->spawn_flag2(nullptr, spawn_script, layer, nullptr);

    if (index == 0) {
        state.field_24 = state.integer_argument(1);
        state.field_20 = state.field_1c;
    }

    Animation* animation = state.animations[index].handle.resolve();
    if (index == 0) {
        state.vector_170.x = animation->height();
        state.vector_170.y = animation->width();
    }

    if ((state.flags.word_00 >> 5) & 1u)
        state.animations[index].clear_flag0_recursively();
}

} // namespace

// Native case 7 / opcode 313 adds a nonnegative-index guard before the same
// indexed animation creation protocol used by opcode 303.
int execute_enemy_animation_spawn_guarded(EnemyState& state) {
    const std::int32_t index = state.integer_argument(0);
    const std::int32_t script = state.integer_argument(1);
    if (index < 0)
        return 0;
    create_indexed_enemy_animation(state, index, script, true);
    return 0;
}

// Native case 10 / opcode 316 maps the script operand through field_28: a
// negative selector uses field_28 directly, otherwise it adds 5 + selector.
int execute_enemy_animation_spawn_mapped(EnemyState& state) {
    const std::int32_t index = state.integer_argument(0);
    const std::int32_t selector = state.integer_argument(1);
    if (state.animations.size() < static_cast<std::uint32_t>(index) + 1u)
        state.animations.resize(static_cast<std::uint32_t>(index) + 1u);

    state.animations[index].handle.retire();
    auto* file = state.context->enemy_controller()->animation_file(state.field_1c);
    const std::int32_t layer = static_cast<std::int32_t>(
        static_cast<std::uint32_t>(state.field_34) + 7u);
    const std::int32_t spawn_script = selector < 0
        ? state.field_28
        : static_cast<std::int32_t>(static_cast<std::uint32_t>(state.field_28) + 5u +
                                    static_cast<std::uint32_t>(selector));
    state.animations[index].handle = file->spawn_flag2(nullptr, spawn_script, layer, nullptr);

    if (index == 0) {
        state.field_24 = state.integer_argument(1);
        state.field_20 = state.field_1c;
    }

    Animation* animation = state.animations[index].handle.resolve();
    if (index == 0) {
        state.vector_170.x = animation->height();
        state.vector_170.y = animation->width();
    }

    if ((state.flags.word_00 >> 5) & 1u)
        state.animations[index].clear_flag0_recursively();
    return 0;
}

} // namespace th20
