// Original 244B Animation corner-mode dispatch used by the Animation VM's
// screen-coordinate opcode. This receiver is the Animation object itself;
// the two projection leaf calls use the renderer owner as their unused ECX
// receiver and pass the Animation plus four real Vector3 corner records.
#include "AnimationCornerProjectionOwner.hpp"
#include "AnimationRuntimeOwner.hpp"
namespace th20 {

static_assert(offsetof(AnimationBase, flags)==0x498);
static_assert(sizeof(Vector3)==12);

void NativeAnimationCornerProjectionDispatchView::project_corners(Vector3* corners) {
    switch (reinterpret_cast<Animation*>(this)->base.flags.bytes_00.animation_mode) {
    case 0:
        reinterpret_cast<NativeAnimationCornerProjector*>(current_animation_pool)->project_corners_43eb40(
            reinterpret_cast<Animation*>(this),corners,corners+1,corners+2,corners+3);
        break;
    case 1:
        reinterpret_cast<NativeAnimationCornerProjector*>(current_animation_pool)->project_rotated_corners_43ef20(
            reinterpret_cast<Animation*>(this),corners,corners+1,corners+2,corners+3);
        break;
    case 2:
    case 3:
        reinterpret_cast<NativeAnimationCornerProjector*>(current_animation_pool)->project_corners_43eb40(
            reinterpret_cast<Animation*>(this),corners,corners+1,corners+2,corners+3);
        break;
    }
}

} // namespace th20
