#include "EnemyStateDialogueOpcode.hpp"
#include "EnemyState.hpp"
#include "Context.hpp"
#include "HudGauge.hpp"
#include "FrontInfDialogueCommand626.hpp"
#include "DialogueText.hpp"
#include "Bullet.hpp"
#include "LaserParameters.hpp"
#include "EnemyController.hpp"

namespace th20 {

int execute_enemy_dialogue_opcode(EnemyState& state) {
    const std::int32_t command = state.integer_argument(0);
    current_front->set_dialogue_command_4b9740(command);
    bullet_controller(0)->cancel_all(0);
    laser_controller(0)->cancel_all(0, 0);
    enemy_controller(0)->clear();
    return 0;
}

} // namespace th20
