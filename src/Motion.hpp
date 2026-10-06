#pragma once

#include "Angle.hpp"
#include "Vector3.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

// The low four bits select motion mode; bit 5 freezes both native updates.
struct MotionFlags { std::uint32_t bits; };

// Shared by native Bomb, Damage and Enemy. Unknown scalar roles retain offsets.
struct Motion {
    Vector3 position, velocity;
    float value_18;
    Angle angle_1c;
    float value_20, value_24;
    Angle angle_28;
    float value_2c;
    Angle angle_30;
    float value_34;
    Vector3 vector_38;
    MotionFlags flags;

    Motion();
    void update_velocity();
    void update_position();
    void update();
    int outside_bounds(float x, float y, float width, float height) const;
};

static_assert(sizeof(MotionFlags) == 4);
static_assert(sizeof(Motion) == 72);
static_assert(offsetof(Motion, velocity) == 0x0c);
static_assert(offsetof(Motion, angle_1c) == 0x1c);
static_assert(offsetof(Motion, angle_28) == 0x28);
static_assert(offsetof(Motion, angle_30) == 0x30);
static_assert(offsetof(Motion, vector_38) == 0x38);
static_assert(offsetof(Motion, flags) == 0x44);

} // namespace th20
