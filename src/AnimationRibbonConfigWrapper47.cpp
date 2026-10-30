// Complete original 47B ribbon diagnostic allocation/configuration wrapper.
// The native 156B C++17 allocation owner is declared extern template here,
// preventing a conflicting C++20 template instantiation.
#include "NativeRibbonPolygonGroup.hpp"
#include "DiagnosticObjectFactories.hpp"
#include <cstdint>
namespace th20 {
extern const std::uint8_t native_ribbon_type_marker_56edf8[];
extern template NativeRibbonGroup* DiagnosticAllocator::allocate_object<
    NativeRibbonGroup, Animation*>(const char*, Animation*);
std::int32_t __cdecl configure_ribbon_group_45ec70(
    std::uint32_t handle, const NativeRibbonGroupOptions* options,
    std::int32_t token) {
    NativeRibbonGroup* const group = process_allocator->allocate_object<
        NativeRibbonGroup, Animation*>(
            reinterpret_cast<const char*>(native_ribbon_type_marker_56edf8),
            reinterpret_cast<Animation*>(handle));
    return group->configure_group_45eb10(*options, token);
}
}
