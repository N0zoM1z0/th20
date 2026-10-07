#pragma once

#include "Angle.hpp"
#include "Vector3.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

// The low four bits select motion mode; bit 5 freezes both native updates.
struct MotionFlags {
    union {
        std::uint32_t bits;
        struct {
            std::uint32_t mode : 4;
            std::uint32_t spin : 1;
            std::uint32_t frozen : 1;
            std::uint32_t reserved : 26;
        } fields;
    };
};

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
    Motion& operator=(const Vector3& input);
    Vector3& position_ref();
    Vector3 position_copy() const;
    void set_position(const Vector3& input);
    float position_x() const;
    float position_y() const;
    void set_position_x(float value);
    void set_position_y(float value);
    void set_angle(float value) noexcept;
    void set_speed(float value);
    void select_linear();
    void select_orbit();
    void select_elliptic();
    int is_orbit() const;
    int is_elliptic() const;
    void set_parameter_20(float value);
    void set_parameter_24(float value);
    void clear();
    Vector3& motion_vector();
    void set_motion_z(float value);
    void set_motion_vector(const Vector3& value);
    void snap_position();
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
