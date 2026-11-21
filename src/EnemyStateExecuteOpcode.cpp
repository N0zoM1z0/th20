// Partial natural-C++ source for the original 41,967-byte EnemyState opcode
// dispatcher at 0x0048C010. The opcode families below have independently
// reconstructed source fragments; the remaining inline cases are still open.
#include "EnemyState.hpp"
#include "Enemy.hpp"
#include "EclRuntime.hpp"
#include "EnemyStateMovementOpcode.hpp"
#include "EnemyStatePatternOpcode.hpp"
#include "EnemyStateControlOpcode.hpp"
#include "EnemyStateDynamicParameterOpcode.hpp"
#include "EnemyStateControllerManagementOpcode.hpp"
#include "EnemyStateTimeOpcode.hpp"
#include "EnemyStateCardOpcode.hpp"
#include "EnemyStateFrontendOpcode.hpp"
#include "EnemyStateAnimationSpawnOpcode.hpp"
#include "EnemyStateCardStartOpcode.hpp"
#include "EnemyStateControllerSetterOpcode.hpp"
#include "EnemyStateFogOpcode.hpp"
#include "EnemyStateLaserOpcode.hpp"
#include "EnemyStateMembershipOpcode.hpp"
#include "EnemyStateMeshOpcode.hpp"
#include "EnemyStatePhaseOpcode.hpp"
#include "EnemyStateQueueCopyOpcode.hpp"
#include "EnemyStateQueuedParametersOpcode.hpp"
#include "EnemyStateScriptPointerOpcode.hpp"
#include "EnemyStateSharedQueuedParametersOpcode.hpp"
#include "EnemyStateShotCommandOpcode.hpp"
#include "EnemyStateShotFireOpcode.hpp"

namespace th20 {

int EnemyState::execute_opcode() {
    // EclRuntime::tick enters this virtual owner only with a live current
    // runtime. The original packet, including any trailing payload, remains
    // borrowed; no instruction or operand copy is introduced here.
    const auto& instruction = *entity->current_runtime->current();
    const auto opcode = static_cast<std::int32_t>(instruction.opcode);

    // The 400-448 family is a contiguous 49-opcode movement boss. It remains
    // one natural C++ switch because the native root shares movement records,
    // interpolation lifetimes and combine_movements boundaries throughout.
    if (execute_enemy_movement_opcode(*this, opcode))
        return 0;
    if (execute_enemy_pattern_opcode(*this, opcode))
        return 0;
    if (execute_enemy_control_opcode(*this, opcode))
        return 0;
    if (execute_enemy_dynamic_parameter_opcode(*this, opcode))
        return 0;
    std::int32_t controller_result = 0;
    if (execute_enemy_controller_management_opcode(*this, opcode, controller_result))
        return controller_result;
    if (execute_enemy_time_opcode(*this, opcode))
        return 0;
    if (execute_enemy_card_opcode(*this, opcode))
        return 0;
    std::int32_t frontend_result = 0;
    if (execute_enemy_frontend_opcode(*this, opcode, frontend_result))
        return frontend_result;

    // Native switch case 0 dispatches the five direct spawn opcodes through
    // the recovered 653-byte EnemyState::spawn_from_opcode leaf. Cases 309,
    // 311 and 312 share the leaf behind a separate native guard not restored
    // at this boundary yet.
    switch (opcode) {
    case 300: case 301: case 304: case 305: case 321:
        return spawn_from_opcode();
    default:
        break;
    }

    // Native switch case 1 is the scalar field setter: opcode 302 consumes
    // integer argument zero and stores it in EnemyState::field_1c.
    if (opcode == 302) {
        field_1c = integer_argument(0);
        return 0;
    }

    // Native switch case 0x0d funnels this complete animation-setter family
    // through EnemyState::change_animation (the original 0x00496B90 owner).
    switch (opcode) {
    case 319: case 325: case 326: case 327: case 328: case 329: case 330:
    case 331: case 332: case 333: case 335: case 336: case 337:
        change_animation();
        return 0;
    default:
        break;
    }

    // Independently reconstructed inline case families. Each helper returns
    // false without reading operands when the opcode is outside its family.
    if (execute_enemy_phase_opcode(*this, instruction, opcode))
        return 0;
    if (execute_enemy_card_start_opcode(*this, instruction, opcode))
        return 0;
    if (execute_enemy_script_pointer_opcode(*this, instruction, opcode))
        return 0;
    if (execute_enemy_animation_spawn_opcode(*this, opcode))
        return 0;
    if (execute_enemy_controller_setter_opcode(*this, opcode))
        return 0;
    if (execute_enemy_fog_opcode(*this, opcode))
        return 0;
    if (execute_enemy_membership_opcode(*this, opcode))
        return 0;
    if (execute_enemy_mesh_opcode(*this, opcode))
        return 0;
    if (execute_enemy_queue_copy_opcode(*this, opcode))
        return 0;
    if (execute_enemy_shot_fire_opcode(*this, opcode))
        return 0;
    if (execute_enemy_shared_queued_parameters_opcode(*this, opcode))
        return 0;
    if (execute_enemy_shot_command_opcode(*this, opcode))
        return 0;
    if (execute_enemy_queued_parameters_opcode(*this, opcode))
        return 0;
    if (execute_enemy_laser_opcode(*this, opcode))
        return 0;

    // Native opcode 560 is special: defeat requests a same-tick script exit
    // (return 1 to EclRuntime::tick), not the ordinary instruction advance.
    if (opcode == 560 && entity->defeat())
        return 1;

    // This is a deliberately incomplete source frontier, not a claim that
    // unknown native cases are no-ops. Unrecovered inline families are next.
    return 0;
}

} // namespace th20
