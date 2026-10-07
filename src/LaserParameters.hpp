#pragma once

#include "BulletValues.hpp"
#include <cstddef>
#include <memory_resource>
#include <vector>

namespace th20 {

// Four real dispatcher temporaries, with separate command-vector lifetimes.
// Neutral field names retain unresolved opcode-specific roles.
struct LaserType0Parameters {
    Vector3 position;
    float angle, length, field_14, length_limit, width, speed;
    std::uint32_t type, color;
    float radial_offset;
    std::uint32_t command_index, flags;
    std::pmr::vector<BulletCommand> commands;
    std::int32_t field_48, field_4c, view_index;
    LaserType0Parameters();
    ~LaserType0Parameters();
};
struct LaserType1Parameters {
    Vector3 position, velocity;
    float angle, angular_velocity, length_limit, length, width, growth_speed;
    std::int32_t delay, grow_time, sustain_time, shrink_time, sound, field_44;
    std::uint32_t handle;
    float radial_offset;
    std::uint32_t command_index, type, color, flags;
    std::pmr::vector<BulletCommand> commands;
    std::int32_t view_index;
    LaserType1Parameters();
    ~LaserType1Parameters();
};
struct CurveNode;
struct LaserType2Flags { std::uint32_t word; };
struct LaserType2Parameters {
    Vector3 position;
    float angle, width, speed;
    std::uint32_t type, color, count;
    float radial_offset;
    LaserType2Flags flags;
    std::pmr::vector<BulletCommand> commands;
    std::int32_t sound, motion_sound;
    std::uint32_t command_index;
    CurveNode* path;
    float time;
    std::uint32_t field_50, field_54;
    std::int32_t view_index;
    LaserType2Parameters();
    ~LaserType2Parameters();
};
struct LaserType3Parameters {
    Vector3 position, vector_0c;
    float angle, field_1c, field_20, field_24;
    std::uint32_t handle, field_2c;
    float field_30;
    std::uint32_t field_34, flags;
    std::pmr::vector<BulletCommand> commands;
    std::int32_t view_index;
    LaserType3Parameters();
    ~LaserType3Parameters();
};

static_assert(sizeof(LaserType2Flags) == 4);
#if defined(_M_IX86)
static_assert(sizeof(LaserType0Parameters) == 0x54);
static_assert(sizeof(LaserType1Parameters) == 0x74);
static_assert(sizeof(LaserType2Parameters) == 0x5c);
static_assert(sizeof(LaserType3Parameters) == 0x50);
static_assert(offsetof(LaserType0Parameters, commands) == 0x38);
static_assert(offsetof(LaserType1Parameters, commands) == 0x60);
static_assert(offsetof(LaserType2Parameters, flags) == 0x28);
static_assert(offsetof(LaserType2Parameters, commands) == 0x2c);
static_assert(offsetof(LaserType2Parameters, path) == 0x48);
static_assert(offsetof(LaserType3Parameters, field_30) == 0x30);
static_assert(offsetof(LaserType3Parameters, commands) == 0x3c);
#endif

} // namespace th20
