#include "NativeParticleGridGroup.hpp"
#include "DiagnosticObjectFactories.hpp"
namespace th20 {
template NativeParticleGridGroup* DiagnosticAllocator::allocate_object<
    NativeParticleGridGroup,Animation*>(const char*,Animation*);
}
