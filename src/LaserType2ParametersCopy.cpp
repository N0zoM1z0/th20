#include "LaserParameters.hpp"

namespace th20 {

LaserType2Parameters::LaserType2Parameters(const LaserType2Parameters& other)
    : position(other.position), angle(other.angle), width(other.width), speed(other.speed),
      type(other.type), color(other.color), count(other.count),
      radial_offset(other.radial_offset), flags(other.flags), commands(other.commands),
      sound(other.sound), motion_sound(other.motion_sound), command_index(other.command_index),
      path(other.path), time(other.time), field_50(other.field_50),
      field_54(other.field_54), view_index(other.view_index) {}

} // namespace th20
