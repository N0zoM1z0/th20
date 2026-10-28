#include "EnemyController.hpp"
#include "Context.hpp"
#include "Bullet.hpp"
#include "ItemResourceOwners.hpp"
#include "StageResource.hpp"

namespace th20 {

// Native full 0x004AAE10 selector. The stage-owner getter itself remains a
// separate unresolved 20-byte dependency; no Stage layout is assumed here.
AnimationFile* EnemyController::animation_file(std::int32_t index) {
    AnimationFile* selected;
    if (index == 7) {
        selected = process_stage_resource->animation_file();
    } else {
        AnimationFile* contextual;
        if (index == 0) {
            contextual = context->bullet_controller()->animation_file();
        } else {
            AnimationFile* from_context_or_array;
            if (index == 1)
                from_context_or_array = context->effect_info()->animation_file(0);
            else
                from_context_or_array = animation_files.at(static_cast<std::uint32_t>(index));
            contextual = from_context_or_array;
        }
        selected = contextual;
    }
    return selected;
}

} // namespace th20
