#pragma once

#include <cstdint>

namespace th20 {

// Graphics frame-chain callbacks registered by register_graphics_chain.
// Callbacks without a body here are native functions still under review.
std::int32_t __cdecl graphics_update_4dc510(void* graphics);
std::int32_t __cdecl graphics_startup_4dd600(void* graphics);
std::int32_t __cdecl graphics_begin_frame_4dc5f0(void* graphics);
std::int32_t __cdecl graphics_draw_world_4dc8b0(void* graphics);
std::int32_t __cdecl graphics_draw_scene_4d9120(void* graphics);
std::int32_t __cdecl graphics_clear_scene_depth_4dd1c0(void* graphics);
std::int32_t __cdecl graphics_draw_overlay_4d8e90(void* graphics);
std::int32_t __cdecl graphics_clear_overlay_depth_4dd2e0(void* graphics);
std::int32_t __cdecl graphics_draw_front_4d8f80(void* graphics);
std::int32_t __cdecl graphics_select_backbuffer_4dd400(void* graphics);
std::int32_t __cdecl graphics_draw_frame_4d9040(void* graphics);
std::int32_t __cdecl graphics_clear_view_points_4dc7c0(void* graphics);
std::int32_t register_graphics_chain();
// Optional replacements for the scene and overlay passes; cleared at startup.
extern void (*graphics_scene_draw_hook)();
extern void (*graphics_overlay_draw_hook)();
std::int32_t load_version_data();

} // namespace th20
