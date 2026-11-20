#include "EnemyStateSharedQueuedParametersOpcode.hpp"
#include "EnemyState.hpp"
#include "Angle.hpp"

namespace th20 {

bool execute_enemy_shared_queued_parameters_opcode(EnemyState& state,
                                                    std::int32_t opcode) {
    switch (opcode) {
    case 602: {
        const auto selector = state.integer_argument(0);
        auto selected = state.shared_shot(static_cast<std::uint32_t>(selector));
        auto& parameters = selected.first->parameters;
        parameters.type = static_cast<std::uint32_t>(state.integer_argument(1));
        parameters.color = static_cast<std::uint32_t>(state.integer_argument(2));
        return true;
    }
    case 603: {
        const auto selector = state.integer_argument(0);
        auto selected = state.shared_shot(static_cast<std::uint32_t>(selector));
        auto& offset = selected.first->vector_34;
        offset.x = state.float_argument(1);
        offset.y = state.float_argument(2);
        return true;
    }
    case 604: {
        const auto selector = state.integer_argument(0);
        auto selected = state.shared_shot(static_cast<std::uint32_t>(selector));
        auto& parameters = selected.first->parameters;
        parameters.angle = normalize_angle(state.float_argument(1));
        parameters.angle_step = normalize_angle(state.float_argument(2));
        return true;
    }
    default:
        return false;
    }
}

} // namespace th20
