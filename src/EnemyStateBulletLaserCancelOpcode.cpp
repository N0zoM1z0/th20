#include "EnemyStateBulletLaserCancelOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "Bullet.hpp"
#include "LaserParameters.hpp"

namespace th20 {

bool execute_enemy_bullet_laser_cancel_opcode(EnemyState& state, std::int32_t opcode) {
    const bool limited = opcode == 627 || opcode == 628;
    if (opcode != 616 && !limited)
        return false;

    // All three native branches read the radius first, then resolve each live
    // controller and position independently. The 627/628 pair use the real
    // 401B capped Bullet cancellation Boss with the original 99,999 limit;
    // 616 uses the uncapped radial Bullet boss.
    const float radius = state.float_argument(0);

    auto* bullets = state.context->bullet_controller();
    auto& bullet_center = state.position_ref();
    if (limited)
        bullets->cancel_near_limited(bullet_center, radius, 0, 0x1869f, 0);
    else
        bullets->cancel_near(bullet_center, radius, 0);

    auto* lasers = state.context->laser_controller();
    auto& laser_center = state.position_ref();
    lasers->cancel_near(laser_center, radius, 0, 1);
    return true;
}

} // namespace th20
