#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

// REF-032: native Overlay constructs this 8-byte member at offset 0x38.
// Names and signed types follow the reference; native arithmetic, signedness
// and the threshold's use remain unresolved. Only construction is accepted.
struct OverlayCounter {
    std::int32_t current;
    std::int32_t threshold;

    OverlayCounter() noexcept;
};

static_assert(sizeof(OverlayCounter) == 8);
static_assert(offsetof(OverlayCounter, current) == 0);
static_assert(offsetof(OverlayCounter, threshold) == 4);

} // namespace th20
