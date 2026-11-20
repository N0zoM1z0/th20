#include "LaserInfiniteInf.hpp"
#include "AnimationFile.hpp"
#include "Bullet.hpp"
#include "Context.hpp"
#include "CollisionGeometry.hpp"
#include "MotionMath.hpp"
#include <cstdint>
#include <cstring>

namespace th20 {

extern const float native_screen_top_16_56cd90;
extern const float native_screen_half_2_56c8d0;

std::int32_t LaserInfiniteInf::cancel_rectangle(
    const Vector3& rectangle_center, const Vector3& rectangle_size,
    float rectangle_direction, std::int32_t, std::int32_t argument) {
    if (argument!=0 && field_6cc!=0) return 0;

    std::int32_t hit_count=0;
    std::int32_t segment_count=0;
    Vector3 position;
    Vector3 step;
    float distance=native_screen_top_16_56cd90/native_screen_half_2_56c8d0;
    std::uint8_t segment_mask[512];
    std::memset(segment_mask,0,sizeof(segment_mask));

    polar(step,angle,native_screen_top_16_56cd90/native_screen_half_2_56c8d0);
    step.z=0.0f;
    position=this->position+step;
    position.z=0.0f;
    step+=step;

    while (native_screen_top_16_56cd90/native_screen_half_2_56c8d0+distance<=field_74) {
        if (geometry::rectangle_rectangle(
                rectangle_center.x,rectangle_center.y,
                rectangle_size.x,rectangle_size.y,rectangle_direction,
                position.x,position.y,step.x,step.y,angle)) {
            segment_mask[segment_count]=1;
            ++hit_count;
            ++context->bullet_controller()->cancel_counter;

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
        ++segment_count;
    }

    if (hit_count!=0) cancel_segments(segment_mask,segment_count);
    return hit_count;
}

} // namespace th20
