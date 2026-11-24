#pragma once

#include "Viewport.hpp"

#include <cstdint>

namespace th20 {

void stage_resource_select_viewport(std::int32_t index);
void stage_resource_set_clip(std::int32_t index);
void stage_resource_enable_fog();
void stage_resource_disable_fog();
void stage_resource_enable_depth_writes();
void stage_resource_disable_depth_writes();
const ViewportState& stage_resource_viewport(std::int32_t index);

} // namespace th20
