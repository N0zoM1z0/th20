#pragma once
// Original separate polygon/ribbon AnimationCallback group, distinct from
// NativePolygonMotionGroup (3 * 0x3D4 segments). The genuine 0x56EDDC vtable
// has update 0x45E770 and draw 0x45EA20, with 3 * 0x3C0 segments at +8.
#include "AnimationCallback.hpp"
#include "Timer.hpp"
#include "Vector2.hpp"
#include "AnimationHandle.hpp"
#include "NativeRibbonArraySpans.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
namespace th20 {
class Animation;
struct Vector3;
struct NativeRibbonGroupOptions;
// Native element boundaries independently confirm 60 two-float positions,
// 60 four-byte color cells, and 60 float radii: 0x1E0+0xF0+0xF0=0x3C0.
struct NativeRibbonSegment {
    NativeRibbonPointSpan perimeter_00;
    std::array<AnimationHandle, 60> color_cells_1e0;
    NativeRibbonScalarSpan radius_2d0;
    NativeRibbonSegment() noexcept;
    void update_ribbon_45e800(float scale);
    void draw_ribbon_45eac0(const Vector3* position);
};
static_assert(offsetof(NativeRibbonSegment, color_cells_1e0) == 0x1E0);
static_assert(offsetof(NativeRibbonSegment, radius_2d0) == 0x2D0);
struct NativeRibbonSegmentArray {
    std::array<NativeRibbonSegment, 3> elements;
    NativeRibbonSegmentArray();
    NativeRibbonSegment* end_45eca0();
};
class NativeRibbonGroup : public AnimationCallback {
public:
    // Native group constructor invokes the actual std::array constructor
    // directly at +8, not a competing wrapper object constructor.
    std::array<NativeRibbonSegment, 3> segments_08;
    union { std::uint32_t control_b48; float control_b48_float; };
    Timer timer_b4c;
    // Original +0xB5C 4-byte zero-initialized storage is independently
    // attested by group ctor and original 0xB60 deleting-wrapper extent.
    void* resource_token_b5c;
    explicit NativeRibbonGroup(Animation* owner);
    std::int32_t configure_group_45eb10(const NativeRibbonGroupOptions& options,
                                          std::int32_t token);
    std::int32_t update() override;
    std::int32_t draw() override;
};
static_assert(sizeof(NativeRibbonSegment) == 0x3C0);
static_assert(sizeof(NativeRibbonSegmentArray) == 0xB40);
static_assert(offsetof(NativeRibbonGroup, segments_08) == 8);
static_assert(offsetof(NativeRibbonGroup, timer_b4c) == 0xB4C);
static_assert(offsetof(NativeRibbonGroup, resource_token_b5c) == 0xB5C);
static_assert(sizeof(NativeRibbonGroup) == 0xB60);
} // namespace th20
