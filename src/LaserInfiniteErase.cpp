#include "LaserInfiniteInf.hpp"
#include "AnimationFile.hpp"
#include "Bullet.hpp"
#include "BulletScreenBounds.hpp"
#include "Context.hpp"
#include "MotionMath.hpp"

namespace th20 {

extern const float native_screen_top_16_56cd90;
extern const float native_screen_half_2_56c8d0;

std::int32_t LaserInfiniteInf::erase(std::int32_t, std::int32_t argument) {
    if (argument!=0 && field_6cc!=0) return 0;

    std::int32_t count=0;
    Vector3 position;
    Vector3 step;
    float distance=native_screen_top_16_56cd90/native_screen_half_2_56c8d0;

    polar(step,angle,native_screen_top_16_56cd90/native_screen_half_2_56c8d0);
    step.z=0.0f;
    position=this->position+step;
    step+=step;

    while (native_screen_top_16_56cd90/native_screen_half_2_56c8d0+distance<field_74) {
        ++count;
        if (!bullet_position_outside_screen(position,native_screen_top_16_56cd90,
                                             native_screen_top_16_56cd90)) {
            if (field_6e4<=0x11 || field_6e4==0x22 || field_6e4==0x26) {
                context->bullet_controller()->animation_file()->spawn(
                    "bullet",static_cast<std::int32_t>(parameters.color*2u+0xd4u),
                    position,0.0f,-1,nullptr);
            } else if (field_6e4<=0x1f || field_6e4==0x1b) {
                context->bullet_controller()->animation_file()->spawn(
                    "bullet",static_cast<std::int32_t>(parameters.color*2u+0x104u),
                    position,0.0f,-1,nullptr);
            } else if (field_6e4<=0x21) {
                context->bullet_controller()->animation_file()->spawn(
                    "bullet",static_cast<std::int32_t>(parameters.color*2u+0x11cu),
                    position,0.0f,-1,nullptr);
            }
        }
        position+=step;
        distance+=native_screen_top_16_56cd90;
    }

    state=1;
    return count;
}

} // namespace th20
