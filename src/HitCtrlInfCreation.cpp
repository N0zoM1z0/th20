#include "HitCtrlInf.hpp"
#include "DiagnosticObjectFactories.hpp"

namespace th20 {
template HitCtrlInf* DiagnosticAllocator::allocate_object<HitCtrlInf>(const char*);
template DamageRegion* DiagnosticAllocator::allocate_object<DamageRegion>(const char*);

HitCtrlInf* create_hit_controller(std::int32_t index) {
    auto* owner=process_allocator->allocate_object<HitCtrlInf>(
        "D:\\cygwin\\home\\zun\\prog\\th20\\src\\game\\hit.cpp:73 HitCtrlInf");
    if (!owner) return nullptr;
    // The original error path releases the owned controller and clears
    // the by-value local allocation pointer before returning null.
    if (owner->initialize(index)) goto cleanup;
    return owner;
cleanup:
    if (owner) {
        process_allocator->release_object(owner);
        owner = nullptr;
    }
    return nullptr;
}
}
