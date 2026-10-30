// Whole native 140B ribbon group update Boss at original 0x0045E770.
// Distinct 3x0x3C0 polygon segment array and Timer +0xB4C, genuine
// AnimationCallback base and original E8 edge to the 538B segment updater.
#include "NativeRibbonPolygonGroup.hpp"
#include "Animation.hpp"
#include "Motion.hpp"
namespace th20 {
// Original 0x45D030 timer-gate body is not yet attributed to its genuine
// C++ class; this ABI-only interface does not construct a separate object.
struct NativeRibbonGate { std::int32_t changed_45d030(); };
std::int32_t NativeRibbonGroup::update() {
    if (reinterpret_cast<NativeRibbonGate*>(&timer_b4c)->changed_45d030()) {
        NativeRibbonSegmentArray* const segment_array =
            reinterpret_cast<NativeRibbonSegmentArray*>(&segments_08);
        auto* current = reinterpret_cast<NativeRibbonSegment*>(
            &reinterpret_cast<Motion*>(segment_array)->position_ref());
        auto* finish = segment_array->end_45eca0();
        for (; current != finish; ++current) {
            NativeRibbonSegment* const active = current;
            active->update_ribbon_45e800(animation->scale_x_value());
        }
    }
    timer_b4c++;
    return 0;
}
} // namespace th20
