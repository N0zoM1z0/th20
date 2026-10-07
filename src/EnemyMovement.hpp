#pragma once

#include "Interpolation.hpp"
#include "Motion.hpp"
#include <cstddef>
#include <cstdint>

namespace th20 {

struct AxisModes { std::int32_t values[3]; };
// Bit zero selects the three axis modes instead of the shared mode.
struct EnemyInterpolationFlags { std::uint32_t bits; };

// ECL movement puts current first and adds three independent axis modes.
// This is a distinct native value from the 84-byte ANM VectorInterpolation.
struct EnemyMotionInterpolation {
    Vector3 current, start, end, tangent_start, tangent_end;
    Timer timer;
    std::int32_t duration;
    AxisModes axis_modes;
    std::int32_t mode;
    EnemyInterpolationFlags flags;

    EnemyMotionInterpolation();
    // Positive durations advance and clamp. Terminal returns leave current intact
    // and use the shared mode even when the low flags bit selects axis modes.
    Vector3 sample();
    void stop();
    std::int32_t duration_value() const;
    float factor() const;
    // Axis indices are the native signed 0, 1 and 2 coordinate indices.
    float factor(std::int32_t axis) const;
};

struct EnemyMovement {
    Motion motion;
    EnemyMotionInterpolation position;
    FloatInterpolation scalar_ac, scalar_d8;
    Vector2Interpolation vector_104, vector_144;

    EnemyMovement();
};

static_assert(sizeof(AxisModes) == 12);
static_assert(sizeof(EnemyInterpolationFlags) == 4);
static_assert(sizeof(EnemyMotionInterpolation) == 100);
static_assert(offsetof(EnemyMotionInterpolation, start) == 0x0c);
static_assert(offsetof(EnemyMotionInterpolation, tangent_end) == 0x30);
static_assert(offsetof(EnemyMotionInterpolation, timer) == 0x3c);
static_assert(offsetof(EnemyMotionInterpolation, duration) == 0x4c);
static_assert(offsetof(EnemyMotionInterpolation, axis_modes) == 0x50);
static_assert(offsetof(EnemyMotionInterpolation, mode) == 0x5c);
static_assert(offsetof(EnemyMotionInterpolation, flags) == 0x60);
static_assert(sizeof(EnemyMovement) == 388);
static_assert(offsetof(EnemyMovement, position) == 0x48);
static_assert(offsetof(EnemyMovement, scalar_ac) == 0xac);
static_assert(offsetof(EnemyMovement, scalar_d8) == 0xd8);
static_assert(offsetof(EnemyMovement, vector_104) == 0x104);
static_assert(offsetof(EnemyMovement, vector_144) == 0x144);

} // namespace th20
