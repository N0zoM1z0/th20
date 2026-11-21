#include "EnemyStateTimeOpcode.hpp"
#include "EnemyState.hpp"
#include "Enemy.hpp"
#include "ClockScalar.hpp"
#include "Session.hpp"
#include "Context.hpp"
#include "LaserParameters.hpp"

namespace th20 {

bool execute_enemy_time_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 539:
        state.context->laser_controller()->reset_all_lasers();
        break;
    case 538: {
        const auto value = static_cast<std::uint32_t>(state.integer_argument(0));
        state.flags.word_04 = (state.flags.word_04 & ~0x800u) | ((value & 1u) << 11);
        break;
    }
    case 540: {
        const auto value = static_cast<std::uint32_t>(state.integer_argument(0));
        state.flags.word_04 = (state.flags.word_04 & ~0x1000u) | ((value & 1u) << 12);
        state.field_54 = state.integer_argument(1);
        state.field_58 = state.field_28;
        state.flags.word_04 &= ~0x2000u;
        state.flags.word_00 &= ~1u;
        break;
    }
    case 541:
        default_timer_clock.set(state.float_argument(0));
        break;
    case 542: {
        const auto first = state.integer_argument(0);
        const auto second = state.integer_argument(1);
        const auto third = state.integer_argument(2);
        const auto fourth = state.integer_argument(3);
        auto* receiver = state.entity;
        const float amount = session.mode() == 0 ? static_cast<float>(first)
            : session.mode() == 1 ? static_cast<float>(second)
            : session.mode() == 2 ? static_cast<float>(third)
            : static_cast<float>(fourth);
        receiver->subtract_time(amount);
        break;
    }
    case 574:
        if (!(state.flags.word_08 & 0x40u))
            state.entity->subtract_time(1.0f);
        break;
    default:
        return false;
    }
    return true;
}

} // namespace th20
