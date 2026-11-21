#include "EnemyStateControlOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"
#include "PlayerRecord.hpp"
#include "Session.hpp"

namespace th20 {

bool execute_enemy_control_opcode(EnemyState& state, std::int32_t opcode) {
    switch (opcode) {
    case 500:
        state.bounds_5c.x = state.float_argument(0);
        state.bounds_5c.y = state.float_argument(1);
        if (state.field_284 == 0) {
            state.field_284 = 1;
            auto* record = state.context->player_record();
            const auto delta = state.field_284;
            record->add_field_dc(delta);
        }
        break;
    case 501:
        state.bounds_64.x = state.float_argument(0);
        state.bounds_64.y = state.float_argument(1);
        break;
    case 504:
        state.flags.word_04 |= 2u;
        state.bounds_178.x = state.float_argument(0);
        state.bounds_178.y = state.float_argument(1);
        state.bounds_178.width = state.float_argument(2);
        state.bounds_178.height = state.float_argument(3);
        break;
    case 505:
        state.flags.word_04 &= ~2u;
        break;
    case 511: {
        state.health.set_health(static_cast<std::uint32_t>(state.integer_argument(0)));
        state.health.set_initial(state.health.get_health());
        state.health.set_phase(state.health.get_health());
        if (state.flags.word_04 & 0x80u)
            state.flags.word_04 |= 0x4000u;
        state.health.set_scaled_health(state.health.get_health());
        break;
    }
    case 566:
        state.health.set_health(static_cast<std::uint32_t>(state.integer_argument(0)));
        state.health.set_scaled_health(state.health.get_health());
        break;
    case 563:
        if (state.field_284 == 0) {
            state.field_284 = state.integer_argument(0);
            if (state.field_284 > 0) {
                auto* record = state.context->player_record();
                const auto delta = state.field_284;
                record->add_field_dc(delta);
            }
        } else if (state.field_284 == 1) {
            state.field_284 = state.integer_argument(0);
            auto* record = state.context->player_record();
            const auto delta = static_cast<std::int32_t>(
                static_cast<std::uint32_t>(state.field_284) - 1u);
            record->add_field_dc(delta);
        }
        break;
    case 564:
        if (state.field_284 != 0 && state.field_280 == session.clamped_field_1fc()) {
            auto* record = state.context->player_record();
            const auto delta = state.field_284;
            record->add_field_e0(delta);
            state.field_284 = 0;
        }
        break;
    case 512: {
        const auto index = state.integer_argument(0);
        auto* controller = state.context->enemy_controller();
        controller->set_field_84_bit_0(0);
        if (index < 0) {
            if (state.flags.word_04 & 0x80u) {
                controller = state.context->enemy_controller();
                const auto previous = state.field_270;
                controller->set_selected(static_cast<std::uint32_t>(previous), nullptr);
            }
            state.flags.word_04 &= ~0x80u;
        } else {
            state.flags.word_04 |= 0x80u;
            controller = state.context->enemy_controller();
            auto* enemy = state.entity;
            controller->set_selected(static_cast<std::uint32_t>(index), enemy);
            state.field_270 = index;
        }
        break;
    }
    case 513:
        state.timer_a8 = 0;
        break;
    case 515:
        state.timer_288 = state.integer_argument(0);
        break;
    case 535:
        state.timer_298 = state.integer_argument(0);
        break;
    case 526:
        state.field_274 = state.float_argument(0);
        state.field_274 *= state.field_274;
        break;
    case 557: {
        const auto value = static_cast<std::uint32_t>(state.integer_argument(0));
        state.flags.word_00 = (state.flags.word_00 & ~0x1000u) | ((value & 1u) << 12);
        break;
    }
    case 558:
        state.field_38 = state.float_argument(0);
        break;
    case 559:
        state.field_4c = state.float_argument(0);
        break;
    case 543: {
        const auto value = static_cast<std::uint32_t>(state.integer_argument(0));
        state.flags.word_04 = (state.flags.word_04 & ~0x8000u) | ((value & 1u) << 15);
        break;
    }
    case 544:
        state.field_30 = state.integer_argument(0);
        break;
    case 546:
        state.field_34 = state.integer_argument(0);
        break;
    case 547:
        state.field_264 = state.integer_argument(0);
        break;
    default:
        return false;
    }
    return true;
}

} // namespace th20
