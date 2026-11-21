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
