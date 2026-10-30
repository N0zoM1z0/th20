#include "NativeRibbonSoloGroup.hpp"
#include "Animation.hpp"
#include "Motion.hpp"
namespace th20 {
struct NativeRibbonGate { std::int32_t changed_45d030(); };
std::int32_t NativeRibbonSoloGroup::update() {
    if (reinterpret_cast<NativeRibbonGate*>(&timer_3cc)->changed_45d030()) {
        NativeRibbonSoloSegmentArray* const array = reinterpret_cast<NativeRibbonSoloSegmentArray*>(&segments_08);
        auto* current = reinterpret_cast<NativeRibbonSegment*>(
            &reinterpret_cast<Motion*>(array)->position_ref());
        auto* finish = array->end_45dce0();
        for (; current != finish; ++current) {
            NativeRibbonSegment* const active = current;
            reinterpret_cast<NativeRibbonSoloSegmentUpdateView*>(active)->update_45d780(animation->scale_x_value());
        }
    }
    timer_3cc++;
    return 0;
}
}
