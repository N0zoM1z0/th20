#include "Graphics.hpp"
#include <cstring>
namespace th20 {
TransformMatrix::TransformMatrix() {}
ViewportState::ViewportState()
    : field_of_view(0), field_58(0), field_5c(0), viewport{}, field_f8(0),
      offset_x(0), offset_y(0), adjusted_viewport{} {}
GraphicsFlags::GraphicsFlags()
    : bit0(0), bit1(0), bit2(0), bit3(0), bit4(0), bits5_6(0), bit7(1),
      bit8(0), bit9(0), bit10(0), bit11(1), bit12(0), bit13(0) {}
Graphics::Graphics() noexcept
    : object_00(nullptr), direct3d(nullptr), device(nullptr), window_rectangle{},
      input_device_caps{}, window_handle(nullptr), viewport{},
      presentation{}, saved_presentation{}, alternate_presentation{}, adapter_mode{},
      resource_19c(nullptr), resource_1a0(nullptr), resource_1a4(nullptr), field_1a8(0),
      surface_sprite_0(nullptr), surface_sprite_1(nullptr), surface_sprite_2(nullptr),
      surface_sprite_3(nullptr), surface_sprite_4(nullptr), field_1c0(0),
      current_viewport(nullptr), field_b04(0), field_b08(-2), field_b0c(-2), field_b10(-2),
      field_b14(0), field_b18(0), field_b1c(0), field_b20(0), field_b24(0), field_b28(0),
      reset_countdown(0), field_b30(0), disable_vsync(0), graphics_ready(0), render_counter(0),
      surface_animation(nullptr), field_b44(0), startup_seed(0), field_b50(0),
      snapshot_pixels(nullptr), snapshot_pitch(0), snapshot_path{},
      field_db4(0), render_value(0), field_dbc(0), dynamic_buffer(nullptr),
      startup_scene(nullptr), field_dcc(0), field_dd0(0), field_dd4(0),
      update_duration(0), clear_color(0) {}
}
