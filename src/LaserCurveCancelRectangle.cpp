#include "LaserCurveInf.hpp"
#include "AnimationFile.hpp"
#include "Bullet.hpp"
#include "Context.hpp"
#include "DiagnosticAllocator.hpp"
#include "CollisionGeometry.hpp"
#include <cstdint>
#include <cstring>

namespace th20 {

extern const float native_screen_half_2_56c8d0;

std::int32_t LaserCurveInf::cancel_rectangle(
    const Vector3& rectangle_center, const Vector3& rectangle_size,
    float rectangle_direction, std::int32_t, std::int32_t argument) {
    if (argument!=0 && field_6cc!=0) return 0;

    std::int32_t hit_count=0;
    std::int32_t point_index=0;
    // These three native vector results are materialized even though the
    // later point predicate consumes the original rectangle arguments.
    Vector3 lower_corner;
    Vector3 half_size;
    Vector3 point;
    const Vector3 base_position_snapshot=this->position;

    std::uint8_t* segment_mask=static_cast<std::uint8_t*>(
        process_allocator->allocate_bytes(static_cast<std::int32_t>(parameters.count),
            "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\laser.cpp:3617 u_char"));
    if (segment_mask==nullptr) return 0;

    std::memset(segment_mask,0,parameters.count);

    half_size=rectangle_size/native_screen_half_2_56c8d0;
    lower_corner=rectangle_center-half_size;
    half_size=rectangle_center+half_size;

    LaserCurvePathPoint* current_point=point_data;
    point_index=0;
    for (;point_index<static_cast<std::int32_t>(parameters.count);++point_index) {
        point=current_point->position;
        // The original /Od body keeps the miss edge as a forward goto. This
        // preserves the native two-jump control-flow shape without assembly.
        if (!geometry::rotated_rectangle_point(
                rectangle_center.x,rectangle_center.y,
                rectangle_size.x,rectangle_size.y,rectangle_direction,
                point.x,point.y)) {
            goto curve_rectangle_iteration_tail;
        }

        segment_mask[point_index]=1;
        ++hit_count;
        ++context->bullet_controller()->cancel_counter;

        if (point_index%20==0) {
            context->bullet_controller()->animation_file()->spawn(
                "bullet",static_cast<std::int32_t>(parameters.color*2u+0xd4u),
                point,0.0f,-1,nullptr);
        }

curve_rectangle_iteration_tail:
        ++current_point;
    }

    if (hit_count>=static_cast<std::int32_t>(parameters.count)) {
        flags=(flags&0xfffffff9u)|2u;
    } else if (hit_count>0) {
        cancel_segments(segment_mask,point_index);
    }

    if (segment_mask!=nullptr) {
        process_allocator->release_bytes(segment_mask);
        segment_mask=nullptr;
    }
    return hit_count;
}

} // namespace th20
