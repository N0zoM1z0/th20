#include "LaserLineInf.hpp"
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

std::int32_t LaserLineInf::cancel_rectangle(
    const Vector3& rectangle_center, const Vector3& rectangle_size,
    float rectangle_direction, std::int32_t, std::int32_t argument) {
    if (argument!=0 && field_6cc!=0) return 0;

    struct SegmentCounts { std::int32_t segment_count; std::int32_t hit_count; } counters;
    counters.hit_count=0;
    counters.segment_count=0;
    Vector3 position;
    Vector3 step;
    const Vector3 base_position_snapshot=this->position;
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
            segment_mask[counters.segment_count]=1;
            ++counters.hit_count;
            ++context->bullet_controller()->cancel_counter;

            if (field_6e4<=0x11 || field_6e4==0x22 || field_6e4==0x26) {
                context->bullet_controller()->animation_file()->spawn(
                    "bullet",static_cast<std::int32_t>(parameters.color*2u+0xd4u),
                    position,0.0f,-1,nullptr);
            } else if (field_6e4<=0x1e) {
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
        ++counters.segment_count;
    }

    if (counters.hit_count!=0) {
        if (counters.hit_count>=counters.segment_count) {
            flags=(flags&0xfffffff9u)|2u;
            return counters.hit_count;
        }
        cancel_segments(segment_mask,counters.segment_count);
    }
    return counters.hit_count;
}

} // namespace th20
