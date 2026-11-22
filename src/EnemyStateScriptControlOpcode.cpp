#include "EnemyStateScriptControlOpcode.hpp"

#include "Context.hpp"
#include "Enemy.hpp"
#include "EnemyController.hpp"
#include "EnemyState.hpp"
#include "EclRuntime.hpp"

namespace th20 {

bool execute_enemy_script_control_opcode(EnemyState& state,
                                         const EclInstruction& instruction,
                                         std::int32_t opcode) {
    switch (opcode) {
    case 800: {
        auto* controller = state.context->enemy_controller();
        const auto identifier = state.integer_argument(0);
        auto* target = controller->find(static_cast<std::uint32_t>(identifier));
        if (target) {
            target->terminate_async();
            target->reset();
            const auto* script_name = reinterpret_cast<const char*>(&instruction) + 0x18;
            target->select(script_name);
        }
        return true;
    }
    case 801: {
        auto* controller = state.context->enemy_controller();
        const auto identifier = state.integer_argument(2);
        auto* target = controller->find(static_cast<std::uint32_t>(identifier));
        const auto x = target->position_ref().x;
        *state.float_argument_destination(0) = x;
        const auto y = target->position_ref().y;
        *state.float_argument_destination(1) = y;
        return true;
    }
    case 802: {
        const auto phase_index = state.integer_argument(0);
        for (std::int32_t player_index = 0; player_index < 3; ++player_index) {
            auto* controller = state.context->enemy_controller();
            auto* target = controller->selected(static_cast<std::uint32_t>(player_index));
            if (player_index == state.field_270 || !target)
                continue;
            if (target->state_value().phases[static_cast<std::uint32_t>(phase_index)].life < 0)
                continue;
            const auto* script = target->state_value().phases[
                static_cast<std::uint32_t>(phase_index)].script;
            if (script) {
                target->terminate_async();
                target->reset();
                target->select(target->state_value().phases[
                    static_cast<std::uint32_t>(phase_index)].script);
            }
        }
        return true;
    }
    default:
        return false;
    }
}

} // namespace th20
