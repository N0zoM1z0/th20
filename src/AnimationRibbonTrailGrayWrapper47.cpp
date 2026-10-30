#include "NativeRibbonTrailGroup.hpp"
#include "DiagnosticObjectFactories.hpp"
#include <cstdint>
namespace th20 {
extern const std::uint8_t native_ribbon_trail_gray_marker_56ed88[];
extern template NativeRibbonTrailGroup* DiagnosticAllocator::allocate_object<
    NativeRibbonTrailGroup,Animation*>(const char*,Animation*);
std::int32_t __cdecl create_trail_gray_45e520(std::uint32_t handle,const Vector3* location,std::int32_t token) {
    NativeRibbonTrailGroup* const group=process_allocator->allocate_object<
        NativeRibbonTrailGroup,Animation*>(
        reinterpret_cast<const char*>(native_ribbon_trail_gray_marker_56ed88),
        reinterpret_cast<Animation*>(handle));
    return group->configure_gray_45e240(*location,token);
}
}
