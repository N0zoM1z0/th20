#include "EnemyStateBulletLaserCancelOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "Bullet.hpp"
#include "LaserParameters.hpp"

namespace th20 {

bool execute_enemy_bullet_laser_cancel_opcode(EnemyState& state, std::int32_t opcode) {
    if (opcode != 616)
        return false;

    // Native 616 reads the radius first, then resolves each live controller
    // and position independently. Keep the position arguments as references:
    // BulletController::cancel_near may run callbacks before the Laser pass.
    const float radius = state.float_argument(0);

    auto* bullets = state.context->bullet_controller();
    auto& bullet_center = state.position_ref();
    bullets->cancel_near(bullet_center, radius, 0);

    auto* lasers = state.context->laser_controller();
    auto& laser_center = state.position_ref();
    lasers->cancel_near(laser_center, radius, 0, 1);
    return true;
}

} // namespace th20
