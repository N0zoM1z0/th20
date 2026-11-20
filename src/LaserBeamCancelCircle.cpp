#include "LaserBeamInf.hpp"
#include "AnimationFile.hpp"
#include "Bullet.hpp"
#include "Context.hpp"
#include "CollisionGeometry.hpp"
#include <cstdint>
#include <cstring>

namespace th20 {

std::int32_t LaserBeamInf::cancel_circle(const Vector3& center, float radius,
                                         std::int32_t mode, std::int32_t argument) {
    if (argument!=0 && field_6cc!=0) return 0;

    LaserBeamPathPoint* current_point;
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
        if (!(squared_distance>radius)) {
            segment_mask[point_index]=1;
            ++hit_count;
            ++context->bullet_controller()->cancel_counter;

            if (point_index%20==0) {
                context->bullet_controller()->animation_file()->spawn(
                    "bullet",static_cast<std::int32_t>(parameters.color*2u+0xd4u),
                    point,0.0f,-1,nullptr);
            }
        }

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
