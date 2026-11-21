#include "EnemyStateControllerManagementOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"

namespace th20 {

bool execute_enemy_controller_management_opcode(
    EnemyState& state, std::int32_t opcode, std::int32_t& result) {
    switch (opcode) {
    case 520:
        if (state.context->enemy_controller()->selected(0)) {
            result = -1;
            return true;
        }
        if (state.context->enemy_controller()->selected(1)) {
            result = -1;
            return true;
        }
        if (state.context->enemy_controller()->selected(2)) {
            result = -1;
            return true;
        }
        result = 0;
        break;
    case 525:
        state.context->enemy_controller()->clear();
        result = 0;
        break;
    case 545: {
        auto* receiver = state.context->enemy_controller();
        const auto value = state.integer_argument(0);
        receiver->clear_matching(value);
        result = 0;
        break;
    }
    case 565:
        state.context->enemy_controller()->clear_variant_565();
        result = 0;
        break;
    case 573:
        state.context->enemy_controller()->clear_variant_573();
        result = 0;
        break;
    default:
        return false;
    }
    return true;
}

} // namespace th20
