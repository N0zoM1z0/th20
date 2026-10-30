#include "NativeRibbonTrailGroup.hpp"
#include "DiagnosticObjectFactories.hpp"
namespace th20 {
template NativeRibbonTrailGroup* DiagnosticAllocator::allocate_object<
    NativeRibbonTrailGroup,Animation*>(const char*,Animation*);
}
