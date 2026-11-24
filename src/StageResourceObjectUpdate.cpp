#include "StageResource.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Angle.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

std::int32_t StageResourceOwner::update_objects() {
    auto** object_table = static_cast<StageResourceObjectRecord**>(objects);
    for (std::int32_t object_index = 0; object_index < file->object_count;
         ++object_index) {
        StageResourceObjectRecord& object = *object_table[object_index];
        if (object.flags & 1u) {
            std::int32_t active_animations = 0;
            auto* primitive = reinterpret_cast<StageResourcePrimitiveHeader*>(
                reinterpret_cast<std::byte*>(&object) + sizeof(object));
            while (primitive->type >= 0) {
                Animation* animation = primitive_animations + primitive->animation_index;
                current_animation_pool->update_animation(animation);
                if (animation->is_active())
                    ++active_animations;
                primitive = reinterpret_cast<StageResourcePrimitiveHeader*>(
                    reinterpret_cast<std::byte*>(primitive) + primitive->size);
            }
            if (active_animations == 0)
                object.flags &= 0xfeu;
        }
        if (object.parameters.rotation_y_velocity != 0.0f && (state_flags & 16u) == 0) {
            object.parameters.rotation_y = normalize_angle(
                object.parameters.rotation_y + object.parameters.rotation_y_velocity);
        }
    }
    return 0;
}

} // namespace th20
