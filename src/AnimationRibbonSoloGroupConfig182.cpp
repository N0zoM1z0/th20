#include "NativeRibbonSoloGroup.hpp"
#include "Animation.hpp"
#include "Vector3.hpp"
#include <cstdint>
#include <cstddef>
namespace th20 {
struct NativeRibbonSoloGroupOptions {
    Vector3 position;
    std::uint8_t unknown_0c_to_24[0x18];
    std::uint32_t control_24;
};
static_assert(offsetof(NativeRibbonSoloGroupOptions,control_24)==0x24);
struct NativeRibbonSoloPaletteView {
    void initialize_palette_45dbf0(std::uint32_t color);
};
struct NativeRibbonAnimationConfigView {
    void configure_438c60(std::int32_t,std::int32_t,std::uint8_t,std::uint8_t);
};
std::int32_t NativeRibbonSoloGroup::configure_group_45db30(
        const NativeRibbonSoloGroupOptions& config,std::int32_t token) {
    resource_token_3dc = reinterpret_cast<void*>(static_cast<std::uintptr_t>(token));
    control_3c8 = config.control_24;
    timer_3cc = 0;
    NativeRibbonSegmentArray* const array = reinterpret_cast<NativeRibbonSegmentArray*>(&segments_08);
    NativeRibbonSegment* const slot = array->at_45d690(0);
    reinterpret_cast<NativeRibbonSoloPaletteView*>(slot)->initialize_palette_45dbf0(0x00FF0000u);
    Animation* const anim0 = animation;
    anim0->set_position(config.position);
    Animation* const anim1 = animation;
    anim1->set_layer(11);
    Animation* const anim2 = animation;
    reinterpret_cast<NativeRibbonAnimationConfigView*>(anim2)->configure_438c60(30,0,255,0);
    Animation* const anim3 = animation;
    anim3->set_flag_byte_01(1);
    return 0;
}
}
