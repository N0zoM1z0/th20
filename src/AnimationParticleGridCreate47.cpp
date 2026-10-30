#include "NativeParticleGridGroup.hpp"
#include "DiagnosticObjectFactories.hpp"
#include <cstdint>
namespace th20 {
extern const std::uint8_t native_particle_grid_marker_56ec30[];
extern template NativeParticleGridGroup* DiagnosticAllocator::allocate_object<
    NativeParticleGridGroup,Animation*>(const char*,Animation*);
std::int32_t __cdecl create_particle_grid_45d000(std::uint32_t animation_handle,
                                                 const Vector3* position, std::int32_t token) {
    NativeParticleGridGroup* group=process_allocator->allocate_object<
        NativeParticleGridGroup,Animation*>(
        reinterpret_cast<const char*>(native_particle_grid_marker_56ec30),
        reinterpret_cast<Animation*>(animation_handle));
    return group->configure_45cfe0(*position,token);
}
}
