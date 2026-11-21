#include "EnemyState.hpp"
#include "Enemy.hpp"
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

namespace th20 {

// Native case 14 / opcode 320 writes the per-link XY offset and zeros Z.
int execute_enemy_animation_link_offset_opcode(EnemyState& state) {
    const std::int32_t index = state.integer_argument(0);
    const float x = state.float_argument(1);
    auto& offset = state.animations[index].offset;
    offset.x = x;
    const float y = state.float_argument(2);
    offset.y = y;
    offset.z = 0.0f;
    return 0;
}

// Native case 15 / opcode 322 reads the parent operand before the link index.
int execute_enemy_animation_link_parent_opcode(EnemyState& state) {
    const std::int32_t parent = state.integer_argument(1);
    const std::int32_t index = state.integer_argument(0);
    state.animations[index].parent = parent;
    return 0;
}

// Native case 16 / opcode 323 stores the two integer state selectors.
int execute_enemy_animation_state_selectors_opcode(EnemyState& state) {
    state.field_258 = state.integer_argument(0);
    state.field_254 = state.integer_argument(1);
    return 0;
}

// Native cases 22/23/24 toggle the three low bits of EnemyState word_08.
int execute_enemy_animation_flags_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 341:
        state.flags.word_08 |= 4u;
        break;
    case 342:
        state.flags.word_08 &= ~4u;
        break;
    case 343: {
        const std::uint32_t value = static_cast<std::uint32_t>(state.integer_argument(0));
        state.flags.word_08 = (state.flags.word_08 & ~8u) | ((value & 1u) << 3);
        break;
    }
    default:
        return 0;
    }
    return 0;
}

// Native case 25 aliases opcodes 44/73/344 and writes whether the identifier
// resolves to a live Enemy into integer destination zero.
int execute_enemy_has_selected_identifier_opcode(EnemyState& state) {
    auto* controller = state.context->enemy_controller();
    const std::int32_t identifier = state.integer_argument(1);
    const std::uint32_t exists = controller->find(identifier) != nullptr;
    *state.integer_argument_destination(0) = static_cast<std::int32_t>(exists);
    return 0;
}

} // namespace th20

namespace th20 {

// Native case 52 / opcode 502 ORs the supplied low 14 flag bits. When bit 5
// is active, all current animation links recursively clear Animation flag 0.
int execute_enemy_animation_flags_add_opcode(EnemyState& state) {
    const std::uint32_t bits = static_cast<std::uint32_t>(state.integer_argument(0)) & 0x3fffu;
    state.flags.word_00 |= bits;
    if ((state.flags.word_00 >> 5) & 1u) {
        for (auto& link : state.animations)
            link.clear_flag0_recursively();
    }
    return 0;
}



} // namespace th20
