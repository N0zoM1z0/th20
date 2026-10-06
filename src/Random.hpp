#pragma once

#include <cstdint>

namespace th20 {

// REF-001: independently checked at 0x00422CB0 and 0x004235F0.
// These are MSVC minstd_rand component equivalents, excluded from authored credit.
// The transition accepts the complete uint32_t domain, including zero.
std::uint32_t random_step(std::uint32_t state);

struct RandomState {
    std::uint32_t state;
    std::uint32_t next();
};

static_assert(sizeof(RandomState) == 4);

} // namespace th20
