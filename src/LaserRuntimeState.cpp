#include "LaserRuntimeState.hpp"
#include "DiagnosticObjectFactories.hpp"

namespace th20 {

LaserRuntimeState::LaserRuntimeState() noexcept
    : vector_00(), vector_0c(), vector_18(), field_20(0.0f), field_24(0.0f),
      field_28(0.0f), field_2c(0.0f), field_30(0), field_34(0), field_38(0) {}

template LaserRuntimeState* DiagnosticAllocator::allocate_object<LaserRuntimeState>(const char*);

} // namespace th20
