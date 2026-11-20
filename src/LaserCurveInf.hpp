#pragma once

#include "Angle.hpp"
#include "Animation.hpp"
#include "LaserParameters.hpp"

namespace th20 {

// The independently constructed 64-byte LaserCurveInf tail state at +0x1330.
// Its native constructor initializes the five leading words, two Vector3
// values, one Angle and the three trailing scalar lanes.
struct LaserCurvePathState {
    std::uint32_t field_00, field_04;
    float field_08, field_0c;
    std::uint32_t field_10;
    Vector3 vector_14;
    Vector3 vector_20;
    Angle angle_2c;
    float field_30, field_34, field_38;
    std::uint32_t field_3c;

    LaserCurvePathState() noexcept;
};
static_assert(sizeof(LaserCurvePathState)==0x40);
static_assert(offsetof(LaserCurvePathState,vector_14)==0x14);
static_assert(offsetof(LaserCurvePathState,vector_20)==0x20);
static_assert(offsetof(LaserCurvePathState,angle_2c)==0x2c);

// The native Curve path is a sequence of 0x20-byte records. Cancellation
// consumes the leading Vector3; the remaining five words are retained as
// independently named fields until their other consumers are recovered.
struct LaserCurvePathPoint {
    Vector3 position;
    std::uint32_t field_0c, field_10, field_14, field_18, field_1c;
};
static_assert(sizeof(LaserCurvePathPoint)==0x20);
static_assert(offsetof(LaserCurvePathPoint,position)==0);

// Native Curve family (vtable 0x00571214). The point-data pointer is a real
// member at +0x1328, advanced in 0x20-byte records by cancel_circle().
class LaserCurveInf : public Laser {
public:
    LaserCurveInf() noexcept;
    std::int32_t cancel_rectangle(const Vector3& rectangle_center,
                                  const Vector3& rectangle_size,
                                  float rectangle_direction, std::int32_t mode,
                                  std::int32_t argument) override;
    std::int32_t cancel_circle(const Vector3& center, float radius,
                               std::int32_t mode, std::int32_t argument) override;
    std::int32_t erase(std::int32_t mode, std::int32_t argument) override;

    LaserType2Parameters parameters;
    Animation animation_0;
    Animation animation_1;
    float field_131c;
    std::uint32_t field_1320, field_1324;
    LaserCurvePathPoint* point_data;
    std::uint32_t field_132c;
    LaserCurvePathState path_state;
};

#if defined(_M_IX86)
static_assert(sizeof(LaserCurveInf)==0x1370);
static_assert(offsetof(LaserCurveInf,parameters)==0x6f8);
static_assert(offsetof(LaserCurveInf,animation_0)==0x754);
static_assert(offsetof(LaserCurveInf,animation_1)==0xd38);
static_assert(offsetof(LaserCurveInf,field_131c)==0x131c);
static_assert(offsetof(LaserCurveInf,field_1320)==0x1320);
static_assert(offsetof(LaserCurveInf,field_1324)==0x1324);
static_assert(offsetof(LaserCurveInf,point_data)==0x1328);
static_assert(offsetof(LaserCurveInf,field_132c)==0x132c);
static_assert(offsetof(LaserCurveInf,path_state)==0x1330);
#endif

} // namespace th20
