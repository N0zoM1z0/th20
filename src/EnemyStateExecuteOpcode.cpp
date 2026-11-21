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
