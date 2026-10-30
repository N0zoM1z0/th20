// Complete original 156B polymorphic solo ribbon group draw.
// Scoped C++ traversal naturally emits the real NOP after position update.
#include "NativeRibbonSoloGroup.hpp"
#include "Animation.hpp"
#include "Motion.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Vector3.hpp"
namespace th20 {
std::int32_t NativeRibbonSoloGroup::draw() {
    reinterpret_cast<AnimationQuadSubmitOwner*>(current_animation_pool)->bind_native_texture_state(animation);
    Vector3 position;
    animation->position(position);
    {
        NativeRibbonSoloSegmentArray* const segment_array =
            reinterpret_cast<NativeRibbonSoloSegmentArray*>(&segments_08);
        auto* current = reinterpret_cast<NativeRibbonSegment*>(
            &reinterpret_cast<Motion*>(segment_array)->position_ref());
        auto* finish = segment_array->end_45dce0();
        for (; current != finish; ++current) {
            NativeRibbonSegment* const active = current;
            reinterpret_cast<NativeRibbonSoloSegmentDrawView*>(active)->draw_45dae0(&position);
        }
    }
    return 0;
}
} // namespace th20
