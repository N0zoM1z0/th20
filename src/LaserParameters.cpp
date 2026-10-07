#include "LaserParameters.hpp"

namespace th20 {

LaserType0Parameters::LaserType0Parameters()
    : angle(0), length(0), field_14(0), length_limit(0), width(0), speed(0),
      type(0), color(0), radial_offset(0), command_index(0), flags(0),
      field_48(0), field_4c(0), view_index(0) {}
LaserType0Parameters::~LaserType0Parameters() = default;
LaserType1Parameters::LaserType1Parameters()
    : angle(0), angular_velocity(0), length_limit(0), length(0), width(0),
      growth_speed(8), delay(0), grow_time(0), sustain_time(0), shrink_time(0),
      sound(0), field_44(0), handle(0), radial_offset(0), command_index(0),
      type(0), color(0), flags(0), view_index(0) {}
LaserType1Parameters::~LaserType1Parameters() = default;
LaserType2Parameters::LaserType2Parameters()
    : angle(0), width(0), speed(0), type(0), color(0), count(0), radial_offset(0),
      flags{}, sound(0), motion_sound(0), command_index(0), path(nullptr), time(0),
      field_50(0), field_54(0), view_index(0) {}
LaserType2Parameters::~LaserType2Parameters() = default;
LaserType3Parameters::LaserType3Parameters()
    : angle(0), field_1c(0), field_20(0), field_24(0), handle(0), field_2c(0),
      field_30(0), field_34(0), flags(0), view_index(0) {}
LaserType3Parameters::~LaserType3Parameters() = default;

} // namespace th20
