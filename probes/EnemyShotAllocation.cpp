// Emit the standard allocation/control-block protocol on the actual owners.
// This translation unit owns no alternate implementation of the STL helpers.
#include "DebugAllocator.hpp"
#include "ShotMetadata.hpp"
#include <memory>

template std::shared_ptr<EtamaArgInf> std::allocate_shared<EtamaArgInf>(
    const DebugAllocator<EtamaArgInf>&);

template std::shared_ptr<EtamaArgInf> std::allocate_shared<EtamaArgInf>(
    const DebugAllocator<EtamaArgInf>&, EtamaArgInf&);
