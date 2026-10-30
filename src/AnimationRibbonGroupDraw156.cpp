// Whole native 156B ribbon-group draw Boss at original 0x0045EA20.
// Native AnimationCallback vtable, 3x0x3C0 segments and a genuine scoped
// traversal after the separate texture binding and position preparation.
#include "NativeRibbonPolygonGroup.hpp"
#include "Animation.hpp"
#include "Motion.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Vector3.hpp"
namespace th20 {
std::int32_t NativeRibbonGroup::draw() {
    reinterpret_cast<AnimationQuadSubmitOwner*>(current_animation_pool)->bind_native_texture_state(animation);
    Vector3 position;
    animation->position(position);
    {
        NativeRibbonSegmentArray* const segment_array =
            reinterpret_cast<NativeRibbonSegmentArray*>(&segments_08);
        auto* current = reinterpret_cast<NativeRibbonSegment*>(
            &reinterpret_cast<Motion*>(segment_array)->position_ref());
        auto* finish = segment_array->end_45eca0();
        for (; current != finish; ++current) {
            NativeRibbonSegment* const active = current;
            active->draw_ribbon_45eac0(&position);
        }
    }
    return 0;
}
} // namespace th20
