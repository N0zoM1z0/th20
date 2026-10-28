// Entire original 67-byte native DamageHandle lookup by its game Hit controller.
// Preserve the raw four-byte storage and use a type-safe compiler intrinsic
// for C++20 bit_cast semantics; no alias-violating pointer cast or fake ABI.
#include "PlayerStorage.hpp"
#include "HitCtrlInf.hpp"
#include <type_traits>

namespace th20 {

static_assert(sizeof(DamageHandle) == sizeof(Identifier32));
static_assert(std::is_trivially_copyable_v<Identifier32>);

DamageRegion* DamageHandle::resolve() {
    auto* owner = hit_controller(0);
    // The native method copies the four-byte raw handle into an actual
    // Identifier32 value object before passing it to HitCtrlInf::find.
    // MSVC __builtin_bit_cast expresses the same defined bit-wise conversion
    // as std::bit_cast without an unobserved /Od library wrapper call.
    Identifier32 id = __builtin_bit_cast(Identifier32, value);
    auto* region = owner->find(id);
    if (!region) value = 0;
    return region;
}

} // namespace th20
