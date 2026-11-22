#include "EnemyStateBulletCancelOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "Bullet.hpp"
#include "Animation.hpp"

namespace th20 {

bool execute_enemy_bullet_cancel_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 712) return false;

    Vector3 dimensions;
    dimensions.x = state.float_argument(0);
    dimensions.y = state.float_argument(1);

    auto* animation = state.animations[0].handle.resolve();
    auto* controller = state.context->bullet_controller();
    const float direction = animation->rotation_z_value();
    auto& center = state.position_ref();
    (void)controller->cancel_in_rectangle(center, dimensions, direction, 1, 0);
    return true;
}

} // namespace th20
