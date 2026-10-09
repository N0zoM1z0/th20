#pragma once
#include "Configuration.hpp"
#include "Viewport.hpp"
#include "GraphicsApi.hpp"
#include "AnimationHandle.hpp"
#include "TaskInfo.hpp"
#include "Worker.hpp"
namespace th20 {
struct AnimationFile;
struct GraphicsFlags {
    std::uint32_t bit0:1, bit1:1, bit2:1, bit3:1, bit4:1, bits5_6:2;
    std::uint32_t bit7:1, bit8:1, bit9:1, bit10:1, bit11:1, bit12:1, bit13:1, retained:18;
    GraphicsFlags();
};
// Complete native owner: two matrices, three presentation records, six
// viewports and two actual Workers. Unknown scalar roles retain offsets.
struct Graphics {
    void* object_00;
    graphics_api::Direct3D* direct3d;
    graphics_api::Device* device;
    graphics_api::WindowRect window_rectangle;
    graphics_api::InputDeviceCaps input_device_caps;
    graphics_api::WindowHandle window_handle;
    TransformMatrix view, projection;
    NativeViewport viewport;
    graphics_api::Presentation presentation, saved_presentation, alternate_presentation;
    graphics_api::DisplayMode adapter_mode;
    graphics_api::Resource* resource_19c;
    graphics_api::Resource* resource_1a0;
    graphics_api::Resource* resource_1a4;
    std::uint32_t field_1a8;
    Animation* surface_sprite_0;
    Animation* surface_sprite_1;
    Animation* surface_sprite_2;
    Animation* surface_sprite_3;
    Animation* surface_sprite_4;
    std::uint32_t field_1c0;
    AnimationHandle handle_1c4;
    Configuration configuration;
    ViewportState viewports[6];
    ViewportState* current_viewport;
    std::uint32_t field_b04;
    std::int32_t field_b08, field_b0c, field_b10;
    std::uint32_t field_b14, field_b18, field_b1c, field_b20, field_b24, field_b28;
    std::uint32_t reset_countdown, field_b30, disable_vsync, graphics_ready, render_counter;
    AnimationFile* surface_animation;
    std::uint32_t field_b44;
    GraphicsFlags flags;
    std::uint32_t startup_seed, field_b50;
    graphics_api::DeviceCaps device_caps;
    std::uint8_t* snapshot_pixels;
    std::int32_t snapshot_pitch;
    char snapshot_path[260];
    Worker worker_0, worker_1;
    std::uint32_t field_db0, field_db4, render_value, field_dbc, version_data_size;
    void* dynamic_buffer;
    TaskInfo* startup_scene;
    std::uint32_t field_dcc, field_dd0, field_dd4;
    double update_duration;
    std::uint32_t clear_color;
    Graphics() noexcept;
    ~Graphics();
    AnimationHandle create_grid_strip(std::int32_t rows,std::int32_t script);
    AnimationHandle create_surface_strip(std::int32_t rows,std::int32_t script);
    std::int32_t uses_preloaded_music() const;
};
// Production global definition/startup and destruction remain open.
extern Graphics process_graphics;
#if defined(_M_IX86)
static_assert(sizeof(Graphics)==0xde8);
static_assert(offsetof(Graphics,configuration)==0x1c8);
static_assert(offsetof(Graphics,viewports)==0x278);
static_assert(offsetof(Graphics,device_caps)==0xb54);
static_assert(offsetof(Graphics,worker_0)==0xd90);
static_assert(offsetof(Graphics,update_duration)==0xdd8);
#endif
}
