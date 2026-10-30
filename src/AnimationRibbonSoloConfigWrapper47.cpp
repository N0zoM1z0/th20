#include "NativeRibbonSoloGroup.hpp"
#include "DiagnosticObjectFactories.hpp"
#include <cstdint>
namespace th20 {
extern const std::uint8_t native_ribbon_solo_marker_56ecc0[];
extern template NativeRibbonSoloGroup* DiagnosticAllocator::allocate_object<
    NativeRibbonSoloGroup, Animation*>(const char*,Animation*);
std::int32_t __cdecl configure_ribbon_solo_group_45dc70(
    std::uint32_t handle,const NativeRibbonSoloGroupOptions* options,std::int32_t token) {
    NativeRibbonSoloGroup* const group=process_allocator->allocate_object<
        NativeRibbonSoloGroup,Animation*>(
        reinterpret_cast<const char*>(native_ribbon_solo_marker_56ecc0),
        reinterpret_cast<Animation*>(handle));
    return group->configure_group_45db30(*options,token);
}
}
