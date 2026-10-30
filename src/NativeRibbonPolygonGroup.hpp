#pragma once
// Original separate polygon/ribbon AnimationCallback group, distinct from
// NativePolygonMotionGroup (3 * 0x3D4 segments). The genuine 0x56EDDC vtable
// has update 0x45E770 and draw 0x45EA20, with 3 * 0x3C0 segments at +8.
#include "AnimationCallback.hpp"
#include "Timer.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
namespace th20 {
class Animation;
struct Vector3;
struct NativeRibbonSegment {
    // Original element size/stride and beginning/end addresses are native
    // verified; internals of the 538B updater have not been reconstructed.
    std::uint8_t unresolved_record_3c0[0x3C0];
    void update_ribbon_45e800(float scale);
    void draw_ribbon_45eac0(const Vector3* position);
};
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
