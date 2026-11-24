// Original 244B Animation corner-mode dispatch used by the Animation VM's
// screen-coordinate opcode. This receiver is the Animation object itself;
// the two projection leaf calls use the renderer owner as their unused ECX
// receiver and pass the Animation plus four real Vector3 corner records.
#include "AnimationCornerProjectionOwner.hpp"
#include "AnimationRuntimeOwner.hpp"
namespace th20 {

static_assert(offsetof(AnimationBase, flags)==0x498);
static_assert(sizeof(Vector3)==12);

void Animation::project_corners(Vector3* corners) {
    // The mode and byte stride have disjoint lifetimes. Reuse one native-width
    // scratch word after dispatch rather than adding a second local object.
    union DispatchScratch {
        std::uint32_t mode;
        std::uint32_t corner_stride;
    } dispatch;
    dispatch.mode = base.flags.bytes_00.animation_mode;
    switch (dispatch.mode) {
    case 0:
        dispatch.corner_stride = sizeof(Vector3);
        reinterpret_cast<NativeAnimationCornerProjector*>(current_animation_pool)->project_corners_43eb40(
            this,
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 0),
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 1),
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 2),
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 3));
        break;
    case 1:
        dispatch.corner_stride = sizeof(Vector3);
        reinterpret_cast<NativeAnimationCornerProjector*>(current_animation_pool)->project_rotated_corners_43ef20(
            this,
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 0),
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 1),
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 2),
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 3));
        break;
    case 2:
    case 3:
        dispatch.corner_stride = sizeof(Vector3);
        reinterpret_cast<NativeAnimationCornerProjector*>(current_animation_pool)->project_corners_43eb40(
            this,
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 0),
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 1),
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 2),
            reinterpret_cast<Vector3*>(reinterpret_cast<std::uintptr_t>(corners) + dispatch.corner_stride * 3));
        break;
    }
}

} // namespace th20
