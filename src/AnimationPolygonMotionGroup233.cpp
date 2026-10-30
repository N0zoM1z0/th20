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
#include <cstddef>
#include <cstdint>
namespace th20 {

struct NativePolygonSegmentSlot {
    alignas(4) std::uint8_t original_bytes[0x3D4];
};
static_assert(sizeof(NativePolygonSegmentSlot)==0x3D4);

struct NativePolygonSegmentArray {
    NativePolygonSegmentSlot segments[3];
    NativePolygonSegmentSlot* at(std::int32_t index);
    NativePolygonSegmentSlot* end();
};
static_assert(sizeof(NativePolygonSegmentArray)==0xB7C);

NativePolygonSegmentSlot* NativePolygonSegmentArray::at(std::int32_t index) {
    return &segments[index];
}
NativePolygonSegmentSlot* NativePolygonSegmentArray::end() {
    return reinterpret_cast<NativePolygonSegmentSlot*>(
        reinterpret_cast<std::uint8_t*>(this) + sizeof(segments));
}

struct NativePolygonMotionGroup {
    std::uint32_t native_field_00;
    Animation* animation_04;
    NativePolygonSegmentArray segments_08;
    std::uint8_t retained_b84_to_b9c[0x18];
    Vector3 saved_position_b9c;
    std::uint8_t use_animation_position_ba8;

    std::int32_t draw_motion_group_45f9b0();
};
static_assert(offsetof(NativePolygonMotionGroup,animation_04)==4);
static_assert(offsetof(NativePolygonMotionGroup,segments_08)==8);
static_assert(offsetof(NativePolygonMotionGroup,saved_position_b9c)==0xB9C);
static_assert(offsetof(NativePolygonMotionGroup,use_animation_position_ba8)==0xBA8);

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
} // namespace th20
