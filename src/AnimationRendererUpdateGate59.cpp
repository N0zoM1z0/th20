// Original complete 59B Renderer animation-update GameController gate.
#include "GameController.hpp"
#include "NativeAnimationRendererUpdate.hpp"
namespace th20 {
extern GameController* current_game_controller;
int __cdecl animation_renderer_update_if_running_450880(AnimationPoolOwner* pool) {
    if (current_game_controller && current_game_controller->update_suppressed() &&
        current_game_controller->animation_frozen()) return 1;
    return animation_renderer_update_4497d0(pool);
}
}
