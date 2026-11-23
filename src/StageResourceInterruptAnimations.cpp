#include "StageResource.hpp"
#include "NativeCardHudAnimationView.hpp"

namespace th20 {

void StageResourceOwner::interrupt_animations(std::int32_t event) {
    if (primitive_animations != nullptr) {
        Animation* animation = primitive_animations;
        for (std::int32_t index = 0; index < file->animation_count; ++index) {
            reinterpret_cast<NativeHudAnimationView*>(animation)->set_vm_event_477450(event);
            ++animation;
        }
    }
    for (std::int32_t index = 0; index < 8; ++index) {
        reinterpret_cast<NativeHudAnimationView*>(
            &script_state.animations[index])->set_vm_event_477450(event);
    }
}

} // namespace th20
