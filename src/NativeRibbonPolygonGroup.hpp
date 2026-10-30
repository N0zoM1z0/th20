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
    NativeRibbonSegment* end_45eca0();
};
class NativeRibbonGroup : public AnimationCallback {
public:
    NativeRibbonSegmentArray segments_08;
    std::uint32_t control_b48;
    Timer timer_b4c;
    std::int32_t update() override;
    std::int32_t draw() override;
};
static_assert(sizeof(NativeRibbonSegment) == 0x3C0);
static_assert(sizeof(NativeRibbonSegmentArray) == 0xB40);
static_assert(offsetof(NativeRibbonGroup, segments_08) == 8);
static_assert(offsetof(NativeRibbonGroup, timer_b4c) == 0xB4C);
} // namespace th20
