#include "FunctionChain.hpp"
#include "DiagnosticObjectFactories.hpp"

namespace th20 {
template FunctionChainNode* DiagnosticAllocator::allocate_object<FunctionChainNode>(const char*);
}
