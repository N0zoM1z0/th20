#include "Context.hpp"
#include "LaserInfiniteInf.hpp"
#include "AnimationFile.hpp"
#include "BulletStyle.hpp"
#include "LaserRuntimeState.hpp"
#include "DiagnosticAllocator.hpp"
#include "MotionMath.hpp"
#include "SoundInf.hpp"

namespace th20 {

extern const float native_zero_56e0e8;
extern const float native_0_01;
extern const float native_screen_half_2_56c8d0;

std::int32_t laser_infinite_animation_script_callback(Animation*,std::int32_t);
void __fastcall set_animation_flag_byte_01_one(Animation*);

std::int32_t LaserInfiniteInf::initialize_laser(const void* input) {
    parameters=*static_cast<const LaserType1Parameters*>(input);
    state=3;
    field_24=1;
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
    Animation* animation=&animation_0;
    animation->set_field_5e0(&laser_infinite_animation_script_callback);
    animation_0.user_data=this;
    AnimationFile* file=context->laser_controller()->file;
    std::int32_t script=type_to_script(field_6e4);
    file->load_script(&animation_0,script);
    animation=&animation_0;
    animation->interrupt(2);
    animation_0.update();
    set_animation_flag_byte_01_one(&animation_0);
    animation_0.base.flags.bytes_00.animation_mode=1;
    animation_0.base.flags.word_10=0;
    animation_0.base.flags.word_14=2;
    animation_0.base.flags.bits_0b.viewport_placement_mode=1;

    file=context->laser_controller()->file;
    script=static_cast<std::int32_t>(parameters.color)+0x3a;
    file->bind_animation(&animation_1,script);
    animation=&animation_1;
    animation->interrupt(2);
    animation_1.update();
    set_animation_flag_byte_01_one(&animation_1);
    animation_1.base.flags.bytes_00.animation_mode=1;
    animation_1.base.flags.bits_0b.viewport_placement_mode=1;

    if (parameters.sound>=0) process_sound.request_effect_at(parameters.sound,0.0f);

    position=parameters.position;
    if (parameters.radial_offset!=native_zero_56e0e8) {
        Vector3 offset;
        polar(offset,parameters.angle,parameters.radial_offset);
        position+=offset;
    }
    field_74=parameters.length;
    speed=native_screen_half_2_56c8d0;
    field_7c=parameters.growth_speed;
    angle=parameters.angle;
    if (field_74<parameters.length_limit || field_74==parameters.length_limit)
        field_80=native_zero_56e0e8;
    else
        field_80=native_0_01;
    polar(velocity,angle,field_7c);
    handle=parameters.handle;
    command_index=parameters.command_index;
    timer_38=0;
    field_76c=0;
    runtime_state_6d8=process_allocator->allocate_object<LaserRuntimeState>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\laser.cpp:1730 LaserHitDataInf");
    field_6dc=1;
    if (field_6e4==0x26) flags|=0x80;
    return 0;
}

} // namespace th20
