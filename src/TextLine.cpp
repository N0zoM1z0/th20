#include "TextLine.hpp"
#include "EclDiagnostic.hpp"

namespace th20 {

TextLine::TextLine() noexcept
    : text{}, position(), color(0), blend(0), scale_x(0.0f), scale_y(0.0f),
      rotation(0.0f), field_120(0), field_124(0), font(0), shadow(0), layer(0),
      frames(0), align_x(1), align_y(1) {}

AsciiInf* current_ascii;

AsciiInf::AsciiInf() noexcept
    : line_count(0), color(0xFFFFFFFFu), shadow_color(0xFF000000u),
      field_1a1c8(0xFFFFFFFFu), scale_x(1.0f), scale_y(1.0f),
      field_1a1d4(0), field_1a1d8(0), shadow(0), font(0), field_1a1e4(2),
      field_1a1e8(0), layer(0), frames(0), align_x(1), align_y(1), blend(0),
      rotation(0.0f), font_width(9), field_1a240(0), animation_file(nullptr),
      draw_node_1a250(nullptr), draw_node_1a254(nullptr),
      draw_node_1a258(nullptr), draw_node_1a25c(nullptr), text_buffer{} {
    ecl_diagnostic_hint("initialize AsciiInf\n");
    current_ascii = this;
    color = 0xFFFFFFFFu;
    shadow_color = 0xFF000000u;
    scale_x = 1.0f;
    scale_y = 1.0f;
    field_1a1d8 = 0;
}

AnimationFile* AsciiInf::text_animation_file() {
    return shared_text_animation_file;
}

} // namespace th20
