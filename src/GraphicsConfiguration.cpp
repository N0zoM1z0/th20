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

} // namespace th20
