// Partial natural-C++ source for the original 41,967-byte EnemyState opcode
// dispatcher at 0x0048C010. The opcode families below have independently
// reconstructed source fragments; the remaining inline cases are still open.
#include "EnemyState.hpp"
#include "Enemy.hpp"
#include "Context.hpp"
#include "EnemyController.hpp"
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

int execute_enemy_animation_secondary_opcode(EnemyState& state);
int execute_enemy_animation_state_opcode(EnemyState& state);
int execute_enemy_animation_effect_flag2_opcode(EnemyState& state);
int execute_enemy_animation_effect_spawn_opcode(EnemyState& state);
int execute_enemy_animation_effect_flag2_handle_opcode(EnemyState& state);
int execute_enemy_animation_effect_rotate_opcode(EnemyState& state);
int execute_enemy_animation_spawn_mapped(EnemyState& state);
int execute_enemy_animation_spawn_primary_from_field(EnemyState& state);
int execute_enemy_animation_link_offset_opcode(EnemyState& state);
int execute_enemy_animation_link_parent_opcode(EnemyState& state);
int execute_enemy_animation_state_selectors_opcode(EnemyState& state);
int execute_enemy_selected_position_opcode(EnemyState& state);
int execute_enemy_animation_flags_opcode(EnemyState& state, std::int32_t opcode);
int execute_enemy_has_selected_identifier_opcode(EnemyState& state);
int execute_enemy_effect_position_request_opcode(EnemyState& state);
int execute_enemy_effect_position_spawn_opcode(EnemyState& state);
int execute_enemy_effect_spawn_and_update_opcode(EnemyState& state);
int execute_enemy_set_found_flag_bit_9_opcode(EnemyState& state);
void __fastcall set_enemy_state_flag_04_bit_9(Enemy* enemy);

int EnemyState::execute_opcode() {
    // EclRuntime::tick enters this virtual owner only with a live current
    // runtime. The original packet, including any trailing payload, remains
    // borrowed; no instruction or operand copy is introduced here.
    const auto& instruction = *entity->current_runtime->current();
    const auto opcode = static_cast<std::int32_t>(instruction.opcode);

    // The 400-448 family is a contiguous 49-opcode movement boss. It remains
    // one natural C++ switch because the native root shares movement records,
    // interpolation lifetimes and combine_movements boundaries throughout.
    std::int32_t movement_opcode = opcode;
    switch (opcode) {
    // These low-numbered and 400-series aliases share native switch bodies.
    case 57: case 61: movement_opcode = 402; break;
    case 13: case 56: movement_opcode = 403; break;
    case 53: case 108: case 180: movement_opcode = 430; break;
    case 49: case 77: movement_opcode = 411; break;
    case 65: movement_opcode = 414; break;
    case 69: case 236: movement_opcode = 415; break;
    case 89: movement_opcode = 419; break;
    case 133: movement_opcode = 410; break;
    case 76: case 93: case 120: movement_opcode = 426; break;
    case 97: movement_opcode = 432; break;
    case 101: case 149: movement_opcode = 433; break;
    case 153: movement_opcode = 435; break;
    case 157: case 212: movement_opcode = 442; break;
    case 105: movement_opcode = 443; break;
    case 109: case 113: movement_opcode = 446; break;
    default: break;
    }
    if (execute_enemy_movement_opcode(*this, movement_opcode))
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
    // the recovered 653-byte EnemyState::spawn_from_opcode leaf.
    switch (opcode) {
    case 300: case 301: case 304: case 305: case 321:
        return spawn_from_opcode();
    // Native case 6 gates the same spawn leaf on the selected Enemy slot.
    case 309: case 310: case 311: case 312:
        if (!context->enemy_controller()->selected(0))
            return spawn_from_opcode();
        return 0;
    // Native case 2 is the complete animation-link creation operation.
    case 303:
        return spawn_animation();
    // Native case 3 (306) creates the secondary animation and publishes its
    // state only for link zero; case 7 (313) uses field_28 + 5 as its script.
    case 306:
        return execute_enemy_animation_secondary_opcode(*this);
    case 313:
        return execute_enemy_animation_state_opcode(*this);
    // EffectInfo-published animation handles: 307/315 use flag-2 positioned
    // spawn, 314 uses positioned flag-zero spawn, and 308 uses null position.
    case 307:
        return execute_enemy_animation_effect_flag2_opcode(*this);
    case 308:
        return execute_enemy_animation_effect_flag2_handle_opcode(*this);
    case 314:
        return execute_enemy_animation_effect_spawn_opcode(*this);
    case 315:
        return execute_enemy_animation_effect_rotate_opcode(*this);
    // Native case 10 aliases five opcodes to the field_28-based animation
    // selector; its negative and nonnegative selector branches differ.
    case 48: case 173: case 177: case 201: case 316:
        return execute_enemy_animation_spawn_mapped(*this);
    // Native case 11 interrupts the selected link; case 12 replaces link zero.
    case 181: case 193: case 317: {
        const std::int32_t index = integer_argument(0);
        auto& link = animations[index];
        const std::int32_t event = integer_argument(1);
        link.handle.interrupt(event);
        return 0;
    }
    case 41: case 318:
        return execute_enemy_animation_spawn_primary_from_field(*this);
    case 320:
        return execute_enemy_animation_link_offset_opcode(*this);
    case 322:
        return execute_enemy_animation_link_parent_opcode(*this);
    case 323:
        return execute_enemy_animation_state_selectors_opcode(*this);
    case 17: case 21: case 25: case 45: case 260:
        return execute_enemy_selected_position_opcode(*this);
    case 341: case 342: case 343:
        return execute_enemy_animation_flags_opcode(*this, opcode);
    case 44: case 73: case 344:
        return execute_enemy_has_selected_identifier_opcode(*this);
    case 334:
        return execute_enemy_effect_position_request_opcode(*this);
    case 338:
        return execute_enemy_effect_position_spawn_opcode(*this);
    case 339:
        return execute_enemy_effect_spawn_and_update_opcode(*this);
    case 340:
        return execute_enemy_set_found_flag_bit_9_opcode(*this);
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
