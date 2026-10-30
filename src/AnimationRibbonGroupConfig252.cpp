// Complete original 252B ribbon group configuration Boss at 0x0045EB10.
// Real 3-segment palette, animation positioning/layer, Timer and token ABI.
// Independent original physical 11 E8 call target roles are required.
#include "NativeRibbonPolygonGroup.hpp"
#include "Animation.hpp"
#include "Vector3.hpp"
#include <cstdint>
namespace th20 {
struct NativeRibbonAnimationConfigView {
    void configure_438c60(std::int32_t, std::int32_t, std::uint8_t, std::uint8_t);
};
std::int32_t NativeRibbonGroup::configure_group_45eb10(
    const NativeRibbonGroupOptions& config, std::int32_t token) {
    resource_token_b5c = reinterpret_cast<void*>(static_cast<std::uintptr_t>(token));
    control_b48 = config.control_24;
    timer_b4c = 0;
    NativeRibbonSegmentArray* const array0 = reinterpret_cast<NativeRibbonSegmentArray*>(&segments_08);
    NativeRibbonSegment* const slot0 = array0->at_45d690(0);
    slot0->initialize_palette_45ec10(0xFFFF4040u);
    NativeRibbonSegmentArray* const array1 = reinterpret_cast<NativeRibbonSegmentArray*>(&segments_08);
    NativeRibbonSegment* const slot1 = array1->at_45d690(1);
    slot1->initialize_palette_45ec10(0xFFC040FFu);
    NativeRibbonSegmentArray* const array2 = reinterpret_cast<NativeRibbonSegmentArray*>(&segments_08);
    NativeRibbonSegment* const slot2 = array2->at_45d690(2);
    slot2->initialize_palette_45ec10(0xFFFFFF40u);
    Animation* const anim0 = animation;
    anim0->set_position(config.position);
    Animation* const anim1 = animation;
    anim1->set_layer(11);
    Animation* const anim2 = animation;
    reinterpret_cast<NativeRibbonAnimationConfigView*>(anim2)->configure_438c60(30, 0, 255, 0);
    Animation* const anim3 = animation;
    anim3->set_flag_byte_01(1);
    return 0;
}
}
