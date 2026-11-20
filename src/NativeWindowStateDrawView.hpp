#pragma once
#include <cstdint>
namespace th20 {
// Non-owning overlay for the original WindowState receiver at 0x005B6758.
// These four native 17B getter bodies are already physically shared with
// Context, FloatInterpolation and Player owner aliases; this view names the
// integer fields as they are consumed by the ScreenInf rectangle renderer.
struct NativeWindowStateDrawView {
    std::int32_t offset_x_41cad0();
    std::int32_t playfield_height_41caf0();
    std::int32_t playfield_width_424010();
    std::int32_t offset_y_421810();
};
}
