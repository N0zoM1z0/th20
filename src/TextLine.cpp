#include "TextLine.hpp"

namespace th20 {

TextLine::TextLine()
    : text{}, position(), color(0), blend(0), scale_x(0.0f), scale_y(0.0f),
      rotation(0.0f), field_120(0), field_124(0), font(0), shadow(0), layer(0),
      frames(0), align_x(1), align_y(1) {}

} // namespace th20
