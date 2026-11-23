#include "EnemyStateResourceOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"
#include "StageResource.hpp"

namespace th20 {

bool execute_enemy_resource_opcode(EnemyState& state, std::int32_t opcode) {
    using Callback = int (EnemyState::*)();
    static const Callback callback_table[] = {
        nullptr,
        &EnemyState::clear_bullets_in_animation_rectangle,
        &EnemyState::clear_all_bullets_for_enemy_clear,
    };
    // The later selectors address overlapping windows of the same all-zero
    // data table: 0x0056FE98 and 0x0056FE9C.
    static const std::uint32_t callback_table_tail[8]{};

    switch (opcode) {
    case 622: {
        // Read the VM key before loading the process StageResource owner.
        const auto identifier = state.integer_argument(0);
        process_stage_resource->select_record(identifier);
        return true;
    }
    case 623: {
        // Native captures the Context EnemyController before the operand read.
        auto* const owner = state.context->enemy_controller();
        const auto value = static_cast<std::uint32_t>(state.integer_argument(0));
        owner->set_field_84_bit_0(value);
        return true;
    }
    case 624:
    case 631: {
        const auto index = state.integer_argument(0);
        state.update_callback = callback_table[index];
        state.field_2d8 = opcode == 631 ? 1u : 0u;
        return true;
    }
    case 625: {
        const auto index = state.integer_argument(0);
        state.field_2dc = callback_table_tail[index];
        return true;
    }
    case 626: {
        const auto index = state.integer_argument(0);
        state.field_2e4 = callback_table_tail[index + 1];
        return true;
    }
    default:
        return false;
    }
}

} // namespace th20
