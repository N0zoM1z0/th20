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

std::int32_t LaserLineInf::cancel_circle(const Vector3& center, float radius,
                                         std::int32_t mode, std::int32_t argument) {
    if (argument!=0 && field_6cc!=0) return 0;

    std::int32_t hit_count=0;
    std::int32_t segment_count=0;
    Vector3 position;
    Vector3 step;
    // The native body also materializes a separate copy of the base position.
    const Vector3 base_position_snapshot=this->position;
    float distance=native_screen_top_16_56cd90/native_screen_half_2_56c8d0;
    std::uint8_t segment_mask[512];
    std::memset(segment_mask,0,sizeof(segment_mask));

    step.z=0.0f;
    polar(step,angle,native_screen_top_16_56cd90/native_screen_half_2_56c8d0);
    position=this->position+step;
    position.z=0.0f;
    step+=step;

    radius*=radius;
    std::int32_t hit_index=0;
    while (native_screen_top_16_56cd90/native_screen_half_2_56c8d0+distance<=field_74) {
        float squared_distance=geometry::squared_distance_xy(center,position);
        // Keep the native forward miss edge as ordinary C++ control flow.
        // Under the locked MSVC /Od profile this also preserves the original
        // JBE/two-JMP layout without inline assembly or synthetic padding.
        if (squared_distance>radius) goto line_iteration_tail;
        {
            segment_mask[segment_count]=1;
            ++hit_count;
            ++context->bullet_controller()->cancel_counter;

            if (hit_index%4==0) {
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
            ++hit_index;
        }

line_iteration_tail:
        position+=step;
        distance+=native_screen_top_16_56cd90;
        ++segment_count;
    }

    if (hit_count!=0) {
        if (hit_count>=segment_count) {
            flags=(flags&0xfffffff9u)|2u;
            return hit_count;
        }
        cancel_segments(segment_mask,segment_count);
    }
    return hit_count;
}

} // namespace th20
