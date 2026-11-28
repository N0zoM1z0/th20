#include "Graphics.hpp"
#include "SoundInf.hpp"
#include "WindowState.hpp"

namespace th20 {

void Graphics::reset_view_selection() {
    field_b08 = -2;
    field_b0c = 0;
}

// Both branches request the same "dummy" track; preloaded music uses the
// fade command 4 and streamed music command 3.
std::int32_t Graphics::stop_background_music() {
    if (process_graphics.uses_preloaded_music()) {
        process_sound.enqueue(4, 0, "dummy");
    } else {
        process_sound.enqueue(3, 0, "dummy");
    }
    return 0;
}

// Every viewport keeps its pixel rectangle as unsigned D3D fields and its
// clip bounds as floats; the original repeats this conversion inline.
#define TH20_VIEWPORT_BOUNDS(state)                                                        \
    (state)->bounds_11c.x = static_cast<float>((state)->adjusted_viewport.x);              \
    (state)->bounds_11c.y = static_cast<float>((state)->adjusted_viewport.y);              \
    (state)->bounds_124.x = static_cast<float>((state)->adjusted_viewport.x) +             \
                            static_cast<float>((state)->adjusted_viewport.width);          \
    (state)->bounds_124.y = static_cast<float>((state)->adjusted_viewport.y) +             \
                            static_cast<float>((state)->adjusted_viewport.height)

void Graphics::initialize_viewports() {
    ViewportState* state = &viewports[2];
    state->vector_00 = Vector3(0.0f, 0.0f, 0.0f);
    state->vector_0c = Vector3(0.0f, 0.0f, 0.0f);
    state->vector_18 = Vector3(0.0f, 1.0f, 0.0f);
    state->field_of_view = 3.14159274f / 6.0f;
    state->viewport.x = 0;
    state->viewport.y = 0;
    state->viewport.width = window_state.scaled_width;
    state->viewport.height = window_state.scaled_height;
    state->viewport.min_z = 0.0f;
    state->viewport.max_z = 1.0f;
    state->field_f8 = 2;
    state->vector_3c = Vector3(0.0f, 0.0f, 0.0f);
    state->vector_48 = Vector3(0.0f, 0.0f, 0.0f);
    state->field_58 = window_state.scaled_width;
    state->field_5c = window_state.scaled_height;
    state->offset_x = 0;
    state->offset_y = 0;
    state->adjusted_viewport = state->viewport;
    state->adjusted_viewport.x = state->offset_x;
    state->adjusted_viewport.y = state->offset_y;
    state->adjusted_viewport.width = window_state.scaled_width;
    state->adjusted_viewport.height = window_state.scaled_height;
    TH20_VIEWPORT_BOUNDS(state);
    recompute_current_4da1f0(state, &state->viewport);

    state = &viewports[0];
    *state = viewports[2];
    state->field_f8 = 0;
    state->offset_x = 0;
    state->offset_y = 0;
    state->viewport.x = window_state.scaled_width / 2 - static_cast<std::int32_t>((384.0f + 32.0f) / 2.0f);
    state->viewport.y = window_state.scaled_height / 2 - static_cast<std::int32_t>((448.0f + 32.0f) / 2.0f);
    state->viewport.width = static_cast<std::int32_t>(384.0f + 32.0f);
    state->viewport.height = static_cast<std::int32_t>(448.0f + 32.0f);
    state->adjusted_viewport = state->viewport;
    TH20_VIEWPORT_BOUNDS(state);
    recompute_current_4da1f0(state, &state->viewport);

    state = &viewports[1];
    *state = viewports[0];
    state->field_f8 = 1;
    state->offset_x = 0;
    state->offset_y = 0;
    state->viewport.x = static_cast<std::int32_t>((640.0f - 384.0f) / 2.0f * window_state.scale);
    state->viewport.y = static_cast<std::int32_t>(16.0f * window_state.scale);
    state->viewport.width = static_cast<std::int32_t>(384.0f * window_state.scale);
    state->viewport.height = static_cast<std::int32_t>(448.0f * window_state.scale);
    state->adjusted_viewport = state->viewport;
    TH20_VIEWPORT_BOUNDS(state);
    recompute_current_4da1f0(state, &state->viewport);

    state = &viewports[4];
    *state = viewports[0];
    state->field_f8 = 1;
    state->offset_x = viewports[2].offset_x;
    state->offset_y = viewports[2].offset_y;
    state->viewport.x = state->offset_x;
    state->viewport.y = state->offset_y;
    state->viewport.width = window_state.scaled_width;
    state->viewport.height = window_state.scaled_height;
    state->adjusted_viewport = state->viewport;
    TH20_VIEWPORT_BOUNDS(state);
    recompute_current_4da1f0(state, &state->viewport);

    state = &viewports[5];
    *state = viewports[2];
    state->field_f8 = 1;
    state->offset_x = viewports[2].offset_x +
                      static_cast<std::int32_t>((640.0f - 384.0f) / 2.0f * window_state.scale) +
                      static_cast<std::int32_t>(384.0f * window_state.scale) / 2;
    state->offset_y = viewports[2].offset_y + static_cast<std::int32_t>(16.0f * window_state.scale);
    state->viewport.x = viewports[2].offset_x + static_cast<std::int32_t>((640.0f - 384.0f) / 2.0f * window_state.scale);
    state->viewport.y = viewports[2].offset_y + static_cast<std::int32_t>(16.0f * window_state.scale);
    state->viewport.width = viewports[2].offset_x + static_cast<std::int32_t>(384.0f * window_state.scale);
    state->viewport.height = viewports[2].offset_y + static_cast<std::int32_t>(448.0f * window_state.scale);
    state->adjusted_viewport = state->viewport;
    TH20_VIEWPORT_BOUNDS(state);
    recompute_current_4da1f0(state, &state->viewport);

    state = &viewports[3];
    *state = viewports[0];
    state->field_f8 = 3;
    state->offset_x = 0;
    state->offset_y = 0;
    state->viewport.x = static_cast<std::int32_t>((static_cast<float>(window_state.scaled_width) - (384.0f + 32.0f)) / 2.0f);
    state->viewport.y = static_cast<std::int32_t>((static_cast<float>(window_state.scaled_height) - (448.0f + 32.0f)) / 2.0f);
    state->viewport.width = static_cast<std::int32_t>(384.0f + 32.0f);
    state->viewport.height = static_cast<std::int32_t>(448.0f + 32.0f);
    state->adjusted_viewport = state->viewport;
    TH20_VIEWPORT_BOUNDS(state);
    recompute_current_4da1f0(state, &state->viewport);
}

void Graphics::set_view_offset(std::int32_t x, std::int32_t y) {
    ViewportState* state = &viewports[2];
    state->offset_x = x;
    state->offset_y = y;
    state->adjusted_viewport = state->viewport;
    state->adjusted_viewport.x = state->offset_x;
    state->adjusted_viewport.y = state->offset_y;
    state->adjusted_viewport.width = window_state.scaled_width;
    state->adjusted_viewport.height = window_state.scaled_height;
    TH20_VIEWPORT_BOUNDS(state);

    state = &viewports[5];
    state->offset_x = static_cast<std::int32_t>(32.0f * window_state.scale) + x +
                      static_cast<std::int32_t>(384.0f * window_state.scale) / 2;
    state->offset_y = static_cast<std::int32_t>(16.0f * window_state.scale) + y;
    state->viewport.x = static_cast<std::int32_t>(32.0f * window_state.scale) + x;
    state->viewport.y = static_cast<std::int32_t>(16.0f * window_state.scale) + y;
    state->viewport.width = static_cast<std::int32_t>(384.0f * window_state.scale);
    state->viewport.height = static_cast<std::int32_t>(448.0f * window_state.scale);
    state->adjusted_viewport = state->viewport;
    TH20_VIEWPORT_BOUNDS(state);
    recompute_current_4da1f0(state, &state->viewport);
}

} // namespace th20
