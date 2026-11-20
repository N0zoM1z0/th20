#include "EnemyStateShotCommandOpcode.hpp"
#include "EnemyState.hpp"

namespace th20 {

// Original 609/610 and 611/612 differ only in explicit-vs-cursor indexing and
// base-vs-extended operand layouts. Keep the native read/store order visible:
// each successful VM read is committed before the next one can throw.
bool execute_enemy_shot_command_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 609:
    case 610:
    case 611:
    case 612: {
        const auto record_index = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(record_index));
        auto& metadata = *selected.second;

        const bool cursor_mode = opcode == 611 || opcode == 612;
        const bool extended = opcode == 610 || opcode == 612;
        std::uint32_t command_index = cursor_mode
            ? metadata.field_30
            : static_cast<std::uint32_t>(state.integer_argument(1));
        std::uint32_t operand = cursor_mode ? 1u : 2u;

        const std::uint32_t required_size = command_index + 1u;
        if (metadata.commands.size() < required_size)
            metadata.commands.resize(required_size);

        // Do not cache a BulletCommand& here. The original emits one real
        // vector::operator[] call after each VM operand evaluation; this also
        // preserves partial writes when a later operand throws.
        metadata.commands[command_index].flags =
            static_cast<std::uint32_t>(state.integer_argument(operand++));
        metadata.commands[command_index].opcode =
            static_cast<std::uint32_t>(state.integer_argument(operand++));
        metadata.commands[command_index].operand_10 = state.integer_argument(operand++);
        metadata.commands[command_index].operand_14 = state.integer_argument(operand++);
        if (extended) {
            metadata.commands[command_index].operand_18 = state.integer_argument(operand++);
            metadata.commands[command_index].operand_1c = state.integer_argument(operand++);
        }
        metadata.commands[command_index].operand_00 =
            state.float_argument(static_cast<std::int32_t>(operand++));
        metadata.commands[command_index].operand_04 =
            state.float_argument(static_cast<std::int32_t>(operand++));
        if (extended) {
            metadata.commands[command_index].operand_08 =
                state.float_argument(static_cast<std::int32_t>(operand++));
            metadata.commands[command_index].operand_0c =
                state.float_argument(static_cast<std::int32_t>(operand++));
        }

        // The native cursor store is the final operation. In explicit-index
        // mode it becomes index+1; cursor mode increments the old cursor.
        metadata.field_30 = cursor_mode ? metadata.field_30 + 1u : required_size;
        return true;
    }
    default:
        return false;
    }
}

} // namespace th20
