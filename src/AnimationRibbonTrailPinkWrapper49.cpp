#include "NativeRibbonTrailGroup.hpp"
#include "DiagnosticObjectFactories.hpp"
#include <cstdint>
namespace th20 {
extern const std::uint8_t native_ribbon_trail_pink_marker_56ed38[];
extern template NativeRibbonTrailGroup* DiagnosticAllocator::allocate_object<
    NativeRibbonTrailGroup,Animation*>(const char*,Animation*);
std::int32_t __cdecl create_trail_pink_45e550(std::uint32_t handle,const Vector3* location,std::int32_t token) {
    NativeRibbonTrailGroup* const group=process_allocator->allocate_object<
        NativeRibbonTrailGroup,Animation*>(
        reinterpret_cast<const char*>(native_ribbon_trail_pink_marker_56ed38),
        reinterpret_cast<Animation*>(handle));
    group->configure_pink_45e3a0(*location,token);
    return 0;
}
}
