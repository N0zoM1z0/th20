#include "StageResource.hpp"

#include "AnimationRuntimeOwner.hpp"
#include "AnimationFile.hpp"
#include "StageResourceDrawAdapters.hpp"

#include <bit>
#include <cstdint>

namespace th20 {

void StageBackgroundScriptState::draw_inline_animations_for_layer(
    std::int32_t layer) {
    for (std::int32_t index = 0; index < 8; ++index) {
        Animation& animation = animations[index];
        if (animation.sprite_data() == nullptr ||
            std::bit_cast<std::int32_t>(fields_3294[index]) != layer)
            continue;

        stage_resource_set_clip(3);
        stage_resource_disable_fog();
        current_animation_pool->flush_draws();
        stage_resource_disable_depth_writes();
        if (animation.sprite_data() != nullptr)
            current_animation_pool->draw(&animation);
        stage_resource_enable_depth_writes();
        stage_resource_select_viewport(3);
    }
}


} // namespace th20
