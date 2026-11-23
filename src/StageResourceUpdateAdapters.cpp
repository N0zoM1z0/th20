#include "StageResourceUpdateAdapters.hpp"
#include "Graphics.hpp"

namespace th20 {

void stage_vm_publish_camera(const ViewportState& camera) {
    process_graphics.viewports[3] = camera;
}

} // namespace th20
