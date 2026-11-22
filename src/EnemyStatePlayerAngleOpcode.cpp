#include "EnemyStatePlayerAngleOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "Player.hpp"
#include "ScalarMath.hpp"

namespace th20 {

bool execute_enemy_player_angle_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 617)
        return false;

    // Native 617 obtains Player/position before each operand read. Keep the
    // first reference alive across float_argument(1), then re-read Context
    // for Y so a Context retarget during the first VM read affects only Y.
    auto& first_position = state.context->player()->position_ref();
    const float target_x = state.float_argument(1);
    const float delta_x = first_position.x - target_x;

    auto& second_position = state.context->player()->position_ref();
    const float target_y = state.float_argument(2);
    const float delta_y = second_position.y - target_y;

    const float angle = scalar_math::arctangent(delta_y, delta_x);
    float* destination = state.float_argument_destination(0);
    *destination = angle;
    return true;
}

} // namespace th20
