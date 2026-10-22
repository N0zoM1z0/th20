#include "PbgFile.hpp"
#include "DiagnosticObjectFactories.hpp"

namespace th20 {
template Pbg::File* DiagnosticAllocator::allocate_object<Pbg::File>(const char*);
}
