#include "StageResource.hpp"
#include "StageResourceUpdateAdapters.hpp"
#include "Animation.hpp"
#include "Vector3.hpp"

namespace th20 {
void normalize_vector3_45cf10(Vector3& output, const Vector3& input);

std::int32_t __fastcall StageResourceOwner::update() {
    if ((state_flags & 8u) != 0 ||
        ((state_flags & 4u) != 0 && fade_timer.current >= 60))
        return 1;

    auto& background = script_state;
    background.camera.points[0] = {};
    background.camera.points[1] = {};
    background.camera.points[2] = {};
    background.camera.final_vector = {};
    const Vector3 camera_target = background.camera.vector_0c +
                                  background.camera.vector_48;
    normalize_vector3_45cf10(background.camera.vector_24, camera_target);
    background.overlay_color = 0x00808080u;

    if ((state_flags & 4u) == 0 || fade_timer.current < 30) {
        update_objects();
        background.execute_script();
    }

    stage_vm_publish_camera(background.camera);
    for (auto& animation : background.animations)
        animation.update();
    background.update_meshes();
    ++frame_count;
    return 1;
}

} // namespace th20
