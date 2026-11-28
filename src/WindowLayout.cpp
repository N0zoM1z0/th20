#include "WindowState.hpp"

#include "Graphics.hpp"

namespace th20 {

std::int32_t WindowState::nominal_width_value() { return nominal_width; }
std::int32_t WindowState::nominal_height_value() { return nominal_height; }
std::int32_t WindowState::offset_x_value() { return offset_x; }
std::int32_t WindowState::offset_y_value() { return offset_y; }

void WindowState::set_nominal_width(std::int32_t value) { nominal_width = value; }
void WindowState::set_nominal_height(std::int32_t value) { nominal_height = value; }
void WindowState::set_playfield_width(std::int32_t value) { playfield_width = value; }
void WindowState::set_playfield_height(std::int32_t value) { playfield_height = value; }
void WindowState::set_offset_x(std::int32_t value) { offset_x = value; }
void WindowState::set_offset_y(std::int32_t value) { offset_y = value; }

void WindowState::set_retained_28(std::int32_t index, std::int32_t value) {
    retained_28[index] = value;
}

void WindowState::set_retained_30(std::int32_t index, std::int32_t value) {
    retained_30[index] = value;
}

void WindowState::set_mesh_offset_x(std::int32_t index, std::int32_t value) {
    mesh_offset_x[index] = value;
}

void WindowState::set_mesh_offset_y(std::int32_t index, std::int32_t value) {
    mesh_offset_y[index] = value;
}

void WindowState::set_retained_48(std::int32_t index, std::int32_t value) {
    retained_48[index] = value;
}

void WindowState::set_retained_50(std::int32_t index, std::int32_t value) {
    retained_50[index] = value;
}

void WindowState::set_field_0058(std::int32_t value) { field_0058 = value; }
void WindowState::set_field_005c(std::int32_t value) { field_005c = value; }
void WindowState::set_field_0060(std::int32_t value) { field_0060 = value; }
void WindowState::set_field_0064(std::int32_t value) { field_0064 = value; }
void WindowState::set_display_mode(std::int32_t value) { display_mode_value = value; }
std::uint32_t WindowState::reset_delay_value() { return reset_delay; }
void WindowState::add_reset_delay(std::int32_t delta) { reset_delay += delta; }

// Derives the client size, render scale and 640x480 scaled frame from the
// display mode, then places the 384x448 playfield inside the scaled frame.
// Modes 8 and 9 follow the desktop size; 9 stretches to the desktop aspect
// and 8 snaps to half-frame steps. The fixed modes select their own client
// size. The method reads the global scaling fields while it writes the
// placement through its receiver; the original callers pass window_state.
void WindowState::compute_layout(std::int32_t choose_scale) {
    if (window_state.display_mode() == 9 || window_state.display_mode() == 8) {
        window_state.client_width = window_state.display_width;
        window_state.client_height = window_state.display_height;
        if (choose_scale) {
            if (window_state.client_width >= 2560 && window_state.client_height >= 1920) {
                window_state.scale = 2.0f;
                process_graphics.configuration.scale_choice = 4;
            } else if (window_state.client_width >= 1920 && window_state.client_height >= 1440) {
                window_state.scale = 2.0f;
                process_graphics.configuration.scale_choice = 3;
            } else if (window_state.client_width >= 1280 && window_state.client_height >= 960) {
                window_state.scale = 2.0f;
                process_graphics.configuration.scale_choice = 2;
            } else if (window_state.client_width >= 960 && window_state.client_height >= 720) {
                window_state.scale = 1.5f;
                process_graphics.configuration.scale_choice = 1;
            } else {
                process_graphics.configuration.scale_choice = 0;
                window_state.scale = 1.0f;
            }
        }
        window_state.scaled_width = static_cast<std::int32_t>(640.0f * window_state.scale);
        window_state.scaled_height = static_cast<std::int32_t>(480.0f * window_state.scale);
        if (window_state.display_mode() == 9) {
            if (static_cast<float>(window_state.client_width) / static_cast<float>(window_state.client_height) >=
                static_cast<float>(window_state.scaled_width) / static_cast<float>(window_state.scaled_height)) {
                float aspect = static_cast<float>(window_state.client_width) / static_cast<float>(window_state.client_height);
                window_state.viewport_width = static_cast<std::int32_t>(static_cast<float>(window_state.scaled_height) * aspect);
                window_state.viewport_height = window_state.scaled_height;
            } else {
                float aspect = static_cast<float>(window_state.client_height) / static_cast<float>(window_state.client_width);
                window_state.viewport_width = window_state.scaled_width;
                window_state.viewport_height = static_cast<std::int32_t>(static_cast<float>(window_state.scaled_width) * aspect);
            }
        } else {
            if (static_cast<float>(window_state.client_width) / static_cast<float>(window_state.client_height) >=
                static_cast<float>(window_state.scaled_width) / static_cast<float>(window_state.scaled_height)) {
                float aspect = static_cast<float>(window_state.client_width) / static_cast<float>(window_state.client_height);
                std::int32_t height = window_state.scaled_height;
                while (window_state.scaled_height / 2 + height < window_state.client_height) {
                    height = window_state.scaled_height / 2 + height;
                }
                float ratio = static_cast<float>(window_state.client_height) / static_cast<float>(height);
                window_state.viewport_height = static_cast<std::int32_t>(static_cast<float>(window_state.scaled_height) * ratio);
                window_state.viewport_width = static_cast<std::int32_t>(static_cast<float>(window_state.viewport_height) * aspect);
            } else {
                float aspect = static_cast<float>(window_state.client_height) / static_cast<float>(window_state.client_width);
                std::int32_t width = window_state.scaled_width;
                while (window_state.scaled_width / 2 + width < window_state.client_width) {
                    width = window_state.scaled_width / 2 + width;
                }
                float ratio = static_cast<float>(window_state.client_width) / static_cast<float>(width);
                window_state.viewport_width = static_cast<std::int32_t>(static_cast<float>(window_state.scaled_height) * ratio);
                window_state.viewport_height = static_cast<std::int32_t>(static_cast<float>(window_state.viewport_height) * aspect);
            }
        }
    } else if (window_state.display_mode() == 7) {
        window_state.scale = 2.0f;
        window_state.client_width = 2560;
        window_state.client_height = 1920;
    } else if (window_state.display_mode() == 6) {
        window_state.scale = 2.0f;
        window_state.client_width = 1920;
        window_state.client_height = 1440;
    } else if (window_state.display_mode() == 2 || window_state.display_mode() == 5) {
        window_state.scale = 2.0f;
        window_state.client_width = 1280;
        window_state.client_height = 960;
    } else if (window_state.display_mode() == 1 || window_state.display_mode() == 4) {
        window_state.scale = 1.5f;
        window_state.client_width = 960;
        window_state.client_height = 720;
    } else {
        window_state.scale = 1.0f;
        window_state.client_width = 640;
        window_state.client_height = 480;
    }
    window_state.scaled_width = static_cast<std::int32_t>(640.0f * window_state.scale);
    window_state.scaled_height = static_cast<std::int32_t>(480.0f * window_state.scale);
    set_nominal_width(640);
    set_nominal_height(480);
    set_playfield_width(384);
    set_playfield_height(448);
    set_offset_x((window_state.scaled_width - nominal_width_value()) / 2);
    set_offset_y((window_state.scaled_height - nominal_height_value()) / 2);
    set_retained_28(0, offset_x_value() + 32);
    set_retained_28(1, offset_x_value() + 32);
    set_retained_30(0, offset_x_value() + 16);
    set_retained_30(1, offset_x_value() + 16);
    set_retained_48(0, static_cast<std::int32_t>(32.0f * window_state.scale));
    set_retained_48(1, static_cast<std::int32_t>(32.0f * window_state.scale));
    set_retained_50(0, static_cast<std::int32_t>(16.0f * window_state.scale));
    set_retained_50(1, static_cast<std::int32_t>(16.0f * window_state.scale));
    set_mesh_offset_x(0, offset_x_value() + static_cast<std::int32_t>((640.0f - 384.0f) / 2.0f + 384.0f / 2.0f));
    set_mesh_offset_x(1, offset_x_value() + static_cast<std::int32_t>((640.0f - 384.0f) / 2.0f + 384.0f / 2.0f));
    set_mesh_offset_y(0, offset_y_value() + 16);
    set_mesh_offset_y(1, offset_y_value() + 16);
    set_field_0058(window_state.scaled_width / 2);
    set_field_005c((window_state.scaled_height - 448) / 2);
    set_field_0060(window_state.scaled_width / 2);
    set_field_0064(static_cast<std::int32_t>(16.0f * window_state.scale));
}

} // namespace th20
