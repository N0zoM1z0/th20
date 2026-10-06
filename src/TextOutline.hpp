#pragma once

namespace th20 {

// REF-022: the raster producer consumes this scalar and resets it to one.
extern float next_text_outline_scale;
void set_next_text_outline_scale(float value);

} // namespace th20
