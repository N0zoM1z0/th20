#pragma once

#include <cstddef>
#include <cstdint>

namespace th20 {

// REF-032: four 8-byte markers per boss panel. Native 0x004B3BB0 reads
// fraction as a float. The second word's role and signedness are unresolved.
struct HudGauge {
    float fraction;
    std::uint32_t value_04;

    HudGauge();
};

static_assert(sizeof(HudGauge) == 8);
static_assert(offsetof(HudGauge, fraction) == 0);
static_assert(offsetof(HudGauge, value_04) == 4);

} // namespace th20
