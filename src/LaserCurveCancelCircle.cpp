#include "LaserCurveInf.hpp"
#include "AnimationFile.hpp"
#include "Bullet.hpp"
#include "Context.hpp"
#include "CollisionGeometry.hpp"
#include <cstdint>
#include <cstring>

namespace th20 {

std::int32_t LaserCurveInf::cancel_circle(const Vector3& center, float radius,
                                         std::int32_t mode, std::int32_t argument) {
    if (argument!=0 && field_6cc!=0) return 0;

    LaserCurvePathPoint* current_point;
    std::int32_t hit_count=0;
    std::int32_t point_index=0;
    Vector3 point;
    const Vector3 base_position_snapshot=this->position;
    std::uint8_t segment_mask[512];
    std::memset(segment_mask,0,sizeof(segment_mask));

    radius*=radius;
    current_point=point_data;
    point_index=0;
    for (;point_index<static_cast<std::int32_t>(parameters.count);++point_index) {
        point=current_point->position;

        const float squared_distance=geometry::squared_distance_xy(center,point);
        // Preserve the native unordered-aware hit edge with a forward miss path.
        // A forward miss edge preserves the native JBE/two-JMP layout
        // while retaining the unordered-aware COMISS hit semantics.
        if (squared_distance>radius) goto curve_iteration_tail;
        {
            segment_mask[point_index]=1;
            ++hit_count;
            ++context->bullet_controller()->cancel_counter;

            if (point_index%20==0) {
                context->bullet_controller()->animation_file()->spawn(
                    "bullet",static_cast<std::int32_t>(parameters.color*2u+0xd4u),
                    point,0.0f,-1,nullptr);
            }
        }

curve_iteration_tail:
        ++current_point;
    }

    if (hit_count>=static_cast<std::int32_t>(parameters.count)) {
        flags=(flags&0xfffffff9u)|2u;
    } else if (hit_count>0) {
        cancel_segments(segment_mask,point_index);
    }
    return hit_count;
}

} // namespace th20
