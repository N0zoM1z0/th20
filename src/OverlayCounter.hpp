#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {
struct Vector3;

// REF-032: native Overlay constructs this 8-byte member at offset 0x38.
// Native reward accounting uses signed comparisons and modulo32 addition.
// The original Item spawn owner remains open; add_reward is an undefined
// production interface consumed by the complete Overlay forwarding wrapper.
struct OverlayCounter {
    std::int32_t current;
    std::int32_t threshold;

    OverlayCounter() noexcept;
    void add_reward(const Vector3*,std::int32_t,std::int32_t);
};

static_assert(sizeof(OverlayCounter) == 8);
static_assert(offsetof(OverlayCounter, current) == 0);
static_assert(offsetof(OverlayCounter, threshold) == 4);

} // namespace th20
