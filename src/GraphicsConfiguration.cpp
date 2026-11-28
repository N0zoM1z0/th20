#include "Graphics.hpp"

namespace th20 {

// The physical 0x00415800 body folds with an identical getter credited
// elsewhere; window creation and the window procedure call it here.
std::int32_t Graphics::windowed() const {
    return presentation.Windowed;
}

std::uint32_t Graphics::reference_rasterizer_enabled() const {
    return configuration.flags.reference_rasterizer;
}

// Display modes 8 and 9 follow the desktop resolution.
std::int32_t Graphics::uses_desktop_display_mode() const {
    return configuration.saved_display_mode == 8 || configuration.saved_display_mode == 9;
}

std::uint32_t Graphics::fog_disabled() const {
    return configuration.flags.disable_fog;
}

std::uint32_t Graphics::direct_input_disabled() const {
    return configuration.flags.disable_direct_input;
}

std::uint32_t Graphics::vsync_disabled() const {
    return configuration.flags.disable_vsync;
}

std::uint32_t Graphics::text_detection_disabled() const {
    return configuration.flags.disable_text_detection;
}

} // namespace th20
