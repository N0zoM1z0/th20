#include "EnemyStateCardOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "Card.hpp"

namespace th20 {

bool execute_enemy_card_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 523:
        state.context->card()->finish_spell();
        state.health.set_scaled_enabled(0);
        break;
    case 536:
        state.context->card()->request_flag_3();
        break;
    case 537:
        state.context->card()->request_flag_4();
        break;
    case 561: {
        auto* receiver = state.context->card();
        const auto value = static_cast<std::uint32_t>(state.integer_argument(0));
        receiver->set_flag_8(value);
        break;
    }
    case 562: {
        auto* receiver = &state.health;
        const auto value = static_cast<std::uint32_t>(state.integer_argument(0));
        receiver->set_scaled_enabled(value);
        break;
    }
    default:
        return false;
    }
    return true;
}

} // namespace th20
