#include "StageResourceDrawAdapters.hpp"

#include "AnimationRuntimeOwner.hpp"
#include "Graphics.hpp"
#include "NativeGraphicsModeAction.hpp"

namespace th20 {

std::int32_t __fastcall graphics_enable_fog(Graphics*);
std::int32_t __fastcall graphics_disable_fog(Graphics*);
std::int32_t __fastcall graphics_enable_depth_writes(Graphics*);
std::int32_t __fastcall graphics_disable_depth_writes(Graphics*);

void stage_resource_select_viewport(std::int32_t index) {
    reinterpret_cast<NativeGraphicsModeAction&>(process_graphics)
        .select_view_477520(index);
}

void stage_resource_set_clip(std::int32_t index) {
    reinterpret_cast<NativeGraphicsModeAction&>(process_graphics)
        .set_clip_41dce0(index);
}

void stage_resource_enable_fog() {
    graphics_enable_fog(&process_graphics);
}

void stage_resource_disable_fog() {
    graphics_disable_fog(&process_graphics);
}

void stage_resource_enable_depth_writes() {
    graphics_enable_depth_writes(&process_graphics);
}

void stage_resource_disable_depth_writes() {
    graphics_disable_depth_writes(&process_graphics);
}

const ViewportState& stage_resource_viewport(std::int32_t index) {
    return process_graphics.viewports[index];
}

} // namespace th20
