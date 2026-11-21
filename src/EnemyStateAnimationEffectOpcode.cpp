#include "EnemyState.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"
#include "AnimationFile.hpp"
#include "Animation.hpp"
#include "ItemResourceOwners.hpp"

namespace th20 {

// Native jump-table case 4 (opcode 307): positioned flag-2 spawn, then publish.
int execute_enemy_animation_effect_flag2_opcode(EnemyState& state) {
    auto* effects = state.context->effect_info();
    auto* controller = state.context->enemy_controller();
    const std::int32_t file_index = state.integer_argument(0);
    auto* file = controller->animation_file(file_index);
    Vector3& position = state.position_ref();
    const std::int32_t script = state.integer_argument(1);
    const AnimationHandle handle = file->spawn_flag2_position(
        nullptr, script, position, 0.0f, -1, nullptr);
    effects->publish_handle(handle.value);
    return 0;
}

// Native jump-table case 8 (opcode 314): same handoff with the flag-zero spawn.
int execute_enemy_animation_effect_spawn_opcode(EnemyState& state) {
    auto* effects = state.context->effect_info();
    auto* controller = state.context->enemy_controller();
    const std::int32_t file_index = state.integer_argument(0);
    auto* file = controller->animation_file(file_index);
    Vector3& position = state.position_ref();
    const std::int32_t script = state.integer_argument(1);
    const AnimationHandle handle = file->spawn(
        nullptr, script, position, 0.0f, -1, nullptr);
    effects->publish_handle(handle.value);
    return 0;
}

// Native jump-table case 5 (opcode 308): null-position flag-2 spawn.
int execute_enemy_animation_effect_flag2_handle_opcode(EnemyState& state) {
    auto* controller = state.context->enemy_controller();
    const std::int32_t file_index = state.integer_argument(0);
    auto* file = controller->animation_file(file_index);
    const std::int32_t script = state.integer_argument(1);
    const AnimationHandle handle = file->spawn_flag2(nullptr, script, -1, nullptr);
    auto* effects = state.context->effect_info();
    effects->publish_handle(handle.value);
    return 0;
}

// Native jump-table case 9 (opcode 315): positioned flag-2 spawn, then apply
// the current position and a third float operand when the new handle is live.
int execute_enemy_animation_effect_rotate_opcode(EnemyState& state) {
    AnimationHandle handle;
    auto* controller = state.context->enemy_controller();
    const std::int32_t file_index = state.integer_argument(0);
    auto* file = controller->animation_file(file_index);
    Vector3& position = state.position_ref();
    const std::int32_t script = state.integer_argument(1);
    handle = file->spawn_flag2_position(nullptr, script, position, 0.0f, -1, nullptr);

    if (Animation* animation = handle.resolve()) {
        animation->set_position(state.position_ref());
        animation->set_rotation(state.float_argument(2));
    }

    auto* effects = state.context->effect_info();
    effects->publish_handle(handle.value);
    return 0;
}

} // namespace th20
