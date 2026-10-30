#pragma once
// Native 0xBAC-byte polygon Motion group, shared with its C++17 factory.
// One canonical C++ class owns the real three 0x3D4-byte polygon segments.
#include "Timer.hpp"
#include "Vector3.hpp"
#include "NativePolygonSegmentSlot.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
namespace th20 {
class Animation;

struct NativePolygonSegmentArray {
    // Native 78B C++20 STL constructor owns this original three-segment array.
    std::array<NativePolygonSegmentSlot,3> segments;
    NativePolygonSegmentArray();
    NativePolygonSegmentSlot* at(std::int32_t index);
    NativePolygonSegmentSlot* end();
};
static_assert(sizeof(NativePolygonSegmentArray)==0xB7C);

struct NativePolygonGroupOptions {
    Vector3 position;
    std::uint8_t unresolved_0c_to_24[0x18];
    std::uint32_t control_24;
    std::uint8_t choose_animation_28;
};
static_assert(offsetof(NativePolygonGroupOptions,control_24)==0x24);
static_assert(offsetof(NativePolygonGroupOptions,choose_animation_28)==0x28);

// A real Animation pointer member is required for native C++17 /sdl
// class auto-initialization; storage and offsets are original PE backed.
class NativePolygonMotionGroup {
public:
    std::uint32_t native_field_00;
    Animation* animation_04;
    NativePolygonSegmentArray segments_08;
    std::uint32_t control_b84;
    Timer timer_b88;
    std::uint32_t value_b98;
    Vector3 saved_position_b9c;
    std::uint8_t use_animation_position_ba8;

    explicit NativePolygonMotionGroup(std::uint32_t handle);
    std::int32_t tick_polygon_group_45f5e0();
    std::int32_t draw_motion_group_45f9b0();
    std::int32_t configure_group_45fb60(const NativePolygonGroupOptions& config,
                                       std::int32_t value);
};
static_assert(sizeof(NativePolygonMotionGroup)==0xBAC);
static_assert(offsetof(NativePolygonMotionGroup,animation_04)==4);
static_assert(offsetof(NativePolygonMotionGroup,segments_08)==8);
static_assert(offsetof(NativePolygonMotionGroup,control_b84)==0xB84);
static_assert(offsetof(NativePolygonMotionGroup,timer_b88)==0xB88);
static_assert(offsetof(NativePolygonMotionGroup,value_b98)==0xB98);
static_assert(offsetof(NativePolygonMotionGroup,saved_position_b9c)==0xB9C);
static_assert(offsetof(NativePolygonMotionGroup,use_animation_position_ba8)==0xBA8);
} // namespace th20
