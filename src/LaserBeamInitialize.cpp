#include "LaserBeamInf.hpp"

namespace th20 {

void __fastcall set_animation_flag_byte_01_one(Animation* animation);
extern const float native_one_56c8cc;

std::int32_t LaserBeamInf::initialize_laser(const void* input) {
    parameters=*static_cast<const LaserType3Parameters*>(input);
    state=3;
    field_24=3;
    position=parameters.position;
    select_context(parameters.view_index);
    field_74=parameters.field_20;
    angle=parameters.angle;
    field_6e8=parameters.field_2c;
    handle=parameters.handle;
    for (std::int32_t index=0;index<0x200;++index)
        field_d30[index]=field_74;
    speed=native_one_56c8cc;
    field_d2c=0.0f;
    animation_0.reset();
    set_animation_flag_byte_01_one(&animation_0);
    return 0;
}

} // namespace th20
