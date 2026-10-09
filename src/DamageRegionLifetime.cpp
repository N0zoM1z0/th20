#include "HitCtrlInf.hpp"

namespace th20 {
void DamageRegion::select_context(std::int32_t index) {
    value_bc=index;context=&session.context(value_bc);
}
void DamageRegion::retire() {
    if (!identifier.get()) return;
    const auto handle=identifier.get();
    auto* owner=context->hit_controller();
    owner->detach(this);
    flags.fields.active=0;
    identifier=0u;
    if (handle&0x01000000u) process_allocator->release_object(this);
}
}
