#include "EnemyStateControllerSetterOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"
#include "Bullet.hpp"

namespace th20 {

bool execute_enemy_controller_setter_opcode(EnemyState& state,
                                             std::int32_t opcode) {
    switch (opcode) {
    case 553: {
        // Native caches the live EnemyController before evaluating operand 0.
        auto* owner = state.context->enemy_controller();
        const auto value = static_cast<std::uint32_t>(state.integer_argument(0));
        owner->set_field_88(value);
        return true;
    }
    case 554: {
        // Native caches the live BulletController, then reads Y before X.
        auto* owner = state.context->bullet_controller();
        const float y = state.float_argument(1);
        const float x = state.float_argument(0);
        owner->set_vector_4c(x, y);
        return true;
    }
    default:
        return false;
    }
}

} // namespace th20
