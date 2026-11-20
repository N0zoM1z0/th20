#pragma once

#include "Angle.hpp"
#include "Animation.hpp"
#include "LaserParameters.hpp"

namespace th20 {

// The independently constructed 64-byte LaserBeamInf tail state at +0x1330.
// Its native constructor initializes the five leading words, two Vector3
// values, one Angle and the three trailing scalar lanes.
struct LaserBeamPathState {
    std::uint32_t field_00, field_04;
    float field_08, field_0c;
    std::uint32_t field_10;
    Vector3 vector_14;
    Vector3 vector_20;
    Angle angle_2c;
    float field_30, field_34, field_38;
    std::uint32_t field_3c;

    LaserBeamPathState() noexcept;
};
static_assert(sizeof(LaserBeamPathState)==0x40);
static_assert(offsetof(LaserBeamPathState,vector_14)==0x14);
static_assert(offsetof(LaserBeamPathState,vector_20)==0x20);
static_assert(offsetof(LaserBeamPathState,angle_2c)==0x2c);

// The native Beam path is a sequence of 0x20-byte records. Cancellation
// consumes the leading Vector3; the remaining five words are retained as
// independently named fields until their other consumers are recovered.
struct LaserBeamPathPoint {
    Vector3 position;
    std::uint32_t field_0c, field_10, field_14, field_18, field_1c;
};
static_assert(sizeof(LaserBeamPathPoint)==0x20);
static_assert(offsetof(LaserBeamPathPoint,position)==0);

// Native Beam family (vtable 0x00571214). The point-data pointer is a real
// member at +0x1328, advanced in 0x20-byte records by cancel_circle().
class LaserBeamInf : public Laser {
public:
    std::int32_t cancel_circle(const Vector3& center, float radius,
                               std::int32_t mode, std::int32_t argument) override;

    LaserType2Parameters parameters;
    Animation animation_0;
    Animation animation_1;
    std::uint32_t field_131c, field_1320, field_1324;
    LaserBeamPathPoint* point_data;
    std::uint32_t field_132c;
    LaserBeamPathState path_state;
};

#if defined(_M_IX86)
static_assert(sizeof(LaserBeamInf)==0x1370);
static_assert(offsetof(LaserBeamInf,parameters)==0x6f8);
static_assert(offsetof(LaserBeamInf,animation_0)==0x754);
static_assert(offsetof(LaserBeamInf,animation_1)==0xd38);
static_assert(offsetof(LaserBeamInf,point_data)==0x1328);
static_assert(offsetof(LaserBeamInf,path_state)==0x1330);
#endif

} // namespace th20
