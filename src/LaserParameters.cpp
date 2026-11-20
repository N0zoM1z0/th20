#include "LaserParameters.hpp"
#include "Session.hpp"
#include "EclDiagnostic.hpp"

namespace th20 {

LaserType0Parameters::LaserType0Parameters() noexcept
    : angle(0), length(0), field_14(0), length_limit(0), width(0), speed(0),
      type(0), color(0), radial_offset(0), command_index(0), flags(0),
      field_48(0), field_4c(0), view_index(0) {}
LaserType0Parameters::~LaserType0Parameters() = default;
LaserType0Parameters& LaserType0Parameters::operator=(const LaserType0Parameters& other) {
    position=other.position;
    angle=other.angle;
    length=other.length;
    field_14=other.field_14;
    length_limit=other.length_limit;
    width=other.width;
    speed=other.speed;
    type=other.type;
    color=other.color;
    radial_offset=other.radial_offset;
    command_index=other.command_index;
    flags_alias_34=other.flags_alias_34;
    flags=other.flags;
    commands=other.commands;
    field_48=other.field_48;
    field_4c=other.field_4c;
    view_index=other.view_index;
    return *this;
}
LaserType1Parameters::LaserType1Parameters() noexcept
    : angle(0), angular_velocity(0), length_limit(0), length(0), width(0),
      growth_speed(8), delay(0), grow_time(0), sustain_time(0), shrink_time(0),
      sound(0), field_44(0), handle(0), radial_offset(0), command_index(0),
      type(0), color(0), flags(0), view_index(0) {}
LaserType1Parameters::~LaserType1Parameters() = default;
LaserType1Parameters& LaserType1Parameters::operator=(const LaserType1Parameters& other) {
    position=other.position;
    velocity=other.velocity;
    angle=other.angle;
    angular_velocity=other.angular_velocity;
    length_limit=other.length_limit;
    length=other.length;
    width=other.width;
    growth_speed=other.growth_speed;
    delay=other.delay;
    grow_time=other.grow_time;
    sustain_time=other.sustain_time;
    shrink_time=other.shrink_time;
    sound=other.sound;
    field_44=other.field_44;
    handle=other.handle;
    radial_offset=other.radial_offset;
    command_index=other.command_index;
    type=other.type;
    color=other.color;
    flags_alias_5c=other.flags_alias_5c;
    flags=other.flags;
    commands=other.commands;
    view_index=other.view_index;
    return *this;
}
LaserType2Parameters::LaserType2Parameters() noexcept
    : angle(0), width(0), speed(0), type(0), color(0), count(0), radial_offset(0),
      flags{}, sound(0), motion_sound(0), command_index(0), path(nullptr), time(0),
      field_50(0), field_54(0), view_index(0) {}
LaserType2Parameters::~LaserType2Parameters() = default;
LaserType3Parameters::LaserType3Parameters() noexcept
    : angle(0), field_1c(0), field_20(0), field_24(0), handle(0), field_2c(0),
      field_30(0), field_34(0), flags(0), view_index(0) {}
LaserType3Parameters::~LaserType3Parameters() = default;
LaserType3Parameters& LaserType3Parameters::operator=(const LaserType3Parameters& other) {
    position=other.position;
    vector_0c=other.vector_0c;
    angle=other.angle;
    field_1c=other.field_1c;
    field_20=other.field_20;
    field_24=other.field_24;
    handle=other.handle;
    field_2c=other.field_2c;
    field_30=other.field_30;
    field_34=other.field_34;
    flags_alias_38=other.flags_alias_38;
    flags=other.flags;
    commands=other.commands;
    view_index=other.view_index;
    return *this;
}

LaserController::LaserController() noexcept
    : count(0), next_handle(0x10000), file(nullptr), field_4c(0),
      view_index(0), context(nullptr) {
    ecl_diagnostic_hint("initialize LaserInf\n");
}

void LaserController::select_context(std::int32_t index) {
    view_index = index;
    context = &session.context(view_index);
}

LaserController* laser_controller(std::int32_t index) {
    return session.context(index).laser_controller();
}

std::int32_t LaserController::reset_all_lasers() {
    [[maybe_unused]] std::int32_t count = 0;
    IntrusiveList<Laser>* const list = &active;
    {
        IntrusiveIterator<Laser> it = list->begin();
        IntrusiveIterator<Laser>* const last = list->end();
        for (; it.differs(last); it.advance()) {
            IntrusiveLink<Laser>* link = it.get();
            link->node_access()->timer_6ac = 0;
            link->node_access()->field_6cc = 0;
            link->node_access()->erase(1, 0);
        }
    }
    return 0;
}

} // namespace th20
