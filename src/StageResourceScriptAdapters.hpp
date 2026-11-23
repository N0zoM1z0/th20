#pragma once
#include "StageResource.hpp"

namespace th20 {
void stage_vm_assign_animation(StageBackgroundScriptState& state,
                               std::int32_t index, std::int32_t script);
void stage_vm_stop_animation(Animation& animation);
void stage_vm_reset_meshes(StageBackgroundScriptState& state);
void stage_vm_interrupt_animations(StageResourceOwner& owner, std::uint32_t event);
void stage_vm_set_clear_color(std::uint32_t color);
void stage_vm_set_primary_rotation_flag(std::uint32_t value);
}
