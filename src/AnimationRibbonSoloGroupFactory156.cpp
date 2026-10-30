#include "NativeRibbonSoloGroup.hpp"
#include "DiagnosticObjectFactories.hpp"
namespace th20 {
template NativeRibbonSoloGroup* DiagnosticAllocator::allocate_object<
    NativeRibbonSoloGroup, Animation*>(const char*, Animation*);
}
