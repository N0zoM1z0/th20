#include "EnemyStateFrontendOpcode.hpp"
#include "EnemyState.hpp"
#include "HudGauge.hpp"
#include "SoundInf.hpp"

namespace th20 {

bool execute_enemy_frontend_opcode(
    EnemyState& state, std::int32_t opcode, std::int32_t& result) {
    switch (opcode) {
    case 516: {
        const float x = state.position_ref().x;
        const auto id = state.integer_argument(0);
        process_sound.request_effect_at(id, x);
        result = 0;
        break;
    }
    case 527: {
        const float numerator = state.float_argument(1);
        const auto value = state.integer_argument(2);
        const auto initial = static_cast<std::int32_t>(state.health.field_04);
        const float fraction = numerator / static_cast<float>(initial);
        const auto marker = state.integer_argument(0);
        const auto boss = state.field_270;
        current_front->set_boss_gauge(boss, marker, fraction, value);
        result = 0;
        break;
    }
    case 534: {
        const auto value = state.integer_argument(0);
        current_front->set_field_180(value);
        result = 0;
        break;
    }
    case 548:
        current_front->show_stage_title();
        result = 0;
        break;
    case 519:
        if (current_front->has_dialogue() && !current_front->dialogue_ready()) {
            result = -1;
            return true;
        }
        result = 0;
        break;
    default:
        return false;
    }
    return true;
}

} // namespace th20
