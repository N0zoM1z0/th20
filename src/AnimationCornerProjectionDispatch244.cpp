#include "AnimationCornerProjectionOwner.hpp"
#include "AnimationRuntimeOwner.hpp"

namespace th20 {

using AnimationCornerArray = Vector3[4];

static_assert(offsetof(AnimationBase, flags) == 0x498);
static_assert(sizeof(Vector3) == 12);

void Animation::project_corners(Vector3* corners) {
    switch (base.flags.bytes_00.animation_mode) {
    case 0:
        reinterpret_cast<NativeAnimationCornerProjector*>(current_animation_pool)->project_corners_43eb40(
            this,
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[0],
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[1],
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[2],
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[3]);
        break;
    case 1:
        reinterpret_cast<NativeAnimationCornerProjector*>(current_animation_pool)->project_rotated_corners_43ef20(
            this,
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[0],
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[1],
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[2],
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[3]);
        break;
    case 2:
    case 3:
        reinterpret_cast<NativeAnimationCornerProjector*>(current_animation_pool)->project_corners_43eb40(
            this,
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[0],
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[1],
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[2],
            &(*reinterpret_cast<AnimationCornerArray*>(corners))[3]);
        break;
    }
}

} // namespace th20
