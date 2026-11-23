#include "EnemyStateQueuedParametersOpcode.hpp"
#include "EnemyState.hpp"
#include <utility>

namespace th20 {

#if defined(_M_IX86) || defined(__i386__)
static_assert(offsetof(EnemyQueuedRecord, field_30) == 0x30);
#endif

bool execute_enemy_queued_parameters_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 619: {
        const auto selector = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(selector));
        auto* record = std::get<0>(std::move(selected));
        auto* metadata = std::get<1>(std::move(selected));
        (void)record;
        metadata->field_00 = state.float_argument(1);
        return true;
    }
    case 633: {
        const auto selector = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(selector));
        auto* record = std::get<0>(std::move(selected));
        auto* metadata = std::get<1>(std::move(selected));
        (void)metadata;
        record->field_30 -= 1u;
        if ((record->field_30 & 0x80000000u) != 0) {
            record->field_30 = 0;
        }
        return true;
    }
    case 700: {
        const auto selector = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(selector));
        auto& record = *selected.first;
        auto& metadata = *selected.second;

        record.parameters.position.x = state.float_argument(1);
        record.parameters.position.y = state.float_argument(2);
        record.parameters.position.z = state.float_argument(3);
        metadata.field_14 = state.float_argument(4);
        return true;
    }
    case 701: {
        const auto selector = state.integer_argument(0);
        auto selected = state.writable_shot(static_cast<std::uint32_t>(selector));
        auto& metadata = *selected.second;

        metadata.field_24 = static_cast<std::uint32_t>(state.integer_argument(1));
        metadata.field_28 = static_cast<std::uint32_t>(state.integer_argument(2));
        metadata.field_2c = static_cast<std::uint32_t>(state.integer_argument(3));
        metadata.field_30 = static_cast<std::uint32_t>(state.integer_argument(4));
        metadata.field_34 = static_cast<std::uint32_t>(state.integer_argument(5));
        return true;
    }
    default:
        return false;
    }
}

} // namespace th20
