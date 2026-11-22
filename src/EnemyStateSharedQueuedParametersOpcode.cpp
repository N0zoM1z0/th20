#include "EnemyStateSharedQueuedParametersOpcode.hpp"
#include "EnemyState.hpp"
#include "Angle.hpp"
#include "MotionMath.hpp"

namespace th20 {

extern const float native_speed_override_threshold;
extern const float native_one_56c8cc;

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
    case 618: {
        const auto selector = state.integer_argument(0);
        const float direction = state.float_argument(1);
        const float length = state.float_argument(2);
        auto selected = state.shared_shot(static_cast<std::uint32_t>(selector));
        auto* record = std::get<0>(std::move(selected));
        auto* metadata = std::get<1>(std::move(selected));
        (void)metadata;

        Vector3 offset;
        polar(offset, direction, length);
        record->vector_34.x = offset.x;
        record->vector_34.y = offset.y;
        return true;
    }
    case 620: {
        const auto selector = state.integer_argument(0);
        auto selected = state.shared_shot(static_cast<std::uint32_t>(selector));
        auto* record = std::get<0>(std::move(selected));
        auto* metadata = std::get<1>(std::move(selected));
        (void)metadata;

        const float x = state.float_argument(1);
        record->vector_40.x = x;
        const float y = state.float_argument(2);
        record->vector_40.y = y;
        if (x < native_speed_override_threshold) {
            record->vector_40.z = 0.0f;
        } else {
            record->vector_40.z = native_one_56c8cc;
        }
        return true;
    }
    default:
        return false;
    }
}

} // namespace th20
