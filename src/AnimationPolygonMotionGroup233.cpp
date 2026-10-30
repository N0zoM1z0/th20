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
#include <cstddef>
#include <cstdint>
namespace th20 {

struct NativePolygonSegmentSlot {
    alignas(4) std::uint8_t original_bytes[0x3D4];
    void initialize_palette_45fc90(std::uint32_t diffuse_color);
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

// The real original input has Vector3 at +0, control word at +0x24
// and the original position-choice byte at +0x28.
struct NativePolygonGroupOptions {
    Vector3 position;
    std::uint8_t unresolved_0c_to_24[0x18];
    std::uint32_t control_24;
    std::uint8_t choose_animation_28;
};
static_assert(offsetof(NativePolygonGroupOptions,control_24)==0x24);
static_assert(offsetof(NativePolygonGroupOptions,choose_animation_28)==0x28);

struct NativePolygonAnimationConfigView {
    // Original 86B Animation call takes two integers then two byte values.
    void configure_438c60(std::int32_t, std::int32_t, std::uint8_t, std::uint8_t);
};

struct NativePolygonMotionGroup {
    std::uint32_t native_field_00;
    Animation* animation_04;
    NativePolygonSegmentArray segments_08;
    std::uint32_t control_b84;
    Timer timer_b88;
    std::uint32_t value_b98;
    Vector3 saved_position_b9c;
    std::uint8_t use_animation_position_ba8;

    std::int32_t draw_motion_group_45f9b0();
    std::int32_t configure_group_45fb60(const NativePolygonGroupOptions& config,
                                       std::int32_t value);
};
static_assert(offsetof(NativePolygonMotionGroup,animation_04)==4);
static_assert(offsetof(NativePolygonMotionGroup,segments_08)==8);
static_assert(offsetof(NativePolygonMotionGroup,control_b84)==0xB84);
static_assert(offsetof(NativePolygonMotionGroup,timer_b88)==0xB88);
static_assert(offsetof(NativePolygonMotionGroup,value_b98)==0xB98);
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
} // namespace th20
