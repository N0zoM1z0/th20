#include "Context.hpp"
#include "LaserLineInf.hpp"
#include "AnimationFile.hpp"
#include "BulletStyle.hpp"
#include "LaserRuntimeState.hpp"
#include "DiagnosticAllocator.hpp"
#include "MotionMath.hpp"
#include "SoundInf.hpp"
#include "AnimationAnchorAccess.hpp"

namespace th20 {

extern const float native_zero_56e0e8;
extern const float native_0_01;
extern const float native_one_56c8cc;
extern const float native_screen_half_2_56c8d0;

std::int32_t laser_infinite_animation_script_callback(Animation*,std::int32_t);
void __fastcall set_animation_flag_byte_01_one(Animation*);

std::int32_t LaserLineInf::initialize_laser(const void* input) {
    parameters=*static_cast<const LaserType0Parameters*>(input);
    state=2;
    field_24=0;
    field_6e4=static_cast<std::int32_t>(parameters.type);
    field_6e8=parameters.color;
    select_context(parameters.view_index);

    field_6d0=0xffd08080u;
    BulletStyle* style=bullet_style(field_6e4);
    const std::int32_t style_cancel_type=static_cast<std::int32_t>(style->cancel_type);
    if (style_cancel_type==6) {
        style=bullet_style(field_6e4);
        field_6d0=style->colors[field_6e8].words[4];
    }

    animation_0.reset();
    animation_0.set_field_5e0(&laser_infinite_animation_script_callback);
    animation_0.user_data=this;
    AnimationFile* file=context->laser_controller()->file;
    std::int32_t script=type_to_script(field_6e4);
    file->load_script(&animation_0,script);
    animation_0.interrupt(2);
    animation_0.update();
    set_animation_flag_byte_01_one(&animation_0);
    animation_0.base.flags.bytes_00.animation_mode=1;
    TH20_HORIZONTAL_ANCHOR(animation_0.base.flags)=0;
    TH20_VERTICAL_ANCHOR(animation_0.base.flags)=2;
    animation_0.base.flags.bits_0b.viewport_placement_mode=1;

    file=context->laser_controller()->file;
    script=static_cast<std::int32_t>(parameters.color)+0x3a;
    file->bind_animation(&animation_1,script);
    animation_1.interrupt(2);
    animation_1.update();
    set_animation_flag_byte_01_one(&animation_1);
    animation_1.base.flags.bytes_00.animation_mode=1;
    animation_1.base.flags.bits_0b.viewport_placement_mode=1;

    if (field_6e4<0x12 || field_6e4==0x26) {
        file->bind_animation(&animation_2,static_cast<std::int32_t>(parameters.color)+0x5d);
        set_animation_flag_byte_01_one(&animation_2);
    } else {
        file->bind_animation(&animation_2,static_cast<std::int32_t>(parameters.color)+0x55);
    }
    animation_2.base.flags.bits_0b.viewport_placement_mode=1;

    timer_6ac=30;
    timer_6bc=3;
    if (parameters.field_48>=0) process_sound.request_effect_at(parameters.field_48,0.0f);

    timer_38=0;
    timer_48=0;
    position=parameters.position;
    if (parameters.radial_offset!=native_zero_56e0e8) {
        Vector3 offset;
        polar(offset,parameters.angle,parameters.radial_offset);
        position+=offset;
    }
    field_74=parameters.field_14;
    speed=native_screen_half_2_56c8d0;
    field_7c=parameters.speed;
    angle=parameters.angle;
    if (field_74<parameters.length_limit || field_74==parameters.length_limit)
        field_80=native_zero_56e0e8;
    else
        field_80=native_0_01;
    polar(velocity,angle,field_7c);
    command_index=parameters.command_index;
    handle=parameters.field_48;
    field_84=native_one_56c8cc;
    field_88=native_one_56c8cc;
    runtime_state_6d8=process_allocator->allocate_object<LaserRuntimeState>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\laser.cpp:551 LaserHitDataInf");
    field_6dc=1;
    return 0;
}

} // namespace th20
