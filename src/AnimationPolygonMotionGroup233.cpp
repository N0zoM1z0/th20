// Whole original 233B/78-i386 polygon Motion group Boss native strict exact.
// Original 9 E8/2 PE HIGHLOW site/targets, actual 3x0x3D4 records, and
// complete 233/233 relocated bytes under pinned x86 MSVC were accepted.
// Its 23B/19B array pointer helpers are also whole strict exact but have
// unresolved likely STL/generated-vs-authored provenance and are not counted
// as hand-authored game code pending independent origin proof.
// Retained record bytes reflect original offset evidence, not code padding.
#include "NativeMotionPolygonOwner.hpp"
#include "AnimationQuadSubmitOwner.hpp"
#include "AnimationRuntimeOwner.hpp"
#include "Animation.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Timer.hpp"
#include "NativePolygonMotionGroup.hpp"
#include "DiagnosticObjectFactories.hpp"
#include <cstddef>
#include <cstdint>
namespace th20 {

NativePolygonSegmentSlot* NativePolygonSegmentArray::at(std::int32_t index) {
    return reinterpret_cast<NativePolygonSegmentSlot*>(this) + index;
}
NativePolygonSegmentSlot* NativePolygonSegmentArray::end() {
    return reinterpret_cast<NativePolygonSegmentSlot*>(
        reinterpret_cast<std::uint8_t*>(this) + sizeof(segments));
}

struct NativePolygonAnimationConfigView {
    void configure_438c60(std::int32_t, std::int32_t, std::uint8_t, std::uint8_t);
};

// Complete original game 140B/46-x86 polygon dynamic dispatch Boss.
// The following 4 PE INT3 bytes are alignment, not game function code.
// The unaccepted 827B per-segment update and the timer gate keep
// provisional ABI names, separate from the accepted group state.
struct NativePolygonTimerGate { std::int32_t changed_45d030(); };

std::int32_t NativePolygonMotionGroup::tick_polygon_group_45f5e0() {
    if (reinterpret_cast<NativePolygonTimerGate*>(&timer_b88)->changed_45d030()) {
        NativePolygonSegmentArray* const segment_array=&segments_08;
        auto* current = reinterpret_cast<NativePolygonSegmentSlot*>(
            &reinterpret_cast<Motion*>(segment_array)->position_ref());
        auto* finish = segment_array->end();
        for (; current != finish; ++current) {
            NativePolygonSegmentSlot* const active=current;
            active->update_polygon_dynamics_45f670(animation_04->scale_x_value());
        }
    }
    timer_b88++;
    return 0;
}

std::int32_t NativePolygonMotionGroup::draw_motion_group_45f9b0() {
    reinterpret_cast<AnimationQuadSubmitOwner*>(current_animation_pool)->bind_native_texture_state(animation_04);
    Vector3 position;
    if (use_animation_position_ba8 != 0) {
        animation_04->position(position);
    } else {
        position = saved_position_b9c;
    }
    {
        NativePolygonSegmentArray* const segment_array=&segments_08;
        auto* current = reinterpret_cast<NativePolygonSegmentSlot*>(
            &reinterpret_cast<Motion*>(segment_array)->position_ref());
        auto* finish = segment_array->end();
        for (; current!=finish; ++current) {
            NativeMotionPolygonOwner* const active_segment =
                reinterpret_cast<NativeMotionPolygonOwner*>(current);
            active_segment->draw_polygon_outline_45faa0(
                reinterpret_cast<const Vector2*>(&position));
        }
    }
    NativePolygonSegmentArray* const first_segment_array=&segments_08;
    reinterpret_cast<NativeMotionPolygonOwner*>(first_segment_array->at(0))->draw_polygon_fan_45fb10(
        reinterpret_cast<const Vector2*>(&position));
    return 0;
}

// Whole original 296B/90-x86 group configuration Boss strictly exact.
// Correct single function scope for seven meaningful receiver locals removes
// eight extra MSVC /Od NOPs that nested source braces had caused. Native
// eleven E8/zero HIGHLOW roles and complete 296/296 bytes match the PE.
std::int32_t NativePolygonMotionGroup::configure_group_45fb60(
        const NativePolygonGroupOptions& config, std::int32_t value) {
    value_b98 = value;
    control_b84 = config.control_24;
    saved_position_b9c = config.position;
    use_animation_position_ba8 = config.choose_animation_28;
    timer_b88 = 0;
    NativePolygonSegmentArray* const array0 = &segments_08;
    NativePolygonSegmentSlot* const slot0 = array0->at(0);
    slot0->initialize_palette_45fc90(0x8040F010u);
    NativePolygonSegmentArray* const array1 = &segments_08;
    NativePolygonSegmentSlot* const slot1 = array1->at(1);
    slot1->initialize_palette_45fc90(0xFF20F000u);
    NativePolygonSegmentArray* const array2 = &segments_08;
    NativePolygonSegmentSlot* const slot2 = array2->at(2);
    slot2->initialize_palette_45fc90(0x80FF1010u);
    Animation* const animation0 = animation_04;
    animation0->set_position(config.position);
    Animation* const animation1 = animation_04;
    animation1->set_layer(11);
    Animation* const animation2 = animation_04;
    reinterpret_cast<NativePolygonAnimationConfigView*>(animation2)->configure_438c60(30,0,255,0);
    Animation* const animation3 = animation_04;
    animation3->set_flag_byte_01(1);
    return 0;
}

// Genuine original 47B/18-i386 allocation-to-polygon configuration.
// The global at 0x005B8894 is the actual DiagnosticAllocator instance,
// not a registry. The 156B C++17 scalar factory has one separate owner.
extern const std::uint8_t native_polygon_type_marker_56ee68[];
extern template NativePolygonMotionGroup* DiagnosticAllocator::allocate_object<
    NativePolygonMotionGroup, std::uint32_t>(const char*, std::uint32_t);

std::int32_t __cdecl configure_polygon_group_45fd10(
        std::uint32_t handle, const NativePolygonGroupOptions* options,
        std::int32_t value) {
    NativePolygonMotionGroup* group = process_allocator->allocate_object<
        NativePolygonMotionGroup, std::uint32_t>(
            reinterpret_cast<const char*>(native_polygon_type_marker_56ee68),handle);
    return group->configure_group_45fb60(*options,value);
}
} // namespace th20
